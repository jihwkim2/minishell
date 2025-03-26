#include "minishell.h"

int	g_status;

static void	ft_getpid(t_shell *p)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_perror(FORKERR, NULL, 1);
		ft_free_matrix(&p->envp);
		exit(1);
	}
	if (!pid)
	{
		ft_free_matrix(&p->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	p->pid = pid - 1;
}

static t_shell	init_prompt(char **envp)
{
	t_shell		shell;

	shell.cmds = NULL;
	shell.envp = ft_dup_matrix(envp);
	g_status = 0;
	ft_getpid(&shell);
	return (shell);
}
// 프롬프트 초기화

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	shell;

	shell = init_prompt(envp);
	while (argv && argc)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minisehll>");
		if (!check_args(input, &shell))
			break ;
	}
	rl_clear_history();
	ft_free_matrix(&(shell.envp));
	exit(g_status);
}
