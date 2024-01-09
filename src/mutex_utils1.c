/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:12:57 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/09 18:17:02 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_info_int(pthread_mutex_t *mutex, int *value, int info)
{
	pthread_mutex_lock(mutex);
	*value = info;
	pthread_mutex_unlock(mutex);
}

void	set_info_long(pthread_mutex_t *mutex, long long *value, long long info)
{
	pthread_mutex_lock(mutex);
	*value = info;
	pthread_mutex_unlock(mutex);
}

void	set_bool(pthread_mutex_t *mutex, bool *value, bool info)
{
	pthread_mutex_lock(mutex);
	*value = info;
	pthread_mutex_unlock(mutex);
}

void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
