/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouali <rouali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:23:44 by rouali            #+#    #+#             */
/*   Updated: 2023/06/22 18:49:04 by rouali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	s_philo	*philo;
	int		data_mat;

	philo = (s_philo *)arg;
	if (philo->id % 2 != 0)
		sleep_ino(philo->info_data->nbr_eat, philo);
	data_mat = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->info_data->write);
		data_mat = philo->info_data->mat;
		pthread_mutex_unlock(&philo->info_data->write);
		if (data_mat)
			break ;
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
	return (NULL);
}

int	create(t_data *data, s_philo *philosophers)
{
	long	t;
	int		i;

	t = ft_curent_time();
	i = 0;
	while (i < data->nbr_philo)
	{
		philosophers[i].info_data = data;
		philosophers[i].fork_right = i;
		philosophers[i].fork_left = (i + 1) % data->nbr_philo;
		philosophers[i].id = i + 1;
		philosophers[i].t_eat = t;
		pthread_create(&philosophers[i].info_data->philo[i], NULL, &routine,
			&philosophers[i]);
		i += 2;
	}
	i = 1;
	while (i < data->nbr_philo)
	{
		philosophers[i].info_data = data;
		philosophers[i].fork_right = i;
		philosophers[i].fork_left = (i + 1) % data->nbr_philo;
		philosophers[i].id = i + 1;
		philosophers[i].t_eat = t;
		pthread_create(&philosophers[i].info_data->philo[i], NULL, &routine,
			&philosophers[i]);
		i += 2;
	}
	return (0);
}

int	main(int ac, char **av)
{
	s_philo *philosophers;

	if (ac < 5 || ac > 6)
	{
		printf("Error\n");
		return (1);
	}
	t_data *data = malloc(sizeof(t_data));
	if (upd_data(data, ac, av) == 1)
	{
		printf("Error\n");
		return (free(data), 1);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	philosophers = malloc(sizeof(s_philo) * ft_atoi(av[1]));
	data->time_created = ft_curent_time();
	data->philo = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	int i = 0;
	pthread_mutex_init(&data->write, NULL);
	while (i < ft_atoi(av[1]))
		pthread_mutex_init(&data->forks[i++], NULL);
	create(data, philosophers);
	while (1)
	{
		i = 0;
		int j = 0;
		int eated = 0;
		int cdead = 0;
		int time_die = 0;
		while (j < data->nbr_philo)
		{
			pthread_mutex_lock(&data->write);
			cdead = philosophers[j].cdead;
			pthread_mutex_unlock(&data->write);
			if (cdead == data->tass_meal)
				eated++;
			j++;
		}
		if (eated == data->nbr_philo)
			return (1);
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

				break ;
			}
			i++;
		}
		if (data->mat)
			break ;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_join(philosophers[i].info_data->philo[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	return (0);
}