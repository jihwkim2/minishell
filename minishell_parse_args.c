#include "minishell.h"

extern int	g_status;

static int	ft_count_words2(const char *s, char *c, int i[2])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s[i[0]] != '\0')
	{
		if (!ft_strchr(c, s[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(c, s[i[0]]) || q[0]) && s[i[0]] != '\0')
			{
				if (!q[1] && (s[i[0]] == '\"' || s[i[0]] == '\''))
					q[1] = s[i[0]];
				q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
				q[1] *= q[0] != 0;
				i[0]++;
			}
			if (q[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static char	**ft_fill_array2(char **aux, char const *s, char *set, int i[3])
{
	int		s_len;
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	s_len = ft_strlen(s);
	while (s[i[0]])
	{
		while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
		{
			q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= s_len)
			aux[i[2]++] = "\0";
		else
			aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (aux);
}

char	**ft_cmdtrim(char const *s, char *set)
{
	char	**aux;
	int		nwords;
	int		i[3];
	int		counts[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	counts[0] = 0;
	counts[1] = 0;
	if (!s)
		return (NULL);
	nwords = ft_count_words2(s, set, counts);
	if (nwords == -1)
		return (NULL);
	aux = malloc((nwords + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	aux = ft_fill_array2(aux, s, set, i);
	aux[nwords] = NULL;
	return (aux);
}

static void	*parse_args(char **args, t_shell *p)
{
	int	is_exit;
	int	i;

	is_exit = 0;
	p->cmds = make_nodes(split_all(args, p), -1);
	if (!p->cmds)
		return (p);
	i = ft_lstsize(p->cmds);
	g_status = builtin(p, p->cmds, &is_exit, 0);
	while (i-- > 0)
		waitpid(-1, &g_status, 0);
	if (!is_exit && g_status == 13)
		g_status = 0;
	if (g_status > 255)
		g_status = g_status / 255;
	if (args && is_exit)
	{
		ft_lstclear(&p->cmds, free_content);
		return (NULL);
	}
	return (p);
}

void	*check_args(char *out, t_shell *p)
{
	char	**a;

	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);
	a = ft_cmdtrim(out, " ");
	free(out);
	if (!a)
		ft_perror(QUOTE, NULL, 1);
	if (!a)
		return ("");
	p = parse_args(a, p);
	if (p && p->cmds)
		ft_lstclear(&p->cmds, free_content);
	return (p);
}
