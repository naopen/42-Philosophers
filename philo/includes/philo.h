/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:51:44 by nkannan           #+#    #+#             */
/*   Updated: 2024/10/20 03:17:07 by nkannan          ###   ########.fr       */
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
# include <limits.h>

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
int					check_all_finished(t_philo *philo);
int					dead_verify(t_philo *philo);

int					destroy_philosophers(t_philo *philo);

void				eat_utils(t_philo *philo);
int					eat_with_right_fork_first(t_philo *philo);
int					eat_with_left_fork_first(t_philo *philo);

int					init_args(int argc, char **argv, t_philo *philo, t_data *data);
t_philo				*init_chain(t_philo *philo, t_data *data);
int					thread_join(t_philo *philo);


int					ft_lstadd_back(t_philo *lst, t_philo *new);
void				connect_philosophers_in_circle(t_philo *philo);
t_philo				*ft_lstnew(int id, t_data *data);

int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_tolower(int c);
long				ft_atoi(const char *str);
long				ft_strtol(const char *str, char **endptr, int base);

void				*routine(void *lophi);
int					philo_eat(t_philo *philo);
int					philo_sleep(t_philo *philo);
int					philo_think(t_philo *philo);

long				get_current_time_ms(void);
void				on_death(t_philo *philo);
void				wait_for_ms(long time);
void				wait_until_next_action(t_philo *philo);
int					print_action(t_philo *philo, char *str);
void				ft_bzero(void *s, size_t n);

#endif
