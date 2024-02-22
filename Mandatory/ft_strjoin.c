/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:55:30 by hjabbour          #+#    #+#             */
/*   Updated: 2022/07/28 15:19:22 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static	void	ft(char *s1, char *s2, char *str, int len1)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[len1] = s2[i];
		i++;
		len1++;
	}
	str[len1] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	str = (malloc(sizeof(char) * (len1 + len2 + 1)));
	if (str == NULL)
		return (NULL);
	ft(s1, s2, str, len1);
	return (str);
}
