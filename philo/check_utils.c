#include "philo.h" 
#include <pthread.h>


long	ft_atol(char *arg)
{
	int		sign;
	long	res;

	sign = 1;
	if (*arg == '-' || *arg == '+')
	{
		if (*arg == '-')
			sign *= -1;
		arg++;
	}
	res = 0;
	while (*arg >= '0' && *arg <= '9')
	{
		res = (res * 10) + (*arg - 48);
		if ((res * sign) > INT_MAX || (res * sign) < INT_MIN)
			return (LONG_MAX);
		arg++;
	}
	return (res * sign);
}

int is_num(char *arg)
{
  int i;

  i = 0;
  if (arg[i] == '+')
    ++i;
  while (arg[i])
  {
    if (!(arg[i] >= '0' && arg[i] <= '9'))
      return (0);
    i++;
  }
  if (ft_atol(arg) == LONG_MAX || ft_atol(arg) < 0)
    return (0);
  return (1);
}

int check_args(int ac, char **av)
{
  while (--ac >= 0)
    if (!is_num(av[ac]))
      return (0);
  return (1);
}
long get_current_time()
{
  struct timeval time;
  gettimeofday(&time, NULL);
  return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
int init_data(t_data *data, char **av)
{
  data->num_philos = ft_atol(av[1]);
  data->time_to_die = ft_atol(av[2]);
  data->time_to_eat = ft_atol(av[3]);
  data->time_to_sleep = ft_atol(av[4]);
  if (av[5])
    data->must_eat = ft_atol(av[5]);
  else
    data->must_eat = -1;
  data->dead_flag = 0;
  if (pthread_mutex_init(&data->write_mutex, NULL))
    return (0);
  if (pthread_mutex_init(&data->helper_mutex, NULL))
    return (pthread_mutex_destroy(&data->write_mutex), 0);
  if (pthread_mutex_init(&data->dead_mutex, NULL))
  {
    pthread_mutex_destroy(&data->write_mutex);
    pthread_mutex_destroy(&data->helper_mutex);
    return (0);
  }
  data->start_time = get_current_time();
  return (1);
}

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

