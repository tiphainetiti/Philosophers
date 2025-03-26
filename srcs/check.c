/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:35:14 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/26 19:44:18 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	is_someone_dead(t_parameters *parameters)
{
	bool	result;

	pthread_mutex_lock(&parameters->lock_death);
	result = parameters->someone_died;
	pthread_mutex_unlock(&parameters->lock_death);
	return (result);
}

void	someone_died(t_philo *philo, t_parameters *parameters)
{
	long	current_time;
	long	time_since_last_meal;

	current_time = get_current_time_in_ms();
	pthread_mutex_lock(&philo->lock_last_meal);
	time_since_last_meal = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->lock_last_meal);
	if (time_since_last_meal > parameters->time_to_die)
	{
		display_message(philo, "died");
		pthread_mutex_lock(&parameters->lock_death);
		parameters->someone_died = true;
		pthread_mutex_unlock(&parameters->lock_death);
	}
}

bool	is_everyone_full(t_parameters *parameters)
{
	int	i;

	i = 0;
	if (parameters->number_of_times_must_eat == 0)
		return (false);
	while (i < parameters->number_of_philosophers)
	{
		pthread_mutex_lock(&parameters->philo[i].lock_last_meal);
		if (parameters->philo[i].eaten_meals < parameters->number_of_times_must_eat)
		{
			pthread_mutex_unlock(&parameters->philo[i].lock_last_meal);
			return (false);
		}
		pthread_mutex_unlock(&parameters->philo[i].lock_last_meal);
		i++;
	}
	pthread_mutex_lock(&parameters->lock_death);
	parameters->someone_died = true;
	pthread_mutex_unlock(&parameters->lock_death);
	return (true);
}

int	the_hungriest(t_philo *philo)
{
	int		i;
	int		the_hungriest;
	long	last_meal_time;

	i = 0;
	the_hungriest = 0;
	pthread_mutex_lock(&philo[the_hungriest].lock_last_meal);
	last_meal_time = philo[the_hungriest].last_meal;
	pthread_mutex_unlock(&philo[the_hungriest].lock_last_meal);
	while (i < philo->parameters->number_of_philosophers)
	{
		pthread_mutex_lock(&philo[i].lock_last_meal);
		if (philo[i].last_meal < last_meal_time)
		{
			the_hungriest = i;
			last_meal_time = philo[i].last_meal;
		}
		pthread_mutex_unlock(&philo[i].lock_last_meal);
		i++;
	}
	return (the_hungriest);
}
