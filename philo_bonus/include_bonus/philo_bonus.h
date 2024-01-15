/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:52:22 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/15 10:51:16 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include <sys/ipc.h>
# include <fcntl.h>
# include <stdbool.h>

# define FORK "/fork"
# define INFO "/info"
# define DIED "/died"
# define ALIVE 1
# define DEAD 2
# define EATING 3
# define SLEEPING 4
# define THINKING 5

typedef struct s_data
{
	int				numbers_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_to_eat;
}	t_data;

typedef struct s_philo
{
	int						id;
	int						pid;
	int						value;
	long long				number_of_meal;
	long long				last_meal;
	long long				start_time;
	long long				current_time;
	bool					finish;
	bool					done;
	int						status;
	sem_t					*forks;
	sem_t					*info;
	sem_t					*died;
	t_data					*data;
}	t_philo;

/////////////////////////
///   INIT FUCTIONS   ///
/////////////////////////

t_data		init_data(int argc, char **argv);
t_philo		*init_philos(t_data *data);
int			process(t_philo *philo);
int			init_processes(t_philo *philos);

///////////////////////////
///   ROTINE FUCTIONS   ///
///////////////////////////

void		*rotine(void *arg);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

//////////////////////////
///   UTILS FUCTIONS   ///
//////////////////////////

long long	gettime(void);
int			ft_atoi(const char *str);
int			ft_usleep(long long milliseconds);

///////////////////////////////
///   MONITORING FUCTIONS   ///
///////////////////////////////

int			dead_print(t_philo *philo, int id);
int			monitoring(t_philo *philo);

//////////////////////////////
///   SEMAPHORE FUCTIONS   ///
//////////////////////////////

void		set_info_int(sem_t *semaphore, int *value, int info);
void		set_info_long(sem_t *semaphore, long long *value, long long info);
void		set_bool(sem_t *semaphore, bool *value, bool info);
int			get_info_int(sem_t *semaphore, int *info);
long long	get_info_long(sem_t *semaphore, long long *info);
bool		get_bool(sem_t *semaphore, bool *info);
void		wait_forks(t_philo *philo);
void		post_forks(t_philo *philo);

#endif