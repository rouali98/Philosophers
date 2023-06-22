/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouali <rouali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:06:53 by rouali            #+#    #+#             */
/*   Updated: 2023/06/23 00:31:03 by rouali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create(long curent_time, t_data *data, t_philo *philosophers)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		philosophers[i].info_data = data;
		philosophers[i].fork_right = i;
		philosophers[i].fork_left = (i + 1) % data->nbr_philo;
		philosophers[i].id = i + 1;
		philosophers[i].t_eat = curent_time;
		pthread_create(&philosophers[i].info_data->philo[i], \
			NULL, &routine, &philosophers[i]);
		i += 2;
	}
}

int	create(t_data *data, t_philo *philosophers)
{
	long	curent_time;
	int		i;

	curent_time = ft_curent_time();
	i = 0;
	ft_create(curent_time, data, philosophers);
	i = 1;
	while (i < data->nbr_philo)
	{
		philosophers[i].info_data = data;
		philosophers[i].fork_right = i;
		philosophers[i].fork_left = (i + 1) % data->nbr_philo;
		philosophers[i].id = i + 1;
		philosophers[i].t_eat = curent_time;
		pthread_create(&philosophers[i].info_data->philo[i], \
			NULL, &routine, &philosophers[i]);
		i += 2;
	}
	return (0);
}
