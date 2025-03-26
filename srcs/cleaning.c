/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:27:07 by tlay              #+#    #+#             */
/*   Updated: 2025/03/26 18:57:17 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_mutex(t_parameters *parameters)
{
	int	i;

	i = 0;
	while (i < parameters->number_of_philosophers)
	{
		pthread_mutex_destroy(&parameters->philo[i].my_fork);
		pthread_mutex_destroy(&parameters->philo[i].lock_last_meal);
		i++;
	}
	pthread_mutex_destroy(&parameters->lock_death);
	pthread_mutex_destroy(&parameters->lock_meal);
	pthread_mutex_destroy(&parameters->lock_print);
}

void	free_all(t_parameters *parameters)
{
	destroy_mutex(parameters);
	free(parameters->philo);
}

int	join_threads(t_philo *philo, t_parameters parameters)
{
	int	seat;

	seat = 0;
	while (seat < parameters.number_of_philosophers)
	{
		if (pthread_join(philo[seat].philo, NULL) != 0)
			return (print_error("Thread join failed"), 1);
		seat++;
	}
	return (0);
}
