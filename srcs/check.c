/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:35:14 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/28 16:27:15 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	is_someone_dead(t_parameters *parameters)
{
	bool	result;

	pthread_mutex_lock(&parameters->lock_death);
	result = parameters->someone_died;
	pthread_mutex_unlock(&parameters->lock_death);
	return (result);
}

bool	is_everyone_full(t_parameters *params)
{
	int	i;

	i = 0;
	if (params->number_of_times_must_eat == 0)
		return (false);
	while (i < params->number_of_philosophers)
	{
		pthread_mutex_lock(&params->philo[i].lock_meal);
		if (params->philo[i].eaten_meals < params->number_of_times_must_eat)
		{
			pthread_mutex_unlock(&params->philo[i].lock_meal);
			return (false);
		}
		pthread_mutex_unlock(&params->philo[i].lock_meal);
		i++;
	}
	pthread_mutex_lock(&params->lock_death);
	params->someone_died = true;
	pthread_mutex_unlock(&params->lock_death);
	return (true);
}
