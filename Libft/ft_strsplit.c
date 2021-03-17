/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 10:30:50 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/16 17:53:36 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		exist(char *s, char c)
{
	int		i = 0;

	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int		skipping(char const *s, char *token, int i, int *words, char *q)
{
	int	dq;

	dq = 0;
	while (s[i] && !exist(token, s[i]) && dq == 0)
	{
		if (s[i] < 0)
		{
			*q = s[i];
			dq = 1;
		}
		else
			i++;
	}
	if (exist(token, s[i]) && !dq)
	{
		*words = *words + 1;
		while (s[i] && exist(token, s[i]))
			i++;
	}
	else if (s[i] && s[i] == *q && dq == 1)
	{
		i++;
		while (s[i] && s[i] != *q)
			i++;
		dq = 0;
		i++;
	}
	*words = (!s[i] && !exist(token, s[i - 1])) ? (*words + 1) : *words;
	return (i);
}

static int		count_words(char const *s, char *token, int skip)
{
	int		i;
	int		words;
	char	q;

	words = 0;
	i = 0;
	q = 0;
	while (s[i])
	{
		if (skip == 0)
		{
			while (s[i] && !exist(token, s[i]))
				i++;
			words++;
			while (s[i] && exist(token, s[i]))
				i++;
		}
		else
			i = skipping(s, token, i, &words, &q);
	}
	return (words);
}

static int		words_len(char const *s, char *token, int skip)
{
	int		i;
	char		q;
	int		db;

	i = -1;
	q = 0;
	db = 0;
	while (s[++i])
	{
		if (s[i] < 0)
			q = s[i];
		if (s[i] == q && skip)
			db = (db == 0) ? 1 : 0;
		if (exist(token, s[i]) && !db)
			return (i);
		else if (s[i] && s[i] != q && db && skip)
		{
			i++;
			while (s[i] && s[i] != q)
				i++;
			db = 0;
		}
	}
	return (i);
}

static void		*leak(char **splitted, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	return (NULL);
}

static char		**fill(char const *s, int words, char *c, int skip)
{
	int		i;
	int		j;
	int		len;
	char    **splitted;

	i = -1;
	if (!(splitted = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	while (++i < words)
	{
		while (exist(c, *s))
			s++;
		len = words_len(s, c, skip);
		if (!(splitted[i] = (char *)malloc(sizeof(char) * (len + 1))))
			return (leak(splitted, i));
		j = 0;
		while (j < len)
			splitted[i][j++] = *s++;
		splitted[i][j] = '\0';
	}
	splitted[i] = NULL;
	return (splitted);
}

char			**ft_strsplit(char	const *s, char *c, int skip)
{
	char	**splitted;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c, skip);
	splitted = fill(s, words, c, skip);
	return (splitted);
}