/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:31:24 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/27 20:13:10 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	print_philo(t_philo *philo, t_parameters *parameters)
// {
// 	int	i;

// 	i = 0;
// 	while (i < parameters->number_of_philosophers)
// 	{
// 		// printf("Philosopher[%d]: %d\n", i, philo[i].position);
// 		// printf("Time to die: %d\n", philo[i].parameters->time_to_die);
// 		// printf("Time to eat: %d\n", philo[i].parameters->time_to_eat);
// 		// printf("Time to sleep: %d\n", philo[i].parameters->time_to_sleep);
// 		// printf("Number of times each philosopher must eat: %d\n",
// 		// 	philo[i].parameters->number_of_times_must_eat);
// 		// printf("Eaten meals: %d\n", philo[i].eaten_meals);
// 		// printf("Next philosopher: %d\n", philo[i].next->position);
// 		// printf("Previous philosopher: %d\n", philo[i].prev->position);
// 		printf("someone_died: %d\n", philo[i].parameters->someone_died);
// 		i++;
// 	}
// }

int	run_threads(t_philo *philo, t_parameters parameters)
{
	pthread_t	monitor_thread;
	int			seat;

	// int			ret;
	seat = 0;
	if (pthread_create(&monitor_thread, NULL, monitoring,
			(void *)&parameters) != 0)
		return (print_error("Thread creation failed"), 1);
	while (seat < parameters.number_of_philosophers)
	{
		if (pthread_create(&philo[seat].philo, NULL, philosopher_routine,
				&philo[seat]) != 0)
			return (print_error("Thread creation failed"), join_threads(philo,
					parameters));
		seat++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return (print_error("Thread join failed"), 1);
	join_threads(philo, parameters);
	return (0);
}

int	run_simulation(char **av)
{
	t_parameters	parameters;
	t_philo			*philo;

	if (init_parameters(&parameters, av) != 0)
		return (1);
	if (!(philo = malloc(sizeof(t_philo) * parameters.number_of_philosophers)))
		return (printf("Error: Malloc failed\n"), 1);
	if (init_philo(philo, &parameters) != 0)
		return (1);
	run_threads(philo, parameters);
	free_all(&parameters);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Error: Wrong number of arguments\n"), 1);
	else if (!parsing_digit(av) || !parsing_limit(av)
		|| run_simulation(av) != 0)
		return (1);
	return (0);
}
