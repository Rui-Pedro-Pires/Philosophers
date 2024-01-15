/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:11:33 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/09 18:17:06 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_info_int(pthread_mutex_t *mutex, int *info)
{
	int	value;

	pthread_mutex_lock(mutex);
	value = *info;
	pthread_mutex_unlock(mutex);
	return (value);
}

long long	get_info_long(pthread_mutex_t *mutex, long long *info)
{
	long long	value;

	pthread_mutex_lock(mutex);
	value = *info;
	pthread_mutex_unlock(mutex);
	return (value);
}

bool	get_bool(pthread_mutex_t *mutex, bool *info)
{
	bool	value;

	pthread_mutex_lock(mutex);
	value = *info;
	pthread_mutex_unlock(mutex);
	return (value);
}
