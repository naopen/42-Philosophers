/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:49:30 by nkannan           #+#    #+#             */
/*   Updated: 2024/09/23 01:49:30 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	valid_setup(t_setup *setup)
{
	if (setup->num_philo < 1 || setup->num_philo > 200
		|| setup->msec_to_die < 60
		|| setup->msec_to_eat < 60
		|| setup->msec_to_sleep < 60
		|| setup->must_eat < 0)
		return (false);
	return (true);
}

int	fill_setup(t_setup *setup, int *converted_args)
{
	setup->num_philo = converted_args[0];
	setup->msec_to_die = converted_args[1];
	setup->msec_to_eat = converted_args[2];
	setup->msec_to_sleep = converted_args[3];
	setup->must_eat = converted_args[4];
	return (0);
}

int	parse_setup_args(t_setup *setup, const char **args)
{
	int	i;
	int	converted_args[5];

	i = 0;
	while (args[i] != NULL)
	{
		converted_args[i] = 0;
		if (!str_to_int_safe(args[i], &converted_args[i]))
			return (1);
		i++;
	}
	if (i == 4)
		converted_args[4] = 0;
	if (fill_setup(setup, converted_args))
		return (1);
	if (!valid_setup(setup))
		return (1);
	return (0);
}
