#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <unistd.h>

# define READ_END 0
# define WRITE_END 1

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_shell
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}			t_shell;

enum	e_ft_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_mini;

void	handle_sigint(int sig);
//signal.c

char	*ft_getshell(t_shell shell);
//shell.c

void	*check_args(char *out, t_shell *p);
//parse_args.c

char	*get_here_str(char *str[2], size_t len, char *limit, char *warn);
int		get_here_doc(char *str[2], char *aux[2]);
//heredoc.c

int		get_fd(int oldfd, char *path, int flags[2]);
t_mini	*get_outfile1(t_mini *node, char **args, int *i);
t_mini	*get_outfile2(t_mini *node, char **args, int *i);
t_mini	*get_infile1(t_mini *node, char **args, int *i);
t_mini	*get_infile2(t_mini *node, char **args, int *i);

void	get_cmd(t_shell *shell, t_list *cmd, char **s, char *path);
void	*exec_cmd(t_shell *shell, t_list *cmd);
//get_cmd.c

char	*ft_strtrim_all(char const *s1, int squote, int dquote);
//ft_strtrim_all.c

char	**ft_cmdtrim(char const *s, char *set);
//ft_cmdtrim.c

char	**ft_cmdsubsplit(char const *s, char *set);
//ft_cmdsubsplit.c

t_list	*make_nodes(char **args, int i);
//fill_node.c

char	*expand_path(char *str, int i, int quotes[2], char *var);
char	*expand_vars(char *str, int i, int quotes[2], t_shell *shell);
//expand.c

void	child_builtin(t_shell *shell, t_mini *n, int l, t_list *cmd);
void	*child_process(t_shell *shell, t_list *cmd, int fd[2]);
void	exec_fork(t_shell *shell, t_list *cmd, int fd[2]);
void	*check_to_fork(t_shell *shell, t_list *cmd, int fd[2]);
//exec.c

void	*ft_perror(int err_type, char *param, int err);
int		ft_atoi2(const char *nptr, long *nbr);
int		ft_exit(t_list *cmd, int *is_exit);
void	cd_error(char **str[2]);
void	free_content(void *content);
//error.c

//minishell_envp.c
char	*ft_getenv(char *var, char **envp, int n);
char	**ft_setenv(char *var, char *value, char **envp, int n);

int		ft_export(t_shell *shell);
int		ft_unset(t_shell *shell);
//env.c
//custom_cmd.c

int		builtin(t_shell *shell, t_list *cmd, int *is_exit, int n);
int		find_builtin(t_mini *n);
int		ft_cd(t_shell *p);
int		ft_pwd(void);
int		ft_echo(t_list *cmd);
//builtins.c

//var_in_envp파일이 추가
int		var_in_envp(char *argv, char **envp, int ij[2]);
char	**split_all(char **args, t_shell *shell);

//ftshell_libft_utils4.c
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_putchar_fd(char c, int fd);
int		ft_nbrlen(long n, int base);
void	*ft_memset(void *s, int c, size_t n);

//ftshell_libft_utils3.c
int		ft_isspace(char c);
int		ft_isdigit(int c);
int		ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);

//ftshell_libft_utils5,6.c //각각 따로 넣어줌
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);

//ftshell_libft_list_utils.c 
void	ft_lstadd_back(t_list **lst, t_list *newnode);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void*));
int		ft_lstsize(t_list *lst);

//ftshell_matrix_utils.c
void	ft_free_matrix(char ***m);
int		ft_matrixlen(char **m);
char	**ft_matrix_replace_in(char ***big, char **small, int n);
char	**ft_extend_matrix(char **in, char *newstr);
char	**ft_dup_matrix(char **m);

//ftshell_libft_utils2.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
int		ft_putendl_fd(char *s, int fd);

//ftshell_libft_utils1.c
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s1);
int		ft_atoi(const char *nptr);

//ftshell_utils.c
int		ft_strchr_i(const char *s, int c);
int		ft_strchars_i(const char *s, char *set);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_countchar(char *s, char c);
int		ft_putmatrix_fd(char **m, int nl, int fd);

#endif
