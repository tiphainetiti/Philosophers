/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiphainelay <tiphainelay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:31:24 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/17 19:09:39 by tiphainelay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_parameters(t_parameters *parameters, char **av)
{
	parameters->number_of_philosophers = ft_atoi(av[1]);
	parameters->time_to_die = ft_atoi(av[2]);
	parameters->time_to_eat = ft_atoi(av[3]);
	parameters->time_to_sleep = ft_atoi(av[4]);
	parameters->number_of_times_each_philosopher_must_eat = 0;
	if (av[5])
		parameters->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	parameters->philo = NULL;
	pthread_mutex_init(&parameters->lock_meal, NULL);
	pthread_mutex_init(&parameters->lock_print, NULL);
}

void	init_philo(t_philo *philo, t_parameters *parameters, int seat)
{
	while (seat <= parameters->number_of_philosophers)
	{
		philo[seat].position = seat;
		philo[seat].parameters = parameters;
		philo[seat].next = &philo[seat + 1];
		if (seat == 1)
			philo[seat].prev = &philo[parameters->number_of_philosophers];
		else
			philo[seat].prev = &philo[seat - 1];
		seat++;
	}
}

void	print_philo(t_philo *philo, t_parameters *parameters)
{
	int	i;

	i = 1;
	while (i < parameters->number_of_philosophers)
	{
		printf("Philosopher %d\n", philo[i].position);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_parameters	parameters;
	t_philo			*philo;
	int				seat;

	seat = 1;
	if (ac < 5 || ac > 6 || ft_atoi(av[1]) < 2)
		return (printf("Error: Wrong number of arguments\n"), 1);
	else
	{
		init_parameters(&parameters, av);
		if (!(philo = malloc(sizeof(t_philo)
					* parameters.number_of_philosophers)))
			return (printf("Error: Malloc failed\n"), 1);
		init_philo(philo, &parameters, seat);
		print_philo(philo, &parameters);
	}
	return (0);
}
