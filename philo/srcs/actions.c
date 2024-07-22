/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:56:16 by nkannan           #+#    #+#             */
/*   Updated: 2024/07/22 22:56:11 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->is_finished)
	{
		print_action(philo, THINKING);
		philo_take_forks(philo);
		if (philo->data->is_finished)
			break ;
		philo_eat(philo);
		if (philo->data->is_finished)
			break ;
		philo_sleep(philo);
		if (philo->data->is_finished)
			break ;
	}
	return (NULL);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philo)
	{
		data->philos[i].last_eat_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, philosopher_routine,
				&data->philos[i]) != 0)
			return (error_exit(data, "Error: Thread creation failed"));
		i++;
	}
	return (0);
}

void	philo_take_forks(t_philo *philo)
{
	if (philo->left_fork->owner_id == philo->id)
	{
		request_fork(philo, philo->right_fork);
		if (philo->data->is_finished)
			return ;
		request_fork(philo, philo->left_fork);
		if (philo->data->is_finished)
			return ;
	}
	else
	{
		request_fork(philo, philo->left_fork);
		if (philo->data->is_finished)
			return ;
		request_fork(philo, philo->right_fork);
		if (philo->data->is_finished)
			return ;
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	philo->state = EATING;
	pthread_mutex_unlock(&philo->data->state_mutex);
	print_action(philo, EATING);
	philo->last_eat_time = get_time();
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->is_dirty = true;
	philo->left_fork->owner_id = -1;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->is_dirty = true;
	philo->right_fork->owner_id = -1;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_lock(&philo->data->state_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->state_mutex);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->data->state_mutex);
	print_action(philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
}

void	request_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->is_dirty)
	{
		fork->is_dirty = false;
		fork->owner_id = philo->id;
		pthread_mutex_unlock(&fork->mutex);
		print_action(philo, HAS_FORK);
	}
	else
	{
		pthread_mutex_unlock(&fork->mutex);
		usleep(100);
		if (!philo->data->is_finished)
			request_fork(philo, fork);
	}
}
