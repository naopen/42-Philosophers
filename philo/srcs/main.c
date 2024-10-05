/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:55:16 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/23 15:33:11 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start_philo_threads(t_setup *setup, t_philo *philos)
{
	int			i;
    pthread_t   monitor_thread;

	pthread_mutex_lock(&setup->dead_lock);
	setup->program_start_ms = get_elapsed_time_ms(0);
	pthread_mutex_unlock(&setup->dead_lock);
	i = 0;
	while (i < setup->num_philo)
	{
		if (pthread_create(&philos[i].id, NULL, &philo_routine,
				&philos[i]) != 0)
			return (1);
		i++;
	}
    // 全ての哲学者のスレッド生成後に、監視スレッドを起動
    if (pthread_create(&monitor_thread, NULL, &monitor_philosophers, &setup) != 0)
        return (1);

    // スレッド作成後、一定時間待機
    usleep(100 * setup->num_philo);

	i = 0;
	while (i < setup->num_philo)
	{
		if (pthread_join(philos[i].id, NULL) != 0)
		{
			fprintf(stderr, "Error joining thread %d\n", i);
			return (1);
		}
		i++;
        // usleepをここに移動
        usleep(1000);
	}
    // 監視スレッドの終了を待つ
    if (pthread_join(monitor_thread, NULL) != 0)
    {
        fprintf(stderr, "Error joining monitor thread\n");
        return (1);
    }
	return (0);
}

// 監視スレッドの関数
void *monitor_philosophers(void *setup_arg)
{
    t_setup *setup = (t_setup *)setup_arg;
    t_philo *philos = setup->philos;
    int i;

    while (1)
    {
        i = 0;
        // 全ての哲学者の状態をチェック
        while (i < setup->num_philo)
        {
            // philo_checkの戻り値をチェックし、餓死を検出したらループを抜ける
            if (philo_check(&philos[i]) != NULL)
                break ;
            i++;
        }

        // 餓死または全員満腹になったらループを抜ける
        if (setup->someone_dead || setup->full_philos == setup->num_philo)
            break;

        usleep(1000);
    }
    return (NULL);
}

int	main(int argc, char **argv)
{
	t_setup	setup;
	t_philo	*philos;

	if (argc > 4 && argc < 7)
	{
		init_setup(&setup);
		if (parse_setup_args(&setup, (const char **)(argv + 1)))
			return (print_error(ERR_SETUP) | clean_exit(&setup, NULL));
		if (init_philos_and_mutexes(&setup, &philos))
			return (print_error(ERR_GEN) | clean_exit(&setup, &philos));
		if (start_philo_threads(&setup, philos))
			return (print_error(ERR_GEN) | clean_exit(&setup, &philos));
		clean_exit(&setup, &philos);
	}
	return (0);
}
