/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:42:26 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/31 11:11:31 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_parameters(t_parameters *parameters, char **av)
{
	parameters->number_of_philosophers = ft_atoi(av[1]);
	parameters->time_to_die = ft_atoi(av[2]);
	parameters->time_to_eat = ft_atoi(av[3]);
	parameters->time_to_sleep = ft_atoi(av[4]);
	parameters->number_of_times_must_eat = 0;
	parameters->start_time = get_current_time_in_ms();
	parameters->someone_died = false;
	if (av[5])
		parameters->number_of_times_must_eat = ft_atoi(av[5]);
	parameters->philo = NULL;
	if (pthread_mutex_init(&parameters->lock_death, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&parameters->lock_meal, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&parameters->lock_print, NULL) != 0)
		return (1);
	return (0);
}

int	init_mutex_philo(t_philo *philo, int seat)
{
	if (pthread_mutex_init(&philo[seat].my_fork, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philo[seat].lock_meal, NULL) != 0)
		return (1);
	return (0);
}

int	init_philo(t_philo *philo, t_parameters *parameters)
{
	int	seat;

	seat = 0;
	while (seat < parameters->number_of_philosophers)
	{
		philo[seat].position = seat + 1;
		philo[seat].parameters = parameters;
		if (seat == 0)
			philo[seat].prev = &philo[parameters->number_of_philosophers - 1];
		else
			philo[seat].prev = &philo[seat - 1];
		if (seat == parameters->number_of_philosophers - 1)
			philo[seat].next = &philo[0];
		else
			philo[seat].next = &philo[seat + 1];
		philo[seat].eaten_meals = 0;
		philo[seat].last_meal = get_current_time_in_ms();
		philo[seat].currently_eating = 0;
		if (init_mutex_philo(philo, seat) != 0)
			return (1);
		seat++;
	}
	parameters->philo = philo;
	return (0);
}
