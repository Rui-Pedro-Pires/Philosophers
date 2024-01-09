/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:03:36 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/09 18:26:26 by ruiolive         ###   ########.fr       */
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

int	mono_philo(t_philo *philos)
{
	printf("%d %d is thinking\n", 0, philos[0].id);
	ft_usleep(philos->data->time_to_die);
	printf("%d %d died\n", philos->data->time_to_die, philos[0].id);
	return (1);
}
