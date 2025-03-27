/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:14:23 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/27 20:08:51 by tlay             ###   ########.fr       */
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
// 		pthread_mutex_lock(&parameters->philo[i].lock_last_meal);
// 		pthread_mutex_unlock(&parameters->philo[i].lock_last_meal);
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
}

void	put_back_forks(t_philo *philo)
{
	if (philo->position % 2 == 0)
	{
		// printf("Thread %d is unlocking my_fork\n", philo->position);
		pthread_mutex_unlock(&philo->my_fork);
		// printf("Thread %d is unlocking nxet->my_fork\n", philo->position);
		pthread_mutex_unlock(&philo->next->my_fork);
	}
	else
	{
		// printf("Thread %d is unlocking my_fork\n", philo->position);
		pthread_mutex_unlock(&philo->next->my_fork);
		// printf("Thread %d is unlocking nxet->my_fork\n", philo->position);
		pthread_mutex_unlock(&philo->my_fork);
	}
}

void	lets_eat(t_philo *philo, t_parameters *parameters)
{
	// int	hungriest_index;
	// hungriest_index = the_hungriest(parameters->philo);
	if (parameters->number_of_philosophers == 1 && !is_someone_dead(parameters))
	{
		pthread_mutex_lock(&philo->next->my_fork);
		display_message(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->next->my_fork);
		ft_usleep(parameters, parameters->time_to_die);
		return ;
	}
	// if (parameters->number_of_philosophers % 2 != 0
	// 	&& parameters->time_to_die < parameters->time_to_eat
	// 	&& hungriest_index != philo->position)
	// 	lets_think(philo, parameters);
	grab_forks(philo);
	if (!is_someone_dead(parameters))
	{
		display_message(philo, "is eating");
		pthread_mutex_lock(&philo->lock_last_meal);
		philo->currently_eating = 1;
		philo->last_meal = get_current_time_in_ms();
		philo->eaten_meals++;
		pthread_mutex_unlock(&philo->lock_last_meal);
		philo->currently_eating = 0;
		ft_usleep(parameters, parameters->time_to_eat);
	}
	put_back_forks(philo);
	// pthread_mutex_unlock(&philo->my_fork);
	// pthread_mutex_unlock(&philo->next->my_fork);
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
		lets_eat(philo, parameters);
		lets_sleep(philo, parameters);
		lets_think(philo, parameters);
	}
	return (NULL);
}
