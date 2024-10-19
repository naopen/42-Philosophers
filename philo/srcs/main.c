/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:57:50 by nkannan           #+#    #+#             */
/*   Updated: 2024/10/19 20:46:12 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *lophi)
{
	t_philo	*philo;

	philo = (t_philo *)lophi;
	if (philo->id % 2 == 0)
		waiter(100);
	while (1)
	{
		if (!check_dead(philo))
			break ;
		if (!philo_eat(philo))
			break ;
		if (!sleepy(philo))
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
		if (!dead_verif(philo))
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

	bzero(&data, sizeof(t_data));
	bzero(&philo, sizeof(t_philo));
	if (!(argc == 5 || argc == 6))
		return (write(2, "Error\nWrong number of arguments\n", 32), 0);
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
