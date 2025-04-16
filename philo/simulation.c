/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:15:51 by zatais            #+#    #+#             */
/*   Updated: 2025/04/16 01:07:49 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo_routine(t_phil *phil)
{
	log_message(phil, "has taken a fork\n");
	usleep(phil->data->time_to_sleep * 1000);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	if (phil->data->num_philos == 1)
		return (one_philo_routine(phil));
  if (phil->id % 2)
		usleep(1000);
	while (1)
	{
		if (!take_forks(phil))
      break;
		eat(phil);
    if (phil->data->dead_flag)
    {
      releas_forks(phil);
      break;
    }
		releas_forks(phil);
		log_message(phil, "is sleeping\n");
    if (phil->data->dead_flag)
      break;
		usleep(phil->data->time_to_sleep * 1000);
		log_message(phil, "is thinking\n");
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	return (NULL);
}

int	start_simulation(t_data *data, t_phil *phil)
{
	pthread_t *(threads), (monitor);
	int(i) = -1;
	threads = malloc(data->num_philos * sizeof(pthread_t));
	if (!threads)
		return (print_error(3), 0);
	while (++i < data->num_philos)
	{
		if (pthread_create(&threads[i], NULL, philo_routine, &phil[i]))
		{
			destroy_mutex_data(data, data->num_philos);
			return (ft_free(data->forks, phil, threads), print_error(4), 0);
		}
	}
	if (pthread_create(&monitor, NULL, monitor_routine, &data))
	{
    destroy_mutex_data(data, data->num_philos);
		return (ft_free(data->forks, phil, threads), print_error(4), 0);
	}
	i = -1;
	while (++i < data->num_philos)
		pthread_join(threads[i], NULL);
	pthread_join(monitor, NULL);
	free(threads);
	return (1);
}
