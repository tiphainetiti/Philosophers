/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:17:45 by tlay              #+#    #+#             */
/*   Updated: 2025/03/28 13:57:33 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	unlock_all_mutexes(t_parameters *parameters)
{
	int	i;

	i = 0;
	while (i < parameters->number_of_philosophers)
	{
		// printf("TEST\n");
		if (parameters->philo[i].currently_eating == 1)
		{
			// printf("LACHE CA\n");
			pthread_mutex_unlock(&parameters->philo[i].my_fork);
			pthread_mutex_unlock(&parameters->philo[i].next->my_fork);
		}
		// Déverrouille le mutex de la fourchette du philosophe
		// Déverrouille le mutex de la dernière prise de repas
		// pthread_mutex_unlock(&parameters->philo[i].lock_meal);
		i++;
	}
	// Déverrouille les autres mutex globaux
	// pthread_mutex_unlock(&parameters->lock_death);
	// pthread_mutex_unlock(&parameters->lock_meal);
	// pthread_mutex_unlock(&parameters->lock_print);
}

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

	parameters = philo->parameters;
	i = 0;
	while (i < parameters->number_of_philosophers)
	{
		if (dead_check(parameters, &philo[i]) == 1
			&& philo[i].currently_eating == 0)
		{
			display_message(&philo[i], "died");
			pthread_mutex_lock(&parameters->lock_death);
			parameters->someone_died = true;
			pthread_mutex_unlock(&parameters->lock_death);
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
		ft_usleep(parameters, 100);
	}
	return (NULL);
}
