/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:21:35 by tlay              #+#    #+#             */
/*   Updated: 2025/03/31 11:37:50 by tlay             ###   ########.fr       */
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
		if (av[i][j] == '-' || av[i][j] == '+')
			j++;
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

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if ((!s1 && !s2))
		return (0);
	while (str1[i] == str2[i] && str1[i])
		i++;
	return (str1[i] - str2[i]);
}

bool	check_overflow(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		len++;
		i++;
	}
	if (len > 10)
		return (true);
	else if (len == 10)
		return (ft_strcmp(&str[i - len], "2147483647") > 0);
	return (false);
}

bool	parsing_limit(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_overflow(av[i]))
			return (print_error("Value cannot exceed int limits"), false);
		else if (ft_atoi(av[i]) < 0)
			return (print_error("Negative value"), false);
		else if (ft_atoi(av[1]) > 200)
			return (print_error("Too many philosophers. Maximum is 200"),
				false);
		else if (ft_atoi(av[1]) == 0)
			return (print_error("Number of philosophers cannot be 0"), false);
		else if (av[5])
		{
			if (ft_atoi(av[5]) == 0)
			{
				printf("Number of times each philosopher");
				return (printf(" must eat cannot be 0\n"), false);
			}
		}
		i++;
	}
	return (true);
}
