/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:05:43 by faveline          #+#    #+#             */
/*   Updated: 2023/12/07 12:29:30 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_time(t_philo *philo, char *str, int i)
{
	struct timeval	tv;
	long			time;

	if (pthread_mutex_lock(&philo->wait) != 0)
		return (-1);
	if (philo->all_ok == 0)
	{
		if (pthread_mutex_unlock(&philo->wait) != 0)
			return (-1);
		return (1);
	}
	gettimeofday(&tv, NULL);
	i++;
	time = (useconds_t)tv.tv_usec / 1000 + tv.tv_sec * 1000 - philo->t0;
	printf("%ld %d %s\n", time, i, str);
	if (pthread_mutex_unlock(&philo->wait) != 0)
		return (-1);
	return (1);
}

static int	ft_check_i_eat(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->nbr_eat == -1)
		return (-1);
	while (i < philo->nbr_p)
	{
		if (philo->eat_i[i] < philo->nbr_eat)
			return (-1);
		i++;
	}
	return (1);
}

static int	ft_ini_eat(t_philo *philo)
{
	philo->eat_t = (long *)malloc(philo->nbr_p * sizeof(long));
	if (philo->eat_t == NULL)
		return (-1);
	philo->eat_i = (int *)malloc(philo->nbr_p * sizeof(int));
	if (philo->eat_i == NULL)
		return (-1);
	memset(philo->eat_i, 0, philo->nbr_p);
	return (1);
}

int	ft_loop_philo(t_philo *philo)
{
	int		i;
	long	time;
	int		ok;

	ok = 1;
	if (ft_ini_eat(philo) < 0)
		return (-5);
	while (ok && ft_check_i_eat(philo) == -1)
	{
		i = -1;
		while (++i < philo->nbr_p)
		{
			if (ft_mutex_loop1(philo, i) < 0)
				return (philo->all_ok = 0, -8);
			time = ft_get_time();
			if (time - philo->eat_t[i] > philo->t_death)
			{
				if (ft_print_die(philo, i) < 0)
					return (philo->all_ok = 0, -8);
			}
		}
		ok = philo->all_ok;
	}
	ft_mutex_loop2(philo);
	return (1);
}
