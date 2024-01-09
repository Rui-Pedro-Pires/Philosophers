/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:10:03 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/09 17:59:26 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring(t_philo *philos)
{
	int		n;
	int		count;

	n = 0;
	count = 0;
	while (n < philos->data->numbers_of_philosophers)
	{
		set_info_long(&philos->data->info, \
			&philos->data->current_time, gettime());
		if (philos->data->time_to_die <= get_info_long(&philos->data->info, \
			&philos->data->current_time) - get_info_long(&philos->data->info, \
			&philos[n].last_meal) && get_info_int(&philos->data->info, \
			&philos[n].status) != EATING)
			return (dead_print(philos, philos[n].id));
		if (philos->data->number_of_times_to_eat == \
			get_info_long(&philos[n].philo, &philos[n].number_of_meal))
			count++;
		n++;
	}
	if (philos->data->numbers_of_philosophers == count)
		set_bool(&philos->data->info, &philos->data->finish, true);
	return (1);
}

int	dead_print(t_philo *philos, int id)
{
	printf("%lld %d died\n", \
	get_info_long(&philos->data->info, &philos->data->current_time) - \
	get_info_long(&philos->data->info, &philos->data->start_time), id);
	set_info_int(&philos->data->info, &philos[id].status, DEAD);
	set_bool(&philos->data->info, &philos->data->finish, true);
	return (1);
}
