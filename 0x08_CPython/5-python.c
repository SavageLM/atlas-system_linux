#include <Python.h>
#include <stdlib.h>
#include <stdio.h>

void print_python_int(PyObject *p);

/**
 * print_python_int - Function to print python integers
 * @p: pointer to python object to print
*/
void print_python_int(PyObject *p)
{
	PyLongObject *num;
	ssize_t size, i;
	int neg, int_shift;
	unsigned long total, current;

	num = (PyLongObject *)p;
	if (!p || !PyLong_Check(p))
	{
		printf("Invalid Int Object\n");
		return;
	}
	size = ((PyVarObject *)p)->ob_size;
	if (size < 0)
		neg = 1;
	size = neg ? -size : size;
	if (size > 3 || (size == 3 && num->ob_digit[2] > 0xf))
	{
		printf("C unsigned long int overflow\n");
		return;
	}
	for (i = 0; i < size; i++)
	{
		int_shift = PyLong_SHIFT * i;
		current = ((unsigned long)num->ob_digit[i]) * (1UL << (int_shift));
		total += current;
	}
	if (neg)
		printf("-");
	printf("%lu\n", total);
}
