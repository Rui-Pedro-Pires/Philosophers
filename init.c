/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:05:17 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/09 18:01:54 by ruiolive         ###   ########.fr       */
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
	int		n;

	n = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * data->numbers_of_philosophers);
	if (!philos)
		return (NULL);
	while (n < data->numbers_of_philosophers)
	{
		philos[n].id = n + 1;
		philos[n].data = data;
		philos[n].number_of_meal = 0;
		philos[n].status = ALIVE;
		pthread_mutex_init(&philos[n].left_fork, NULL);
		pthread_mutex_init(&philos[n].philo, NULL);
		if (n == data->numbers_of_philosophers - 1)
			philos[n].right_fork = &philos[0].left_fork;
		else
			philos[n].right_fork = &philos[n + 1].left_fork;
		n++;
	}
	return (philos);
}

int	init_threads(t_philo *philos)
{
	int	n;

	n = 0;
	if (philos->data->numbers_of_philosophers == 1)
		return (mono_philo(philos));
	philos->data->current_time = gettime();
	philos->data->start_time = gettime();
	while (n < philos->data->numbers_of_philosophers)
	{
		set_info_long(&philos[n].philo, &philos[n].last_meal, \
			get_info_long(&philos->data->info, &philos->data->current_time));
		if (pthread_create(&philos[n].ph, NULL, &rotine, &philos[n]) != 0)
			return (2);
		n++;
	}
	while (get_bool(&philos->data->info, &philos->data->finish) == false)
	{
		set_info_long(&philos->data->info, \
			&philos->data->current_time, gettime());
		monitoring(philos);
	}
	return (0);
}
