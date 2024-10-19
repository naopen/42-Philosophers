/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:51:44 by nkannan           #+#    #+#             */
/*   Updated: 2024/10/19 20:58:06 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define FIRST 1
# define SECOND 2
# define FORK "has taken a fork"
# define THINK "is thinking"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define DIED "died"

struct	s_data;

typedef struct s_philo
{
	int				id;
	int				ate;
	long			last_eat;
	pthread_t		pid;
	int				nb_meals;
	struct s_philo	*next;
	pthread_mutex_t	fork;
	pthread_mutex_t	key_mutex;
	struct s_data	*data;

}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	long			life_range;
	long			eat_time;
	long			sleep_time;
	long			start_time;
	int				is_dead;
	int				end_philo;
	pthread_mutex_t	all_finished;
	pthread_mutex_t	smn_died;
	int				argc;
	char			**argv;
}					t_data;


int					check_argv(char **argv);
int					check_dead(t_philo *philo);
int					check_finished(t_philo *philo);
int					dead_verif(t_philo *philo);

int					destroy_philosophers(t_philo *philo);

void				eat_utils(t_philo *philo);
int					if_eat(t_philo *philo);
int					else_eat(t_philo *philo);

int					init_args(int argc, char **argv, t_philo *philo, t_data *data);
t_philo				*init_chain(t_philo *philo, t_data *data);
int					thread_join(t_philo *philo);


int					ft_lstadd_back(t_philo *lst, t_philo *new);
void				create_circular(t_philo *philo);
t_philo				*ft_lstnew(int id, t_data *data);

int					ft_isdigit(int c);
int					ft_atoi(char *str);

void				*routine(void *lophi);
int					philo_eat(t_philo *philo);
int					philo_sleep(t_philo *philo);
int					philo_think(t_philo *philo);

long				time_get(void);
void				one_died(t_philo *philo);
void				waiter(long time);
void				waiter_white(t_philo *philo);
int					print_action(t_philo *philo, char *str);

#endif
