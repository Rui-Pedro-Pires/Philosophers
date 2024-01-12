/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:51:50 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/12 15:21:59 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;

	if (argc < 5 || argc > 6)
		return (1);
	data = init_data(argc, argv);
	philos = init_philos(&data);
	init_processes(philos);
	sleep(1);
	free(philos);
	sem_unlink(FORK);
	sem_unlink(DIED);
	return (1);
}
