/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiphainelay <tiphainelay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:14:23 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/25 18:10:03 by tiphainelay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	lets_think(t_philo *philo, t_parameters *parameters)
{
	if (is_someone_dead(parameters) || is_everyone_full(parameters))
		return ;
	display_message(philo, "is thinking");
	// Formule Gauth
	// ft_usleep((parameters->time_to_eat + parameters->time_to_sleep
	// 		- parameters->time_to_die) * 1000 / 2);
	ft_usleep(parameters->time_to_eat - parameters->time_to_sleep + 1);
}

void	lets_sleep(t_philo *philo, t_parameters *parameters)
{
	if (is_someone_dead(parameters) || is_everyone_full(parameters))
		return ;
	display_message(philo, "is sleeping");
	ft_usleep(parameters->time_to_sleep);
}

void	grab_forks(t_philo *philo)
{
	if (!is_someone_dead(philo->parameters)
		|| !is_everyone_full(philo->parameters))
	{
		if (philo->position % 2 == 0)
		{
			pthread_mutex_lock(&philo->next->my_fork);
			display_message(philo, "has taken a fork");
			pthread_mutex_lock(&philo->my_fork);
			display_message(philo, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(&philo->my_fork);
			display_message(philo, "has taken a fork");
			pthread_mutex_lock(&philo->next->my_fork);
			display_message(philo, "has taken a fork");
		}
	}
}

void	lets_eat(t_philo *philo, t_parameters *parameters)
{
	int	hungriest_index;

	hungriest_index = the_hungriest(parameters->philo);
	// if (parameters->number_of_philosophers % 2 != 0
	// 	&& philo->position != hungriest_index && philo->eaten_meals > 0)
	if (parameters->number_of_philosophers % 2 != 0
		&& parameters->time_to_die < parameters->time_to_eat
		&& hungriest_index != philo->position)
		lets_think(philo, parameters);
	grab_forks(philo);
	if (!is_someone_dead(parameters) && !is_everyone_full(parameters))
	{
		display_message(philo, "is eating !!!!!!!!!");
		philo->last_meal = get_current_time_in_ms();
		ft_usleep(parameters->time_to_eat);
		pthread_mutex_lock(&parameters->lock_meal);
		philo->eaten_meals++;
		if (is_everyone_full(parameters))
		{
			pthread_mutex_lock(&parameters->lock_death);
			parameters->someone_died = true;
			pthread_mutex_unlock(&parameters->lock_death);
		}
		pthread_mutex_unlock(&parameters->lock_meal);
	}
	pthread_mutex_unlock(&philo->my_fork);
	pthread_mutex_unlock(&philo->next->my_fork);
}

void	*philosopher_routine(void *arg)
{
	t_philo			*philo;
	t_parameters	*parameters;

	philo = (t_philo *)arg;
	parameters = philo->parameters;
	// if (philo->position % 2 == 0)
	// 	ft_usleep(1);
	while (!is_someone_dead(parameters) && !is_everyone_full(parameters))
	{
		lets_eat(philo, parameters);
		lets_sleep(philo, parameters);
		lets_think(philo, parameters);
	}
	printf("FINISHED\n");
	return (NULL);
}
