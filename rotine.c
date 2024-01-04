/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:31:19 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/04 16:43:14 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	if (pthread_mutex_lock(philo->right_fork) == 0 && pthread_mutex_lock(&philo->left_fork) == 0 && philo->number_of_meal != philo->data->number_of_times_to_eat)
	{
		printf("%ld %d has taken a fork\n", gettime(philo), philo->id);
		printf("%ld %d has taken a fork\n", gettime(philo), philo->id);
		printf("%ld %d is eating\n", gettime(philo), philo->id);
		philo->number_of_meal++;
		usleep(philo->data->time_to_eat * 1000);
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n", gettime(philo), philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	printf("%ld %d is thinking\n", gettime(philo), philo->id);
}

void	*rotine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		eating(philo);
		finish_update(philo);
		sleeping(philo);
	}
	else
		usleep(1 * 1000);
	while (!finish(philo))
	{
		thinking(philo);
		eating(philo);
		finish_update(philo);
		sleeping(philo);
	}
	return (NULL);
}
