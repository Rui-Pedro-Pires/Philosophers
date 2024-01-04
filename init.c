/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:05:17 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/04 16:30:16 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_data(int argc, char **argv)
{
	t_data	data;

	data.numbers_of_philosophers = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.finish = false;
	pthread_mutex_init(&data.info, NULL);
	if (argc == 6)
		data.number_of_times_to_eat = ft_atoi(argv[5]);
	else
		data.number_of_times_to_eat = -1;
	return (data);
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*philos;
	int	n;

	n = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * data->numbers_of_philosophers);
	if (!philos)
		return (NULL);
	while (n < data->numbers_of_philosophers)
	{
		philos[n].id = n + 1;
		philos[n].data = data;
		philos[n].number_of_meal = 0;
		philos[n].finish = false;
		if (n == data->numbers_of_philosophers - 1)
		{
			pthread_mutex_init(&philos[n].left_fork, NULL);
			philos[n].right_fork = &philos[0].left_fork;
		}
		else
		{
			pthread_mutex_init(&philos[n].left_fork, NULL);
			philos[n].right_fork = &philos[n + 1].left_fork;
		}
		n++;
	}
	return (philos);
}

int	init_threads(t_philo *philos)
{
	int	n;

	n = 0;
	gettimeofday(&philos->data->start_time, NULL);
	gettimeofday(&philos->data->current_time, NULL);
	while (n < philos->data->numbers_of_philosophers)
	{
		if (pthread_create(&philos[n].ph, NULL, &rotine, &philos[n]) != 0)
			return (1);
		n++;
	}
	while (philos->data->finish == false)
	{
		check_meals(philos);
		gettimeofday(&philos->data->current_time, NULL);
	}
	n = 0;
	while (n < philos->data->numbers_of_philosophers)
	{
		if (pthread_join(philos[n].ph, NULL) != 0)
			return (2);
		n++;
	}
	return (0);
}