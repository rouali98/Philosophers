/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouali <rouali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:23:44 by rouali            #+#    #+#             */
/*   Updated: 2023/06/23 01:45:19 by rouali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_countari_mort(t_data *data, t_philo *philosophers)
{
	int		eated;
	int		j;
	int		cdead;

	eated = 0;
	cdead = 0;
	j = 0;
	while (j < data->nbr_philo)
	{
		if (data->nbr_philo == 1)
			return (0);
		pthread_mutex_lock(&data->write);
		cdead = philosophers[j].cdead;
		pthread_mutex_unlock(&data->write);
		if (cdead == data->tass_meal)
			eated++;
		j++;
		if (eated == data->nbr_philo)
			return (-1);
	}
	return (0);
}

int	mort(t_data *data, t_philo *philosophers)
{
	int		i;
	long	time_die;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_lock(&data->write);
		time_die = (ft_curent_time() - philosophers[i].t_eat);
		pthread_mutex_unlock(&data->write);
		if (time_die > data->nbr_die)
		{
			pthread_mutex_lock(&data->write);
			data->mat = 1;
			pthread_mutex_unlock(&data->write);
			pthread_mutex_lock(&data->write);
			printf("%ld %d died\n", (ft_curent_time() - data->time_created),
				philosophers[i].id);
			pthread_mutex_unlock(&data->write);
			if (data->nbr_philo == 1)
				pthread_mutex_unlock(&data->forks[philosophers[i].fork_right]);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	all_died(int ac, t_data *data, t_philo *philosophers)
{
	if (ac == 6)
	{
		if (ft_countari_mort(data, philosophers) == -1)
			return (-1);
	}
	if (mort(data, philosophers) == -1)
		return (-1);
	if (data->mat)
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philosophers;
	t_data	*data;
	int		i;

	if (ac < 5 || ac > 6)
		ft_err();
	data = malloc(sizeof(t_data));
	if (upd_data(data, ac, av) == 1)
		ft_err_data(data);
	data->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	philosophers = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	data->time_created = ft_curent_time();
	data->philo = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	i = 0;
	pthread_mutex_init(&data->write, NULL);
	while (i < ft_atoi(av[1]))
		pthread_mutex_init(&data->forks[i++], NULL);
	create(data, philosophers);
	while (1)
	{
		if (all_died(ac, data, philosophers) == -1)
			return (-1);
	}
	destroy_mutex(data, philosophers);
	return (0);
}
