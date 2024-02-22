/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:55:40 by hjabbour          #+#    #+#             */
/*   Updated: 2022/07/28 16:13:12 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*ft_calloc(int count)
{
	char	*s;
	int		i;

	i = 0;
	s = malloc(count);
	if (s == NULL)
	{
		ft_putstr_fd("memory allocation error", 2);
		exit(1);
	}
	while (count-- > 0)
		s[i++] = '\0';
	return (s);
}

static char	*ft_join(char *buff, char *line)
{
	char	*dest;
	int		i;

	i = -1;
	if (buff == NULL)
		buff = ft_calloc(1);
	if (line == NULL)
		return (free(buff), free(line), NULL);
	dest = ft_calloc(ft_strlen(buff) + 2);
	if (dest == NULL || line == NULL)
		return (NULL);
	while (buff[++i])
		dest[i] = buff[i];
	dest[i++] = line[0];
	free(buff);
	return (dest);
}

static char	*get_line(void)
{
	char		*buff;
	char		*line;
	char		c;
	int			ret;

	ret = 1;
	line = ft_calloc(2);
	buff = NULL;
	while (ret > 0)
	{
		ret = read(0, &c, 1);
		if (ret == 0)
			break ;
		line[0] = c;
		buff = ft_join(buff, line);
		if (c == '\n')
			break ;
	}
	if (line[0] == '\0' || ret == 0)
		return (free(buff), free(line), NULL);
	free(line);
	return (buff);
}

void	here_doc(t_data *d, char *delim)
{
	char	*line;
	char	*end;

	unlink("/tmp/.here_doc.tmp");
	d->fd[0] = open("/tmp/.here_doc.tmp", O_CREAT | O_RDWR, 0644);
	d->fd[1] = open(d->av[d->ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	d->hd = 1;
	if (d->fd[0] == -1)
		perror("here_doc");
	end = ft_strjoin(delim, "\n");
	while (1)
	{
		write(1, "pipe heredoc>", 13);
		line = get_line();
		if (line == NULL || ft_strncmp(line, end, ft_strlen(delim) + 1) == 0)
			break ;
		write(d->fd[0], line, ft_strlen(line));
		free(line);
	}
	close(d->fd[0]);
	d->fd[0] = open("/tmp/.here_doc.tmp", O_RDONLY, 0644);
	free(end);
	if (line != NULL)
		free(line);
}
