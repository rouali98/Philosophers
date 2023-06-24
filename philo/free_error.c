/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouali <rouali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:11:21 by rouali            #+#    #+#             */
/*   Updated: 2023/06/23 15:49:59 by rouali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutex(t_data *data, t_philo *philosophers)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_join(data->philo[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	free(data->forks);
	free(data->philo);
	free(data);
	free(philosophers);
	(void)philosophers;
	return (0);
}

int	ft_err_data(t_data *data)
{
	printf("Error\n");
	return (free(data), 1);
}

int	ft_err(void)
{
	printf("Error\n");
	return (1);
}
