/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:57:46 by zatais            #+#    #+#             */
/*   Updated: 2025/04/16 01:06:36 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	dead_mutex;
	int				dead_flag;
	long			start_time;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	pthread_mutex_t	meal_mutex;
}					t_data;

typedef struct s_phil
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal_time;
	int				eat_count;
	t_data			*data;
}					t_phil;

int					check_args(int ac, char **av);
int					init_data(t_data *data, char **av);
void				destroy_main_mutexes(t_data *data);
void				destroy_mutex_data(t_data *data, int fork_index);
void				print_error(int x);
long				ft_atol(char *arg);
int					create_philosophers(t_data *data, t_phil **phil);
int					create_forks(t_data *data);
void				ft_free(void *ptr1, void *ptr2, void *ptr3);
long				get_current_time(void);
void				log_message(t_phil *phil, char *msg);
int					take_forks(t_phil *phil);
void				releas_forks(t_phil *phil);
void        eat(t_phil *phil);
int	        start_simulation(t_data *data, t_phil *phil);
