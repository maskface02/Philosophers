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
	t_data	*data;
	long	timestamp;
	int		is_dead;

	data = phil->data;
	pthread_mutex_lock(&data->dead_mutex);
	is_dead = data->dead_flag;
	pthread_mutex_unlock(&data->dead_mutex);
	pthread_mutex_lock(&data->write_mutex);
	timestamp = get_current_time() - data->start_time;
  if (!is_dead)
	  printf("%ld %d %s\n", timestamp, phil->id, msg);
	pthread_mutex_unlock(&data->write_mutex);
}

int	take_forks(t_phil *phil)
{
	int	is_dead;

	pthread_mutex_lock(phil->left_fork);
	pthread_mutex_lock(&phil->data->dead_mutex);
	is_dead = phil->data->dead_flag;
	pthread_mutex_unlock(&phil->data->dead_mutex);
	if (is_dead)
	{
		pthread_mutex_unlock(phil->left_fork);
		return (0);
	}
	log_message(phil, "has taken a fork");
	pthread_mutex_lock(phil->right_fork);
	pthread_mutex_lock(&phil->data->dead_mutex);
	is_dead = phil->data->dead_flag;
	pthread_mutex_unlock(&phil->data->dead_mutex);
	if (is_dead)
	{
		pthread_mutex_unlock(phil->right_fork);
		pthread_mutex_unlock(phil->left_fork);
		return (0);
	}
	log_message(phil, "has taken a fork");
	return (1);
}

void	eat(t_phil *phil)
{
  int is_dead;

	pthread_mutex_lock(&phil->meal_mutex);
	phil->last_meal_time = get_current_time();
	phil->eat_count++;
	pthread_mutex_unlock(&phil->meal_mutex);
  pthread_mutex_lock(&phil->data->dead_mutex);
	is_dead = phil->data->dead_flag;
	pthread_mutex_unlock(&phil->data->dead_mutex);
  if (!is_dead)
	  log_message(phil, "is eating");
	if (phil->data->dead_flag)
	usleep(phil->data->time_to_eat * 1000);
}

void	release_forks(t_phil *phil)
{
	pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(phil->right_fork);
}
