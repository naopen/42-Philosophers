/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:49:38 by nkannan           #+#    #+#             */
/*   Updated: 2024/10/19 23:10:19 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_utils(t_philo *philo)
{
	pthread_mutex_lock(&philo->key_mutex);
	philo->last_eat = time_get();
	pthread_mutex_unlock(&philo->key_mutex);
	print_action(philo, EAT);
	waiter(philo->data->eat_time);
	pthread_mutex_lock(&philo->key_mutex);
	if (philo->data->argc == 6)
		philo->nb_meals--;
	philo->ate = 1;
	pthread_mutex_unlock(&philo->key_mutex);
}

int	eat_with_right_fork_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_action(philo, FORK);
	pthread_mutex_lock(&philo->next->fork);
	print_action(philo, FORK);
	eat_utils(philo);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	if (philo->data->argc == 6 && philo->nb_meals == 0)
		return (0);
	return (1);
}

int	eat_with_left_fork_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->next->fork);
	print_action(philo, FORK);
	if (&philo->fork == &philo->next->fork)
		return (pthread_mutex_unlock(&philo->fork), one_died(philo), 0);
	pthread_mutex_lock(&philo->fork);
	print_action(philo, FORK);
	eat_utils(philo);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
	if (philo->data->argc == 6 && philo->nb_meals == 0)
		return (0);
	return (1);
}
