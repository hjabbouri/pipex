/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:27:32 by hjabbour          #+#    #+#             */
/*   Updated: 2022/07/28 16:15:54 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h>

# define CMDERR "command not found\n"
# define ARGERR "invalid argument number\n"
# define HERE_DOCERR "here_doc invalid argument number\n"

typedef struct s_data {
	int		pid;
	int		procn;
	int		fd[2];
	int		*pipe;
	int		limit;
	int		pipe_limit;
	int		hd;
	int		i;
	int		ac;
	char	**av;
	char	**env;
}	t_data;

char	**ft_split(char *s, char c, int yesno);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	**get_path(char **env);
char	*check_access(char **paths, char *cmd, int *fd);
void	ft_free(void);
int		ft_strchr(char *s, int c);
void	ft_perror(char *file, char *err, int *fd);
void	close_all(int *fd);
void	ft_putstr_fd(char *s, int fd);
void	exec(int procn, int *fd, char *cmd, char **env);

char	*check_access_bonus(char **paths, char *cmd, t_data *d);
void	ft_perror_bonus(char *file, char *err, t_data *d);
void	close_all_bonus(t_data *d);
void	exec_bonus(t_data *d);
void	here_doc(t_data *d, char *delim);

#endif
