#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *		with line numbers, starting at 0
 *
 * @info: Structure containing potential arguments. Used to maintain
 *		constant function prototype.
 *
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - unsets an alias by deleting the corresponding node from the
 *			alias list
 *
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p = _strchr(str, '=');
	if (!p)
		return (1);

	char c = *p;
		*p = '\0';
		int ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets an alias to a string by adding it to the alias list.
 *
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p = _strchr(str, '=');
	if (!p)
		return (1);

	if (!*++p)
	return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string in the format alias='value'
 *
 * @node: the alias noe
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	if (node)
	{
		char *p = _strchr(node->str, '=');
		_printf("%.*s='", (int)(p - node->str), node->str);
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 *
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int i;
	char *p;
	list_t *node;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
