/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:21:35 by tlay              #+#    #+#             */
/*   Updated: 2025/03/26 18:21:49 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	parsing_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (print_error("Non-digit character"), false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	parsing_limit(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (ft_atoi(av[i]) < 0)
			return (print_error("Negative value"), false);
		else if (ft_atoi(av[1]) > 200)
			return (print_error("Too many philosophers. Maximum is 200"),
				false);
		else if (ft_atoi(av[i]) > 2147483647)
			return (print_error("Value cannot exceed int max"), false);
		else if (av[5])
		{
			if (ft_atoi(av[5]) == 0)
				return (print_error("Number of times each philosopher must eat"
									" cannot be 0"),
						false);
		}
		i++;
	}
	return (true);
}
