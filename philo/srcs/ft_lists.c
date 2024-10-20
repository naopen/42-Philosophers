/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 21:30:00 by nkannan           #+#    #+#             */
/*   Updated: 2024/10/20 14:41:21 by nkannan          ###   ########.fr       */
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
	res->last_eat = get_current_time_ms();
	res->id = id;
	res->next = NULL;
	if (res->data->argc == 6)
		res->nb_meals = ft_atoi(data->argv[4]);
	return (res);
}

void	connect_philosophers_in_circle(t_philo *philo)
{
	t_philo	*first;

	first = philo;
	while (philo->next)
		philo = philo->next;
	philo->next = first;
}

t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_philo	*ft_lstfirst(t_philo *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_lstadd_back(t_philo *lst, t_philo *new)
{
	if (!lst || !new)
		return (0);
	ft_lstlast(lst)->next = new;
	return (1);
}
