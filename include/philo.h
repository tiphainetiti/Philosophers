/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:01:49 by tiphainelay       #+#    #+#             */
/*   Updated: 2025/03/28 13:55:51 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// INCLUDES
#include <errno.h>
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
	pthread_mutex_t		lock_death;
	pthread_mutex_t		lock_meal;
	pthread_mutex_t		lock_print;
}						t_parameters;

typedef struct s_philo
{
	pthread_t			philo;
	int					currently_eating;
	int					position;
	int					eaten_meals;
	long				last_meal;
	pthread_mutex_t		my_fork;
	pthread_mutex_t		lock_meal;
	struct s_parameters	*parameters;
	struct s_philo		*next;
	struct s_philo		*prev;
}						t_philo;

// PROTOTYPES
// main.c
// void					print_philo(t_philo *philo, t_parameters *parameters);
int						main(int ac, char **av);

// utils.c
int						ft_atoi(const char *str);
void					ft_usleep(t_parameters *parameters, long time);
long					get_current_time_in_ms(void);
void					display_message(t_philo *philo, char *message);
void					print_error(char *message);

// init.c
int						init_parameters(t_parameters *parameters, char **av);
int						init_philo(t_philo *philo, t_parameters *parameters);

// routine.c
void					lets_think(t_philo *philo, t_parameters *parameters);
void					lets_sleep(t_philo *philo, t_parameters *parameters);
void					put_back_forks(t_philo *philo);
void					lets_eat(t_philo *philo, t_parameters *parameters);
void					*philosopher_routine(void *arg);

// check.c
bool					is_someone_dead(t_parameters *parameters);
bool					someone_died(t_parameters *parameters);
bool					is_everyone_full(t_parameters *parameters);
int						the_hungriest(t_philo *philo);

// monitor.c
int						dead_loop(t_philo *philo);
int						dead_check(t_parameters *parameters, t_philo *philo);
void					*monitoring(void *av);

// parsing.c
bool					parsing_digit(char **av);
bool					parsing_limit(char **av);

// cleaning.c
void					destroy_mutex(t_parameters *parameters);
void					free_all(t_parameters *parameters);
int						join_threads(t_philo *philo, t_parameters parameters);
