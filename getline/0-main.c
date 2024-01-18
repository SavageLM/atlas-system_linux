#include "laps.h"

/**
 * main - entry point.
 *
 * Return: always 0.
 */
int main()
{

    int ids[2] = {1, 2};

    race_state(ids, 2);
    race_state(ids, 2);
    race_state(ids, 2);
    race_state(ids, 2);
    race_state(NULL, 0);
    return (0);
}