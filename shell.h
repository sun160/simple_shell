#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct sendInfo - struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@ln_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fileName: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct sendInfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int ln_count;
	int err_num;
	int linecount_flag;
	char *fileName;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_s;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - struct
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_s *);
} builtin_table;


/* hsh.c */
int hsh(info_s *, char **);
int find_builtin(info_s *);
void find_sh(info_s *);
void fork_sh(info_s *);

int is_excutable(info_s *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_s *, char *, char *);


void _sputs(char *);
int _sputchar(char);
int _sput_fd(char c, int fd);
int _sputsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
int ptrFree(void **);
void strFree(char **);
void *_realloc(void *, unsigned int, unsigned int);


/* int ptrFree(void **); */

int interactive(info_s *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

int _eAtoi(char *);
void print_error(info_s *, char *);
int print_decimal(int, int);
char *convert_int(long int, int, int);
void ignore_comment(char *);

int _shellExit(info_s *);
int shellCd(info_s *);
int shellHelp(info_s *);

int histo(info_s *);
int shellAlias(info_s *);

ssize_t getInput(info_s *);
int _getline(info_s *, char **, size_t *);
void signtHandler(int);

void clear(info_s *);
void init_info(info_s *, char **);
void free_info(info_s *, int);

char *envInfo(info_s *, const char *);
int shellEnv(info_s *);
int initenv(info_s *);
int removeEnv(info_s *);
int fillEnvList(info_s *);

char **get_envon(info_s *);
int _removeEnv(info_s *, char *);
int init_env(info_s *, char *, char *);

char *getHistoFile(info_s *info);
int writeHisto(info_s *info);
int read_history(info_s *info);
int creatHistoList(info_s *info, char *buf, int linecount);
int assignNumHistory(info_s *info);

list_t *addStartingNode(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

size_t list_length(const list_t *);
char **listStrings(list_t *);
size_t printList(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

int isChainDel(info_s *, char *, size_t *);
void checkChainDelm(info_s *, char *, size_t *, size_t, size_t);
int change_alias(info_s *);
int changeVars(info_s *);
int replace_string(char **, char *);

#endif

