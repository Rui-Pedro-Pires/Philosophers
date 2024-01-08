/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:31:17 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/08 17:08:42 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finex_philos(t_philo *philos)
{
	int	n;

	n = 0;
	while (n < philos->data->numbers_of_philosophers)
	{
		pthread_mutex_destroy(&philos[n].left_fork);
		n++;
	}
	free(philos);
}