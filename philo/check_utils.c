/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:26:52 by zatais            #+#    #+#             */
/*   Updated: 2025/04/14 14:34:15 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	is_num(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+')
		++i;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			return (0);
		i++;
	}
	if (ft_atol(arg) == LONG_MAX || ft_atol(arg) <= 0)
		return (0);
	return (1);
}

int	check_args(int ac, char **av)
{
	while (--ac >= 0)
		if (!is_num(av[ac]))
			return (0);
	return (1);
}
