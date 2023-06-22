/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouali <rouali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2147/09/29 00:00:00 by 56:21 by ro       #+#    #+#             */
/*   Updated: 2023/06/22 20:43:48 by rouali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int			i;
	int			j;
	long int	result;

	i = 0;
	j = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i] == '-')
			return (-1);
	if (str[i] && ((str[i] >= 'a' && str[i] <= 'z') \
		|| (str[i] >= 'A' && str[i] <= 'Z')))
		return (-1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		result = result * 10 + str[i++] - '0';
		if ((result) > 2147483647)
			return (-1);
	}
	return (result * j);
}
