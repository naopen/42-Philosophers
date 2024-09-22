/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:46:14 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/23 06:47:55 by nkannan          ###   ########.fr       */
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
	int				first_fork;
	int				second_fork;
	uintmax_t		start_time;

	if (philo->seat % 2 != 0)
	{
		first_fork = RIGHT;
		second_fork = LEFT;
	}
	else
	{
		first_fork = LEFT;
		second_fork = RIGHT;
	}

	start_time = get_elapsed_time_ms(0);
	while (get_elapsed_time_ms(start_time) < philo->setup->msec_to_die / 2) // タイムアウト設定(例: 死にかけ時間の半分)
	{
		if (check_lock(philo, philo->p_forks[first_fork], "take_forks") != 0)
			return (1);
		if (check_lock(philo, philo->p_forks[second_fork], "take_forks") == 0)
		{
			log_status(philo, MSG_FORK, FORK);
			log_status(philo, MSG_FORK, FORK);
			return (0);
		}
		pthread_mutex_unlock(philo->p_forks[first_fork]);
		usleep(10); // 少し待機
	}
	return (1); // タイムアウト
}
