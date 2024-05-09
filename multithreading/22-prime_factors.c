#include "multithreading.h"

/**
 * create_task - creates task
 * @entry_func: pointer to entry function of the task
 * @param: the parameter that will later be passed
 *
 * Return: task just created
 */
task_t *create_task(task_entry_t entry_func, void *param)
{
	task_t *new_task;

	new_task = calloc(1, sizeof(task_t));

	new_task->entry = entry_func;
	new_task->param = param;
	new_task->status = 0;

	pthread_mutex_init(&new_task->lock, NULL);

	return (new_task);
}

/**
 * destroy_task - destroys task
 * @task: pointer to task to be destroyed
 */
void destroy_task(task_t *task)
{
	if (task->result)
	{
		list_destroy((list_t *) task->result, free);
		free((list_t *) task->result);
	}
	free(task);
}

/**
 * exec_tasks - executes tasks
 * @tasks: list of tasks
 */
void *exec_tasks(list_t const *tasks)
{
	node_t *current_node = NULL;
	task_t *new_task = NULL;

	int id = 0;

	if (!tasks)
		pthread_exit(NULL);

	current_node = tasks->head;

	while (current_node)
	{
		new_task = current_node->content;
		if (!pthread_mutex_trylock(&new_task->lock))
		{
			current_node = current_node->next;
			id++;
			continue;
		}

		if ((new_task->status) == PENDING)
		{
			new_task->status = STARTED;
			tprintf("[%02d] Started\n", id);
			new_task->result = new_task->entry(new_task->param);
			if (new_task->result == NULL)
			{
				new_task->status = FAILURE;
				tprintf("[%02d] Failure\n", id);
			}
			else
			{
				new_task->status = SUCCESS;
				tprintf("[%02d] Success\n", id);
			}
		}
		current_node = current_node->next;
		id++;
	}
	return (NULL);
}
