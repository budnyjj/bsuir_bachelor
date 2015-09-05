#include <python2.7/Python.h>

extern double c_f(double c);
extern double f_c(double f);

static PyObject *
py_ext_c2f(PyObject *self, PyObject *args)
{
  double c;
  
  if (!PyArg_ParseTuple(args, "d", &c))
    return NULL;

  return Py_BuildValue("d", c_f(c));
}

static PyObject *
py_ext_f2c(PyObject *self, PyObject *args)
{
  double f;
  
  if (!PyArg_ParseTuple(args, "d", &f))
    return NULL;
  return Py_BuildValue("d", f_c(f));
}


static PyMethodDef ModuleMethods[] = {
  {
    "c2f", py_ext_c2f, METH_VARARGS, "Convert Celsius to Fahrengheit"
  },
  {
    "f2c", py_ext_f2c, METH_VARARGS, "Convert Fahrengheit to Celsius"
  },
  {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
inittemperature(void)
{
  Py_InitModule("temperature", ModuleMethods);
}
