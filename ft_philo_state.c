/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:05:43 by faveline          #+#    #+#             */
/*   Updated: 2023/12/01 16:15:41 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	ft_get_t0(t_philo *philo, int flag)
{
	struct timeval	tv;
	int				time;

	if (flag == 0)
	{
		if (gettimeofday(&tv, NULL) < 0)
			return (-1);
		philo->t0 = tv.tv_usec;
		return (0);
	}
	else
	{	
		if (gettimeofday(&tv, NULL) < 0)
			return (-1);
		time = tv.tv_usec;
	}
	return (time);
}

int	ft_print_time(t_philo *philo, int x, int i)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	if (x == 1)
		printf("%ld %d has taken a fork\n", tv.tv_usec - philo->t0, i);
	else if (x == 2)
		printf("%ld %d is eating\n", tv.tv_usec - philo->t0, i);
	else if (x == 3)
		printf("%ld %d is sleeping\n", tv.tv_usec - philo->t0, i);
	else if (x == 4)
		printf("%ld %d is thinking\n", tv.tv_usec - philo->t0, i);
	else if (x == 5)
		printf("%ld %d died\n", tv.tv_usec - philo->t0, i);
	return (1);
}

int	ft_loop_philo(t_philo *philo)
{
	struct timeval	tv;
	int				i;
	suseconds_t		time;

	while (philo->all_ok)
	{	
		i = 0;
		while (i < philo->nbr_p)
		{
			if (time = ft_get_t0(philo, 1) < 0)
				return (-1);
			if (time - philo->pers[i].eat_end > philo->t_death)
			{
				philo->all_ok = 0;
				ft_print_time(philo, 5, i);
			}
			i++;
		}
	}
}
