/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:58:54 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/11 16:44:10 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	*rotine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_bool(philo->info, &philo->finish) == false)
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}

int	process(t_philo *philo)
{
	pthread_t	ph;

	sem_unlink(INFO);
	philo->forks = sem_open(FORK, 0);
	philo->died = sem_open(DIED, 0);
	philo->info = sem_open(INFO, O_CREAT, 0600, 1);
	philo->current_time = gettime();
	philo->start_time = gettime();
	philo->last_meal = gettime();
	pthread_create(&ph, NULL, &rotine, philo);
	while (get_bool(philo->info, &philo->finish) == false)
	{
		set_info_long(philo->info, &philo->current_time, gettime());
		monitoring(philo);
	}
	pthread_join(ph, NULL);
	sem_close(philo->info);
	sem_close(philo->forks);
	sem_close(philo->died);
	return (0);
}

void	eating(t_philo *philo)
{
	long long	start_time;
	long long	current_time;

	wait_forks(philo);
	if (get_bool(philo->info, &philo->finish) == true || \
	get_info_int(philo->info, &philo->status) == DEAD)
		return (post_forks(philo));
	set_info_long(philo->info, &current_time, \
		get_info_long(philo->info, &philo->current_time));
	set_info_long(philo->info, &start_time, \
		get_info_long(philo->info, &philo->start_time));
	sem_wait(philo->died);
	printf("%lld %d has taken a fork\n", current_time - start_time, philo->id);
	printf("%lld %d has taken a fork\n", current_time - start_time, philo->id);
	printf("%lld %d is eating\n", current_time - start_time, philo->id);
	sem_post(philo->died);
	set_info_int(philo->info, &philo->status, EATING);
	set_info_long(philo->info, &philo->last_meal, \
		get_info_long(philo->info, &philo->current_time));
	ft_usleep(philo->data->time_to_eat);
	set_info_long(philo->info, &philo->number_of_meal, \
		(get_info_long(philo->info, &philo->number_of_meal) + 1));
	post_forks(philo);
}

void	sleeping(t_philo *philo)
{
	long long	start_time;
	long long	current_time;

	if (get_bool(philo->info, &philo->finish) == true || \
		get_info_int(philo->info, &philo->status) != EATING)
		return ;
	set_info_long(philo->info, &current_time, \
		get_info_long(philo->info, &philo->current_time));
	set_info_long(philo->info, &start_time, \
		get_info_long(philo->info, &philo->start_time));
	sem_wait(philo->died);
	printf("%lld %d is sleeping\n", current_time - start_time, philo->id);
	sem_post(philo->died);
	set_info_int(philo->info, &philo->status, SLEEPING);
	ft_usleep(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	long long	start_time;
	long long	current_time;

	if (get_bool(philo->info, &philo->finish) == true || \
		get_info_int(philo->info, &philo->status) == THINKING)
		return ;
	set_info_long(philo->info, &current_time, \
		get_info_long(philo->info, &philo->current_time));
	set_info_long(philo->info, &start_time, \
		get_info_long(philo->info, &philo->start_time));
	sem_wait(philo->died);
	printf("%lld %d is thinking\n", current_time - start_time, philo->id);
	sem_post(philo->died);
	set_info_int(philo->info, &philo->status, THINKING);
}
