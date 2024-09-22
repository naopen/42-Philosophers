/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:57:50 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/22 09:52:42 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (init_mutexes(&data) != 0)
		return (1);
	if (init_forks(&data) != 0)
		return (1);
	if (init_philos(&data) != 0)
		return (1);
	if (create_threads(&data) != 0)
		return (1);
	pthread_t monitor_thread;
	pthread_create(&monitor_thread, NULL, (void *(*)(void *))check_death, &data);
	pthread_detach(monitor_thread);
	i = -1;
	while (++i < data.num_philo)
		pthread_join(data.philos[i].thread, NULL);
	i = -1;
	while (++i < data.num_philo)
		pthread_mutex_destroy(&data.forks[i].mutex);
	pthread_mutex_destroy(&data.output_mutex);
	pthread_mutex_destroy(&data.state_mutex);
	free(data.forks);
	free(data.philos);
	return (0);
}
