/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiphainelay <tiphainelay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:42:26 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/24 17:18:27 by tiphainelay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_parameters(t_parameters *parameters, char **av)
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
	pthread_mutex_init(&parameters->lock_meal, NULL);
	pthread_mutex_init(&parameters->lock_print, NULL);
}
void	init_philo(t_philo *philo, t_parameters *parameters)
{
	int	seat;

	seat = 0;
	while (seat < parameters->number_of_philosophers)
	{
		// Attribution du numéro (1 à number_of_philosophers)
		philo[seat].position = seat + 1;
		philo[seat].parameters = parameters;
		// Gestion des liens circulaires
		if (seat == 0)
			philo[seat].prev = &philo[parameters->number_of_philosophers - 1];
		// Philosophe 1 est après le dernier
		else
			philo[seat].prev = &philo[seat - 1];
		if (seat == parameters->number_of_philosophers - 1)
			philo[seat].next = &philo[0]; // Le dernier est lié au premier
		else
			philo[seat].next = &philo[seat + 1];
		pthread_mutex_init(&philo[seat].my_fork, NULL);
		seat++;
	}
}
