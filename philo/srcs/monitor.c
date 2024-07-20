/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:57:21 by nkannan           #+#    #+#             */
/*   Updated: 2024/07/20 23:06:35 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_data *data)
{
	int	i;

	while (!data->is_finished)
	{
		i = 0;
		while (i < data->num_philo)
		{
			if (get_time() - data->philos[i].last_eat_time >= data->time_to_die)
			{
				pthread_mutex_lock(&data->output_mutex);
				printf("%lld %d died\n", get_time() - data->start_time,
					data->philos[i].id);
				pthread_mutex_unlock(&data->output_mutex);
				data->is_finished = TRUE;
				return (1);
			}
			i++;
		}
		usleep(100);
	}
	return (0);
}

int	check_eat_count(t_data *data)
{
	int	i;
	int	count;

	if (data->num_must_eat == -1)
		return (0);
	while (!data->is_finished)
	{
		i = 0;
		count = 0;
		while (i < data->num_philo)
		{
			if (data->philos[i].eat_count >= data->num_must_eat)
				count++;
			i++;
		}
		if (count == data->num_philo)
		{
			data->is_finished = TRUE;
			return (1);
		}
		usleep(100);
	}
	return (0);
}
