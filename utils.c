/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:04:16 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/04 16:45:17 by ruiolive         ###   ########.fr       */
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

	endtime = (philo->data->current_time.tv_sec * 1000 + philo->data->current_time.tv_usec / 1000) 
	- (philo->data->start_time.tv_sec * 1000 + philo->data->start_time.tv_usec / 1000);
	return (endtime);
}

void	finish_update(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->info);
	if (philo->number_of_meal == philo->data->number_of_times_to_eat)
		philo->finish = true;
	pthread_mutex_unlock(&philo->data->info);
}

int	finish(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->info);
	if (philo->data->finish == true)
	{
		pthread_mutex_unlock(&philo->data->info);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->info);
	return (0);
}

void	check_meals(t_philo *philos)
{
	int	n;
	int	count;

	n = 0;
	count = 0;
	while (n < philos->data->numbers_of_philosophers)
	{
		if (philos[n].finish == true)
			count++;
		n++;
	}
	if (count == philos->data->numbers_of_philosophers)
		philos->data->finish = true;
}