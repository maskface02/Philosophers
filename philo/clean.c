/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:59:22 by zatais            #+#    #+#             */
/*   Updated: 2025/04/14 14:59:22 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void  destroy_main_mutexes(t_data *data)
{
  pthread_mutex_destroy(&data->write_mutex);
  pthread_mutex_destroy(&data->helper_mutex);
  pthread_mutex_destroy(&data->dead_mutex);
}

void  destroy_mutex_data(t_data *data, int start_index)
{
  destroy_main_mutexes(data);
  while (--start_index >= 0)
    pthread_mutex_destroy(&data->forks[start_index]);
}

void destroy_lmutex(t_phil **phil, int start_index)
{
  while (--start_index >= 0)
    pthread_mutex_destroy(&(*phil)[i].local_mutex);
}
void destroy_all(t_data *data, t_phil *phil, int start)
{
  destroy_mutex_data(data, start);
  destroy_lmutex(&phil, start);
}

void  ft_free(void *ptr1, void *ptr2, void *ptr3)
{
  if (ptr3)
    free(ptr3);
  free(ptr1);
  free(ptr2);
}
