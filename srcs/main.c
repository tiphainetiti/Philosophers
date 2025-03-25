/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiphainelay <tiphainelay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:31:24 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/25 15:37:42 by tiphainelay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_philo(t_philo *philo, t_parameters *parameters)
{
	int	i;

	i = 0;
	while (i < parameters->number_of_philosophers)
	{
		// printf("Philosopher[%d]: %d\n", i, philo[i].position);
		// printf("Time to die: %d\n", philo[i].parameters->time_to_die);
		// printf("Time to eat: %d\n", philo[i].parameters->time_to_eat);
		// printf("Time to sleep: %d\n", philo[i].parameters->time_to_sleep);
		// printf("Number of times each philosopher must eat: %d\n",
		// 	philo[i].parameters->number_of_times_must_eat);
		// printf("Eaten meals: %d\n", philo[i].eaten_meals);
		// printf("Next philosopher: %d\n", philo[i].next->position);
		// printf("Previous philosopher: %d\n", philo[i].prev->position);
		printf("someone_died: %d\n", philo[i].parameters->someone_died);
		i++;
	}
}
void	*monitor_routine(void *arg)
{
	t_parameters	*parameters;
	int				i;

	parameters = (t_parameters *)arg;
	i = 0;
	while (1)
	{
		i = 0;
		while (i < parameters->number_of_philosophers)
		{
			someone_died(&parameters->philo[i], parameters);
			if (parameters->someone_died)
			{
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_parameters	parameters;
	t_philo			*philo;
	pthread_t		monitor_thread;
	int				seat;

	seat = 0;
	if (ac < 5 || ac > 6 || ft_atoi(av[1]) < 2)
		return (printf("Error: Wrong number of arguments\n"), 1);
	else
	{
		init_parameters(&parameters, av);
		if (!(philo = malloc(sizeof(t_philo)
					* parameters.number_of_philosophers)))
			return (printf("Error: Malloc failed\n"), 1);
		init_philo(philo, &parameters);
		// Création des threads
		pthread_create(&monitor_thread, NULL, monitor_routine,
			(void *)&parameters);
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
		pthread_join(monitor_thread, NULL);
	}
	return (0);
}
