#include <Python.h>
#include <stdlib.h>
#include <stdio.h>

void print_python_list(PyObject *p);
void print_python_bytes(PyObject *p);

/**
 * print_python_list - Function for printing info of a python list
 * @p: pointer to the python list
*/
void print_python_list(PyObject *p)
{
	PyObject *item = NULL;
	PyListObject *list = NULL;
	Py_ssize_t length, i;
	const char *type = NULL;

	if (!p || !PyList_Check(p))
		return;
	length = PyObject_Length(p);
	list = (PyListObject *)p;
	printf("[*] Python list info\n"
			"[*] Size of the Python List = %ld\n"
			"[*] Allocated = %ld\n", length, list->allocated);
	for (i = 0; i < length; i++)
	{
		item = list->ob_item[i];
		type = item->ob_type->tp_name;
		printf("Element %ld: %s\n", i, type);
	}
}

/**
 * print_python_bytes - Prints the info about the bytes
 * @p: pointer to an objet
*/
void print_python_bytes(PyObject *p)
{
	Py_ssize_t size, i;
	PyBytesObject *byte;

	printf("[.] bytes object info\n");
	if (!p || !PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	byte = (PyBytesObject *)p;
	size = ((PyVarObject *)p)->ob_size;
	printf("  size: %ld\n", size);
	printf("  trying string: %s\n", byte->ob_sval);
	size = size < 9 ? size + 1 : 10;
	printf("  first %ld bytes: ", size);
	for (i = 0; i < size; i++)
		printf("%02hhx%c", byte->ob_sval[i], i + 1 == size ? '\n' : ' ');
}

/**
 * print_python_float - prints a python float object
 * @p: pointer to python float object
 */
void print_python_float(PyObject *p)
{
	char *str;
	PyFloatObject *floater;

	floater = (PyFloatObject *)p;
	setbuf(stdout, NULL);
	printf("[.] float object info\n");
	if (!p || !PyFloat_Check(p))
	{
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}
	str = PyOS_double_to_string(floater->ob_fval, 'g', 16, 0, NULL);
	printf("  value: %s%s\n", str, strchr(str, '.') ? "" : ".0");
}
