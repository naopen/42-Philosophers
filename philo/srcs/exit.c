/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:46:08 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/23 01:46:08 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	print_error(const char *message)
{
	if (message)
		write(STDERR_FILENO, message, ft_strlen(message));
	return (1);
}

int	clean_exit(t_setup *setup, t_philo **philos)
{
	int	i;

	i = 0;
	if (setup != NULL)
	{
		pthread_mutex_destroy(&setup->msg_lock);
		pthread_mutex_destroy(&setup->dead_lock);
	}
	if (philos != NULL && setup->initialized.philos_init)
	{
		while (i < setup->num_philo)
		{
			pthread_mutex_destroy(&((*philos)[i].eat_lock));
			pthread_mutex_destroy(((*philos)[i].p_forks[LEFT]));
			i++;
		}
		free(*philos);
	}
	if (setup->initialized.fork_init)
		free(setup->forks);
	return (0);
}
