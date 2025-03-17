/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiphainelay <tiphainelay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:01:49 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/17 19:03:13 by tiphainelay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// INCLUDES
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

// STRUCTURES
typedef struct s_parameters
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	struct s_philo		*philo;
	pthread_mutex_t		lock_meal;
	pthread_mutex_t		lock_print;
}						t_parameters;

typedef struct s_philo
{
	pthread_t			philo;
	int					position;
	pthread_mutex_t		my_fork;
	struct s_parameters	*parameters;
	struct s_philo		*next;
	struct s_philo		*prev;
}						t_philo;

// PROTOTYPES
// main.c
// utils.c
int						ft_atoi(const char *str);