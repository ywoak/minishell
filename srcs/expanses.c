/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanses.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:41:37 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/22 19:00:04 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace(t_env *env_s, char *newline, char *key, char *name, t_lst **head)
{
/*
 * But = avoir dans newline le line mais en ayant remplace $key par sa value *
 * Malloc le newline de la bonne taille					*
 * Cpy tant que on est pas sur le $						*
 * une fois sur le $ ecrire la value de key				*
 * une fois la value de la key ecrite cpy jusqua la fin	*
 * */

	int		dollars;
	int		size;
	int		count;
	char	*value;

	count = 0;
	value = get_value_of_key(head, name);
	size = (ft_strlen(env_s->line) - ft_strlen(key) + ft_strlen(value));
	if (!(newline = ft_memalloc(sizeof(char) * (size + 1))))
		return ;
	size = 0;
	while (env_s->line[size] != '$')
	{
		newline[size] = env_s->line[size];
		size++;
	}
	dollars = size;
	while (value[count])
	{
		newline[size] = value[count];
		count++;
		size++;
	}
	dollars = dollars + ft_strlen(key);
	while (env_s->line[dollars])
	{
		newline[size] = env_s->line[dollars];
		size++;
		dollars++;
	}
	ft_putendl(newline);
}

char	*to_check(char *str)
{
	char	*name;

	name = ft_strsub(str, 1, (ft_strlen(str) - 1));
	return (name);
}

int		delimiter(char c)
{
	if (c == '-' || c == '+' || c == '/' || c == ' ' || c == '\t' || c == '=' || c == '|' || c == '$' || c == '\n' || c == '\r' || c == '\0')
		return (1);
	return (0);
}

void	expanse(t_env *env_s, t_lst **head)
{
	int		start;
	int		count;
	char	*key;
	char	*name;
	char	*newline;
/*
	 * when $ is found														*
	 * everything in between $ and end delimiter has to be check			*
	 * if it is an env variable												*
	 * replace from $ to (delimiter - 1) with the value of that variable
	 * */

	count = 0;
	start = 0;
	key = NULL;
	name = NULL;
	newline = NULL;
	while (env_s->line[start] && (env_s->line[start] != '$'))
		start++;
	if (env_s->line[start])
	{
		start++;
		count++;
		while (42)
		{
			if (delimiter(env_s->line[start]))
			{
				key = ft_strsub(env_s->line, (start - count), count);
				name = to_check(key);
				if (lst_check_name(name, head))
					replace(env_s, newline, key, name, head);
				break ;
			}
			start++;
			count++;
		}
	}
}
