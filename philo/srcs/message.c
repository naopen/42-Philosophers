/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:55:24 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/23 02:24:37 by nkannan          ###   ########.fr       */
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
	const char	*color;

	time = get_elapsed_time_ms(philo->setup->program_start_ms);
	if (type == FORK)
		color = "\033[0;33m";
	else if (type == EAT)
		color = "\033[0;32m";
	else if (type == SLEEP)
		color = "\033[0;34m";
	else if (type == THINK)
		color = "\033[0;36m";
	else if (type == DEAD)
		color = "\033[0;31m";
	else if (type == ENOUGH)
		color = "\033[0;35m";
	else
		color = "\033[0m";
	printf("%s%ju ms | Philosopher [%d] %s\033[0m", color, time, philo->seat,
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
