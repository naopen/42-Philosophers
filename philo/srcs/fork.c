/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:46:14 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/23 01:46:41 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->p_forks[LEFT]);
	pthread_mutex_unlock(philo->p_forks[RIGHT]);
	return ;
}

int	take_forks(t_philo *philo)
{
	int	side;

	if (philo->seat % 2 == 0)
		side = LEFT;
	else
		side = RIGHT;
	if (check_lock(philo, philo->p_forks[side], "take_forks") != 0)
		return (1);
	log_status(philo, MSG_FORK, FORK);
	if (check_lock(philo, philo->p_forks[!side], "take_forks") != 0)
	{
		pthread_mutex_unlock(philo->p_forks[side]);
		return (1);
	}
	log_status(philo, MSG_FORK, FORK);
	return (0);
}
