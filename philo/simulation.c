/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:15:51 by zatais            #+#    #+#             */
/*   Updated: 2025/04/19 01:34:49 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo_routine(t_phil *phil)
{
	log_message(phil, "has taken a fork");
	usleep(phil->data->time_to_sleep * 1000);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	phil->last_meal_time = get_current_time();
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
		if (phil->data->dead_flag || ((phil->data->must_eat != -1)
				&& (phil->eat_count >= phil->data->must_eat)))
			break ;
		log_message(phil, "is sleeping");
		if (phil->data->dead_flag)
			break ;
		usleep(phil->data->time_to_sleep * 1000);
		log_message(phil, "is thinking");
	}
	return (NULL);
}

void	monitor(t_phil *phil)
{
	t_data	*data;
	int		all_ate_enough;
	int		i;
	long	last_meal;
	int		eat_count;

	data = phil->data;
	while (1)
	{
		all_ate_enough = 1;
		i = -1;
		while (++i < data->num_philos)
		{
			pthread_mutex_lock(&phil[i].meal_mutex);
			last_meal = phil[i].last_meal_time;
			pthread_mutex_unlock(&phil[i].meal_mutex);
			if ((get_current_time() - last_meal) > data->time_to_die)
			{
				pthread_mutex_lock(&data->dead_mutex);
				if (!data->dead_flag)
				{
					pthread_mutex_lock(&data->write_mutex);
					printf("%ld %d died\n", get_current_time()
						- data->start_time, phil[i].id);
					pthread_mutex_unlock(&data->write_mutex);
			    pthread_mutex_lock(&data->dead_mutex);
			    data->dead_flag = 1;
		    	pthread_mutex_unlock(&data->dead_mutex);
				}
				pthread_mutex_unlock(&data->dead_mutex);
				return ;
			}
			pthread_mutex_lock(&phil[i].meal_mutex);
			eat_count = phil[i].eat_count;
			pthread_mutex_unlock(&phil[i].meal_mutex);
			if (data->must_eat != -1 && eat_count < data->must_eat)
				all_ate_enough = 0;
		}
		if (all_ate_enough && data->must_eat != -1)
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			return ;
		}
		usleep(1000);
	}
}

int	start_simulation(t_phil *phil)
{
	pthread_t *(threads);
	int(i) = -1;
	threads = malloc(phil->data->num_philos * sizeof(pthread_t));
	if (!threads)
		return (print_error(3), 0);
	phil->data->start_time = get_current_time();
	while (++i < phil->data->num_philos)
	{
		if (pthread_create(&threads[i], NULL, philo_routine, &phil[i]))
		{
			clean_destroy_all(phil);
			return (ft_free(phil->data->forks, phil, threads), print_error(4),
				0);
		}
	}
	usleep(1500);
	monitor(phil);
	i = -1;
	while (++i < phil->data->num_philos)
		pthread_join(threads[i], NULL);
	free(threads);
	return (1);
}
