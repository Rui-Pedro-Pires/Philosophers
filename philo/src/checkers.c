/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:03:36 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/16 11:16:01 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

void	*mono_rotine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("%d %d has taken a fork\n", 0, philo->id);
	ft_usleep(philo->data->time_to_die);
	printf("%d %d died\n", philo->data->time_to_die, philo->id);
	return (NULL);
}

int	mono_philo(t_philo *philos)
{
	pthread_create(&philos->ph, NULL, &mono_rotine, &philos[0]);
	pthread_join(philos->ph, NULL);
	return (1);
}
