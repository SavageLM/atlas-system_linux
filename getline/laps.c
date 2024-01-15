#include "laps.h"

/**
 * race_state- Function to track cars and laps
 * @id: array of I.Ds for cars
 * @size: size of ID array
*/

void race_state(int *id, size_t size)
{
	cars_t *cars;

	if (!id || size == 0)
	{
		printf("Entering free_cars");
		free_cars(&cars);
	}

	printf("Entering ID check loop");
	for (size_t i = 0; i < size; i++)
	{
		if (!check_ids(id[i], &cars))
		{
			printf("entering new_car");
			new_car(id[i], &cars);
			printf("Car %d joinded the race", id[i]);
		}
	}
	printf("Entering print_state");
	print_state(cars);
}

/**
 * free_cars - Function to free the list of cars
 * @cars: List of cars
*/

void free_cars(cars_t **cars)
{
	cars_t *tmp = *cars;

	if (!*cars)
		return;

	while (*cars)
	{
		tmp = (*cars)->next;
		free(*cars);
		*cars = tmp;
	}
	free(*cars);
	*cars = NULL;
}

/**
 * check_ids - Function to check if id is in list
 * @id: id to check for
 * @cars: List of Cars
 * Return: Returns 1 if id is present, 0 if not
*/

int check_ids(int id, cars_t **cars)
{
	cars_t *tmp = *cars;

	for (; tmp->next != NULL; tmp = tmp->next)
	{
		if (id == tmp->id)
		{
			tmp->laps++;
			return (1);
		}
	}

	return (0);
}

/**
 * new_car - Function to insert a new car into list in order
 * @id: ID of the new car
 * @cars: List of cars in race
*/

void new_car(int id, cars_t **cars)
{
	cars_t *newcar, *prev, *tmp = *cars;

	newcar = malloc(sizeof(cars_t));
	if (!newcar)
	{
		free(newcar);
		return;
	}
	newcar->id = id;
	newcar->laps = 0;

	if (tmp == NULL)
	{
		*cars = newcar;
		newcar->next = NULL;
	}
	else if (tmp->id > id)
	{
		*cars = newcar;
		newcar->next = tmp;
	}

	while (tmp->next != NULL)
	{
		if (tmp->id < id)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		else if (tmp->id > id)
		{
			prev->next = newcar;
			newcar->next = tmp;
			return;
		}
	}

	tmp->next = newcar;
	newcar->next = NULL;
}

/**
 * print_state - Function that prints list
 * @cars: List of Cars in race
*/

void print_state(cars_t *cars)
{
	cars_t *tmp = cars;
	int car_id = 0, laps = 0;

	printf("Race state:");

	for (; tmp->next != NULL; tmp = tmp->next)
	{
		car_id = tmp->id;
		laps = tmp->laps;
		printf("Car %d [%d]", car_id, laps);
	}
}
