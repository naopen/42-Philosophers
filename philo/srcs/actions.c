/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:56:16 by nkannan           #+#    #+#             */
/*   Updated: 2024/10/19 20:50:39 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->key_mutex);
	if (philo->ate == 1)
		return (pthread_mutex_unlock(&philo->key_mutex), 1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->key_mutex);
		if (!eat_with_right_fork_first(philo))
			return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->key_mutex);
		if (!eat_with_left_fork_first(philo))
			return (0);
	}
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	long	time;

	print_action(philo, SLEEP);
	pthread_mutex_lock(&philo->key_mutex);
	time = (philo->data->sleep_time);
	pthread_mutex_unlock(&philo->key_mutex);
	waiter(time);
	return (1);
}

int	philo_think(t_philo *philo)
{
	print_action(philo, THINK);
	waiter_white(philo);
	return (1);
}
