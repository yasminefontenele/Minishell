/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:48:13 by yasmine           #+#    #+#             */
/*   Updated: 2024/09/05 19:45:13 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define GREEN      "\033[0;32m"
# define RED        "\033[0;31m"
# define YELLOW	    "\033[0;33m"
# define MAGENTA	"\033[0;35m"
# define CYAN       "\033[0;36m"
# define RST_COLOR  "\033[0m"

# define STDIN  0
# define STDOUT 1
# define STDERR 2

# define MAX_PATH 4096

# define CMD 3
# define ARG 4      
# define REDIR_OUT_SUBS 5//Output redirection, e.g. '>' | subscribe
# define REDIR_OUT_ATTACH 6//Output redirection, e.g. '>>' | attach
# define REDIR_IN 7//Input redirection, e.g. '<'
# define REDIR_DOC 8//Redirection with special handling that does not apply to simple redirection
# define FILE 9//File or directory name (ex.: 'file.txt')
# define ERROR 10//Error in the sintaxe
# define PROTECTED_DOLLAR 11//protection of strings of environment variables or file names(ex.: $HOME)
# define PROTECTED_QUOTE 12// protection of strings or arguments that are enclosed in quotes(ex.:"Hello World")
# define SKIPED	13//Skip current token and next token(ex.: '&&' ou '||')
# define HERE_DOC 14//Input redirection, ex.: '<<'
# define HERE_DOC_END 15//ffinal of heredoc

/*
* ' ' Everything inside single quotes is treated as literal text, i.e. no special characters are interpreted.
* e.g. echo 'Hello, $USER', prints 'Hello, $USER'
* " " Allow a string to contain spaces and preserve most special characters except $, `, and \.
* e.g. echo "Hello, $USER", prints 'Hello, yasmine'
*/
typedef struct s_quote
{
	bool				single_quote;
	bool				double_quote;
}						t_quote;

typedef struct s_env
{
	char				**env;
	char				**sorted;
	int					exit_status;
}						t_env;

typedef struct s_tokens
{
	int					nbr;
	int					pipe;
	int					*type;//categorizar o token (ex.:CMD, ARG, ...)
	char				**tokens;
}						t_tokens;


typedef struct s_separator
{
	int					*separator_index;
	int					nbr_separator;
	char				**content;
}						t_separator;


/*
										***** TO DO ******
example of the t_execution structure:
command: echo "hello" > output.txt

nb_pipelines: 1 (since there are no pipelines)
args_type: (indicating that echo is a CMD and "hello" is an ARG)
files_type: (indicating that there is a redirection >)
file_dscp: [3] (indicating the file descriptor for output.txt)
args: ["echo", "hello"]
files: ["output.txt"]
exec_path: "/bin/echo"
command: "echo"

typedef struct s_execution
{
	int					nbr_pipelines;
	int					*args_type;//(ex.:CMD, ARG, ...)
	int					*files_type;//(ex.:REDIR_OUT_SUBS, REDIR_OUT_ATTACH, ...)
	int					*file_dscp;//file descriptor
	char				**args;//(ex.:'ls -l /home', the array will be ["ls", "-l", "/home"].)
	char				**files;//(ex.: 'ls -l > file.txt', o array files conteria ["file.txt"].)
	char				*command;
}						t_execution;
*/

typedef struct s_data
{
	int					oldlen;
	int					newlen;
	int					presence;
}						t_data;

t_env					g_env;

//BUILTINS
int		builtin_cd(char **path);
void	no_arg_cd(char *oldpwd);
int		builtin_echo(char **args, int *type);
int		contains_equal(char *str);
int		builtin_env(void);
int     builtin_exit(char **args, int child_process, int count);
void    print_export(void);
char    *extract_var(char *arg);
char    *extract_value(char *arg);
int     export(char **args);
int     builtin_export(char **args, int *type);
int		builtin_pwd(int fd);
int		find_env_index(char *var);
int		find_env_index(char *var);
int		builtin_unset(char **args);

//UTILS
int     absolute_value(int nb);
int     count(char **str);
int		max_of(int i, int j);
int		ft_error(char *description, int exit_code);
void    free_str_array(char **arr);
void    error_file(char *file);
int		error_redirection(int file_type);
void	error_no_such_file(char *command);
void    error_command(char *command);
char    ft_stringjoin(char *str, char c);
char	*extract_substring(char const *s, unsigned int start, size_t len);
void    join_backslash(char **path);
char	*format_var(char *var, char *value);
void	new_var(char *var, char *value);
void	update_env(char *var, char *value);
void	append_to_env(char *variable, char *value, int size);
char    *set_dollar(char *str, int i);
int     len_dollar(char *str, int i);
void    dup_array(void);
void    sort_array(void);
void    env_init(char **env);
int     count_backslash(char *line, int i);
int     valid_backslash(char **tokens);
void	free_tokens(t_tokens token);
void	free_dollar(char **original, char **replacement);
int		syntax_redirections(t_tokens *tokens);
int		syntax_grammar(char **commands, t_tokens *tokens);
char	*is_builtin(char *command);
int		count_separator(char *line, char separator);
int		str_isdigit(char *str);
t_quote	quote_value(char type_quote, t_quote status_quote);
t_separator position_separator(char *line, char separator);
char **separator_split(char *line, int *separatorI, int nbr_separator);
char    **token_split(char *line, int nbr);
int get_token_type(char *content, int len);
void set_token_aux(int i, int *cmd, int *type);
void set_tokens_type(int *type, char **content);
int set_token(t_tokens token);
int skip_sapace(char *line, int i);
int	get_end(char *line, int i);
int count_token(char *line);
int is_empty(char *str);
int is_protected(int type);
int is_cmd(int type);
int is_arg(int type);
int is_redirection(int type);
void env_update(char *env, char *new_value);
void replace_value(int i, char *new_value, size_t len, char **arr);
char	*assemble_argument(char **args, int *token_class, int i);
int get_next_positive(char **args, int *token_class, int i);
char **join_args(char **args, int *token_class);
char **arg_add(char *arg, char **arr);
void	print_invalid_identifier_error(char **args);
int	is_invalid_identifier(char *arg);

//PARSING
t_quote		quote_init(void);
char    	*find_env_value(char *str, int i);
void    	process_pipeline(char *line);
void    	process_command_line(char *line);
void    	dollar_replace(char **token, int i);
char    	dollar_spaces_split(char **old, int i);
void    	arg_type(t_tokens *token, int oldsize, int newsize, int i);
int			dollar_aux_config(t_tokens *token, int *i, t_data *data);
t_tokens    dollar_config(t_tokens *token);
int 		dollar_presence(char *str);
char		*process_quotes(char *str);
char		quotes_expand(char *content, int i);
t_tokens	process_quotes_tokens(t_tokens tokens);
void		exec_process_quotes(t_tokens *tokens);//FINISH!!
int			type_of_separator(int type_of, char **token);
void		filler_stokens(char **cmds, t_tokens **token, int nbr);
int			token_dollar_end(char *str, int i);
int			token_word_end(char *str, int i);
int			token_quotes_end(char *str, int i);
int			token_redir_end(char *str, int i);
char		*parse_next_token(char *line, int reset);


#endif