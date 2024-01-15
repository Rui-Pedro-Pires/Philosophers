/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:31:19 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/15 14:24:55 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*rotine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_bool(&philo->data->info, &philo->data->done) != true)
		;
	set_info_long(&philo->philo, \
			&philo->start_time, gettime());
	set_info_long(&philo->data->info, \
			&philo->last_meal, gettime());
	while (get_bool(&philo->data->info, &philo->data->finish) == false)
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	long long	time;

	lock_forks(philo);
	if (get_bool(&philo->data->info, &philo->data->finish) == true || \
	get_info_int(&philo->philo, &philo->status) == DEAD)
		return (unlock_forks(philo));
	time = gettime() - get_info_long(&philo->philo, &philo->start_time);
	printf("%lld %d has taken a fork\n", time, philo->id);
	printf("%lld %d has taken a fork\n", time, philo->id);
	printf("%lld %d is eating\n", time, philo->id);
	set_info_int(&philo->philo, &philo->status, EATING);
	set_info_long(&philo->data->info, &philo->last_meal, gettime());
	ft_usleep(philo->data->time_to_eat);
	if (get_info_long(&philo->data->info, &philo->number_of_meal) \
	!= philo->data->number_of_times_to_eat)
		set_info_long(&philo->philo, &philo->number_of_meal, \
			(get_info_long(&philo->data->info, &philo->number_of_meal) + 1));
	unlock_forks(philo);
}

void	sleeping(t_philo *philo)
{
	long long	time;

	if (get_bool(&philo->data->info, &philo->data->finish) == true || \
		get_info_int(&philo->data->info, &philo->status) != EATING)
		return ;
	time = gettime() - get_info_long(&philo->philo, &philo->start_time);
	printf("%lld %d is sleeping\n", time, philo->id);
	set_info_int(&philo->philo, &philo->status, SLEEPING);
	ft_usleep(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	long long	time;

	if (get_bool(&philo->data->info, &philo->data->finish) == true || \
		get_info_int(&philo->data->info, &philo->status) == THINKING)
		return ;
	time = gettime() - get_info_long(&philo->philo, &philo->start_time);
	printf("%lld %d is thinking\n", time, philo->id);
	set_info_int(&philo->philo, &philo->status, THINKING);
	ft_usleep(1);
}
