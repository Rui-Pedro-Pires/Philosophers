/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:04:16 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/09 18:17:26 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
