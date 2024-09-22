/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:55:24 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/23 05:36:53 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	mark_as_dead(t_philo *philo)
{
	if (check_lock(philo, &philo->setup->dead_lock, "mark_as_dead") != 0)
		return (1);
	philo->setup->someone_dead = true;
	pthread_mutex_unlock(&philo->setup->dead_lock);
	return (0);
}

void	print_message(t_philo *philo, const char *message, t_msg_type type)
{
	uintmax_t	time;

	time = get_elapsed_time_ms(philo->setup->program_start_ms);
	printf("%ju ms | Philosopher [%d] %s", time, philo->seat,
		message);
	if (philo->setup->must_eat && type == EAT)
		printf(" (%d/%d)", philo->times_eaten + 1, philo->setup->must_eat);
	printf("\n");
}

int	log_status(t_philo *philo, const char *message, t_msg_type type)
{
	if (check_lock(philo, &philo->setup->msg_lock, "log_status") != 0)
		return (1);
	if (!is_simulation_over(philo))
	{
		print_message(philo, message, type);
		if (type == DEAD)
			mark_as_dead(philo);
	}
	pthread_mutex_unlock(&philo->setup->msg_lock);
	return (0);
}
