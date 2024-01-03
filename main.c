/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:55:32 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/03 17:38:05 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	rec;
	int	dest;

	i = 0;
	rec = 0;
	dest = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		rec = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		dest = dest * 10 + (str[i] - '0');
		i++;
	}
	if (rec == 1)
		return (dest *= -1);
	return (dest);
}

long	gettime(t_philo *philo)
{
	long endtime;
	struct timeval execute_time;
	gettimeofday(&execute_time, NULL);
	endtime = (execute_time.tv_sec * 1000 + execute_time.tv_usec) 
	- (philo->start_time.tv_sec * 1000 + philo->start_time.tv_usec);
	return (endtime);
}

int	is_dead(t_philo *philo)
{
	if (philo->data->finish == true)
		return (1);
	return (0);
}

void	eating(t_philo *philo)
{
	if (pthread_mutex_lock(philo->right_fork) != 0)
		return ;
	printf("%ldms | Philo %d has taken the right fork\n", gettime(philo), philo->id);
	if (pthread_mutex_lock(&philo->left_fork) != 0)
		return ;
	printf("%ldms | Philo %d has taken the left fork\n", gettime(philo), philo->id);
	printf("%ldms | Philo %d has fucked\n", gettime(philo), philo->id);
	usleep(philo->data->time_to_eat * 1000);
	if (pthread_mutex_unlock(philo->right_fork) != 0)
		return ;
	printf("%ldms | Philo %d droped the right fork\n", gettime(philo), philo->id);
	if (pthread_mutex_unlock(&philo->left_fork) != 0)
		return ;
	printf("%ldms | Philo %d droped the left fork\n", gettime(philo), philo->id);
}

void	sleeping(t_philo *philo)
{
	printf("%ldms | Philo %d is sleeping\n", gettime(philo), philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	printf("%ldms | Philo %d is thinking\n", gettime(philo), philo->id);
	while (pthread_mutex_lock(philo->right_fork) != 0 && pthread_mutex_lock(&philo->left_fork) != 0)	
		usleep(1 * 100);
	return ;
}

void	*rotine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		eating(philo);
	while (!is_dead(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

t_data	init_data(int argc, char **argv)
{
	t_data	data;

	data.numbers_of_philosophers = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.finish = false;
	if (argc == 6)
		data.number_of_times_to_eat = ft_atoi(argv[5]);
	else
		data.number_of_times_to_eat = -1;
	return (data);
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*philos;
	struct	timeval start_time;
	int	n;

	n = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * data->numbers_of_philosophers);
	if (!philos)
		return (NULL);
	gettimeofday(&start_time, NULL);
	while (n < data->numbers_of_philosophers)
	{
		philos[n].start_time = start_time;
		philos[n].id = n + 1;
		philos[n].data = data;
		if (n == data->numbers_of_philosophers - 1)
		{
			pthread_mutex_init(&philos->left_fork, NULL);
			philos[n].right_fork = &philos[0].left_fork;
		}
		else
		{
			pthread_mutex_init(&philos->left_fork, NULL);
			philos[n].right_fork = &philos[n + 1].left_fork;
		}
		n++;
	}
	return (philos);
}

int	init_threads(t_philo *philos)
{
	pthread_t ph[philos->data->numbers_of_philosophers];
	int	n;

	n = 0;
	while (n < philos->data->numbers_of_philosophers)
	{
		if (pthread_create(&ph[n], NULL, &rotine, &philos[n]) != 0)
			return (1);
		n++;
	}
	n = 0;
	while (n < philos->data->numbers_of_philosophers)
	{
		if (pthread_join(ph[n], NULL) != 0)
			return (2);
		n++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	t_philo	*philos;
	t_data	data;

	data = init_data(argc, argv);
	philos = init_philos(&data);
	init_threads(philos);
}