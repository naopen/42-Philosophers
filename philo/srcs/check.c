/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:46:02 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/23 01:46:05 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*mark_philosopher_full(t_philo *philo)
{
	log_status(philo, MSG_ENOUGH, ENOUGH);
	philo->setup->full_philos++;
	return (NULL);
}

void	*mark_philosopher_dead(t_philo *philo)
{
	log_status(philo, MSG_DIED, DEAD);
	pthread_mutex_unlock(&philo->eat_lock);
	release_forks(philo);
	return (NULL);
}

void	*philo_check(void *philo_arg)
{
	t_philo		*philo;
	uintmax_t	current_time;

	philo = (t_philo *)philo_arg;
	while (1)
	{
		if (check_lock(philo, &philo->eat_lock, "philo_check") != 0)
			return ((void *)1);
		if (!philo->active)
		{
			pthread_mutex_unlock(&philo->eat_lock);
			break ;
		}
		current_time = get_elapsed_time_ms(0);
		if (current_time > philo->deadline)
		{
			pthread_mutex_unlock(&philo->eat_lock);
			return (mark_philosopher_dead(philo));
		}
		pthread_mutex_unlock(&philo->eat_lock);

		if (check_lock(philo, &philo->setup->dead_lock, "philo_check") != 0)
			return ((void *)1);
		if (philo->setup->someone_dead)
		{
			pthread_mutex_unlock(&philo->setup->dead_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->setup->dead_lock);
		if (philo->setup->must_eat > 0 && has_reached_meal_limit(philo))
			return (mark_philosopher_full(philo));
		usleep(1000);
	}
	return (NULL);
}
