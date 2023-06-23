/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouali <rouali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:06:02 by rouali            #+#    #+#             */
/*   Updated: 2023/06/23 12:51:20 by rouali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_routine(t_philo	*philo, int data_mat)
{
	while (1)
	{
		pthread_mutex_lock(&philo->info_data->write);
		data_mat = philo->info_data->mat;
		pthread_mutex_unlock(&philo->info_data->write);
		if (data_mat)
			return ;
		pthread_mutex_lock(&philo->info_data->forks[philo->fork_right]);
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->info_data->forks[philo->fork_left]);
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->info_data->write);
		philo->t_eat = ft_curent_time();
		pthread_mutex_unlock(&philo->info_data->write);
		ft_print(philo, "is eating");
		pthread_mutex_lock(&philo->info_data->write);
		philo->cdead++;
		pthread_mutex_unlock(&philo->info_data->write);
		sleep_ino(philo->info_data->nbr_eat, philo);
		pthread_mutex_unlock(&philo->info_data->forks[philo->fork_left]);
		pthread_mutex_unlock(&philo->info_data->forks[philo->fork_right]);
		ft_print(philo, "is sleeping");
		sleep_ino(philo->info_data->nbr_sleep, philo);
		ft_print(philo, "is thinking");
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		data_mat;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		sleep_ino(philo->info_data->nbr_eat, philo);
	data_mat = 0;
	ft_routine (philo, data_mat);
	return (NULL);
}
