/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 02:16:19 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/23 03:20:38 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_lock(t_philo *philo, pthread_mutex_t *lock, const char *fn)
{
	if (pthread_mutex_lock(lock) != 0)
	{
		printf("philo [%d] | FAILED to lock in %s\n", philo->seat, fn);
		return (1);
	}
	return (0);
}

int	update_last_meal_time(t_philo *philo)
{
	if (check_lock(philo, &philo->eat_lock, "update_last_meal_time") != 0)
		return (1);
	philo->last_ate_msec = get_elapsed_time_ms(0);
	philo->deadline = philo->last_ate_msec + philo->setup->msec_to_die;
	pthread_mutex_unlock(&philo->eat_lock);
	return (0);
}

bool	has_reached_meal_limit(t_philo *philo)
{
	bool	enough;

	enough = false;
	if (check_lock(philo, &philo->eat_lock, "has_reached_meal_limit") != 0)
		return (1);
	if (philo->setup->must_eat > 0
		&& philo->times_eaten == philo->setup->must_eat)
		enough = true;
	pthread_mutex_unlock(&philo->eat_lock);
	return (enough);
}

bool	is_simulation_over(t_philo *philo)
{
	bool	done;

	done = false;
	if (check_lock(philo, &philo->setup->dead_lock, "is_simulation_over") != 0)
		return (1);
	if (philo->setup->someone_dead == true
		|| philo->setup->full_philos == philo->setup->num_philo)
		done = true;
	pthread_mutex_unlock(&philo->setup->dead_lock);
	return (done);
}

// usleep in microseconds

void	usleep_accurate(uintmax_t usec)
{
	uintmax_t	start;

	start = get_current_time_us();
	while (get_current_time_us() - start < usec)
		usleep(100);
}
