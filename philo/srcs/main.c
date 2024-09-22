/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:55:16 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/23 01:55:16 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start_philo_threads(t_setup *setup, t_philo *philos)
{
	int			i;

	setup->program_start_ms = get_elapsed_time_ms(0);
	i = 0;
	i = 0;
	while (i < setup->num_philo)
	{
		if (pthread_create(&philos[i].id, NULL, &philo_routine,
				&philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < setup->num_philo)
	{
		if (pthread_join(philos[i].id, NULL) != 0)
		{
			fprintf(stderr, "Error joining thread %d\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_setup	setup;
	t_philo	*philos;

	if (argc > 4 && argc < 7)
	{
		init_setup(&setup);
		if (parse_setup_args(&setup, (const char **)(argv + 1)))
			return (print_error(ERR_SETUP) | clean_exit(&setup, NULL));
		if (init_philos_and_mutexes(&setup, &philos))
			return (print_error(ERR_GEN) | clean_exit(&setup, &philos));
		if (start_philo_threads(&setup, philos))
			return (print_error(ERR_GEN) | clean_exit(&setup, &philos));
		clean_exit(&setup, &philos);
	}
	return (0);
}
