/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:55:27 by hjabbour          #+#    #+#             */
/*   Updated: 2022/07/28 15:19:12 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static	int	nbr_mots(char *s, char c)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			len++;
		}
		else
			i++;
	}
	return (len);
}

static	void	fct_free(char **str, int k)
{
	if (k == 0)
		free(str[k]);
	if (k >= 0)
		while (k > 0)
			free(str[k--]);
	free(str);
	return ;
}

static	void	malloc_colones(char *s, char **str, char c)
{
	int	i;
	int	len;
	int	k;

	i = 0;
	len = 0;
	k = 0;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i++] != '\0')
				len++;
			str[k] = (char *)(malloc((len + 2) * sizeof(char)));
			if (str[k] == NULL)
				fct_free(str, k);
			k++;
			len = 0;
		}
		else
			i++;
	}
	if (str == NULL)
		return ;
}

static	void	remplissage(char *s, char **str, char c, int yesno)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
				str[j][k++] = s[i++];
			if (yesno == 1)
				str[j][k++] = '/';
			str[j][k] = '\0';
			k = 0;
			j++;
		}
		else
			i++;
	}
}

char	**ft_split(char *s, char c, int yesno)
{
	char	**str;
	int		mots;

	if (!(char *)s)
		return (NULL);
	mots = nbr_mots((char *)s, c);
	str = (char **)malloc((mots + 1 + yesno) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	str[mots] = NULL;
	malloc_colones((char *)s, str, c);
	if (str == NULL)
		return (NULL);
	remplissage(s, str, c, yesno);
	return (str);
}
