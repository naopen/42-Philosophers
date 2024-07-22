/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:51:44 by nkannan           #+#    #+#             */
/*   Updated: 2024/07/22 22:30:17 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define DEAD 3
# define HAS_FORK 1

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					num_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_must_eat;
	long long			start_time;
	bool				is_finished;
	pthread_mutex_t		*forks;
	pthread_mutex_t		output_mutex;
	pthread_mutex_t		state_mutex;
	t_philo				*philos;
}						t_data;

typedef struct s_philo
{
	int					id;
	long long			last_eat_time;
	int					eat_count;
	int					state;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
}						t_philo;

// utils.c
int						error_exit(t_data *data, char *message);
long long				get_time(void);
int						ft_atoi(const char *str);

// init.c
int						init_data(t_data *data, int argc, char **argv);
int						init_mutexes(t_data *data);
int						init_philos(t_data *data);

// actions.c
void					*philosopher_routine(void *arg);
int						create_threads(t_data *data);
void					philo_take_forks(t_philo *philo);
void					philo_eat(t_philo *philo);
void					philo_sleep(t_philo *philo);

// monitoring.c
int						check_death(t_data *data);
int						check_eat_count(t_data *data);
void					print_action(t_philo *philo, int action);

#endif
