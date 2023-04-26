#include "shell.h"

/**
 * _myexit - exits the shell
 * @info - structure containing potential argument.
 * Return - exit a given status
 *		(0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exit_status;

	if (info->argv[1])
	{
		exit_status = _erratoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
		else
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);

		return (-2);
	}
	info->err_num = -1;

	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential argument.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *dir, buffer[1024];
	int chdir_ret;

	if (getcwd(buffer, 1024) == NULL)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(buffer);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
		else
			chdir_ret = chdir(info->argv[1]);
	}
	return (0);
}

/**
 * _myhelp - displays information about built-in commands
 * info - structure containing potential argument.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	(void)info; /* Silence unused parameter warning */
	_puts("The following built-in commands are supported:\n");
	_puts("cd - Change the current directory\n");
	_puts("exit - Exit the shell\n");
	_puts("help - Display information about built-in commands\n");
	return (0);
}
