PyCA – Python C extension Assistant
====================================

Generates Python C API code in order to aid in C extension development.

Copyright (c) 2009 Rasmus Andersson.
Licensed under MIT.

Commands
--------

mk
^^^^^^

usage: pyca mk func|meth|smeth SIGNATURE...

The ``mk`` command generates code for functions (``mk func``), methods (``mk meth``) and static methods  (``mk smeth``). A ``SIGNATURE`` looks like a regular Python *def* with the addition of *types*. The symbol used to express type are the same used for ``PyArg_Parse``. See http://docs.python.org/c-api/arg.html for a detailed overview.
