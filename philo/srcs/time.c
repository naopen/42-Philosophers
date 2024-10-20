/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:49:50 by nkannan           #+#    #+#             */
/*   Updated: 2024/10/20 14:41:21 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	on_death(t_philo *philo)
{
	wait_for_ms(philo->data->life_range);
	print_action(philo, DIED);
}

void	wait_for_ms(long time)
{
	long	start;

	start = get_current_time_ms();
	while ((get_current_time_ms() - start) < time)
		usleep(100);
}

void	wait_until_next_action(t_philo *philo)
{
	long	last_meal;
	long	life_range;

	pthread_mutex_lock(&philo->key_mutex);
	last_meal = philo->last_eat;
	pthread_mutex_unlock(&philo->key_mutex);
	life_range = philo->data->life_range;
	while ((get_current_time_ms() - last_meal) < life_range - 10)
		usleep(100);
}

void	on_death(t_philo *philo)
{
	wait_for_ms(philo->data->life_range);
	print_action(philo, DIED);
}

int	print_action(t_philo *philo, char *str)
{
	long	time;

	time = get_current_time_ms();
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->is_dead)
		printf("%li %d %s\n", time - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (1);
}
