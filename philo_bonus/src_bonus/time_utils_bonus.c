/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:53:49 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/11 14:40:31 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

long long	gettime(void)
{
	long long			current_time;
	struct timeval		st;

	gettimeofday(&st, NULL);
	current_time = (long long)st.tv_sec * 1000 + (long long)st.tv_usec / 1000;
	return (current_time);
}

int	ft_usleep(long long milliseconds)
{
	long long	start;

	start = gettime();
	while ((gettime() - start) < milliseconds)
		usleep(500);
	return (0);
}
