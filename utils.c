/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:04:16 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/08 17:31:42 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	dest;

	i = 0;
	dest = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (-1);
		dest = dest * 10 + (str[i] - '0');
		i++;
	}
	return (dest);
}

long long	gettime(void)
{
	long long current_time;
	struct timeval st;

	
	gettimeofday(&st, NULL);
	current_time = (long long)st.tv_sec * 1000 + (long long)st.tv_usec / 1000;
	return (current_time);
}

int	monitoring(t_philo *philos)
{
	long	last_meal;
	int	n;
	int count;
	
	n = 0;
	count = 0;
	while (n < philos->data->numbers_of_philosophers)
	{
		philos->data->current_time = gettime();
		last_meal = philos[n].last_meal;
		if (philos->data->time_to_die <= (philos->data->current_time - last_meal) && philos[n].status != EATING)
		{
			printf("%lld %d died\n", philos->data->current_time - philos->data->start_time, philos[n].id);
			philos[n].status = DEAD;
			philos->data->finish = true;
			break;
		}
		if (philos->data->number_of_times_to_eat == philos[n].number_of_meal)
			count++;
		n++;
	}
	if (philos->data->numbers_of_philosophers == count)
		philos->data->finish = true;
	return (0);
}

int    ft_usleep(long long milliseconds)
{
    long long    start;

    start = gettime();
    while ((gettime() - start) < milliseconds)
        usleep(500);
    return (0);
}

int	checker(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}
