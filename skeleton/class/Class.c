#include "${CLASS_NAME}.h"

/* Private --------------------------------------------------------------- */

/* Define any internal private code here, or just remove this section. */


/* Public ---------------------------------------------------------------- */


static void ${PROJECT_MODULE}_${CLASS_NAME}_dealloc(${PROJECT_MODULE}_${CLASS_NAME} *self) {
  log_trace("ENTER");
  /* free any instance members here, which you allocated in ${PROJECT_MODULE}_${CLASS_NAME}_new */
  PyObject_Del(self);
}


static PyObject *${PROJECT_MODULE}_${CLASS_NAME}_new(PyTypeObject *type, PyObject *args, PyObject *keywds) {
  log_trace("ENTER");
  ${PROJECT_MODULE}_${CLASS_NAME} *self;
  
  if (!(self = (${PROJECT_MODULE}_${CLASS_NAME} *)type->tp_alloc(type, 0))) {
    PyErr_SetString(PyExc_MemoryError, "Cannot alloc ${PROJECT_MODULE}_${CLASS_NAME} instance");
    return NULL;
  }
  
  /* allocate any instance members here */
  
  return (PyObject *)self;
}

/*
  Define your methods and getters/setters here.
  You can ask pyca to generate methods. See 'pyca help show' for more info.
*/


/* Type ------------------------------------------------------------------ */

/* Methods */
static PyMethodDef ${PROJECT_MODULE}_${CLASS_NAME}_methods[] = {
  /* This is how a method registry look like:
  {"method_name", (PyCFunctionWithKeywords)${PROJECT_MODULE}_${CLASS_NAME}_method_name, METH_VARARGS | METH_KEYWORDS,
    "Do something awesome."}, */
  {NULL, NULL, 0, NULL} ///< sentinel
};


PyTypeObject ${PROJECT_MODULE}_${CLASS_NAME}Type = {
  #if (PY_VERSION_HEX < 0x03000000)
    PyObject_HEAD_INIT(NULL)
    0,                  /*ob_size*/
  #else
    PyVarObject_HEAD_INIT(NULL, 0)
  #endif
  "${PROJECT_MODULE}.${CLASS_NAME}",                                 /* tp_name */
  sizeof(${PROJECT_MODULE}_${CLASS_NAME}),                           /* tp_basicsize */
  0,                                        /* tp_itemsize */
  (destructor)${PROJECT_MODULE}_${CLASS_NAME}_dealloc,               /* tp_dealloc */
  0,                                        /* tp_print */
  0,                                        /* tp_getattr */
  0,                                        /* tp_setattr */
  0,                                        /* tp_compare */
  0,                                        /* tp_repr */
  0,                                        /* tp_as_number */
  0,                                        /* tp_as_sequence */
  0,                                        /* tp_as_mapping */
  ,                                         /* tp_hash  */
  0,                                        /* tp_call */
  0,                                        /* tp_str */
  0,                                        /* tp_getattro */
  0,                                        /* tp_setattro */
  0,                                        /* tp_as_buffer */
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
  NULL, /* The class' __doc__ string  */    /* tp_doc */
  0,                                        /* tp_traverse */
  0,                                        /* tp_clear */
  0,                                        /* tp_richcompare */
  0,                                        /* tp_weaklistoffset */
  (getiterfunc)0,                           /* tp_iter */
  (iternextfunc)0,                          /* tp_iternext */
  ${PROJECT_MODULE}_${CLASS_NAME}_methods,                           /* tp_methods */
  0,                                        /* tp_members */
  0,                                        /* tp_getset */
  0,                                        /* tp_base */
  0,                                        /* tp_dict */
  0,                                        /* tp_descr_get */
  0,                                        /* tp_descr_set */
  0,                                        /* tp_dictoffset */
  0,                                        /* tp_init */
  0,                                        /* tp_alloc */
  ${PROJECT_MODULE}_${CLASS_NAME}_new,                               /* tp_new */
};

int ${PROJECT_MODULE}_${CLASS_NAME}_register(PyObject *module) {
  log_trace("ENTER");
  if (PyType_Ready(&${PROJECT_MODULE}_${CLASS_NAME}Type) == 0)
    return PyModule_AddObject(module, "${CLASS_NAME}", (PyObject *)&${PROJECT_MODULE}_${CLASS_NAME}Type);
  return -1;
}
