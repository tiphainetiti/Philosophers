/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiphainelay <tiphainelay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:14:23 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/24 18:18:18 by tiphainelay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	lets_think(t_philo *philo, t_parameters *parameters)
{
	display_message(philo, "is thinking");
	// Formule Gauth
	usleep((parameters->time_to_eat + parameters->time_to_sleep
			- parameters->time_to_die) * 1000 / 2);
}

void	lets_sleep(t_philo *philo, t_parameters *parameters)
{
	display_message(philo, "is sleeping");
	usleep(parameters->time_to_sleep * 1000);
}

void	lets_eat(t_philo *philo, t_parameters *parameters)
{
	// Condition pour quand impair pas de vol
	if (parameters->number_of_philosophers % 2 != 0)
		lets_think(philo, parameters);
	// Prendre les fourchettes
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
	display_message(philo, "is eating");
	philo->last_meal = get_current_time_in_ms();
	usleep(parameters->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->my_fork);
	pthread_mutex_unlock(&philo->next->my_fork);
	pthread_mutex_lock(&parameters->lock_meal);
	if (parameters->number_of_times_must_eat > 0)
		parameters->number_of_times_must_eat--;
	pthread_mutex_unlock(&parameters->lock_meal);
	is_someone_died(philo, parameters);
}

void	is_someone_died(t_philo *philo, t_parameters *parameters)
{
	long	current_time;
	long	time_since_last_meal;

	while (1)
	{
		current_time = get_current_time_in_ms();
		time_since_last_meal = current_time - philo->last_meal;
		if (time_since_last_meal > parameters->time_to_die)
		{
			display_message(philo, "died");
			parameters->someone_died = true;
			return ;
		}
		usleep(1000);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo			*philo;
	t_parameters	*parameters;

	philo = (t_philo *)arg;
	parameters = philo->parameters;
	while (parameters->someone_died == false)
	{
		lets_eat(philo, parameters);
		lets_sleep(philo, parameters);
		lets_think(philo, parameters);
	}
	return (NULL);
}
