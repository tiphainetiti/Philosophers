/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:15:06 by tlay              #+#    #+#             */
/*   Updated: 2025/03/28 16:15:24 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	grab_forks(t_philo *philo)
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
