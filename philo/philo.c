/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:35:56 by zatais            #+#    #+#             */
/*   Updated: 2025/04/18 22:10:40 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(int x)
{
	if (x == 1)
		printf("Error: wrong number of arguments\n");
	if (x == 2)
		printf("Error: mutex is uninitialized or corrupted\n");
	if (x == 3)
		printf("Error: allocation failure\n");
  if (x == 4)
	  printf("Error: unable to create a Thread\n");
	else
		printf("Error : invalid arguments\n");
}

int	main(int ac, char **av)
{
	t_data	data;
	t_phil	*philos;

	if (!(ac < 5 || ac > 6))
	{
		if (!check_args(ac, av))
			return (print_error(0), 1);
		if (!init_data(&data, av))
			return (print_error(2), 1);
		if (!create_forks(&data))
			return (1);
		if (!init_philosophers(data , &philos))
			return (1);
    if (!start_simulation(philos))
      return (1);
    clean_destroy_all(philos);
	}
	else
		return (print_error(1), 1);
}
