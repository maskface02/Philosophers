/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:59:22 by zatais            #+#    #+#             */
/*   Updated: 2025/04/27 16:12:07 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_main_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
}

void	destroy_mutex_data(t_data *data, int start_index)
{
	destroy_main_mutexes(data);
	while (--start_index >= 0)
		pthread_mutex_destroy(&data->forks[start_index]);
}

void	ft_free(void *ptr1, void *ptr2)
{
	free(ptr1);
	free(ptr2);
}

void	clean_destroy_all(t_phil *phil)
{
	destroy_mutex_data(phil->data, phil->data->num_philos);
	ft_free(phil->data->forks, phil, NULL);
}
