/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:51:44 by nkannan           #+#    #+#             */
/*   Updated: 2024/07/20 23:07:29 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_eat_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				is_finished;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	output_mutex;
	t_philo			*philos;
}					t_data;

// utils.c
long long			get_time(void);
int					ft_atoi(const char *str);
int					error_exit(t_data *data, char *message);

// init.c
int					init_data(t_data *data, int argc, char **argv);
int					init_mutexes(t_data *data);
int					init_philos(t_data *data);

// actions.c
void				*philosopher_routine(void *arg);
int					create_threads(t_data *data);

// actions_eat.c
void				philo_take_forks(t_philo *philo, t_data *data);
void				philo_eat(t_philo *philo, t_data *data);

// monitoring.c
int					check_death(t_data *data);
int					check_eat_count(t_data *data);

#endif