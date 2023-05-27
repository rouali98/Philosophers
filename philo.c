/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouali <rouali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:23:44 by rouali            #+#    #+#             */
/*   Updated: 2023/05/27 23:14:32 by rouali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long ft_time_now(void)
{
    struct timeval tv;;
    gettimeofday(&tv, NULL);
    long time_ms = (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
    return time_ms;
}

void print(philo_t *philo, char *ac) {
        pthread_mutex_lock(&philo->info->write);
        if (philo->info->mat == 0)
             printf("%ld %d %s\n", (ft_time_now() - philo->info->time_to_start) ,philo->id, ac);
        pthread_mutex_unlock(&philo->info->write);
}

void sleppppp(long t) {
    long time = (ft_time_now() + t);
    while (ft_time_now() < time) {
        usleep(50);
    }
}

void *thread2(void *data)
{
    philo_t *philo;
    philo = (philo_t *)data;
    if (philo->id % 2 != 0) {
        usleep(100);
    }
    while (1)
    {
        print(philo, "is thinking");
        pthread_mutex_lock(&philo->info->forks[philo->i_right]);
        print(philo, "has taken a fork right");
        pthread_mutex_lock(&philo->info->forks[philo->i_left]);
        print(philo, "has taken a fork left");
        philo->last_mil = ft_time_now();
        print(philo, "is eating");
        sleppppp(philo->info->time_to_eat);
        pthread_mutex_unlock(&philo->info->forks[philo->i_left]);
        pthread_mutex_unlock(&philo->info->forks[philo->i_right]);
        print(philo, "is sleeping");
        sleppppp(philo->info->time_to_sleep);
    }
    return NULL;
}

int main(int ac, char **av)
{
    int i;
    
    (void)ac;
    philo_t * phi=NULL;
    information_t *info=NULL;
    info = malloc(sizeof(information_t));
    info->nbr_philo = atoi(av[1]);
    info->time_to_die = atoi(av[2]);
    info->time_to_eat = atoi(av[3]);
    info->time_to_sleep = atoi(av[4]);
    phi = malloc(sizeof(philo_t) * info->nbr_philo);
    info->time_to_start = ft_time_now();
    info->mat = 0;
    int count = 0;

    while (count < info->nbr_philo)
    {
        phi[count].info = info;
        count++;
    }
    phi->info->forks = malloc((sizeof(pthread_mutex_t)) * info->nbr_philo);
    i = 0;
    while(i < phi->info->nbr_philo)
    {
        pthread_mutex_init(&phi->info->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&phi->info->write, NULL);
    i = 0;
    while (i < info->nbr_philo)
    {
        phi[i].id = i + 1;
       i++;
    }
    info->nbr_philo = info->nbr_philo;
    i = 0;
    long time = ft_time_now();
    while(i < phi->info->nbr_philo)
    {
        phi[i].last_mil = time;
        phi[i].i_left = (i + 1) % phi->info->nbr_philo;
        phi[i].i_right = i;
        pthread_create(&phi[i].philo, NULL, &thread2, &phi[i]);
        i++;
    }

    while (1) {
        int i = 0;
        while (i < phi->info->nbr_philo) {
            if ((ft_time_now() - phi[i].last_mil) > phi[i].info->time_to_die)
            {
                pthread_mutex_lock(&phi->info->forks[i]);
                phi->info->mat = 1;
                printf("%ld %d is died\n", (ft_time_now() - phi->info->time_to_start) ,phi->id);
                pthread_mutex_unlock(&phi->info->forks[i]);
                return 0;
            }
            i++;
        }
    }
    i = 0;
    while( i < phi->info->nbr_philo)
    {
        pthread_join(phi[i].philo, NULL);
        i++;
    }
    return (0); 
}