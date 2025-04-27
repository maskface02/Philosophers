/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:15:51 by zatais            #+#    #+#             */
/*   Updated: 2025/04/27 16:38:45 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo_routine(t_phil *phil)
{
	log_message(phil, "has taken a fork");
	while (!is_dead(phil->data))
		usleep(1000);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	pthread_mutex_lock(&phil->data->meal_mutex);
	phil->last_meal_time = get_current_time();
	pthread_mutex_unlock(&phil->data->meal_mutex);
	if (phil->data->num_philos == 1)
		return (one_philo_routine(phil));
	if (phil->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (!take_forks(phil))
			break ;
		eat(phil);
		release_forks(phil);
		if (is_dead(phil->data) || (phil->data->must_eat != -1
				&& phil->eat_count >= phil->data->must_eat))
			break ;
		log_message(phil, "is sleeping");
		usleep(phil->data->time_to_sleep * 1000);
		log_message(phil, "is thinking");
		usleep(phil->data->time_to_think * 1000);
	}
	return (NULL);
}

void	monitor(t_phil *phil)
{
	long (last_meal), (eat_count), (all_ate_enough), (i);
	while (!is_dead(phil->data))
	{
		all_ate_enough = 1;
		i = -1;
		while (++i < phil->data->num_philos)
		{
			set_meal(&last_meal, &eat_count, phil, i);
			if ((get_current_time() - last_meal) > phil->data->time_to_die)
			{
				log_message(&phil[i], "died");
				set_dead_flag(phil->data);
				break ;
			}
			if (phil->data->must_eat != -1 && eat_count < phil->data->must_eat)
				all_ate_enough = 0;
		}
		if (phil->data->must_eat != -1 && all_ate_enough)
		{
			set_dead_flag(phil->data);
			break ;
		}
		usleep(1000);
	}
}

int	start_simulation(t_phil *phil)
{
	pthread_t *(threads);
	int (i) = -1;
	threads = malloc(phil->data->num_philos * sizeof(pthread_t));
	if (!threads)
		return (print_error(3), 0);
	phil->data->start_time = get_current_time();
	while (++i < phil->data->num_philos)
	{
		if (pthread_create(&threads[i], NULL, philo_routine, &phil[i]))
			return (clean_destroy_all(phil), print_error(4), 0);
	}
	usleep(1000);
	monitor(phil);
	i = -1;
	while (++i < phil->data->num_philos)
		if (pthread_join(threads[i], NULL))
			return (clean_destroy_all(phil), print_error(5), 0);
	free(threads);
	return (1);
}
