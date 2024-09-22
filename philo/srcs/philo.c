/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:55:39 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/23 01:55:39 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

int	philo_think(t_philo *philo)
{
	if (log_status(philo, MSG_THINK, THINK))
		return (1);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (log_status(philo, MSG_SLEEP, SLEEP))
		return (1);
	usleep_accurate(philo->setup->msec_to_sleep * 1000);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (update_last_meal_time(philo))
		return (1);
	log_status(philo, MSG_EAT, EAT);
	usleep_accurate(philo->setup->msec_to_eat * 1000);
	philo->times_eaten++;
	release_forks(philo);
	return (0);
}

void	*philo_routine(void *philo_arg)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)philo_arg;
	philo->active = true;
	if (pthread_create(&tid, NULL, &philo_check, philo_arg) != 0)
		return ((void *)1);
	if (philo->seat % 2 == 0)
		usleep(1000);
	if (update_last_meal_time(philo) == 0)
	{
		while (!is_simulation_over(philo) && !has_reached_meal_limit(philo))
		{
			if (take_forks(philo)
				|| philo_eat(philo)
				|| philo_sleep(philo)
				|| philo_think(philo))
				break ;
			usleep(1000);
		}
	}
	philo->active = false;
	pthread_join(tid, NULL);
	return (NULL);
}
