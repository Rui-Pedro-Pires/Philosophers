/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 09:59:14 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/11 16:50:49 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	monitoring(t_philo *philo)
{
	set_info_long(philo->info, &philo->current_time, gettime());
	if (philo->data->time_to_die <= get_info_long(philo->info, \
		&philo->current_time) - get_info_long(philo->info, \
		&philo->last_meal) && get_info_int(philo->info, \
		&philo->status) != EATING)
	{
		sem_wait(philo->died);
		dead_print(philo, philo->id);
		exit(EXIT_SUCCESS);
	}
	if (get_info_long(philo->info, \
		&philo->number_of_meal) == philo->data->number_of_times_to_eat)
		set_bool(philo->info, &philo->finish, true);
	set_info_long(philo->info, &philo->current_time, gettime());
	return (1);
}

int	dead_print(t_philo *philo, int id)
{
	printf("%lld %d died\n", \
	get_info_long(philo->info, &philo->current_time) - \
	get_info_long(philo->info, &philo->start_time), id);
	set_bool(philo->info, &philo->finish, true);
	set_info_int(philo->info, &philo->status, DEAD);
	return (1);
}
