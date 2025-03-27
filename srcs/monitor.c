/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:17:45 by tlay              #+#    #+#             */
/*   Updated: 2025/03/27 14:04:35 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	dead_check(t_parameters *parameters, t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(&philo->lock_last_meal);
	current_time = get_current_time_in_ms();
	if ((current_time - philo->last_meal) >= parameters->time_to_die)
	{
		pthread_mutex_unlock(&philo->lock_last_meal);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->lock_last_meal);
		return (0);
	}
}

int	dead_loop(t_philo *philo)
{
	int				i;
	t_parameters	*parameters;

	parameters = philo->parameters;
	i = 0;
	while (i < parameters->number_of_philosophers)
	{
		if (dead_check(parameters, &philo[i]) == 1)
		{
			display_message(&philo[i], "died");
			pthread_mutex_lock(&parameters->lock_death);
			parameters->someone_died = true;
			pthread_mutex_unlock(&parameters->lock_death);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitoring(void *av)
{
	t_parameters	*parameters;

	parameters = (t_parameters *)av;
	while (1)
	{
		if (dead_loop(parameters->philo) == 1 || is_everyone_full(parameters))
			break ;
		ft_usleep(parameters, 100);
	}
	return (NULL);
}
