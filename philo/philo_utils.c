/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouali <rouali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:24:55 by rouali            #+#    #+#             */
/*   Updated: 2023/06/22 21:34:02 by rouali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Current_Time
long	ft_curent_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

// Sleep
int	sleep_ino(int time, t_philo *philo)
{
	long	newtime;
	int		mort;

	(void)philo;
	newtime = ft_curent_time();
	while (ft_curent_time() < (newtime + time))
	{
		pthread_mutex_lock(&philo->info_data->write);
		mort = philo->info_data->mat;
		pthread_mutex_unlock(&philo->info_data->write);
		if (mort == 1)
			break ;
		usleep(250);
	}
	return (0);
}

// Print
void	ft_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->info_data->write);
	if (philo->info_data->mat == 0)
		printf("%ld %d %s\n", (ft_curent_time() \
			- philo->info_data->time_created), philo->id, msg);
	pthread_mutex_unlock(&philo->info_data->write);
}

// Update_Data
int	upd_data(t_data *data, int ac, char **av)
{
	data->nbr_philo = ft_atoi(av[1]);
	if (ft_atoi(av[1]) == -1)
		return (1);
	data->nbr_die = ft_atoi(av[2]);
	if (ft_atoi(av[2]) == -1)
		return (1);
	data->nbr_eat = ft_atoi(av[3]);
	if (ft_atoi(av[3]) == -1)
		return (1);
	data->nbr_sleep = ft_atoi(av[4]);
	if (ft_atoi(av[4]) == -1)
		return (1);
	if (ac == 6)
	{
		data->tass_meal = ft_atoi(av[5] + 1);
		if (ft_atoi(av[5]) <= 0)
			return (1);
	}
	else
		data->tass_meal = -1;
	return (0);
}

// Update_Philosophers
int	update_philo(t_data *data, t_philo *philosophers)
{
	int		i;
	long	curent_time;

	i = 0;
	curent_time = ft_curent_time();
	while (i < data->nbr_philo)
	{
		philosophers[i].id = i + 1;
		philosophers[i].fork_left = (i + 1) % data->nbr_philo;
		philosophers[i].t_eat = curent_time;
		philosophers[i].info_data = data;
		philosophers[i].fork_right = i;
		i++;
	}
	return (0);
}
