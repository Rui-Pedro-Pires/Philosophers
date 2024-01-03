/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:55:32 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/03 16:39:22 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(t_philo *philo)
{
	long endtime;
	struct timeval execute_time;
	gettimeofday(&execute_time, NULL);
	endtime = (execute_time.tv_sec * 1000 + execute_time.tv_usec) 
	- (philo->start_time.tv_sec * 1000 + philo->start_time.tv_usec);
	return (endtime);
}

int	is_dead(t_philo philo)
{
	
}

void	eating(t_philo *philo)
{
	if (pthread_mutex_lock(philo->right_fork) != 0)
		return ;
	printf("%ldms | Philo %d has taken the right fork\n", gettime(philo), philo->id);
	if (pthread_mutex_lock(&philo->left_fork) != 0)
		return ;
	printf("%ldms | Philo %d has taken the left fork\n", gettime(philo), philo->id);
	printf("%ldms | Philo %d has fucked\n", gettime(philo), philo->id);
	usleep(200 * 1000);
	if (pthread_mutex_unlock(philo->right_fork) != 0)
		return ;
	printf("%ldms | Philo %d droped the right fork\n", gettime(philo), philo->id);
	if (pthread_mutex_unlock(&philo->left_fork) != 0)
		return ;
	printf("%ldms | Philo %d droped the left fork\n", gettime(philo), philo->id);
}

void	sleeping(t_philo *philo)
{
	printf("%ldms | Philo %d is sleeping\n", gettime(philo), philo->id);
	usleep(500 * 1000);
}

void	thinking(t_philo *philo)
{
	printf("%ldms | Philo %d is thinking\n", gettime(philo), philo->id);
	while (pthread_mutex_lock(philo->right_fork) != 0 && pthread_mutex_lock(&philo->left_fork) != 0)	
		usleep(1 * 100);
	return ;
}

void	*rotine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		eating(philo);
	while (!is_dead)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

t_philo	*init_philos(number_of_philos)
{
	t_philo	*philos;
	struct	timeval start_time;
	int	n;

	n = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * number_of_philos);
	if (!philos)
		return (NULL);
	gettimeofday(&start_time, NULL);
	while (n < number_of_philos)
	{
		philos[n].start_time = start_time;
		philos[n].id = n + 1;
		philos[n].died = false;
		if (n == number_of_philos - 1)
		{
			pthread_mutex_init(&philos->left_fork, NULL);
			philos[n].right_fork = &philos[0].left_fork;
		}
		else
		{
			pthread_mutex_init(&philos->left_fork, NULL);
			philos[n].right_fork = &philos[n + 1].left_fork;
		}
		n++;
	}
	return (philos);
}

int	philos_init()

int	threads_init(int number_of_philos)
{
	pthread_t ph[number_of_philos];
	t_philo	*philos;
	int	n;

	n = 0;
	philos = init_philos(number_of_philos);
	while (n < number_of_philos)
	{
		if (pthread_create(&ph[n], NULL, &rotine, &philos[n]) != 0)
			return (1);
		n++;
	}
	n = 0;
	while (n < number_of_philos)
	{
		if (pthread_join(ph[n], NULL) != 0)
			return (2);
		n++;
	}
	return (0);
}

int	main(void)
{
	threads_init(7);
}