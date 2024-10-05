/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:46:02 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/23 15:33:27 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*mark_philosopher_full(t_philo *philo)
{
	log_status(philo, MSG_ENOUGH, ENOUGH);
	philo->setup->full_philos++;
	return (NULL);
}

void	*mark_philosopher_dead(t_philo *philo)
{
	if (check_lock(philo, &philo->setup->dead_lock, "mark_as_dead") != 0)
		return ((void *)1);
	if (philo->setup->someone_dead == false) // すでに死亡済みの場合はメッセージを出力しない
	{
		log_status(philo, MSG_DIED, DEAD);
		philo->setup->someone_dead = true;
	}
	pthread_mutex_unlock(&philo->setup->dead_lock);
	pthread_mutex_unlock(&philo->eat_lock);
	release_forks(philo);
	return (philo); // 餓死を検出したらphiloへのポインタを返す
}

void	*philo_check(void *philo_arg)
{
	t_philo		*philo;
	uintmax_t	current_time;

	philo = (t_philo *)philo_arg;
	if (check_lock(philo, &philo->eat_lock, "philo_check") != 0)
		return ((void *)1);
	if (!philo->active)
	{
		pthread_mutex_unlock(&philo->eat_lock);
		return (NULL);
	}
	current_time = get_elapsed_time_ms(0);
	if (current_time > philo->deadline)
	{
		pthread_mutex_unlock(&philo->eat_lock);
		return (mark_philosopher_dead(philo)); // 餓死を検出したらphiloへのポインタを返す
	}
	pthread_mutex_unlock(&philo->eat_lock);
	return (NULL); // 餓死していない場合はNULLを返す
}
