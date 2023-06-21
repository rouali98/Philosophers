/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouali <rouali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:23:44 by rouali            #+#    #+#             */
/*   Updated: 2023/06/21 21:35:28 by rouali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long ft_curent_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long time = (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
    return time;
}

int sleep_ino(int time, s_philo *philo) {
    (void)philo;
    long newtime = ft_curent_time();
    while (ft_curent_time() < (newtime + time)) {
        usleep(200);
    }
    return 0;
}

int update_philo(t_data *data, s_philo *philosophers) {
    int i = 0;
    long t = ft_curent_time();
    while (i < data->nbr_philo)
    {
        philosophers[i].info_data = data;
        philosophers[i].id = i + 1;
        philosophers[i].fork_right = i; 
        philosophers[i].fork_left = (i + 1) % data->nbr_philo;
        philosophers[i].t_eat = t;
        i++;
    }
    return 0;
}

void ft_print(s_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->info_data->write);
    if (philo->info_data->mat == 0) {
        printf ("%ld %d %s\n", (ft_curent_time() - philo->info_data->time_created),philo->id, msg);
    }
    pthread_mutex_unlock(&philo->info_data->write);
}

void *routine(void *arg)
{
    s_philo *philo = (s_philo *)arg;

    if (philo->id % 2 == 0)
        sleep_ino(philo->info_data->nbr_eat, philo);
    while (!philo->info_data->mat) 
    {
        pthread_mutex_lock(&philo->info_data->forks[philo->fork_left]);
        ft_print(philo, "has taken a fork");
        pthread_mutex_lock(&philo->info_data->forks[philo->fork_right]);
        ft_print(philo, "has taken a fork");
        ft_print(philo, "is eating");
        philo->t_eat = ft_curent_time();
        pthread_mutex_unlock(&philo->info_data->forks[philo->fork_right]);
        pthread_mutex_unlock(&philo->info_data->forks[philo->fork_left]);
        sleep_ino(philo->info_data->nbr_eat, philo);
        ft_print(philo, "is sleeping");
        sleep_ino(philo->info_data->nbr_sleep, philo);
        ft_print(philo, "is thinking");
    }
    return NULL;
}

int create(t_data *data, s_philo *philosophers)
{
    // update_philo(data, philosophers);
    long t = ft_curent_time();
    int i = 0;
    while (i < data->nbr_philo)
    {
        philosophers[i].info_data = data;
        philosophers[i].id = i + 1;
        philosophers[i].fork_right = i; 
        philosophers[i].fork_left = (i + 1) % data->nbr_philo;
        philosophers[i].t_eat = t;
        pthread_create(&philosophers[i].philo, NULL, &routine, &philosophers[i]);
        i++;
    }
    return (0);
}

int update_forks(t_data *data) {
    int i = 0;
    while (i < data->nbr_philo)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    return 0;
}

int upd_data(t_data *data, int ac, char **av)
{
    data->nbr_philo = ft_atoi(av[1]);
    data->nbr_die = ft_atoi(av[2]);
    data->nbr_eat = ft_atoi(av[3]);
    data->nbr_sleep = ft_atoi(av[4]);
    data->forks = malloc (sizeof(pthread_mutex_t) * data->nbr_philo);
    pthread_mutex_init(&data->write, NULL);
    if (!data->forks)
        return (1);
    int i = 0;
    while (i < data->nbr_philo)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
     (void)ac;
     return (0);
}

int main(int ac, char **av)
{
    if (ac >= 5 && ac <= 6)
    {
        s_philo *philosophers;

        t_data *data = malloc(sizeof(t_data));
        upd_data(data, ac, av);
        philosophers = malloc(sizeof(s_philo) * ft_atoi(av[1]));
        data->time_created = ft_curent_time();
        create(data, philosophers);
        int i = 0;
        while (1)
        {
            i = 0;
            while (i < data->nbr_philo)
            {
                if ((ft_curent_time() - philosophers[i].t_eat) > data->nbr_die)
                {
                    data->mat = 1;
                    pthread_mutex_lock(&data->write);
                    printf("%ld %d died\n", (ft_curent_time() - data->time_created), philosophers[i].id);
                    pthread_mutex_unlock(&data->write);
                    break;
                }
            }
            if (data->mat)
                break;
        }
        while (i < ft_atoi(av[1])) 
        {
            pthread_join(philosophers[i].philo, NULL);
            i++;
        }
        i = 0;
    }
    return 0;
}