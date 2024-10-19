/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:49:50 by nkannan           #+#    #+#             */
/*   Updated: 2024/10/19 20:49:53 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_get(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	one_died(t_philo *philo)
{
	waiter(philo->data->life_range);
	print_action(philo, DIED);
}

void	waiter(long time)
{
	long	start;

	start = time_get();
	while ((time_get() - start) < time)
		usleep(100);
}

void	waiter_white(t_philo *philo)
{
	long	last_meal;
	long	life_range;

	pthread_mutex_lock(&philo->key_mutex);
	last_meal = philo->last_eat;
	pthread_mutex_unlock(&philo->key_mutex);
	life_range = philo->data->life_range;
	while ((time_get() - last_meal) < life_range - 10)
		usleep(100);
}

int	print_action(t_philo *philo, char *str)
{
	long	time;

	time = time_get();
	pthread_mutex_lock(&philo->data->smn_died);
	if (!philo->data->is_dead)
		printf("%li %d %s\n", time - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->smn_died);
	return (1);
}
