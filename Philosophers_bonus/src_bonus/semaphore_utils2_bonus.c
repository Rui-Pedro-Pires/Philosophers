/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_utils2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 09:44:39 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/11 14:39:11 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	get_info_int(sem_t *semaphore, int *info)
{
	int	value;

	sem_wait(semaphore);
	value = *info;
	sem_post(semaphore);
	return (value);
}

long long	get_info_long(sem_t *semaphore, long long *info)
{
	long long	value;

	sem_wait(semaphore);
	value = *info;
	sem_post(semaphore);
	return (value);
}

bool	get_bool(sem_t *semaphore, bool *info)
{
	bool	value;

	sem_wait(semaphore);
	value = *info;
	sem_post(semaphore);
	return (value);
}
