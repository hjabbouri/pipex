/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 08:44:14 by hjabbour          #+#    #+#             */
/*   Updated: 2022/07/28 18:19:20 by hjabbour         ###   ########.fr       */
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

static void	duplicate(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

void	exec(int procn, int *fd, char *cmd, char **env)
{
	char	**paths;
	char	**args;
	char	*cmd_path;

	if (fd[procn - 1] == -1)
		exit(1);
	paths = get_path(env);
	args = ft_split(cmd, ' ', 0);
	cmd_path = check_access(paths, args[0], fd);
	if (args == NULL || cmd_path == NULL)
		exit(1);
	close(fd[procn + 1]);
	if (procn == 1)
		duplicate(fd[0], fd[3]);
	else
		duplicate(fd[2], fd[1]);
	if (execve(cmd_path, args, env) == -1)
	{
		free_exec(paths, args, cmd_path);
		ft_perror(cmd, NULL, fd);
	}
}

static void	init_man(int *fd, char **av)
{
	if (pipe(fd + 2) == -1)
		ft_perror("Pipe failed", NULL, fd);
	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[0] == -1)
		perror(av[1]);
	if (fd[1] == -1)
		perror(av[4]);
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		fd[4];
	int		stat;
	int		procn;

	if (ac != 5)
		return (ft_putstr_fd(ARGERR, 2), 1);
	pid = 1;
	procn = 0;
	init_man(fd, av);
	while (pid != 0 && ++procn < 3)
	{
		pid = fork();
		if (pid == -1)
			perror("fork failed");
	}
	if (procn < 3)
		exec(procn, fd, av[procn + 1], env);
	close_all(fd);
	waitpid(pid, &stat, 0);
	while (wait(NULL) != -1)
		;
	return (WEXITSTATUS(stat));
}
