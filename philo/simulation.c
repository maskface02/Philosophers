/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:15:51 by zatais            #+#    #+#             */
/*   Updated: 2025/04/14 18:15:51 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
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
	pthread_t	*threads;
	pthread_t	monitor;
	int			i;

	threads = malloc(data->num_philos * sizeof(pthread_t));
	if (!threads)
		return (print_error(3), 0);
	while (++i < data->num_philos)
	{
		if (pthread_create(&threads[i], NULL, philo_routine, &phil[i]))
		{
			// TODO
			return (print_error(4), 0);
		}
	}
	if (pthread_create(&monitor, NULL, monitor_routine, &data))
	{
		// TODO
		return (print_error(4), 0);
	}
	i = -1;
	while (++i < data->num_philos)
		pthread_join(threads[i], NULL);
	pthread_join(monitor, NULL);
	free(threads);
	return (1);
}
