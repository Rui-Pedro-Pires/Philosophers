/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:17:26 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/10 13:47:34 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

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
