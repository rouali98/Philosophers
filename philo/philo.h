/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouali <rouali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:23:39 by rouali            #+#    #+#             */
/*   Updated: 2023/06/23 00:25:19 by rouali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_mutex_t	*forks;
	long			time_created;
	int				nbr_philo;
	int				nbr_eat;
	int				nbr_die;
	int				nbr_sleep;
	int				mat;
	int				tass_meal;
	pthread_mutex_t	write;
	pthread_t		*philo;
}					t_data;

typedef struct philo
{
	int				id;
	long			t_eat;
	int				fork_left;
	int				fork_right;
	int				died;
	int				cdead;
	t_data			*info_data;
}					t_philo;

int		ft_atoi(char *str);

long	ft_curent_time(void);
int		sleep_ino(int time, t_philo *philo);
void	ft_print(t_philo *philo, char *msg);
int		upd_data(t_data *data, int ac, char **av);

void	*routine(void *arg);

int		create(t_data *data, t_philo *philosophers);

int		destroy_mutex(t_data *data, t_philo *philosophers);
int		ft_err_data(t_data *data);
int		ft_err(void);

#endif
