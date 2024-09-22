/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:49:22 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/23 01:49:26 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

uintmax_t	get_current_time_us(void)
{
	struct timeval	time;
	uintmax_t		time_usec;

	gettimeofday(&time, NULL);
	time_usec = (time.tv_sec * 1000) * 1000;
	time_usec += time.tv_usec;
	return (time_usec);
}

uintmax_t	get_elapsed_time_ms(uintmax_t start)
{
	struct timeval	time;
	uintmax_t		time_msec;

	gettimeofday(&time, NULL);
	time_msec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (time_msec < start)
		return (0);
	return (time_msec - start);
}
