/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:55:39 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/23 15:25:04 by nkannan          ###   ########.fr       */
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

	philo = (t_philo *)philo_arg;
	if (check_lock(philo, &philo->eat_lock, "philo_routine") != 0)
		return ((void *)1);
	philo->active = true;
	pthread_mutex_unlock(&philo->eat_lock);
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
			// usleepはmain関数に移動
		}
	}
	if (check_lock(philo, &philo->eat_lock, "philo_routine") != 0)
		return ((void *)1);
	philo->active = false;
	pthread_mutex_unlock(&philo->eat_lock);
	return (NULL);
}
