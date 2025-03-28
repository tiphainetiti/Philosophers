/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:14:23 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/28 15:22:22 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	stop_all_philosophers(t_parameters *parameters)
// {
// 	int	i;

// 	i = 0;
// 	while (i < parameters->number_of_philosophers)
// 	{
// 		pthread_mutex_lock(&parameters->philo[i].my_fork);
// 		pthread_mutex_unlock(&parameters->philo[i].my_fork);
// 		pthread_mutex_lock(&parameters->philo[i].lock_meal);
// 		pthread_mutex_unlock(&parameters->philo[i].lock_meal);
// 		i++;
// 	}
// }

void	lets_think(t_philo *philo, t_parameters *parameters)
{
	int	think_time;

	think_time = parameters->time_to_eat - parameters->time_to_sleep + 1;
	if (!is_someone_dead(parameters))
		display_message(philo, "is thinking");
	if (think_time > 0)
		ft_usleep(parameters, think_time);
}

void	lets_sleep(t_philo *philo, t_parameters *parameters)
{
	if (!is_someone_dead(parameters))
	{
		display_message(philo, "is sleeping");
		ft_usleep(parameters, parameters->time_to_sleep);
	}
}

void	grab_forks(t_philo *philo)
{
	if (philo->position % 2 == 0)
	{
		// printf("Thread %d is locking next->my_fork\n", philo->position);
		pthread_mutex_lock(&philo->next->my_fork);
		display_message(philo, "has taken a fork");
		// printf("Thread %d is locking my_fork\n", philo->position);
		pthread_mutex_lock(&philo->my_fork);
		display_message(philo, "has taken a fork");
	}
	else
	{
		// printf("Thread %d is locking my_fork\n", philo->position);
		pthread_mutex_lock(&philo->my_fork);
		display_message(philo, "has taken a fork");
		// printf("Thread %d is locking next->my_fork\n", philo->position);
		pthread_mutex_lock(&philo->next->my_fork);
		display_message(philo, "has taken a fork");
	}
	// pthread_mutex_lock(&philo->lock_meal);
	// philo->last_meal = get_current_time_in_ms();
	// pthread_mutex_unlock(&philo->lock_meal);
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

void	one_philo(t_philo *philo, t_parameters *parameters)
{
	pthread_mutex_lock(&philo->next->my_fork);
	display_message(philo, "has taken a fork");
	ft_usleep(parameters, parameters->time_to_die);
	pthread_mutex_unlock(&philo->next->my_fork);
}

void	lets_eat(t_philo *philo, t_parameters *parameters)
{
	// int	hungriest_index;
	// hungriest_index = the_hungriest(parameters->philo);
	// if (parameters->number_of_philosophers == 1
	// && !is_someone_dead(parameters))
	// {
	// 	pthread_mutex_lock(&philo->next->my_fork);
	// 	display_message(philo, "has taken a fork");
	// 	ft_usleep(parameters, parameters->time_to_die);
	// 	pthread_mutex_unlock(&philo->next->my_fork);
	// 	return ;
	// }
	// if (parameters->number_of_philosophers % 2 != 0
	// 	&& parameters->time_to_die < parameters->time_to_eat
	// 	&& hungriest_index != philo->position)
	// 	lets_think(philo, parameters);
	if (!is_someone_dead(parameters))
	{
		grab_forks(philo);
		pthread_mutex_lock(&philo->lock_meal);
		philo->currently_eating = 1;
		display_message(philo, "is eating");
		philo->last_meal = get_current_time_in_ms();
		philo->eaten_meals++;
		pthread_mutex_unlock(&philo->lock_meal);
		ft_usleep(parameters, parameters->time_to_eat);
		pthread_mutex_lock(&philo->lock_meal);
		philo->currently_eating = 0;
		pthread_mutex_unlock(&philo->lock_meal);
		put_back_forks(philo);
	}
	// pthread_mutex_unlock(&philo->my_fork);
	// pthread_mutex_unlock(&philo->next->my_fork);
}

void	*philosopher_routine(void *arg)
{
	t_philo			*philo;
	t_parameters	*parameters;

	philo = (t_philo *)arg;
	parameters = philo->parameters;
	if (parameters->number_of_philosophers == 1)
	{
		one_philo(philo, parameters);
		return (NULL);
	}
	if (philo->position % 2 == 0)
		ft_usleep(parameters, 100);
	while (!is_someone_dead(parameters) && !is_everyone_full(parameters))
	{
		lets_eat(philo, parameters);
		lets_sleep(philo, parameters);
		lets_think(philo, parameters);
	}
	return (NULL);
}
