/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:31:24 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/28 18:09:36 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	run_threads(t_philo *philo, t_parameters parameters)
{
	pthread_t	monitor_thread;
	int			seat;

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
	return (join_threads(philo, parameters));
}

int	run_simulation(char **av)
{
	t_parameters	parameters;
	t_philo			*philo;

	if (init_parameters(&parameters, av) != 0)
		return (1);
	philo = malloc(sizeof(t_philo) * parameters.number_of_philosophers);
	if (!philo)
		return (print_error("Malloc t_philo failed"), 1);
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

// bool	should_philosopher_die(int number_of_philosophers, int time_to_die,
// int time_to_eat, int time_to_sleep)
// {
//     int	time_for_one_cycle;
//     int	max_wait_time;

//     // Temps pour qu'un philosophe mange et dorme
//     time_for_one_cycle = time_to_eat + time_to_sleep;

//     // Temps maximum qu'un philosophe doit attendre avant de manger
//     if (number_of_philosophers % 2 == 0)
//         max_wait_time = (number_of_philosophers / 2 - 1) * time_to_eat;
//     else
//         max_wait_time = (number_of_philosophers / 2) * time_to_eat;

//     // Si le temps d'attente dépasse time_to_die, le philosophe mourra
//     if (max_wait_time + time_to_eat > time_to_die)
//         return (true);
//     return (false);
// }