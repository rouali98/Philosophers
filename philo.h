/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouali <rouali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:23:39 by rouali            #+#    #+#             */
/*   Updated: 2023/06/21 19:32:50 by rouali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_data
{
    pthread_mutex_t *forks;
    long time_created;
    int nbr_philo;
    int nbr_eat;
    int nbr_die;
    int nbr_sleep;
    int mat;
    pthread_mutex_t write;
} t_data;

typedef struct philo
{
    int id;
    pthread_t philo;
    long t_eat;
    int fork_left;
    int fork_right;
    int died;
    t_data *info_data;
} s_philo;

int	ft_atoi(const char *str);


#endif
