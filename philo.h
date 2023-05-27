/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouali <rouali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:23:39 by rouali            #+#    #+#             */
/*   Updated: 2023/05/27 23:05:04 by rouali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
#include <sys/time.h>

// pthread_mutex_t mutex;

typedef struct s_information
{
    int nbr_philo;
    pthread_mutex_t *forks;
    pthread_mutex_t write;
    long int time_to_start;
    long int time_to_sleep;
    long int time_to_eat;
    long int time_to_die;
    int mat;
} information_t;

typedef struct s_philo
{
    int id;
    pthread_t philo;
    int i_left;
    int i_right;
    long last_mil;
    information_t *info;
} philo_t;

#endif
