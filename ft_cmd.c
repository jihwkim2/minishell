#include "minishell.h"

extern int	g_status;

int	ft_exit(t_list *cmd, int *is_exit)
{
	t_mini	*node;
	long	status[2];

	node = (t_mini *)cmd->content;
	*is_exit = !cmd->next;
	if (*is_exit)
		ft_putstr_fd("exit\n", 2);
	if (!node->full_cmd || !node->full_cmd[1])
		return (0);
	status[1] = ft_atoi2(node->full_cmd[1], &status[0]);
	if (status[1] == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->full_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	else if (node->full_cmd[2])
	{
		*is_exit = 0;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	status[0] %= 256 + 256 * (status[0] < 0);
	return (status[0]);
}

void	cd_error(char **str[2])
{
	DIR		*dir;

	dir = NULL;
	if (str[0][1])
		dir = opendir(str[0][1]);
	if (!str[0][1] && str[1][0] && !str[1][0][0])
	{
		g_status = 1;
		ft_putstr_fd("minishell: HOME not set\n", 2);
	}
	if (str[1][0] && !str[0][1])
		g_status = chdir(str[1][0]) == -1;
	if (str[0][1] && dir && access(str[0][1], F_OK) != -1)
		chdir(str[0][1]);
	else if (str[0][1] && access(str[0][1], F_OK) == -1)
		ft_perror(NDIR, str[0][1], 1);
	else if (str[0][1])
		ft_perror(NOT_DIR, str[0][1], 1);
	if (str[0][1] && dir)
		closedir(dir);
}

int	ft_cd(t_shell *p)
{
	char	**str[2];
	char	*aux;

	g_status = 0;
	str[0] = ((t_mini *)p->cmds->content)->full_cmd;
	aux = ft_getenv("HOME", p->envp, 4);
	if (!aux)
		aux = ft_strdup("");
	str[1] = ft_extend_matrix(NULL, aux);
	free(aux);
	aux = getcwd(NULL, 0);
	str[1] = ft_extend_matrix(str[1], aux);
	free(aux);
	cd_error(str);
	if (!g_status)
		p->envp = ft_setenv("OLDPWD", str[1][1], p->envp, 6);
	aux = getcwd(NULL, 0);
	if (!aux)
		aux = ft_strdup("");
	str[1] = ft_extend_matrix(str[1], aux);
	free(aux);
	p->envp = ft_setenv("PWD", str[1][2], p->envp, 3);
	ft_free_matrix(&str[1]);
	return (g_status);
}

int	ft_export(t_shell *shell)
{
	int		ij[2];
	int		pos;
	char	**argv;

	argv = ((t_mini *)shell->cmds->content)->full_cmd;
	if (ft_matrixlen(argv) >= 2)
	{
		ij[0] = 1;
		while (argv[ij[0]])
		{
			pos = var_in_envp(argv[ij[0]], shell->envp, ij);
			if (pos == 1)
			{
				free(shell->envp[ij[1]]);
				shell->envp[ij[1]] = ft_strdup(argv[ij[0]]);
			}
			else if (!pos)
				shell->envp = ft_extend_matrix(shell->envp, argv[ij[0]]);
			ij[0]++;
		}
	}
	return (0);
}

int	ft_unset(t_shell *shell)
{
	char	**argv;
	char	*aux;
	int		ij[2];

	ij[0] = 0;
	argv = ((t_mini *)shell->cmds->content)->full_cmd;
	if (ft_matrixlen(argv) >= 2)
	{
		while (argv[++ij[0]])
		{
			if (argv[ij[0]][ft_strlen(argv[ij[0]]) - 1] != '=')
			{
				aux = ft_strjoin(argv[ij[0]], "=");
				free(argv[ij[0]]);
				argv[ij[0]] = aux;
			}
			if (var_in_envp(argv[ij[0]], shell->envp, ij))
				ft_matrix_replace_in(&shell->envp, NULL, ij[1]);
		}
	}
	return (0);
}
