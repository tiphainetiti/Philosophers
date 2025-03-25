/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiphainelay <tiphainelay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:14:23 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/25 16:01:51 by tiphainelay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	lets_think(t_philo *philo, t_parameters *parameters)
{
	if (is_someone_died(parameters))
		return ;
	display_message(philo, "is thinking");
	// Formule Gauth
	// usleep((parameters->time_to_eat + parameters->time_to_sleep
	// 		- parameters->time_to_die) * 1000 / 2);
	usleep(parameters->time_to_eat - parameters->time_to_sleep + 1);
}

void	lets_sleep(t_philo *philo, t_parameters *parameters)
{
	if (is_someone_died(parameters))
		return ;
	display_message(philo, "is sleeping");
	usleep(parameters->time_to_sleep * 1000);
}

void	lets_eat(t_philo *philo, t_parameters *parameters)
{
	int	the_hungriest_index;

	the_hungriest_index = the_hungriest(philo);
	if (parameters->number_of_philosophers % 2 != 0
		&& philo->position != the_hungriest_index && philo->eaten_meals > 0)
		lets_think(philo, parameters);
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
	display_message(philo, "is eating !!!!!!!!!");
	philo->last_meal = get_current_time_in_ms();
	usleep(parameters->time_to_eat * 1000);
	philo->eaten_meals++;
	pthread_mutex_unlock(&philo->my_fork);
	pthread_mutex_unlock(&philo->next->my_fork);
	pthread_mutex_lock(&parameters->lock_meal);
	if (is_everyone_full(parameters))
	{
		pthread_mutex_lock(&parameters->lock_death);
		parameters->someone_died = true;
		pthread_mutex_unlock(&parameters->lock_death);
	}
	pthread_mutex_unlock(&parameters->lock_meal);
}

void	*philosopher_routine(void *arg)
{
	t_philo			*philo;
	t_parameters	*parameters;

	philo = (t_philo *)arg;
	parameters = philo->parameters;
	while (!is_someone_died(parameters))
	{
		lets_eat(philo, parameters);
		lets_sleep(philo, parameters);
		lets_think(philo, parameters);
	}
	printf("FINISHED\n");
	return (NULL);
}
