/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:51:27 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/04 16:38:03 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_data
{
	pthread_mutex_t info;
	struct timeval start_time;
	struct timeval current_time;
	int	numbers_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_to_eat;
	bool	finish;
}	t_data;

typedef struct s_philo
{
	int	id;
	int	number_of_meal;
	bool	finish;
	pthread_t	ph;
	pthread_mutex_t *right_fork;
	pthread_mutex_t left_fork;
	t_data	*data;
}	t_philo;

/////////////////////////
///   INIT FUCTIONS   ///
/////////////////////////

t_data	init_data(int argc, char **argv);
t_philo	*init_philos(t_data *data);
int	init_threads(t_philo *philos);

///////////////////////////
///   ROTINE FUCTIONS   ///
///////////////////////////

void	*rotine(void *arg);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

//////////////////////////
///   FINEX FUCTIONS   ///
//////////////////////////

void	finex_philos(t_philo *philos);

//////////////////////////
///   UTILS FUCTIONS   ///
//////////////////////////

int	finish(t_philo *philo);
void	finish_update(t_philo *philo);
int	ft_atoi(const char *str);
long	gettime(t_philo *philo);
void	check_meals(t_philo *philos);

#endif
