/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:53:07 by nkannan           #+#    #+#             */
/*   Updated: 2024/07/22 22:31:30 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (error_exit(data, "Error: Invalid arguments"));
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_must_eat = -1;
	if (argc == 6)
		data->num_must_eat = ft_atoi(argv[5]);
	if (data->num_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || (argc == 6 && data->num_must_eat <= 0))
		return (error_exit(data, "Error: Invalid arguments"));
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_philo);
	if (!data->forks)
		return (error_exit(data, "Error: Malloc failed"));
	i = -1;
	while (++i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (error_exit(data, "Error: Mutex init failed"));
	}
	if (pthread_mutex_init(&data->output_mutex, NULL) != 0)
		return (error_exit(data, "Error: Mutex init failed"));
	if (pthread_mutex_init(&data->state_mutex, NULL) != 0)
		return (error_exit(data, "Error: Mutex init failed"));
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philos)
		return (error_exit(data, "Error: Malloc failed"));
	i = -1;
	while (++i < data->num_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat_time = 0;
		data->philos[i].state = THINKING;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philo];
		data->philos[i].data = data;
	}
	return (0);
}
