#include "minishell.h"

extern int	g_status;

static char	*find_command(char **env_path, char *cmd, char *full_path)
{
	char	*temp;
	int		i;
	char 	*full_path;

	i = -1;
	full_path = NULL; 
	while (env_path && env_path[++i])
	{
		if (!env_path || !env_path[i])
		{	
			free(full_path);
			return (NULL);
		}
		//free(full_path); //free를 했는데 여기다가 뭘 넣는다?
		temp = ft_strjoin(env_path[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
	}
	// if (!env_path || !env_path[i])
	// {
	// 	free(full_path);
	// 	return (NULL);
	// }// while 문 안에 들어가야 하는 것이 아닌가
	return (full_path);
}

static DIR	*cmd_checks(t_shell *shell, t_list *cmd, char ***s, char *path)
{
	t_mini	*n;
	DIR		*dir;

	dir = NULL;
	n = (t_mini *)cmd->content;
	if (n && n->full_cmd)
		dir = opendir(*n->full_cmd);
	if (n && n->full_cmd && ft_strchr(*n->full_cmd, '/') && !dir)
	{
		*s = ft_split(*n->full_cmd, '/');
		n->full_path = ft_strdup(*n->full_cmd);
		free(n->full_cmd[0]); //왜 0번째만 free시키는 가
		n->full_cmd[0] = ft_strdup(s[0][ft_matrixlen(*s) - 1]);
		//free를 시켰는데 또 안에 값을 집어넣음
	}
	else if (!find_builtin(n) && n && n->full_cmd && !dir)
	{
		path = ft_getenv("PATH", shell->envp, 4);
		*s = ft_split(path, ':');
		free(path);
		n->full_path = find_command(*s, *n->full_cmd, n->full_path);
		if (!n->full_path || !n->full_cmd[0] || !n->full_cmd[0][0])
			ft_perror(NCMD, *n->full_cmd, 127);
	}
	return (dir);
}

void	get_cmd(t_shell *shell, t_list *cmd, char **s, char *path)
{
	t_mini	*n;
	DIR		*dir;

	n = (t_mini *)cmd->content;
	dir = cmd_checks(shell, cmd, &s, path);
	if (!find_builtin(n) && n && n->full_cmd && dir)
		ft_perror(IS_DIR, *n->full_cmd, 126);
	else if (!find_builtin(n) && n && n->full_path && \
		access(n->full_path, F_OK) == -1)
		ft_perror(NDIR, n->full_path, 127);
	else if (!find_builtin(n) && n && n->full_path && \
		access(n->full_path, X_OK) == -1)
		ft_perror(NPERM, n->full_path, 126);
	if (dir)
		closedir(dir);
	ft_free_matrix(&s);
}

void	*exec_cmd(t_shell *shell, t_list *cmd)
{
	int		fd[2];

	get_cmd(shell, cmd, NULL, NULL);
	if (pipe(fd) == -1)
		return (ft_perror(PIPERR, NULL, 1));
	if (!check_to_fork(shell, cmd, fd))
		return (NULL);
	close(fd[WRITE_END]);
	if (cmd->next && !((t_mini *)cmd->next->content)->infile)
		((t_mini *)cmd->next->content)->infile = fd[READ_END];
	else
		close(fd[READ_END]);
	if (((t_mini *)cmd->content)->infile > 2)
		close(((t_mini *)cmd->content)->infile);
	if (((t_mini *)cmd->content)->outfile > 2)
		close(((t_mini *)cmd->content)->outfile);
	return (NULL);
}

int	builtin(t_shell *shell, t_list *cmd, int *is_exit, int n)
{
	char	**a;

	while (cmd)
	{
		a = ((t_mini *)cmd->content)->full_cmd;
		n = 0;
		if (a)
			n = ft_strlen(*a);
		if (a && !ft_strncmp(*a, "exit", n) && n == 4)
			g_status = ft_exit(cmd, is_exit);
		else if (!cmd->next && a && !ft_strncmp(*a, "cd", n) && n == 2)
			g_status = ft_cd(shell);
		else if (!cmd->next && a && !ft_strncmp(*a, "export", n) && n == 6)
			g_status = ft_export(shell);
		else if (!cmd->next && a && !ft_strncmp(*a, "unset", n) && n == 5)
			g_status = ft_unset(shell);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			exec_cmd(shell, cmd);
		}
		cmd = cmd->next;
	}
	return (g_status);
}