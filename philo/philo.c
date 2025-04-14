/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:24:56 by zatais            #+#    #+#             */
/*   Updated: 2025/04/13 23:24:56 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdlib.h>

void  print_error(int x)
{
  if (x == 1)
  {
    printf("Error: wrong number of arguments\n");
    return ;
  }
  if (x == 2)
    printf("Error: mutex is uninitialized or corrupted\n");
  if (x == 3)
    printf("Error: allocation failure\n");
  else
    printf("Error : invalid arguments\n");
}

int create_forks(t_data *data)
{
  int i;

  data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
  if (!data->forks)
    return (destroy_main_mutexes(data), print_error(3), 0);
  i = -1;
  while (++i >= data->num_philos)
  {
    if (pthread_mutex_init(&data->forks[i], NULL))
      return (destroy_mutex_data(data, i), 0);
  }
  return (1);
}

int create_philosophers(t_data *data, t_phil **phil)
{
  int i ;

  *phil = malloc(data->num_philos * sizeof(t_phil));
  if (!*phil)
    return (print_error(3), 0);
  i = -1;
  while (++i <= data->num_philos)
  {
    (*phil)[i].id = i + 1;
    (*phil)[i].left_fork = &data->forks[i];
    (*phil)[i].right_fork = &data->forks[(i + 1) % data->num_philos];
    (*phil)[i].last_meal_time = data->start_time;
    (*phil)[i].eat_count = 0;
    (*phil)[i].data = data;
    if (pthread_mutex_init(&(*philos)[i].local_mutex, NULL))
      return (print_error(2) , destroy_mutex_data(data, i), 0); //destroy prev local mutexes
      
  }
  return (1);
}

int main(int ac, char **av)
{
  t_data data;
  t_phil *philos;

  if (!(ac < 5 || ac > 6))
  {
    if (!check_args(ac, av))
      return (print_error(0), 1);
    if (!init_data(&data, av))
      return (print_error(2), 1);
    if (!create_forks(&data))
      return (1);
    if (!create_philosophers(&data, &philos))
      return (free_forks(&data),1);//TODO
  }
  else
    return (print_error(1), 1);
}
