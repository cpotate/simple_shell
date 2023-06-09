#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* printf*/
#include <unistd.h> /* fork, execve*/
#include <stdlib.h> /* Library*/
#include <string.h> /* strtok*/
#include <stddef.h> /* types and macros*/
#include <errno.h> /* errno and perror */
#include <sys/types.h> /* type pid */
#include <sys/wait.h> /* wait */
#include <sys/stat.h> /* stat function */
#include <signal.h> /* signal management */
#include <fcntl.h> /* to open file*/


/************* STRUCTURES **************/

/**
 * struct info- struct for the program's data.
 * @program_name: the name of the executable.
 * @input_line: pointer to the input read for _getline.
 * @command_name: pointer to the first command.
 * @exec_counter: number of excecuted comands.
 * @file_descriptor: file descripton to the command input
 * @tokens: pointer to array of input in token form.
 * @env: copy of the environ.
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;


/************* MAIN FUNCTIONS *************/


/*========  shell.c  ========*/

/* Inicialize the struct with the info of the program */
void inicialize_data(data_of_program *data, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void sisifo(char *prompt, data_of_program *data);

/* Print the prompt in a new line */
void handle_ctrl_c(int opr, UNUSED);


/*========  _getline.c  ========*/

/* Read one line of the standar input*/
int _getline(data_of_program *data);

/* split the each line for the logical operators if it exist */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);


/*======== expansions.c ========*/

/* expand variables */
void expand_variables(data_of_program *data);

/* expand aliases */
void expand_alias(data_of_program *data);

/* append the string to the end of the buffer*/
int buffer_add(char *buffer, char *str_to_add);


/*======== str_tok.c ========*/

/* Separate the string in tokens using a designed delimiter */
void tokenize(data_of_program *data);

/* Creates a pointer to a part of a string */
char *_strtok(char *line, char *delim);


/*======== execute.c ========*/

/* Execute a command with its entire path */
int execute(data_of_program *data);


/*======== builtins_list.c ========*/

/* If match a builtin, executes it */
int builtins_list(data_of_program *data);


/*======== find_in_path.c ========*/

/* Creates an array of the path directories */
char **tokenize_path(data_of_program *data);

/* Search for program in path */
int find_program(data_of_program *data);


/************** HELPERS FOR MEMORY MANAGEMENT **************/


/*======== helpers_free.c ========*/

/* Frees the memory for directories */
void free_array_of_pointers(char **directories);

/* Free the fields needed each loop */
void free_recurrent_data(data_of_program *data);

/* Free all field of the data */
void free_all_data(data_of_program *data);


/************** BUILTINS **************/


/*======== builtins_more.c ========*/

/* Close the shell */
int builtin_exit(data_of_program *data);

/* Change the current directory */
int builtin_cd(data_of_program *data);

/* set the work directory */
int set_work_directory(data_of_program *data, char *new_dir);

/* show help information */
int builtin_help(data_of_program *data);

/* set, unset and show alias */
int builtin_alias(data_of_program *data);


/*======== builtins_env.c ========*/

/* Shows the environment where the shell runs */
int builtin_env(data_of_program *data);

/* create or override a variable of environment */
int builtin_set_env(data_of_program *data);

/* delete a variable of environment */
int builtin_unset_env(data_of_program *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== env_management.c ========*/

/* Gets the value of an environment variable */
char *env_get_key(char *name, data_of_program *data);

/* Overwrite the value of the environment variable */
int env_set_key(char *key, char *value, data_of_program *data);

/* Remove a key from the environment */
int env_remove_key(char *key, data_of_program *data);

/* prints current environ */
void print_environ(data_of_program *data);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* Prints a string in the standar output */
int _print(char *string);

/* Prints string in the standar error */
int _printe(char *string);

/* Prints string in standar error */
int _print_error(int errorcode, data_of_program *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== helpers_string.c ========*/

/* Counts number of characters in string */
int str_length(char *string);

/* Duplicates string */
char *str_duplicate(char *string);

/* Compare strings */
int str_compare(char *string1, char *string2, int number);

/* Conbine two strings */
char *str_concat(char *string1, char *string2);

/* Reverse string */
void str_reverse(char *string);


/*======== helpers_numbers.c ========*/

/* Change int to string */
void long_to_string(long number, char *string, int base);

/* convert string to number */
int _atoi(char *s);

/* count character in string */
int count_characters(char *string, char *character);


/*======== alias_management.c ========*/

/* print list */
int print_alias(data_of_program *data, char *alias);

/* get the name */
char *get_alias(data_of_program *data, char *alias);

/* set the name */
int set_alias(char *alias_string, data_of_program *data);

#endif
