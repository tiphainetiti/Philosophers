/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiphainelay <tiphainelay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:35:14 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/25 15:58:22 by tiphainelay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	is_someone_died(t_parameters *parameters)
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
	time_since_last_meal = current_time - philo->last_meal;
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
		if (parameters->philo[i].eaten_meals < parameters->number_of_times_must_eat)
			return (false);
		i++;
	}
	printf("Everyone is FULL\n");
	return (true);
}

int	the_hungriest(t_philo *philo)
{
	int	i;
	int	the_hungriest;

	i = 0;
	the_hungriest = 0;
	while (i < philo->parameters->number_of_philosophers)
	{
		if (philo[i].last_meal < philo[the_hungriest].last_meal)
			the_hungriest = i;
		i++;
	}
	return (the_hungriest);
}

// DEBUG
// Vérification du pointeur parameters
// if (parameters == NULL)
// {
// 	fprintf(stderr, "Error: NULL parameters passed to is_everyone_full\n");
// 	return (false);
// }
// // Vérification du tableau philo
// if (parameters->philo == NULL)
// {
// 	fprintf(stderr, "Error: NULL philo array in parameters\n");
// 	return (false);
// }
// // Vérification du nombre de philosophes
// if (parameters->number_of_philosophers <= 0)
// {
// 	fprintf(stderr, "Error: Invalid number of philosophers\n");
// 	return (false);
// }