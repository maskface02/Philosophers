/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:36:43 by zatais            #+#    #+#             */
/*   Updated: 2025/04/18 23:12:55 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	init_data(t_data *data, char **av)
{
	data->num_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->must_eat = ft_atol(av[5]);
	else
		data->must_eat = -1;
	data->dead_flag = 0;
	if (pthread_mutex_init(&data->write_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&data->meal_mutex, NULL))
		return (pthread_mutex_destroy(&data->write_mutex), 0);
	return (1);
}

int	init_philosophers(t_data data, t_phil **phil)
{
	int	i;

	*phil = malloc(data.num_philos * sizeof(t_phil));
	if (!*phil)
		return (print_error(3), 0);
	i = -1;
	while (++i < data.num_philos)
	{
		(*phil)[i].id = i + 1;
		(*phil)[i].left_fork = &data.forks[i];
		(*phil)[i].right_fork = &data.forks[(i + 1) % data.num_philos];
		(*phil)[i].last_meal_time = data.start_time;
		(*phil)[i].eat_count = 0;
		(*phil)[i].data = &data;
	}
	return (1);
}

int	create_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (destroy_main_mutexes(data), print_error(3), 0);
	i = -1;
	while (++i < data->num_philos)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (destroy_mutex_data(data, i), 0);
	return (1);
}
