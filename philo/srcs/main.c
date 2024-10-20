/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:57:50 by nkannan           #+#    #+#             */
/*   Updated: 2024/10/20 14:42:47 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	if (philo->id % 2 == 0)
		wait_for_ms(100);
	while (1)
	{
		if (!is_any_philosopher_dead(philo))
			break ;
		if (!philo_eat(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
		if (!philo_think(philo))
			break ;
	}
	return (0);
}

int	monitoring(t_philo *philo)
{
	t_philo	*first;
	int		i;

	first = philo;
	i = 1;
	while (philo)
	{
		pthread_mutex_lock(&philo->key_mutex);
		if (philo->nb_meals == 0 && philo->data->argc == 6)
			i++;
		pthread_mutex_unlock(&philo->key_mutex);
		if (!is_philosopher_dead(philo))
			return (0);
		philo = philo->next;
		if (i == philo->data->nb_philo && philo->data->argc == 6)
			return (0);
		if (first == philo)
			break ;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	philo;

	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&philo, sizeof(t_philo));
	if (!(argc == 5 || argc == 6))
		return (write(2, "Error: Wrong number of arguments\n", 33), 0);
	if (!check_argv(argv + 1))
		return (0);
	if (!init_args(argc, argv + 1, &philo, &data))
		return (0);
	while (1)
	{
		if (!monitoring(&philo))
			break ;
	}
	if (!thread_join(&philo))
		return (0);
	destroy_philosophers(&philo);
	return (0);
}
