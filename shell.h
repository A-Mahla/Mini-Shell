/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:32:02 by meudier           #+#    #+#             */
/*   Updated: 2022/07/21 12:38:01 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <limits.h>

//extern int	g_sigint_code;

enum e_type
{
	PIPE,
	REDIR_OUT,
	REDIR_IN,
	REDIR_OUT_APPEND,
	HERDOC,
	WRD,
	EMPTY
};

typedef struct s_lexer
{
	char			*data;
	int				type;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_in
{
	int			stdin;
	struct s_in	*next;
}	t_in;

typedef struct s_pipe_info
{
	int					in;
	int					out;
	int					**pipes;
	int					num_of_process;
	struct s_pipe_info	*next;
}	t_pipe_info;

typedef struct s_parser
{
	char			*cmd;
	char			**arg;
	char			**env;
	t_in			*stdin;
	int				stdout;
	int				is_clear_parser;
	struct s_parser	*prev;
	struct s_parser	*next;
}	t_parser;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_vars
{
	t_env		*envl;
	t_env		*var;
	t_parser	*lst_parser;
	t_lexer		*lst_lexer;
	t_pipe_info	*pipe_info;
	int			exit_code;
}	t_vars;

//				utils
char			*cpy(const char *src);
char			*cpy_2(const char *src, int size);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_bs(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);
char			*ft_strdup(const char *s1);
int				ft_strlen(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strjoin_eq(char const *s1, char const *s2);
int				ft_isalnum(int c);
unsigned long	ft_ltoi(const char *str);
int				ft_isdigit(int c);
char			*ft_check_zero(char *str);
int				ft_isalpha(int c);
int				check_export(char *str);
int				check_unset(char *str);
int				get_size_nb(int nb);
char			*ft_itoa(int n);
void			error_malloc(t_vars *vars);
void			error_malloc_lexer(t_lexer *lst_lexer, t_vars *vars);
void			error_malloc_pipe(t_lexer *lst_lexer, t_vars *vars, \
int i, int **pipes);
void			error_malloc_parser(t_vars *vars);
void			error_parser(t_vars *vars);
char			**lst_to_strs(t_env *env);
void			trim_line(char *line);

//				cd.c
int				cd(t_parser *parser, int *built, t_env *envl);

//				pwd.c
int				pwd(t_parser *parser, int *built);

//				env.c
int				env(t_parser *parser, int *built, t_env *envl);

//				env_2.c
void			lst_clear_envl(t_env *envl);
t_env			*get_env(char **env, t_vars *vars);
void			push_env(t_env **lst, char *str, t_vars *vars);

//				export.c
int				export(t_parser *parser, int *built, t_vars *vars);

//				unset.c
int				unset(t_parser *parser, int *built, t_vars *vars);

//				echo.c
int				echo(t_parser *parser, int *built);

//				exit.c
int				ft_exit(t_vars *vars, int *built, int pipe);

//				exit_error.c
void			error_exit(t_parser *parser);

//				close.c
void			close_std(t_parser *parser);
void			close_pipes(t_pipe_info *pipe_info);

//				lexer.c
t_lexer			*lexer(char *line, t_vars *vars);
char			*get_var(char *str, t_vars *vars, int size);
int				get_num_of_arg(t_lexer *lexer);

//				lexer_2.c
int				check_nb_quote(char *str);
int				check_word(char *str);

//				lexer_push_clear.c
void			push_lexer(t_lexer **lst, char *word, int TYPE, t_vars *vars);
void			lst_clear_lexer(t_lexer *lexer);

//				parser.c
void			init_parser(t_parser *new);
int				create_new(t_parser **new, t_lexer **lexer, \
t_parser *parser, t_vars *vars);
int				push_parser(t_parser **parser, t_lexer **lexer, \
t_pipe_info *pipe_info, t_vars *vars);
int				parser(t_parser **parser, t_lexer *lexer, \
t_pipe_info *pipe_info, t_vars *vars);

//				parser2.c
void			push_in(t_in **stdin, int data, t_vars *vars);
char			*get_arg(char *str, t_vars *vars);
void			lst_clear_parser(t_parser *parser);
void			push_in_front(t_in **stdin, int data, t_vars *vars);
void			init_parser(t_parser *new);

//				pipe.c
int				get_num_of_process(t_lexer *lexer);
int				**get_pipes(t_lexer *lexer, int *num_of_process, t_vars *vars);
int				is_not_a_pipe(int fd, int **pipes, int num_of_process);

//				get_cmdpath.c
int				get_cmdpath(t_parser *parser, char **cmd_path, \
int i, t_env *envl);

//				execute.c
int				execute(t_parser *parser, t_pipe_info *pipe_info, t_vars *vars);

//				execute_2
void			return_value_child(int *pids, t_vars *vars);
int				is_not_slashbar(char *cmd);
int				no_leaks(int *pids, char *cmd_path, t_vars *vars, int built);
void			dup_and_close(t_parser *parser, int built, int *pids, \
t_vars *vars);

//				dup.c
int				dup_fd(t_parser *parser);

//				ft_split_lexer.c
char			**clear_tab(char **tab);
char			**ft_split_lexer(char const *s);
int				is_meta(char c, char *meta);

//				ft_split_lexer_2.c
int				ft_get_size_2(int j, int *i, const char *s, char *meta);
int				ft_get_size_1(char const *s);
int				ft_get_word_2(int j, int *len, char *s, char *meta);
char			*ft_get_word_1(int *index, char *s);

//				write_error.c
void			write_error(char *cmd);
void			write_is_a_directory(char *cmd, t_vars *vars, int *built);
void			clear_err_pars(t_lexer *lexer, t_parser *parser, \
t_pipe_info *pipe_info);

//				parser_action.c
int				redir_in(t_parser **new, t_lexer **lexer, t_vars *vars);
void			wrd(t_parser **new, t_lexer *lexer, t_pipe_info *pipe_info, \
t_vars *vars);
int				redir_out(t_parser **new, t_lexer **lexer, \
t_pipe_info *pipe_info, t_vars *vars);
int				redir_out_append(t_parser **new, t_lexer **lexer, \
t_pipe_info *pipe_info, t_vars *vars);

//				parser_action_2.c
int				heredoc(t_parser **new, t_lexer **lexer, t_vars *vars, \
t_parser *parser);

//				sig.c
void			sig_init(void);

//				builtin.c
int				builtin(t_parser *parser, int *built, t_vars *vars, int pipe);

//				ft_expand.c
void			ft_expand(char **words, t_vars *vars, t_lexer *lst);

//				ft_expand_2.c
int				is_expand(char *str);
void			get_expand(char **words, t_vars *vars, int size, t_lexer *lst);

//				ft_expand_3.c
char			*get_word_expand_2(char *word, int *i, t_vars *vars);

//				gestion_variables.c
int				is_already_a_var(t_vars *vars, char *str);
int				is_already_a_env(t_vars *vars, char *str);
void			push_var_to_env(char *str, t_vars *vars, t_env **begin_var, \
t_env **begin_env);
void			remove_if(char *str, t_env **begin, int (*cmp)(const char *, \
const char *));
void			remove_if_2(t_env **begin);

#endif
