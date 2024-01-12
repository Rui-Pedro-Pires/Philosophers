/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 09:59:14 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/12 15:06:08 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	monitoring(t_philo *philo)
{
	long long	diff_time;
	long long	time;

	diff_time = gettime() - get_info_long(philo->info, \
			&philo->last_meal);
	if (philo->data->time_to_die <= diff_time \
	&& get_info_int(philo->info, &philo->status) != EATING)
	{
		time = gettime() - get_info_long(philo->info, &philo->start_time);
		set_bool(philo->info, &philo->finish, true);
		sem_wait(philo->died);
		printf("%lld %d died\n", time, philo->id);
		exit(EXIT_SUCCESS);
	}
	if (get_info_long(philo->info, \
		&philo->number_of_meal) == philo->data->number_of_times_to_eat)
	{
		ft_usleep(philo->data->time_to_eat);
		set_bool(philo->info, &philo->finish, true);
	}
	return (1);
}
