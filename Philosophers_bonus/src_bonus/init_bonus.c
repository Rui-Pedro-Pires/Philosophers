/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:27:48 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/12 14:21:23 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

t_data	init_data(int argc, char **argv)
{
	t_data	data;

	data.numbers_of_philosophers = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.number_of_times_to_eat = ft_atoi(argv[5]);
	else
		data.number_of_times_to_eat = -1;
	return (data);
}

t_philo	*init_philos(t_data *data)
{
	t_philo		*philos;
	sem_t		*forks;
	sem_t		*died;
	int			i;

	philos = (t_philo *)malloc(sizeof(t_philo) * data->numbers_of_philosophers);
	sem_unlink(FORK);
	sem_unlink(DIED);
	forks = sem_open(FORK, O_CREAT, 0600, data->numbers_of_philosophers);
	died = sem_open(DIED, O_CREAT, 0600, 1);
	i = 0;
	while (i < data->numbers_of_philosophers)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].value = 0;
		philos[i].finish = false;
		philos[i].number_of_meal = 0;
		i++;
	}
	sem_close(died);
	sem_close(forks);
	return (philos);
}

int	init_processes(t_philo *philos)
{
	int			check_return;
	int			i;

	i = -1;
	while (++i < philos->data->numbers_of_philosophers)
	{
		philos[i].pid = fork();
		if (philos[i].pid == 0)
		{
			process(&philos[i]);
			return (0);
		}
	}
	i = -1;
	while (1)
	{
		check_return = waitpid(-1, NULL, WNOHANG);
		if (check_return != 0)
		{
			while (++i < philos->data->numbers_of_philosophers - 1)
				kill (philos[i].pid, SIGINT);
			break ;
		}
	}
	sleep(1);
	return (0);
}
