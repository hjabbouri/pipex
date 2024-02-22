/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 08:44:14 by hjabbour          #+#    #+#             */
/*   Updated: 2022/07/28 16:10:12 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static t_data	init_data(t_data *d, int ac, char **av, char **env)
{
	d = &(t_data){.pid = 1, .procn = 0, .fd[0] = 0, .fd[1] = 0,
		.ac = ac, .av = av, .env = env, .hd = 0, .i = 0};
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		here_doc(d, av[2]);
	else
	{
		d->fd[0] = open(av[1], O_RDONLY);
		d->fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	if (d->fd[0] == -1 && ft_strncmp(av[1], "here_doc", 9) != 0)
		perror(av[1]);
	if (d->fd[1] == -1)
		perror(av[ac - 1]);
	d->pipe_limit = (ac - 4 - d->hd) * 2;
	d->limit = ac - 2 - d->hd;
	d->pipe = malloc(sizeof(int) * d->pipe_limit);
	while (d->i < d->pipe_limit)
	{
		if (pipe(d->pipe + d->i) == -1)
			ft_perror_bonus("Pipe failed", NULL, d);
		d->i += 2;
	}
	return (*d);
}

static void	check_arg(int ac, char **av)
{
	if (ac < 5)
	{
		ft_putstr_fd(ARGERR, 2);
		exit(EXIT_FAILURE);
	}
	else if (ac < 6 && ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		ft_putstr_fd(ARGERR, 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	d;
	pid_t	pid;
	int		stat;

	check_arg(ac, av);
	d = init_data(&d, ac, av, env);
	pid = 1;
	while (pid != 0 && ++(d.procn) < d.limit)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork failed"), unlink("/tmp/.here_doc.tmp") \
				, EXIT_FAILURE);
	}
	if (d.procn < d.limit)
		exec_bonus(&d);
	close_all_bonus(&d);
	waitpid(pid, &stat, 0);
	while (wait(NULL) != -1)
		;
	unlink("/tmp/.here_doc.tmp");
	return (WEXITSTATUS(stat));
}
