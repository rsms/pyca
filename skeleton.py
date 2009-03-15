# encoding: utf-8
'''Use trees of files and directories as templates.

Copyright (c) 2008-2009 Rasmus Andersson


'''
import sys, os, shutil, re


REPLACE_PLACEHOLDER_TPL = '${%s}'


if sys.version_info[0] >= 2 and sys.version_info[1] >= 6:
  relpath = os.path.relpath
else:
  def relpath(path, start=os.path.curdir):
    if not path:
      raise ValueError("no path specified")
    start_list = os.path.abspath(start).split(os.path.sep)
    path_list = os.path.abspath(path).split(os.path.sep)
    i = len(os.path.commonprefix([start_list, path_list]))
    rel_list = [os.path.pardir] * (len(start_list)-i) + path_list[i:]
    if not rel_list:
      return os.path.curdir
    return os.path.join(*rel_list)


def copy_tree(srcdir,
              dstdir,
              subs      = {},
              sub_re    = None,
              symlinks  = False,
              maxdepth  = 10,
              event_cb  = None,
              dry_run   = False,
              ignore_re = None,
              path_subs = {},
              dstroot   = None):
  
  if maxdepth < 1:
    raise Exception('max directory depth reached')
  
  if isinstance(sub_re, basestring):
    sub_re = re.compile(sub_re)
  elif sub_re is None:
    sub_re = re.compile(r'.+')
  
  if isinstance(ignore_re, basestring):
    ignore_re = re.compile(ignore_re)
  elif ignore_re is None:
    ignore_re = re.compile(r'.+/(\.DS_Store$|\._.*)')
  
  if not callable(event_cb):
    event_cb = lambda ev,src,dst,*va: None
  
  dstdir = dstdir.rstrip('/')
  if dstroot is None:
    dstroot = dstdir
  
  def dstpathsub(path):
    rpath = path[len(dstroot)+1:]
    try:
      return os.path.join(dstroot, path_subs[rpath])
    except KeyError:
      pass
    return path
  
  dstdir = dstpathsub(dstdir)
  
  #log.debug('copying directory %r to %r', srcdir, dstdir)
  if ignore_re.match(dstdir):
    event_cb('ign', srcdir, dstdir)
    return {}
  
  event_cb('dir', srcdir, dstdir)
  paths_copied = {srcdir: dstdir}
  
  if not dry_run:
    os.makedirs(dstdir)
  
  for fn in os.listdir(srcdir):
    srcpath = os.path.join(srcdir, fn)
    dstpath = dstpathsub(os.path.join(dstdir, fn))
    if ignore_re.match(dstpath):
      event_cb('ign', srcpath, dstpath)
      continue
    if os.path.islink(srcpath):
      if symlinks:
        if not dry_run:
          copy_symlink(srcpath, dstpath)
        paths_copied[srcpath] = dstpath
        event_cb('cpy', srcpath, dstpath)
    elif os.path.isfile(srcpath):
      if sub_re.match(dstpath):
        copy_template_file(srcpath, dstpath, subs, dry_run, event_cb)
      else:
        if not dry_run:
          copy_file(srcpath, dstpath)
        event_cb('cpy', srcpath, dstpath)
      paths_copied[srcpath] = dstpath
    elif os.path.isdir(srcpath):
      paths = copy_tree(srcpath, dstpath, subs, sub_re, symlinks, maxdepth-1, 
                        event_cb, dry_run, ignore_re, path_subs, dstroot)
      paths_copied.update(paths)
    #else:
    #log.warn('unknown directory entry: %r', srcpath)
  
  return paths_copied


def copy_symlink(src, dst):
  #log.debug('copying symlink %r to %r', src, dst)
  os.symlink(os.readlink(src), dst)


def copy_file(src, dst):
  #log.debug('copying file %r to %r', src, dst)
  # Copy both data and mode
  shutil.copyfile(src, dst)
  shutil.copymode(src, dst)


def copy_template_file(src, dst, subs, dry_run, event_cb):
  #log.debug('copying and rendering template %r to %r with env %r', src, dst, env)
  fsrc = None
  fdst = None
  indices = []
  try:
    fsrc = open(src, 'rb')
    if not dry_run:
      fdst = open(dst, 'wb')
    buf = fsrc.read()
    buf, indices = multisub(buf, subs, REPLACE_PLACEHOLDER_TPL)
    if not dry_run:
      fdst.write(buf)
  finally:
    if fdst:
      fdst.close()
    if fsrc:
      fsrc.close()
  if not dry_run:
    shutil.copymode(src, dst)
  if event_cb:
    event_cb('sub', src, dst, indices)


def multisub(src, subs, keytpl=None):
  '''String substitution by indexing, avoiding recursive replacement.
  '''
  # build index
  index = {}
  subsk = {}
  for k,v in subs.items():
    if keytpl:
      k = keytpl % k
    p = 0
    while 1:
      p = src.find(k, p)
      if p == -1:
        break
      index[p] = k
      subsk[k] = v
      p += len(k)
  
  indices = sorted(index.keys())
  dst = src
  
  if indices:
    dst = ''
    srccur = 0
    for p in indices:
      k = index[p]
      dst += src[srccur:p]
      dst += subsk[k]
      srccur = p+len(k)
    dst += src[srccur:]
  
  return dst, indices

