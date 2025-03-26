/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:17:45 by tlay              #+#    #+#             */
/*   Updated: 2025/03/26 19:41:32 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor_routine(void *arg)
{
	t_parameters	*parameters;
	int				i;

	parameters = (t_parameters *)arg;
	i = 0;
	while (1)
	{
		i = 0;
		someone_died(parameters->philo, parameters);
		if (is_someone_dead(parameters) || is_everyone_full(parameters))
			break ;
		ft_usleep(parameters, 700);
	}
	return (NULL);
}

// bool	check_all_eaten(t_parameters *parameters)
// {
// 	int		i;
// 	bool	all_eaten;

// 	i = 0;
// 	all_eaten = true;
// 	pthread_mutex_lock(&parameters->lock_meal);
// 	while (i < parameters->number_of_philosophers)
// 	{
// 		if (parameters->philo[i].eaten_meals < parameters->number_of_times_must_eat)
// 		{
// 			all_eaten = false;
// 			break ;
// 		}
// 		i++;
// 	}
// 	pthread_mutex_unlock(&parameters->lock_meal);
// 	return (all_eaten);
// }

// bool	check_death(t_parameters *parameters)
// {
// 	bool	result;

// 	pthread_mutex_lock(&parameters->lock_death);
// 	result = parameters->someone_died;
// 	pthread_mutex_unlock(&parameters->lock_death);
// 	return (result);
// }

// void	print_death(t_philo *philo, t_parameters *parameters)
// {
// 	pthread_mutex_lock(&parameters->lock_print);
// 	printf("%ld %d died\n", get_current_time_in_ms() - parameters->start_time,
// 		philo->position);
// 	pthread_mutex_unlock(&parameters->lock_print);
// }

// bool	monitor_death(t_parameters *parameters)
// {
// 	long	current_time;
// 	int		i;

// 	i = 0;
// 	current_time = get_current_time_in_ms();
// 	while (i < parameters->number_of_philosophers)
// 	{
// 		pthread_mutex_lock(&parameters->philo[i].lock_last_meal);
// 		if (current_time
// 			- parameters->philo[i].last_meal >= parameters->time_to_die)
// 		{
// 			pthread_mutex_lock(&parameters->lock_death);
// 			parameters->someone_died = true;
// 			pthread_mutex_unlock(&parameters->lock_death);
// 			print_death(&parameters->philo[i], parameters);
// 			pthread_mutex_unlock(&parameters->philo[i].lock_last_meal);
// 			return (true);
// 		}
// 		pthread_mutex_unlock(&parameters->philo[i].lock_last_meal);
// 		i++;
// 	}
// 	return (false);
// }

// void	*monitoring(void *arg)
// {
// 	t_parameters	*parameters;

// 	parameters = (t_parameters *)arg;
// 	while (1)
// 	{
// 		if (check_all_eaten(parameters))
// 			break ;
// 		if (check_death(parameters))
// 			break ;
// 		if (monitor_death(parameters))
// 			break ;
// 		usleep(100);
// 	}
// 	return (NULL);
// }
