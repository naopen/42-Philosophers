/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:52:42 by nkannan           #+#    #+#             */
/*   Updated: 2024/10/19 22:19:28 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
{
	long	result;
	char	*endptr;

	result = ft_strtol(str, &endptr, 10);
	if (*endptr != '\0' || result > INT_MAX || result < INT_MIN)
		return (-1);  // エラー値として-1を返す
	return (result);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = 0;
}
