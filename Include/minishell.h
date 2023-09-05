/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:32:11 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/08/29 17:30:45 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdio.h>
# include <readline/history.h>
# include "../Lib/includes/lib.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

extern struct s_all	g_all;

typedef enum s_token
{
	CMD,
	ARG,
	GR,
	GR_DBE,
	LESS,
	LESS_DBE,
	FD,
	LIMITOR,
	PIPE,
}			t_token;

typedef struct s_ListNode
{
	char				*data;
	struct s_ListNode	*next;
}						t_ListNode;

typedef struct s_node
{
	int				in;
	int				out;
	char			*here_doc;
	int				here_doc_fd;
	int				index;
	int				has_cmd;
	int				has_out;
	int				in_fail;
	int				out_fail;
	struct s_node	*next;
}			t_node;

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}				t_env;

typedef struct s_stringdata
{
	int		len;
	int		i;
	int		j;
	int		is_escaped;
}			t_stringdata;

typedef struct s_lexer
{
	char			*word;
	t_token			token;
	int				i;
	int				nb_words;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}			t_lexer;

typedef struct s_quote
{
	int	is_quote;
	int	is_dquote;
	int	sq_first;
	int	found;
}				t_quote;

typedef struct s_expand
{
	char	*str;
	int		len;
	int		found;
	int		need_expand;
	int		quote;
	int		i;
}				t_expand;

typedef struct s_export
{
	char			*value;
	struct s_export	*next;
}			t_export;

typedef struct s_exec
{
	int				can_run;
	char			*hd;
	int				dupin;
	int				is_here_doc;
	char			**env;
	int				err;
	t_env			*env_lst;
	int				nb_cmd;
	int				nb_node;
	char			*error;
	int				ret;
	int				previous_fd;
	char			*var;
	t_node			*head_node_lst;
	t_lexer			*head_lexer_lst;
	t_export		*export_lst;
	t_export		*head_export_lst;
	t_env			*head_env_lst;
	struct s_node	*node;
	struct s_exec	*next;
	struct s_exec	*prev;
}				t_exec;

typedef struct s_memory
{
	void			*add;
	struct s_memory	*next;
}			t_memory;

typedef struct s_all
{
	t_exec		*utils;
	t_memory	*d_mem;
}				t_all;

typedef struct s_data
{
	char		*test;
	int			squote;
	int			dquote;
	int			ac;
	int			nb_mots;
	char		**av;
	char		**env;
	char		*line;
	int			index;
	char		**allcommand;
	char		**envpaths;
	char		*finalpath;
	t_lexer		*lexer_list;
	t_quote		*quote;
	t_ListNode	*envp;

}			t_data;

////////////////////////LEXER_LIST////////////////////////////////////
void		ft_lexer(t_data *data);
int			ft_write_fd(char *str, int fd);
int			get_word_in_list(char *str, int i, t_lexer **lexer_list,
				t_lexer *tmp);
void		get_token_in_node(t_lexer **lexer_list, t_lexer *tmp);
void		get_data_in_node(t_lexer **lexer_list);
void		ft_add_back_lexer(t_lexer **lexer_list, char *str);
int			ft_nombre_mots(char *str);
int			is_white_space(char c);
t_token		which_redir(t_lexer *tmp);
int			check_redir_error(t_lexer *tmp);
t_lexer		*ft_lexer_new(char *str);
void		truc(t_lexer *tmp, t_lexer *first);
void		print_lex(t_data *data);

///////////////////////PARSING/////////////////////////////////////////
int			ft_parser(t_data *data);
int			ft_cloporte(t_data *data);
int			base_check(char *str);
int			check_redir(char *str);
int			ft_check_quotes(char *str, t_data *data);
int			ft_arrow(t_data *data);
int			ft_arrow2(t_data *data);
int			pipe_parse(t_data *data);
int			ft_chevron(char *str, char c);
int			pipe_parse2(t_data *data);
size_t		ft_strlen3(char const *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			is_space(char *str, char c);
void		rm_para_quote(t_data *data);
char		*parse_para(char *tmp);
char		*parse_quote(char *tmp);
char		*parse_quote2(char *tmp);

///////////////////////INIT_ENV////////////////////////////////////////
t_exec		*init_env(char **env);
t_env		*ft_get_env_lst(char **env);
void		ft_envlst_add_back(t_env *lst, t_env *new);
t_env		*ft_new_env(char *env);
int			ft_env_size(char **env);
t_env		*ft_get_env_lst_i(t_env *final);

///////////////////////SIGNALS///////////////////////////////////////////
void		handle_sig(void);
void		handle_process_signal(void);
void		ctrl_c_handler_here_doc(int sig);
void		ctrl_c_handler(int sig);
void		sigquit_process(int sig);

///////////////////////INIT_EXEC/////////////////////////////////////////
void		ft_init_exec(t_data *data);
void		get_all_node(t_node *node, t_lexer *lexer_lst, t_exec *utils);
void		get_out(t_node *node, t_lexer *lexer_lst);
void		get_in(t_node *node, t_lexer *lexer_lst);
void		get_in_hd(t_node *node, t_lexer *lex_lst);
void		get_in_fail(t_node *node, t_lexer *lexer_lst);
void		get_out_append(t_node *node, t_lexer *lex_lst, int *has_out);
t_node		*ft_add_back_node(t_node *node_lst, t_node *new);
int			nb_node(t_lexer *lexer_list);
int			nb_cmd(t_lexer *lexer_list);
int			has_cmd(t_lexer *lexer_lst);
void		ft_here_doc(t_node *node, t_lexer *lexer_lst);
void		ft_read_input(t_node *node, t_lexer *lexer_lst);
char		*ft_strdup(char *src);
t_export	*get_export_list(t_export *export_lst);
t_export	*ft_new_export_node(t_export *new);
void		sort_export_lst(t_export **head_export);

///////////////////////////BUILT IN///////////////////////////////////////
int			get_pwd(char *tab);
int			procc_in_echo(char **tab, int i, int j);
void		simulate_echo(t_lexer *lexer_lst);
void		simu_echo(char **tab, int i);
int			ft_strcmp(char *s1, char *s2);
char		**ft_split(char const *s, char c);
char		**ft_malloc_word(char **tab, char *s, char c);
char		*ft_put_word_in_malloc(char *s, char c, char *tab);
int			ft_word_count(char *s, char c);
void		freetab(char **tab, int k);
void		get_cd(t_lexer *lexer_lst);
int			verif_pwd_export(char *str);
int			verif_oldpwd_export(char *str);
int			verif_oldpwd(char *str);
int			verif_pwd(char *str);
char		*var_exist(char *str);
int			change_directory(char *dir);
size_t		ft_strlen_eguale(char *str);
char		*ft_strjoin_2(char *s1, char *s2);
char		*case_egale(char *str);
char		*ft_strjoin4(char *s1, char *s2);
int			ft_strlen4(char *s);
char		*ft_strcpy(char *dest, const char *src);
char		*add_quotes_string(char *str);
int			unset_things(t_lexer *lexer_lst);
char		*unset_var(t_lexer *lexer_lst);
void		remove_node_export(char *var);
void		remove_node(char *var);
int			export_things(t_lexer *lexer_lst);
void		export_quotes(t_export *data);
int			check_case(char *str);
void		print_export(t_export *export_lst);
void		export_remaining(t_lexer *tmp);
int			check_parsing_export(char *str);
void		process_word(t_exec **utils, t_lexer *tmp);
void		remove_double_quotes(char *str);
void		remove_single_quotes(char *str);
int			verif_var_exist_export(t_exec *utils, char *str);
int			verif_var_exist(t_exec *utils, char *str);
int			verif_equal(char *str, char c);
void		lst_add_back(t_exec *utils, char *str);
void		lst_add_back_export(t_export **head, char *str);
t_export	*create_node_str_export(char *str);
int			is_number(char c);
int			check_parsing_2(char *str);
void		ft_exit(t_lexer *lex, int *fd);
void		display_pwd(void);
void		display_pwd_error(void);
void		display_env(void);
int			check_case_2(char *str);
void		remove_export_node(t_export *current, t_export *prev);
void		remove_env_node(t_env *current, t_env *prev);
int			wrong_cd(t_lexer *lexer_lst);
void		process_echo_2(char **tab, int i);
void		simulate_echo_3(char **tab);
int			cd_2(t_lexer *lexer_lst, char *path, char *old, int *i);
void		write_echo(char **tab, int i);
void		exec_chemin(t_lexer *lexer);

///////////////////////////EXEC///////////////////////////////////////////
void		ft_bzero(pid_t *pid, int nb_node);
void		init_var(int *fd, int *y, int *wstatus);
void		ft_prep_exec(t_data *data);
int			start_exec(int *fd, pid_t *pid, t_lexer *lex_lst, int *count);
pid_t		ft_child(t_lexer *lexer_list, int *fd, int count, t_exec utils);
char		**get_arg(t_lexer *lexer_list);
int			check_path_exec(t_lexer *lexer, t_exec utils);
char		*get_cmd_path(char *cmd, t_env *env_lst);
char		**get_path(t_env *env_lst);
void		handle_out(t_exec utils, int *fd, int count);
void		handle_in(t_exec utils, int count);
int			ft_nb_arg(t_lexer *lexer_list);
t_lexer		*go_next_cmd(t_lexer *lexer_list);
int			verif_var_exist_export_2(t_exec *utils, char *str);
int			is_built_in(t_lexer *lexer_lst);
void		ft_exec_single_built_in(t_lexer *lexer_lst, int *fd);
int			close_fd(void);
int			close_pipe(int *fd);
int			slashinlex(t_lexer *lexer);
int			ft_exit_child(t_exec *utils, int *fd);
void		child_of_chill(t_lexer *lexer_list,
				int *fd, int count, t_exec utils);
////////////////expand
int			ft_isdigit(char c);
int			single_quote_expantion(char *word, t_expand *exp);
int			word_not_found(char *w, t_quote *state);
int			put_error_code(t_expand *exp);
int			search_word(char *w, t_expand *exp, char *nv, t_quote *state);
int			basic_expantion(char *w, t_expand *exp, char **nv, t_quote *state);
int			sign(char c, t_quote *st);
int			need_expand_or_rm_quote(t_lexer **to_check, t_quote *state,
				t_expand *exp);
void		expand(t_quote *state, char **env, t_lexer *tmp);
void		state_at_zero(t_quote *state);
int			search_in_env_len(char *w, char **nv, t_quote *st, int *len);
void		type_expantion(t_lexer **expnd, t_quote *st, char **nv,
				t_expand *exp);
void		len_for_expand(t_lexer **exp, t_quote *st, char **env,
				int *len);
char		*malloc_for_expand(t_lexer **exp, t_quote *st, char **env);
void		manage_expantion(t_lexer **expnd, t_quote *st, char **nv,
				t_expand *exp);
void		add_back_new_node(char **insert, t_lexer *back, t_lexer *next,
				int len);
void		replace_old_node(t_lexer **old_node, char **to_insert);
char		*remove_quote(char *old, t_quote *state);
int			on_word(char *word, int index, t_quote *state);
char		*copy_word(char *word, t_quote *state, char *str);
char		*malloc_word(char *word, t_quote *state);
int			len_d_array(char *word, t_quote *state);
char		**split_word(char *word, t_quote *state);
int			next_squote(char *cmd);
int			next_dquote(char *cmd);
int			next_squote_len(char *cmd, int i, t_quote *state);
int			next_dquote_len(char *cmd, int i, t_quote *state);
void		quoting_state(char c, t_quote *state);
int			sep_word(char c);
int			end_word(char *cmd, int i, t_quote *state);
int			len_darr(char **arr);
int			put_error_code(t_expand *exp);
char		*malloc_word_without_quote(int len, char *old, t_quote *state);
char		*put_word_without_quote(char *old, char *nw, t_quote *state);

/////////////////FREE
int			ft_exit_child(t_exec *utils, int *fd);
void		memory_check(void *add);
void		*ft_malloc(size_t size);
void		ft_free(void *add);
void		ft_free_all(void);
int			ft_len_nb(long n);
char		*ft_is_neg(char *res, long n, int i);
char		*ft_itoa(int n);
void		prompt_loop(char *tmp, t_data data, char **env);
int			dollar_at_end(char *str);
int			ft_tiret(char *str);
int			chevron_pipe(char *str);
void		rm_para_quote2(t_data *data);
void		sigint_process(int signo);
void		rm_pwd(void);
void		find_old_pwd(t_env	*env);
int			change_directory2(t_env *tmp);
int			verif_home(char *str);
int			change_directory3(t_env *tmp);
char		*get_old_pwd(t_env	*tmp);
char		*get_pwd_env(t_env	*tmp);
int			change_directory4(t_env *tmp);
void		malloc_single_node(char *str, t_env **env);
int			count_quote(char *str);
void		get_words(t_lexer *lexer_lst, char **tab, int *i);
void		process_echo(char **tab, int i);
void		exit_all(void);
void		ft_lexer4(char *str, int *i, int *j, t_quote *state);

#endif
