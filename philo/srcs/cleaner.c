/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:49:31 by nkannan           #+#    #+#             */
/*   Updated: 2024/10/19 20:49:35 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lstdelone(t_philo *lst)
{
	if (!lst)
		return ;
	if (lst)
		free(lst);
}

int	destroy_philosophers(t_philo *philo)
{
	t_philo	*first;
	t_philo	*tmp;

	first = philo;
	philo = philo->next;
	while (philo)
	{
		tmp = philo->next;
		if (philo == first)
			break ;
		pthread_mutex_destroy(&philo->fork);
		pthread_mutex_destroy(&philo->key_mutex);
		free(philo);
		philo = tmp;
	}
	return (1);
}
