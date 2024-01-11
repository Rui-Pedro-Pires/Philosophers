/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:58:54 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/11 18:10:32 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	*rotine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_info_long(philo->info, &philo->last_meal, gettime());
	thinking(philo);
	while (get_bool(philo->info, &philo->finish) == false)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
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
	philo->start_time = gettime();
	philo->last_meal = gettime();
	pthread_create(&ph, NULL, &rotine, philo);
	set_info_long(philo->info, &philo->start_time, gettime());
	while (get_bool(philo->info, &philo->finish) == false)
		monitoring(philo);
	pthread_join(ph, NULL);
	sem_close(philo->info);
	sem_close(philo->forks);
	sem_close(philo->died);
	return (0);
}

void	eating(t_philo *philo)
{
	long long	time;

	wait_forks(philo);
	if (get_bool(philo->info, &philo->finish) == true || \
	get_info_int(philo->info, &philo->status) == DEAD)
		return (post_forks(philo));
	sem_wait(philo->died);
	time = gettime() - get_info_long(philo->info, &philo->start_time);
	printf("%lld %d has taken a fork\n", time, philo->id);
	printf("%lld %d has taken a fork\n", time, philo->id);
	printf("%lld %d is eating\n", time, philo->id);
	sem_post(philo->died);
	set_info_int(philo->info, &philo->status, EATING);
	set_info_long(philo->info, &philo->last_meal, gettime());
	ft_usleep(philo->data->time_to_eat);
	set_info_long(philo->info, &philo->number_of_meal, \
		(get_info_long(philo->info, &philo->number_of_meal) + 1));
	post_forks(philo);
}

void	sleeping(t_philo *philo)
{
	long long	time;

	if (get_bool(philo->info, &philo->finish) == true || \
		get_info_int(philo->info, &philo->status) != EATING)
		return ;
	sem_wait(philo->died);
	time = gettime() - get_info_long(philo->info, &philo->start_time);
	printf("%lld %d is sleeping\n", time, philo->id);
	sem_post(philo->died);
	set_info_int(philo->info, &philo->status, SLEEPING);
	ft_usleep(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	long long	time;

	if (get_bool(philo->info, &philo->finish) == true || \
		get_info_int(philo->info, &philo->status) == THINKING)
		return ;
	sem_wait(philo->died);
	time = gettime() - get_info_long(philo->info, &philo->start_time);
	printf("%lld %d is thinking\n", time, philo->id);
	sem_post(philo->died);
	set_info_int(philo->info, &philo->status, THINKING);
}