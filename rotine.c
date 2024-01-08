/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:31:19 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/08 17:01:53 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	if (pthread_mutex_lock(philo->right_fork) == 0 && pthread_mutex_lock(&philo->left_fork) == 0 
	&& philo->number_of_meal != philo->data->number_of_times_to_eat
	&& philo->status != DEAD && philo->data->finish == false)
	{
		printf("%lld %d has taken a fork\n", philo->data->current_time - philo->data->start_time, philo->id);
		printf("%lld %d has taken a fork\n", philo->data->current_time - philo->data->start_time, philo->id);
		printf("%lld %d is eating\n", philo->data->current_time - philo->data->start_time, philo->id);
		philo->status = EATING;
		philo->last_meal = philo->data->current_time;
		ft_usleep(philo->data->time_to_eat);
		philo->number_of_meal++;
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	if (philo->status == EATING && philo->data->finish == false)
	{
		printf("%lld %d is sleeping\n", philo->data->current_time - philo->data->start_time, philo->id);
		philo->status = SLEEPING;
		ft_usleep(philo->data->time_to_sleep);
	}
}

void	thinking(t_philo *philo)
{
	if (philo->data->finish == false && philo->status != THINKING)
	{
		printf("%lld %d is thinking\n", philo->data->current_time - philo->data->start_time, philo->id);
		philo->status = THINKING;
	}
}

void	*rotine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		thinking(philo);
		ft_usleep(1);
	}
	while (philo->data->finish == false)
	{
			eating(philo);
			sleeping(philo);
			thinking(philo);
	}
	return (NULL);
}
