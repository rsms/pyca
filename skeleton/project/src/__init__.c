#include "__init__.h"

PyObject *${PROJECT_MODULE}_module;


/*
 * Module functions
 */
static PyMethodDef ${PROJECT_MODULE}_functions[] = {
  {NULL, NULL}
};


/*
 * Module structure (Only used in Python >=3.0)
 */
#if (PY_VERSION_HEX >= 0x03000000)
  static struct PyModuleDef ${PROJECT_MODULE}_module_t = {
    PyModuleDef_HEAD_INIT,
    "_${PROJECT_MODULE}",   /* Name of module */
    NULL,    /* module documentation, may be NULL */
    -1,      /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
    ${PROJECT_MODULE}_functions,
    NULL,   /* Reload */
    NULL,   /* Traverse */
    NULL,   /* Clear */
    NULL    /* Free */
  };
#endif


/*
 * Module initialization
 */
#if (PY_VERSION_HEX < 0x03000000)
DL_EXPORT(void) init_${PROJECT_MODULE}(void)
#else
PyMODINIT_FUNC  PyInit__${PROJECT_MODULE}(void)
#endif
{
  /* Create module */
  #if (PY_VERSION_HEX < 0x03000000)
    ${PROJECT_MODULE}_module = Py_InitModule("_${PROJECT_MODULE}", ${PROJECT_MODULE}_functions);
  #else
    ${PROJECT_MODULE}_module = PyModule_Create(&${PROJECT_MODULE}_module_t);
  #endif
  if (${PROJECT_MODULE}_module == NULL)
    goto exit;
  
  /* Create exceptions here if needed */
  
  /* Register types */
  #define R(name, okstmt) \
    if (name(${PROJECT_MODULE}_module) okstmt) { \
      log_error("sub-component initializer '" #name "' failed"); \
      goto exit; \
    }
  /* Example: R(tc_SomeClass_register, != 0) */
  #undef R
  
  /* Register int constants */
  #define ADD_INT(NAME) PyModule_AddIntConstant(${PROJECT_MODULE}_module, #NAME, NAME)
  /* Example: ADD_INT(TCESUCCESS); */
  #undef ADD_INT
  /* end adding constants */

exit:
  if (PyErr_Occurred()) {
    PyErr_Print();
    PyErr_SetString(PyExc_ImportError, "can't initialize module _${PROJECT_MODULE}");
    Py_XDECREF(${PROJECT_MODULE}_module);
    ${PROJECT_MODULE}_module = NULL;
  }
  
  #if (PY_VERSION_HEX < 0x03000000)
    return;
  #else
    return ${PROJECT_MODULE}_module;
  #endif
}
