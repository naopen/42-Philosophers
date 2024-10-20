/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:48:25 by nkannan           #+#    #+#             */
/*   Updated: 2024/10/20 14:42:47 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argv(char **argv)
{
	short	i;
	long	value;
	char	*endptr;

	i = 0;
	while (argv[i])
	{
		value = ft_strtol(argv[i], &endptr, 10);
		if (*endptr != '\0' || value <= 0 || value > INT_MAX)
		{
			printf("Error: Invalid argument '%s'\n", argv[i]);
			return (0);
		}
		i++;
	}
	if (ft_strtol(argv[0], &endptr, 10) < 1)
	{
		printf("Error: Number of philosophers must be at least 1\n");
		return (0);
	}
	return (1);
}

int	is_any_philosopher_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
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

int	is_philosopher_dead(t_philo *philo)
{
	long	time;

	time = get_current_time_ms();
	pthread_mutex_lock(&philo->key_mutex);
	if (time - philo->last_eat >= philo->data->life_range)
	{
		pthread_mutex_unlock(&philo->key_mutex);
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
		printf("%li %d %s\n", time - philo->data->start_time, philo->id,
			DIED);
		return (0);
	}
	pthread_mutex_unlock(&philo->key_mutex);
	return (1);
}
