PyCA -- Python C extension Assistant
====================================

Generates Python C API code in order to aid in C extension development.

Copyright (c) 2009 Rasmus Andersson.
Licensed under MIT.

Commands
--------

mk
^^^^^^

::

  usage: pyca mk func|meth|smeth SIGNATURE...

The ``mk`` command generates code for functions (``mk func``), methods (``mk meth``) and static methods  (``mk smeth``). A ``SIGNATURE`` looks like a regular Python *def* with the addition of *types*. The symbol used to express type are the same used for ``PyArg_Parse``. See http://docs.python.org/c-api/arg.html for a detailed overview.

**Example:**

::
  
  $ ./pyca mk meth 'mymod.SomeClass.echo(s msg, i times=3, s# prefix = "")'
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
      PyErr_SetString(PyExc_NotImplementedError, "helloworld.echo");
      return NULL;
    }
