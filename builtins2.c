#include "minishell.h"

extern int	g_status;

void	child_builtin(t_shell *prompt, t_mini *n, int l, t_list *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!find_builtin(n) && n->full_cmd)
		execve(n->full_path, n->full_cmd, prompt->envp);
	else if (n->full_cmd && !ft_strncmp(*n->full_cmd, "pwd", l) \
		&& l == 3)
		g_status = ft_pwd();
	else if (find_builtin(n) && n->full_cmd && \ //이게 뭐임?
		!ft_strncmp(*n->full_cmd, "echo", l) && l == 4)
		g_status = ft_echo(cmd);
	else if (find_builtin(n) && n->full_cmd && \
		!ft_strncmp(*n->full_cmd, "env", l) && l == 3)
	{
		ft_putmatrix_fd(prompt->envp, 1, 1);
		g_status = 0;
	}
}

void	*child_redir(t_list *cmd, int fd[2])
{
	t_mini	*node;

	node = (t_mini *)cmd->content;
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			return (ft_perror(DUPERR, NULL, 1));
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			return (ft_perror(DUPERR, NULL, 1));
		close(node->outfile);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (ft_perror(DUPERR, NULL, 1));
	close(fd[WRITE_END]);
	return ("");
}

void	*child_process(t_shell *prompt, t_list *cmd, int fd[2])
{
	t_mini	*n;
	int		l;

	n = (t_mini *)cmd->content;
	l = 0;
	if (n->full_cmd)
		l = ft_strlen(*n->full_cmd);
	child_redir(cmd, fd);
	close(fd[READ_END]);
	child_builtin(prompt, n, l, cmd);
	ft_lstclear(&prompt->cmds, free_content);
	exit(g_status);
}

void	exec_fork(t_shell *prompt, t_list *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		ft_perror(FORKERR, NULL, 1);
	}
	else if (!pid)
		child_process(prompt, cmd, fd);
}

void	*check_to_fork(t_shell *prompt, t_list *cmd, int fd[2])
{
	t_mini	*n;
	DIR		*dir;

	n = (t_mini *)cmd->content;
	dir = NULL;
	if (n->full_cmd)
		dir = opendir(*n->full_cmd);
	if (n->infile == -1 || n->outfile == -1)
		return (0);
	if ((n->full_path && access(n->full_path, X_OK) == 0) || find_builtin(n))
		exec_fork(prompt, cmd, fd);
	else if (!find_builtin(n) && ((n->full_path && \
		!access(n->full_path, F_OK)) || dir))
		g_status = 126;
	else if (!find_builtin(n) && n->full_cmd)
		g_status = 127;
	if (dir)
		closedir(dir);
	return ("");
}
