/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_utils1_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 09:43:47 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/11 14:41:48 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	set_info_int(sem_t *semaphore, int *value, int info)
{
	sem_wait(semaphore);
	*value = info;
	sem_post(semaphore);
}

void	set_info_long(sem_t *semaphore, long long *value, long long info)
{
	sem_wait(semaphore);
	*value = info;
	sem_post(semaphore);
}

void	set_bool(sem_t *semaphore, bool *value, bool info)
{
	sem_wait(semaphore);
	*value = info;
	sem_post(semaphore);
}

void	wait_forks(t_philo *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->forks);
}

void	post_forks(t_philo *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
}
