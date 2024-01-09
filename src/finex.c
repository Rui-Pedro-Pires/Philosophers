/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:31:17 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/09 18:16:49 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	finex_threads(t_philo *philos)
{
	int	n;

	n = 0;
	while (n < philos->data->numbers_of_philosophers)
	{
		if (pthread_join(philos[n].ph, NULL) != 0)
			return ;
		n++;
	}
	n = 0;
	while (n < philos->data->numbers_of_philosophers)
	{
		pthread_mutex_destroy(&philos[n].left_fork);
		pthread_mutex_destroy(&philos[n].philo);
		n++;
	}
	pthread_mutex_destroy(&philos->data->info);
	free(philos);
}
