/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:57:21 by nkannan           #+#    #+#             */
/*   Updated: 2024/07/22 22:32:08 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_data *data)
{
	int	i;

	while (!data->is_finished)
	{
		i = -1;
		while (++i < data->num_philo && !data->is_finished)
		{
			pthread_mutex_lock(&data->state_mutex);
			if (get_time() - data->philos[i].last_eat_time >= data->time_to_die)
			{
				data->philos[i].state = DEAD;
				print_action(&data->philos[i], DEAD);
				data->is_finished = true;
				pthread_mutex_unlock(&data->state_mutex);
				return (1);
			}
			pthread_mutex_unlock(&data->state_mutex);
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
			pthread_mutex_lock(&data->state_mutex);
			if (data->philos[i].eat_count >= data->num_must_eat)
				count++;
			pthread_mutex_unlock(&data->state_mutex);
			i++;
		}
		if (count == data->num_philo)
		{
			pthread_mutex_lock(&data->output_mutex);
			data->is_finished = true;
			pthread_mutex_unlock(&data->output_mutex);
			return (1);
		}
		usleep(100);
	}
	return (0);
}

void	print_action(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->data->output_mutex);
	if (!philo->data->is_finished)
	{
		if (action == HAS_FORK)
			printf("%lld %d has taken a fork\n", get_time()
					- philo->data->start_time, philo->id);
		else if (action == EATING)
			printf("%lld %d is eating\n", get_time() - philo->data->start_time,
					philo->id);
		else if (action == SLEEPING)
			printf("%lld %d is sleeping\n", get_time()
					- philo->data->start_time, philo->id);
		else if (action == DEAD)
			printf("%lld %d died\n", get_time() - philo->data->start_time,
					philo->id);
	}
	pthread_mutex_unlock(&philo->data->output_mutex);
}
