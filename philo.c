/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:55:32 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/08 17:46:38 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	t_philo	*philos;
	t_data	data;

	if (!checker(argv + 1))
	{
		printf("Error: Wrong format\n");
		printf("Please enter: <./philo> <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> \
<number_of_times_each_philosopher_must_eat>\n");
		return (1);
	}
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 is thinking\n");
		ft_usleep(ft_atoi(argv[2]));
		printf("%d %d died\n", ft_atoi(argv[2]), ft_atoi(argv[1]));
		return (2);
	}
	data = init_data(argc, argv);
	philos = init_philos(&data);
	init_threads(philos);
	finex_philos(philos);
}
