/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:05:43 by faveline          #+#    #+#             */
/*   Updated: 2023/12/04 17:43:36 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_time(t_philo *philo, char *str, int i)
{
	struct timeval	tv;
	long			time;

	if (philo->all_ok == 0)
		return (1);
	gettimeofday(&tv, NULL);
	i++;
	time = (useconds_t)tv.tv_usec + tv.tv_sec * 1000000 - philo->t0;
	printf("%ld %d %s\n", time, i, str);
	return (1);
}

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

int	ft_loop_philo(t_philo *philo)
{
	int				i;
	long			time;

	i = 0;
	philo->early_end = 0;
	while (philo->all_ok && ft_check_i_eat(philo) == -1)
	{
		i = 0;
		while (i < philo->nbr_p && philo->all_ok == 1)
		{
			time = ft_get_time();
			if (time - philo->pers[i].eat_end > philo->t_death)
				ft_print_die(philo, i);
			i++;
		}
	}
	philo->all_ok = 0;
	return (1);
}
