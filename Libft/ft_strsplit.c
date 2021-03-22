/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 10:30:50 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/19 17:31:02 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char *s, char *token, int skip)
{
	int		words;
	char	q;

	words = 0;
	q = 0;
	while (*s)
	{
		if (skip == 0)
		{
			while (*s && !exist(token, *s))
				s++;
			words++;
			while (*s && exist(token, *s))
				s++;
		}
		else
			skipping(&s, token, &words, &q);
	}
	return (words);
}

static int		words_len(char *s, char *token, int skip)
{
	int		i;
	char	q;
	int		db;

	i = -1;
	q = 0;
	db = 0;
	while (s[++i])
	{
		if (s[i] < 0 && s[i] != -92)
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

static char		**fill(char *s, int words, char *c, int skip)
{
	int		i;
	int		j;
	int		len;
	char	**splitted;

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

char			**ft_strsplit(char *s, char *c, int skip)
{
	char	**splitted;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c, skip);
	splitted = fill(s, words, c, skip);
	return (splitted);
}
