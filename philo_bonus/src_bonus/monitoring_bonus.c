/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 09:59:14 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/16 11:18:03 by ruiolive         ###   ########.fr       */
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
		set_bool(philo->info, &philo->finish, true);
		time = gettime() - get_info_long(philo->info, &philo->start_time);
		sem_wait(philo->died);
		printf("%lld %d died\n", time, philo->id);
		return (1);
	}
	if (get_info_long(philo->info, \
		&philo->number_of_meal) == philo->data->number_of_times_to_eat)
		set_bool(philo->info, &philo->done, true);
	return (1);
}

int	checker(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}
