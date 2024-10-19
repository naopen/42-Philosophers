/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:48:25 by nkannan           #+#    #+#             */
/*   Updated: 2024/10/19 21:08:50 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argv(char **argv)
{
	short	i;
	short	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[0]) < 1)
		return (0);
	return (1);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->smn_died);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->smn_died);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->smn_died);
	return (1);
}

int	check_finished(t_philo *philo)
{
	t_philo	*first;

	first = philo;
	while (philo)
	{
		pthread_mutex_lock(&philo->key_mutex);
		if (!philo->nb_meals)
		{
			pthread_mutex_unlock(&philo->key_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->key_mutex);
		philo = philo->next;
		if (first == philo)
			break ;
	}
	return (1);
}

int	dead_verify(t_philo *philo)
{
	long	time;

	time = time_get();
	pthread_mutex_lock(&philo->key_mutex);
	if (time - philo->last_eat >= philo->data->life_range)
	{
		pthread_mutex_unlock(&philo->key_mutex);
		pthread_mutex_lock(&philo->data->smn_died);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->smn_died);
		printf("%li %d %s\n", time - philo->data->start_time, philo->id,
			DIED);
		return (0);
	}
	pthread_mutex_unlock(&philo->key_mutex);
	return (1);
}
