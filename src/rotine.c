/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:31:19 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/09 18:42:15 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eating(t_philo *philo)
{
	long long	start_time;
	long long	current_time;

	lock_forks(philo);
	if (get_bool(&philo->data->info, &philo->data->finish) == true || \
	get_info_int(&philo->philo, &philo->status) == DEAD
		|| get_info_long(&philo->philo, &philo->number_of_meal) == \
	philo->data->number_of_times_to_eat)
		return (unlock_forks(philo));
	set_info_long(&philo->data->info, &current_time, \
		get_info_long(&philo->data->info, &philo->data->current_time));
	set_info_long(&philo->data->info, &start_time, \
		get_info_long(&philo->data->info, &philo->data->start_time));
	printf("%lld %d has taken a fork\n", current_time - start_time, philo->id);
	printf("%lld %d has taken a fork\n", current_time - start_time, philo->id);
	printf("%lld %d is eating\n", current_time - start_time, philo->id);
	set_info_int(&philo->philo, &philo->status, EATING);
	set_info_long(&philo->data->info, &philo->last_meal, \
		get_info_long(&philo->data->info, &philo->data->current_time));
	ft_usleep(philo->data->time_to_eat);
	set_info_long(&philo->philo, &philo->number_of_meal, \
		(get_info_long(&philo->data->info, &philo->number_of_meal) + 1));
	unlock_forks(philo);
}

void	sleeping(t_philo *philo)
{
	long long	start_time;
	long long	current_time;

	if (get_bool(&philo->data->info, &philo->data->finish) == true || \
		get_info_int(&philo->data->info, &philo->status) != EATING)
		return ;
	set_info_long(&philo->data->info, &current_time, \
		get_info_long(&philo->data->info, &philo->data->current_time));
	set_info_long(&philo->data->info, &start_time, \
		get_info_long(&philo->data->info, &philo->data->start_time));
	printf("%lld %d is sleeping\n", current_time - start_time, philo->id);
	set_info_int(&philo->philo, &philo->status, SLEEPING);
	ft_usleep(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	long long	start_time;
	long long	current_time;

	if (get_bool(&philo->data->info, &philo->data->finish) == true || \
		get_info_int(&philo->data->info, &philo->status) == THINKING)
		return ;
	set_info_long(&philo->data->info, &current_time, \
		get_info_long(&philo->data->info, &philo->data->current_time));
	set_info_long(&philo->data->info, &start_time, \
		get_info_long(&philo->data->info, &philo->data->start_time));
	printf("%lld %d is thinking\n", current_time - start_time, philo->id);
	set_info_int(&philo->philo, &philo->status, THINKING);
}

void	*rotine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		thinking(philo);
	while (get_bool(&philo->data->info, &philo->data->finish) == false)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
