/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:05:43 by faveline          #+#    #+#             */
/*   Updated: 2023/12/02 18:09:21 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
int	ft_print_time(t_philo *philo, int x, int i)
{
	struct timeval	tv;
	long			time;

	if (philo->all_ok == 0)
		return (1);
	gettimeofday(&tv, NULL);
	time = tv.tv_usec + tv.tv_sec * 1000000 - philo->t0;
	if (x == 1)
		printf("%ld %d has taken a fork\n", time, i + 1);
	else if (x == 2)
		printf("%ld %d is eating\n", time, i + 1);
	else if (x == 3)
		printf("%ld %d is sleeping\n", time, i + 1);
	else if (x == 4)
		printf("%ld %d is thinking\n", time, i + 1);
	else if (x == 5)
	{
		philo->all_ok = 0;
		printf("%ld %d died\n", time, i + 1);
	}
	return (1);
}
*/
int	ft_check_i_eat(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->nbr_eat == -1)
		return (-1);
	while (i < philo->nbr_p)
	{
		if (philo->pers[i].i_eat < philo->nbr_eat)
			return (-1);
		i++;
	}
	return (1);
}

int	ft_check_early(t_philo *philo, int i)
{
	int		j;
	long	time;

	j = 0;
	while (j < i)
	{
		time = ft_get_time(philo);
		if (time - philo->pers[j].eat_end > philo->t_death)
		{
			ft_print_die(philo, j);
			return (-1);
		}
		j++;
	}
	return (1);
}

int	ft_loop_philo(t_philo *philo)
{
	struct timeval	tv;
	int				i;
	long			time;

	i = 0;
	while (philo->all_ok && ft_check_i_eat(philo) == -1)
	{	
		i = 0;
		while (i < philo->nbr_p && philo->all_ok == 1)
		{
			time = ft_get_time(philo);
			if (time - philo->pers[i].eat_end > philo->t_death)
				ft_print_die(philo, i);
			i++;
		}
	}
	philo->all_ok = 0;
	return (1);
}
