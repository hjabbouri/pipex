/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:09:11 by hjabbour          #+#    #+#             */
/*   Updated: 2022/07/28 17:55:50 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	free_exec(char **paths, char **args, char *cmd_path)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	i = -1;
	while (args[++i])
		free(args[i]);
	free(cmd_path);
}

static void	check_file(t_data *d)
{
	if (d->procn == 1 && d->fd[0] == -1)
		exit(1);
	if (d->procn == d->limit - 1 && d->fd[1] == -1)
		exit(1);
}

static void	duplicate(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

void	exec_bonus(t_data *d)
{
	char	**paths;
	char	**args;
	char	*cmd_path;

	check_file(d);
	args = ft_split(d->av[d->procn + 1 + d->hd], ' ', 0);
	paths = get_path(d->env);
	cmd_path = check_access_bonus(paths, args[0], d);
	if (args == NULL || paths == NULL || cmd_path == NULL)
		exit(1);
	if (d->procn == 1)
		duplicate(d->fd[0], d->pipe[1]);
	else if (d->procn == d->limit - 1)
		duplicate(d->pipe[d->pipe_limit - 2], d->fd[1]);
	else
		duplicate(d->pipe[d->procn * 2 - 4], d->pipe[d->procn * 2 - 1]);
	close_all_bonus(d);
	if (execve(cmd_path, args, d->env) == -1)
	{
		free_exec(paths, args, cmd_path);
		ft_perror_bonus(d->av[d->procn + 1 + d->hd], NULL, d);
	}
}
