/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:55:37 by nkannan           #+#    #+#             */
/*   Updated: 2024/07/20 23:07:45 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_take_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&data->output_mutex);
	printf("%lld %d has taken a fork\n", get_time() - data->start_time,
		philo->id);
	pthread_mutex_unlock(&data->output_mutex);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&data->output_mutex);
	printf("%lld %d has taken a fork\n", get_time() - data->start_time,
		philo->id);
	pthread_mutex_unlock(&data->output_mutex);
}

void	philo_eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->output_mutex);
	printf("%lld %d is eating\n", get_time() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->output_mutex);
	philo->last_eat_time = get_time();
	usleep(data->time_to_eat * 1000);
}
