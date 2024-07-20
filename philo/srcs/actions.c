/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:56:16 by nkannan           #+#    #+#             */
/*   Updated: 2024/07/20 23:06:03 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	philo_sleep(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->output_mutex);
	printf("%lld %d is sleeping\n", get_time() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->output_mutex);
	usleep(data->time_to_sleep * 1000);
}

static void	philo_think(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->output_mutex);
	printf("%lld %d is thinking\n", get_time() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->output_mutex);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = (t_data *)(philo - philo->id + 1);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!data->is_finished)
	{
		philo_take_forks(philo, data);
		philo_eat(philo, data);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo->eat_count++;
		philo_sleep(philo, data);
		philo_think(philo, data);
	}
	return (NULL);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philo)
	{
		data->philos[i].last_eat_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, philosopher_routine,
				&data->philos[i]) != 0)
			return (error_exit(data, "Error: Thread creation failed"));
		i++;
	}
	return (0);
}
