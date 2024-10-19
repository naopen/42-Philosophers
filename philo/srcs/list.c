/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:49:44 by nkannan           #+#    #+#             */
/*   Updated: 2024/10/19 20:49:47 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstnew(int id, t_data *data)
{
	t_philo	*res;

	res = malloc(sizeof(t_philo));
	if (!res)
		return (NULL);
	res->data = data;
	if (pthread_mutex_init(&(res->fork), NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&(res->key_mutex), NULL) != 0)
		return (NULL);
	res->ate = 0;
	res->last_eat = time_get();
	res->id = id;
	res->next = NULL;
	if (res->data->argc == 6)
		res->nb_meals = ft_atoi(data->argv[4]);
	return (res);
}

void	create_circular(t_philo *philo)
{
	t_philo	*first;

	first = philo;
	while (philo->next)
		philo = philo->next;
	philo->next = first;
}
