/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiphainelay <tiphainelay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:01:49 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/24 18:17:21 by tiphainelay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// INCLUDES
#include <pthread.h>
#include <stdbool.h>
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
	int					number_of_times_must_eat;
	long				start_time;
	bool				someone_died;
	struct s_philo		*philo;
	pthread_mutex_t		lock_meal;
	pthread_mutex_t		lock_print;
}						t_parameters;

typedef struct s_philo
{
	pthread_t			philo;
	int					position;
	long				last_meal;
	pthread_mutex_t		my_fork;
	struct s_parameters	*parameters;
	struct s_philo		*next;
	struct s_philo		*prev;
}						t_philo;

// PROTOTYPES
// main.c
void					print_philo(t_philo *philo, t_parameters *parameters);
int						main(int ac, char **av);

// utils.c
int						ft_atoi(const char *str);
long					get_current_time_in_ms(void);
void					display_message(t_philo *philo, char *message);

// init.c
void					init_parameters(t_parameters *parameters, char **av);
void					init_philo(t_philo *philo, t_parameters *parameters);

// routine.c
void					lets_think(t_philo *philo, t_parameters *parameters);
void					lets_sleep(t_philo *philo, t_parameters *parameters);
void					lets_eat(t_philo *philo, t_parameters *parameters);
void					is_someone_died(t_philo *philo,
							t_parameters *parameters);
void					*philosopher_routine(void *arg);
