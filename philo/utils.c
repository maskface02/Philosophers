/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:46:39 by zatais            #+#    #+#             */
/*   Updated: 2025/04/19 01:23:31 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	log_message(t_phil *phil, char *msg)
{
	t_data	*data;// like this !!
	long	timestamp;

	data = phil->data;// !!
	pthread_mutex_lock(&data->write_mutex);
	if (!is_dead(phil->data))
	{
		timestamp = get_current_time() - data->start_time;
		printf("%ld %d %s\n", timestamp, phil->id, msg);
	}
	pthread_mutex_unlock(&data->write_mutex);
}

int	take_forks(t_phil *phil)
{
	pthread_mutex_lock(phil->first_fork);
	if (is_dead(phil->data))
	{
		pthread_mutex_unlock(phil->first_fork);
		return (0);
	}
	log_message(phil, "has taken a fork");
	pthread_mutex_lock(phil->second_fork);
	if (is_dead(phil->data))
	{
		pthread_mutex_unlock(phil->second_fork);
		pthread_mutex_unlock(phil->first_fork);
		return (0);
	}
	log_message(phil, "has taken a fork");
	return (1);
}

void	eat(t_phil *phil)
{
	pthread_mutex_lock(&phil->data->meal_mutex);
	phil->last_meal_time = get_current_time();
	phil->eat_count++;
	pthread_mutex_unlock(&phil->data->meal_mutex);
	log_message(phil, "is eating");
	if (is_dead(phil->data))
		return ;
	usleep(phil->data->time_to_eat * 1000);
}

void	release_forks(t_phil *phil)
{
	pthread_mutex_unlock(phil->second_fork);
	pthread_mutex_unlock(phil->first_fork);
}
