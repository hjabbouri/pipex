/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:55:49 by hjabbour          #+#    #+#             */
/*   Updated: 2022/07/28 15:18:59 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
	}
	return (ft_split(env[i] + 5, ':', 1));
}

char	*check_access(char **paths, char *cmd, int *fd)
{
	int		i;
	char	*cmd_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		ft_perror(cmd, NULL, fd);
	}
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (cmd_path == NULL)
			return (NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	ft_perror(cmd, CMDERR, fd);
	return (NULL);
}

void	ft_perror(char *file, char *err, int *fd)
{
	close_all(fd);
	if (err)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(err, 2);
	}
	else
		perror(file);
	exit(1);
}
