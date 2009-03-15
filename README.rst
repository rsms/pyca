PyCA -- Python C extension Assistant
====================================

Generates Python C API code in order to aid in C extension development.

Copyright (c) 2009 Rasmus Andersson.
Licensed under MIT.

Commands
--------

**General usage:**

::

  Usage: pyca [options] COMMAND [ARGS]

  Commands:
    help        Display help about a certain command or pyca itself.
    init        Create and initialize a new project.
    show        Generate and display Python C code.

  Options:
    --version    show program's version number and exit
    -h, --help   show this help message and exit
    -q, --quiet  Don't print status messages to stdout


init
^^^^^^

::

  Usage: pyca init [options] <name> [<path>]

  Create and initialize a new project.

  If <path> is not specified it defaults to './' + <name>

  Options:
    -h, --help            show this help message and exit
    --dry-run             Simulate but don't actually do anything.
    -t <title>, --title=<title>
                          Human-readable title of project. Defaults to <name>.
    -a <author>, --author=<author>
                          Author of the project. If not set, author will be
                          guessed.
    -u <url>, --url=<url>
                          URL pointing to more information.
    -y <year>, --year=<year>
                          Copyright year. Defaults to 2009
    -l <license>, --license=<license>
                          Software license. Defaults to 'mit' (for a list of
                          available licenses, see contents of directory
                          <pycadir>/skeleton/licenses)


show
^^^^^^

::

  Usage: pyca show <signature>
         pyca show <type> <signature> [<type> <signature> ...]

  Generate and display Python C code.

  Examples:

    Show a function:
      pyca show 'mymod.myfunc(i size, s message = "hello")'

    Show a method and a function:
      pyca show meth 'mymod.MyClass.mymeth(i size, s message = "hello")'\
                func 'mymod.myfunc(i size, s message = "hello")'
  
    Show a static method:
      pyca show smeth 'mymod.MyClass.mymeth(i size, s message = "hello")'

  Type hinting is (optionally) performed by adding a PyArg_Parse symbol in front
  of arguments.

  Options:
    -h, --help  show this help message and exit



Examples
-----------------

Creating a new project
^^^^^^^^^^^^^^^^^^^^^^

::

  $ ./pyca init fluffy_hamster
  Creating new project 'fluffy_hamster' in '/Users/rasmus/src/pyca/fluffy_hamster'
    PROJECT_AUTHOR         => 'Rasmus Andersson <rasmus@hidden.email>'
    PROJECT_AUTHOR_EMAIL   => 'rasmus@hidden.email'
    PROJECT_AUTHOR_NAME    => 'Rasmus Andersson'
    PROJECT_MODULE         => 'fluffy_hamster'
    PROJECT_MODULE_UPPER   => 'FLUFFY_HAMSTER'
    PROJECT_TITLE          => 'fluffy_hamster'
    PROJECT_URL            => ''
    PROJECT_YEAR           => '2009'
  dir     fluffy_hamster
  cpy     fluffy_hamster/.gitignore
  cpy     fluffy_hamster/CHANGELOG.rst
  dir     fluffy_hamster/docs
  dir     fluffy_hamster/docs/source
  dir     fluffy_hamster/docs/source/_static
  cpy     fluffy_hamster/docs/source/_static/info.png
  cpy     fluffy_hamster/docs/source/_static/jump.png
  cpy     fluffy_hamster/docs/source/_static/screen.css
  dir     fluffy_hamster/docs/source/_templates
  sub 2   fluffy_hamster/docs/source/_templates/layout.html
  sub 4   fluffy_hamster/docs/source/conf.py
  sub 1   fluffy_hamster/docs/source/index.rst
  dir     fluffy_hamster/docs/source/library
  sub 1   fluffy_hamster/docs/source/library/index.rst
  sub 3   fluffy_hamster/docs/source/library/fluffy_hamster.rst
  dir     fluffy_hamster/lib
  dir     fluffy_hamster/lib/fluffy_hamster
  sub 3   fluffy_hamster/lib/fluffy_hamster/__init__.py
  cpy     fluffy_hamster/lib/fluffy_hamster/release.py
  dir     fluffy_hamster/lib/fluffy_hamster/test
  sub 2   fluffy_hamster/lib/fluffy_hamster/test/__init__.py
  cpy     fluffy_hamster/MANIFEST.in
  sub 1   fluffy_hamster/README.rst
  sub 10  fluffy_hamster/setup.py
  dir     fluffy_hamster/src
  sub 19  fluffy_hamster/src/__init__.c
  sub 3   fluffy_hamster/src/__init__.h
  sub 4   fluffy_hamster/src/_macros.h
  cpy     fluffy_hamster/src/util.c
  sub 2   fluffy_hamster/src/util.h
  sub 1   fluffy_hamster/test-working
  sub 2   fluffy_hamster/LICENSE

  $ cd fluffy_hamster/
  $ ./test-working
  ./test-working: Building and testing with Python 2.4

  ----------------------------------------------------------------------
  Ran 0 tests in 0.000s

  OK
  ./test-working: Building and testing with Python 2.5

  ----------------------------------------------------------------------
  Ran 0 tests in 0.000s

  OK
  ./test-working: Building and testing with Python 2.6

  ----------------------------------------------------------------------
  Ran 0 tests in 0.000s

  OK
  ./test-working: Building and testing with Python 3.0

  ----------------------------------------------------------------------
  Ran 0 tests in 0.000s

  OK



Show generated code
^^^^^^^^^^^^^^^^^^^

Note that you do not need to have any existing project in order to use the
``show`` command, as is simply parses signatures and generates Python C code
just-in-time.

::
  
  $ pyca show meth 'mymod.SomeClass.echo(s msg, i times=3, s# prefix = "")'
  > docs/source/mymod.SomeClass.echo.rst:
      .. method:: echo(msg, times=3, prefix="")

  > src/mymod_SomeClass.h:
    /**
     * @param const char *msg
     * @param int times = 3
     * @param const char *prefix = ""
     */
    PyObject *mymod_SomeClass_echo(PyObject *self, PyObject *args, PyObject *kwargs);

  > src/mymod_SomeClass.c:
    /**
     * mymod.SomeClass.echo(s msg, i times=3, s# prefix = "")
     */
    PyObject *mymod_SomeClass_echo(PyObject *self, PyObject *args, PyObject *kwargs) {
      const char *msg = NULL;
      int times = 3;
      const char *prefix = "";
      int prefix_length = 0;
      static char *kwlist[] = {"msg", "times", "prefix", NULL};
    
      /* Parse arguments */
      if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s|is#:echo", kwlist,
        &msg, &times, &prefix, &prefix_length))
      {
        return NULL;
      }
    
      /* TODO: implementation */
      PyErr_SetString(PyExc_NotImplementedError, "mymod.SomeClass.echo");
      return NULL;
    }

