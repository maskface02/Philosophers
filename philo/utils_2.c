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

void	set_meal(long *meal_time, int *eat_count, t_phil *phil, int i)
{
	pthread_mutex_lock(&phil->data->meal_mutex);
	*meal_time = phil[i].meal_time;
	*eat_count = phil[i].eat_count;
	pthread_mutex_unlock(&phil->data->meal_mutex);
}

void	death_log_message(t_phil *phil, char *msg)
{
	long	timestamp;
	t_data	*data;

	data = phil->data;
	pthread_mutex_lock(&data->write_mutex);
	timestamp = get_current_time() - data->start_time;
	printf("%ld %d %s\n", timestamp, phil->id, msg);
	pthread_mutex_unlock(&data->write_mutex);
}

int	check_death(t_phil *phil, long last_meal, int i)
{
	if ((get_current_time() - last_meal) >= phil->data->time_to_die)
	{
		set_dead_flag(phil->data);
		death_log_message(&phil[i], "died");
		return (1);
	}
	return (0);
}
