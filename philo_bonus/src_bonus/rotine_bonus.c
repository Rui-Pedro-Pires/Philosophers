/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:58:54 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/15 17:56:34 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	*rotine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_info_long(philo->info, &philo->last_meal, gettime());
	while (get_bool(philo->info, &philo->finish) == false)
	{
		thinking(philo);
		eating(philo);
		if (get_bool(philo->info, &philo->done) == true)
			return (NULL);
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
	philo->last_meal = gettime();
	philo->start_time = gettime();
	pthread_create(&ph, NULL, &rotine, philo);
	while (get_bool(philo->info, &philo->finish) == false \
	&& get_bool(philo->info, &philo->done) == false)
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
	if (get_bool(philo->info, &philo->finish) == true)
		return (post_forks(philo));
	time = gettime() - get_info_long(philo->info, &philo->start_time);
	sem_wait(philo->died);
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

	if (get_info_int(philo->info, &philo->status) != EATING && \
	get_bool(philo->info, &philo->finish) == true)
		return ;
	time = gettime() - get_info_long(philo->info, &philo->start_time);
	sem_wait(philo->died);
	printf("%lld %d is sleeping\n", time, philo->id);
	sem_post(philo->died);
	set_info_int(philo->info, &philo->status, SLEEPING);
	ft_usleep(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	long long	time;

	if (get_info_int(philo->info, &philo->status) == THINKING && \
	get_bool(philo->info, &philo->finish) == true)
		return ;
	time = gettime() - get_info_long(philo->info, &philo->start_time);
	sem_wait(philo->died);
	printf("%lld %d is thinking\n", time, philo->id);
	sem_post(philo->died);
	set_info_int(philo->info, &philo->status, THINKING);
	ft_usleep(1);
}
