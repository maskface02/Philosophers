/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:57:46 by zatais            #+#    #+#             */
/*   Updated: 2025/04/13 22:57:46 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>

typedef struct s_data {
    pthread_mutex_t *forks;
    pthread_mutex_t write_mutex;
    pthread_mutex_t dead_mutex;
    int dead_flag;
    long start_time;
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    pthread_mutex_t helper_mutex;
} t_data;

typedef struct s_phil {
    int id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long last_meal_time;
    int eat_count;
    pthread_mutex_t local_mutex;
    t_data *data;
} t_phil;

int check_args(int ac, char **av);
int init_data(t_data *data, char **av);
void  destroy_main_mutexes(t_data *data);
void  destroy_mutex_data(t_data *data, int fork_index);
