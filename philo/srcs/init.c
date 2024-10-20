/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:53:07 by nkannan           #+#    #+#             */
/*   Updated: 2024/10/20 03:10:42 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_first(t_philo *philo, t_data *data)
{
	if (pthread_mutex_init(&(philo->fork), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(philo->key_mutex), NULL) != 0)
		return (0);
	philo->data = data;
	philo->ate = 0;
	philo->id = 1;
	philo->last_eat = get_current_time_ms();
	philo->next = NULL;
	if (philo->data->argc == 6)
		philo->nb_meals = ft_atoi(data->argv[4]);
	return (1);
}

t_philo	*init_chain(t_philo *philo, t_data *data)
{
	int	i;

	if (!init_first(philo, data))
		return (NULL);
	i = 2;
	while (i <= data->nb_philo)
	{
		if (!ft_lstadd_back(philo, ft_lstnew(i, data)))
			return (NULL);
		i++;
	}
	connect_philosophers_in_circle(philo);
	return (philo);
}

t_data	*init_philo(int argc, char **argv, t_data *data)
{
	data->nb_philo = ft_atoi(argv[0]);
	data->life_range = ft_atoi(argv[1]);
	data->eat_time = ft_atoi(argv[2]);
	data->sleep_time = ft_atoi(argv[3]);
	data->is_dead = 0;
	data->start_time = get_current_time_ms();
	data->end_philo = 0;
	data->argc = argc;
	data->argv = argv;
	pthread_mutex_init(&data->all_finished, NULL);
	return (data);
}

int	init_args(int argc, char **argv, t_philo *philo, t_data *data)
{
	t_philo	*tmp;

	data = init_philo(argc, argv, data);
	philo = init_chain(philo, data);
	tmp = philo;
	while (tmp)
	{
		if (pthread_create(&(tmp->pid), NULL, routine, tmp) == -1)
			return (destroy_philosophers(philo), 0);
		tmp = tmp->next;
		if (tmp == philo)
			break ;
	}
	return (1);
}

int	thread_join(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp)
	{
		if (pthread_join(tmp->pid, NULL) != 0)
			return (0);
		tmp = tmp->next;
		if (tmp == philo)
			break ;
	}
	return (1);
}
