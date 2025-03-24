/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiphainelay <tiphainelay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:31:24 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/24 18:41:24 by tiphainelay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_philo(t_philo *philo, t_parameters *parameters)
{
	int	i;

	i = 0;
	while (i < parameters->number_of_philosophers)
	{
		printf("Philosopher %d\n", philo[i].position);
		// printf("Time to die: %d\n", philo[i].parameters->time_to_die);
		// printf("Time to eat: %d\n", philo[i].parameters->time_to_eat);
		// printf("Time to sleep: %d\n", philo[i].parameters->time_to_sleep);
		// printf("Number of times each philosopher must eat: %d\n",
		// 	philo[i].parameters->number_of_times_each_philosopher_must_eat);
		printf("Next philosopher: %d\n", philo[i].next->position);
		printf("Previous philosopher: %d\n", philo[i].prev->position);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_parameters	parameters;
	t_philo			*philo;
	int				seat;

	seat = 0;
	if (ac < 5 || ac > 6 || ft_atoi(av[1]) < 2)
		return (printf("Error: Wrong number of arguments\n"), 1);
	else
	{
		init_parameters(&parameters, av);
		printf("start_time: %ld\n", parameters.start_time);
		if (!(philo = malloc(sizeof(t_philo)
					* parameters.number_of_philosophers)))
			return (printf("Error: Malloc failed\n"), 1);
		init_philo(philo, &parameters);
		// Création des threads
		seat = 0;
		while (seat < parameters.number_of_philosophers)
		{
			pthread_create(&philo[seat].philo, NULL, philosopher_routine,
				&philo[seat]);
			seat++;
		}
		// Attente des threads
		seat = 0;
		while (seat < parameters.number_of_philosophers)
		{
			pthread_join(philo[seat].philo, NULL);
			seat++;
		}
	}
	return (0);
}
