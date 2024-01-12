/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:51:27 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/11 18:26:36 by ruiolive         ###   ########.fr       */
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

# define ALIVE 1
# define DEAD 2
# define EATING 3
# define SLEEPING 4
# define THINKING 5

typedef struct s_data
{
	long long		start_time;
	int				numbers_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_to_eat;
	bool			finish;
	bool			done;
	pthread_mutex_t	info;
}	t_data;

typedef struct s_philo
{
	int						id;
	int						status;
	long long				number_of_meal;
	long long				last_meal;
	pthread_t				ph;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			left_fork;
	pthread_mutex_t			philo;
	t_data					*data;
}	t_philo;

/////////////////////////
///   INIT FUCTIONS   ///
/////////////////////////

t_data		init_data(int argc, char **argv);
t_philo		*init_philos(t_data *data);
int			init_threads(t_philo *philos);

///////////////////////////
///   ROTINE FUCTIONS   ///
///////////////////////////

void		*rotine(void *arg);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

//////////////////////////
///   FINEX FUCTIONS   ///
//////////////////////////

void		finex_threads(t_philo *philos);

//////////////////////////
///   UTILS FUCTIONS   ///
//////////////////////////

long long	gettime(void);
int			finish(t_philo *philo);
int			ft_atoi(const char *str);
int			ft_usleep(long long milliseconds);
int			checker(char **argv);

//////////////////////////
///   MUTEX FUCTIONS   ///
//////////////////////////

int			get_info_int(pthread_mutex_t *mutex, int *info);
void		set_info_int(pthread_mutex_t *mutex, int *value, int info);
long long	get_info_long(pthread_mutex_t *mutex, long long *info);
void		set_info_long(pthread_mutex_t *mutex, \
long long *value, long long info);
bool		get_bool(pthread_mutex_t *mutex, bool *info);
void		set_bool(pthread_mutex_t *mutex, bool *value, bool info);
void		lock_forks(t_philo *philo);
void		unlock_forks(t_philo *philo);

///////////////////////////////
///   MONITORING FUCTIONS   ///
///////////////////////////////

int			dead_print(t_philo *philos, int id);
int			monitoring(t_philo *philos);

////////////////////////////
///   checker FUCTIONS   ///
////////////////////////////

int			mono_philo(t_philo *philos);
int			checker(char **argv);

#endif
