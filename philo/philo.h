/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:57:46 by zatais            #+#    #+#             */
/*   Updated: 2025/04/27 16:00:11 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				must_eat;
	int				dead_flag;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	meal_mutex;
}					t_data;

typedef struct s_phil
{
	int				id;
	int				eat_count;
	t_data			*data;
	long			meal_time;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
}					t_phil;

void				eat(t_phil *phil);
void				print_error(int x);
long				ft_atol(char *arg);
int					is_dead(t_data *data);
long				get_current_time(void);
int					take_forks(t_phil *phil);
int					create_forks(t_data *data);
void				release_forks(t_phil *phil);
void				set_dead_flag(t_data *data);
int					check_args(int ac, char **av);
int					start_simulation(t_phil *phil);
void				clean_destroy_all(t_phil *phil);
int					init_data(t_data *data, char **av);
void				destroy_main_mutexes(t_data *data);
void				log_message(t_phil *phil, char *msg);
void				ft_free(void *ptr1, void *ptr2, void *ptr3);
int					init_philosophers(t_data *data, t_phil **phil);
int					check_dead(t_phil *phil, long last_meal, int i);
void				destroy_mutex_data(t_data *data, int fork_index);
void				set_meal(long *meal_time, int *eat_count, t_phil *phil,
						int i);
#endif
