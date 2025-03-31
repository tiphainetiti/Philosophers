/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:17:45 by tlay              #+#    #+#             */
/*   Updated: 2025/03/31 13:57:13 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	dead_check(t_parameters *parameters, t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(&philo->lock_meal);
	current_time = get_current_time_in_ms();
	if ((current_time - philo->last_meal) >= parameters->time_to_die
		&& philo->currently_eating == 0)
	{
		pthread_mutex_unlock(&philo->lock_meal);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->lock_meal);
		return (0);
	}
}

int	dead_loop(t_philo *philo)
{
	int				i;
	t_parameters	*parameters;
	long			current_time;

	current_time = get_current_time_in_ms() - philo->parameters->start_time;
	parameters = philo->parameters;
	i = 0;
	while (i < parameters->number_of_philosophers)
	{
		if (dead_check(parameters, &philo[i]) == 1
			&& philo[i].currently_eating == 0)
		{
			pthread_mutex_lock(&parameters->lock_death);
			parameters->someone_died = true;
			pthread_mutex_unlock(&parameters->lock_death);
			pthread_mutex_lock(&parameters->lock_print);
			printf("%ld %d died\n", current_time, philo[i].position);
			pthread_mutex_unlock(&parameters->lock_print);
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
		ft_usleep(parameters, 1);
	}
	return (NULL);
}
