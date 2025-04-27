/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:53:20 by zatais            #+#    #+#             */
/*   Updated: 2025/04/27 16:01:59 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_dead_flag(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	data->dead_flag = 1;
	pthread_mutex_unlock(&data->dead_mutex);
}

int	is_dead(t_data *data)
{
	int	is_dead;

	pthread_mutex_lock(&data->dead_mutex);
	is_dead = data->dead_flag;
	pthread_mutex_unlock(&data->dead_mutex);
	return (is_dead);
}

void	set_meal(long *last_meal, long *eat_count, t_phil *phil, int i)
{
	pthread_mutex_lock(&phil->data->meal_mutex);
	*last_meal = phil[i].last_meal_time;
	*eat_count = phil[i].eat_count;
	pthread_mutex_unlock(&phil->data->meal_mutex);
}
