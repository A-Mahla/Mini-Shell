/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:32:02 by meudier           #+#    #+#             */
/*   Updated: 2022/07/11 12:17:11 by ammah            ###   ########.fr       */
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
	t_env	*envl;
	t_env	*var;
}	t_vars;

//			utils
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_bs(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *s1);
int			ft_strlen(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strjoin_eq(char const *s1, char const *s2);
int			ft_isalnum(int c);

//			close.c
void		close_std(t_parser *parser);
void		close_pipes(t_pipe_info *pipe_info);

//			lexer.c
t_lexer		*lexer(char *line, t_vars *vars);
char		*get_var(char *str, t_vars *vars, int size);
int			get_num_of_arg(t_lexer *lexer);
void		push_lexer(t_lexer **lst, char *word, int TYPE/*, t_vars *vars*/);
void		lst_clear_lexer(t_lexer *lexer);

//			parser.c
void		init_parser(t_parser *new);
void		create_new(t_parser **new, t_lexer **lexer, t_pipe_info *pipe_info);
void		push_parser(t_parser **parser, t_lexer **lexer, \
t_pipe_info *pipe_info);
t_parser	*parser(t_lexer *lexer, t_pipe_info *pipe_info);

//			parser2.c
void		push_in(t_in **stdin, int data);
char		*get_arg(char *str);
void		push_in(t_in **stdin, int data);
void		lst_clear_parser(t_parser *parser);

//			pipe.c
int			get_num_of_process(t_lexer *lexer);
int			**get_pipes(t_lexer *lexer, int *num_of_process);
int			is_not_a_pipe(int fd, int **pipes, int num_of_process);

//			cpy.c
char		*cpy(const char *src);

//			get_cmdpath.c
int			get_cmdpath(t_parser *parser, char **cmd_path, int i, t_env *envl);

//			execute.c
int			execute(t_parser *parser, t_pipe_info *pipe_info, t_vars *vars);

//			dup.c
int			dup_fd(t_parser *parser);

//			ft_split_lexer.c
char		**clear_tab(char **tab);
char		**ft_split_lexer(char const *s);

//			ft_split_lexer_2.c
int			is_meta(char c, char *meta);
int			ft_get_size_2(int j, int *i, const char *s, char *meta);
int			ft_get_size_1(char const *s);
int			ft_get_word_2(int j, int *len, char *s, char *meta);
char		*ft_get_word_1(int *index, char *s);

//			write_error.c
void		write_error(char *cmd);

//			parser_action.c
void		redir_in(t_parser **new, t_lexer **lexer);
void		wrd(t_parser **new, t_lexer **lexer, t_pipe_info *pipe_info);
void		redir_out(t_parser **new, t_lexer **lexer, \
t_pipe_info *pipe_info);
void		redir_out_append(t_parser **new, t_lexer **lexer, \
t_pipe_info *pipe_info);

//			env.c
void		lst_clear_envl(t_env *envl);
t_env		*get_env(char **env);
void		push_env(t_env **lst, char *str);

//			sig.c
void		sig_init(void);

//			builtin.c
int			builtin(t_parser *parser, int *built, t_vars *vars);

//			ft_expand.c
void		ft_expand(char **words, t_vars *vars);

//			ft_expand_2.c
int			is_expand(char *str);
void		get_expand(char **words, t_vars *vars, int size);

//gestion_variables.c
int 		is_already_a_var(t_vars *vars, char *str);
int 		is_already_a_env(t_vars *vars, char *str);
void		push_var_to_env(char *str, t_vars *vars, t_env **begin_var, t_env **begin_env);
void		remove_if(char *str, t_env **begin, int (*cmp)(const char *, const char *));

#endif
