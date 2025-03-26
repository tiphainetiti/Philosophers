/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:14:23 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/26 19:54:27 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	lets_think(t_philo *philo, t_parameters *parameters)
{
	if (!is_someone_dead(parameters) && !is_everyone_full(parameters))
	{
		display_message(philo, "is thinking");
		ft_usleep(parameters, parameters->time_to_eat * 0.9);
	}
}

void	lets_sleep(t_philo *philo, t_parameters *parameters)
{
	if (!is_someone_dead(parameters) && !is_everyone_full(parameters))
	{
		display_message(philo, "is sleeping");
		ft_usleep(parameters, parameters->time_to_sleep);
	}
}

void	grab_forks(t_philo *philo, t_parameters *parameters)
{
	if (!is_someone_dead(parameters) || !is_everyone_full(parameters))
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

void	put_back_forks(t_philo *philo)
{
	if (philo->position % 2 == 0)
	{
		pthread_mutex_unlock(&philo->my_fork);
		pthread_mutex_unlock(&philo->next->my_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->next->my_fork);
		pthread_mutex_unlock(&philo->my_fork);
	}
}

void	lets_eat(t_philo *philo, t_parameters *parameters)
{
	int	hungriest_index;

	hungriest_index = the_hungriest(parameters->philo);
	if (parameters->number_of_philosophers == 1 && !is_someone_dead(parameters))
	{
		pthread_mutex_lock(&philo->next->my_fork);
		display_message(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->next->my_fork);
		ft_usleep(parameters, parameters->time_to_die);
		someone_died(philo, parameters);
		return ;
	}
	if (parameters->number_of_philosophers % 2 != 0
		&& parameters->time_to_die < parameters->time_to_eat
		&& hungriest_index != philo->position && !is_someone_dead(parameters))
		lets_think(philo, parameters);
	grab_forks(philo, parameters);
	if (!is_someone_dead(parameters) && !is_everyone_full(parameters))
	{
		display_message(philo, "is eating");
		pthread_mutex_lock(&philo->lock_last_meal);
		philo->last_meal = get_current_time_in_ms();
		philo->eaten_meals++;
		pthread_mutex_unlock(&philo->lock_last_meal);
		ft_usleep(parameters, parameters->time_to_eat);
	}
	put_back_forks(philo);
}

void	*philosopher_routine(void *arg)
{
	t_philo			*philo;
	t_parameters	*parameters;

	philo = (t_philo *)arg;
	parameters = philo->parameters;
	if (philo->position % 2 == 0)
		ft_usleep(parameters, 100);
	while (!is_someone_dead(parameters) && !is_everyone_full(parameters))
	{
		someone_died(philo, parameters);
		lets_eat(philo, parameters);
		lets_sleep(philo, parameters);
		lets_think(philo, parameters);
	}
	return (NULL);
}
