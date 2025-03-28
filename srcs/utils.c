/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:38:35 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/28 15:15:03 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	result *= sign;
	return (result);
}

void	ft_usleep(t_parameters *parameters, long time_in_ms)
{
	long	start_time;

	start_time = get_current_time_in_ms();
	while (get_current_time_in_ms() - start_time < time_in_ms)
	{
		if (is_someone_dead(parameters))
			break ;
		usleep(50);
	}
}

long	get_current_time_in_ms(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	display_message(t_philo *philo, char *message)
{
	long	current_time;

	current_time = get_current_time_in_ms() - philo->parameters->start_time;
	pthread_mutex_lock(&philo->parameters->lock_print);
	if (!is_someone_dead(philo->parameters))
		printf("%ld %d %s\n", current_time, philo->position, message);
	pthread_mutex_unlock(&philo->parameters->lock_print);
}

void	print_error(char *message)
{
	printf("Error: %s.\n", message);
}


// 0 philosopher sf
// parsing no values under 60 ms