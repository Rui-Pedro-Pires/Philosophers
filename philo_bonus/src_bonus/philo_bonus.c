/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:51:50 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/16 11:24:26 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;

	if (argc < 5 || argc > 6)
		return (1);
	if (argv[1][0] == '0')
		return (printf("Error: the number of philosophers \
		need to be 1 or more"));
	if (!checker(argv + 1))
	{
		printf("Error: Wrong format\n");
		printf("Please enter: <./philo> <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> \
			<number_of_times_each_philosopher_must_eat>\n");
		return (3);
	}
	data = init_data(argc, argv);
	if (data.numbers_of_philosophers == 1)
		mono_process(&data);
	philos = init_philos(&data);
	init_processes(philos);
	sleep(1);
	free(philos);
	sem_unlink(FORK);
	sem_unlink(DIED);
	return (1);
}
