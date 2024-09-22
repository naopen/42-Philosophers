/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:50:47 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/23 01:50:47 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_strcmp(void *s1, void *s2)
{
	int		i;
	char	*str1;
	char	*str2;

	i = 0;
	str1 = s1;
	str2 = s2;
	while ((str1[i] && str2[i]) && str1[i] == str2[i])
		i++;
	if (!str1[i] && !str2[i])
		return (0);
	return (str1[i] - str2[i]);
}

bool	ft_iswhitespace(const char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (true);
	return (false);
}

int	ft_skipws(const char **str, int i)
{
	if (*str == NULL || *str[i] == '\0' || !ft_iswhitespace(*str[i]))
		return (0);
	while (ft_iswhitespace(*str[i]))
		(*str)++;
	return (1);
}

// Converts string to int
// Returns 0 on success
// Returns 1 on failure

bool	str_to_int_safe(const char *num_str, int *num)
{
	bool		is_negative;
	intmax_t	res;

	res = 0;
	if (!num_str)
		return (false);
	ft_skipws(&num_str, 0);
	is_negative = (*num_str == '-');
	if (*num_str == '-' || *num_str == '+')
		num_str++;
	while (*num_str != '\0')
	{
		if (*num_str < '0' || *num_str > '9')
			return (false);
		res = res * 10 + (*num_str - '0');
		if ((!is_negative && res > INT_MAX)
			|| (is_negative && -(res) < INT_MIN))
			return (false);
		num_str++;
	}
	if (is_negative)
		*num = res * -1;
	else
		*num = res;
	return (true);
}
