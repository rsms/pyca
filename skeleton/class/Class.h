#ifndef ${PROJECT_MODULE_UPPER}_${CLASS_NAME_UPPER}_H
#define ${PROJECT_MODULE_UPPER}_${CLASS_NAME_UPPER}_H

#include "__init__.h"

typedef struct {
  PyObject_HEAD
  /* Define any instance storage */
} tc_TDB;

extern PyTypeObject ${PROJECT_MODULE}_${CLASS_NAME}Type;

int ${PROJECT_MODULE}_${CLASS_NAME}_register(PyObject *module);

#define ${PROJECT_MODULE}_${CLASS_NAME}_CheckExact(op) (Py_TYPE(op) == &${PROJECT_MODULE}_${CLASS_NAME}Type)
#define ${PROJECT_MODULE}_${CLASS_NAME}_Check(op) \
  ((Py_TYPE(op) == &${PROJECT_MODULE}_${CLASS_NAME}Type) || PyObject_TypeCheck((PyObject *)(op), &${PROJECT_MODULE}_${CLASS_NAME}Type))

#endif
