/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:54:50 by faveline          #+#    #+#             */
/*   Updated: 2023/12/07 13:28:49 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_mutex_loop1(t_philo *philo, int i)
{
	if (pthread_mutex_lock(&philo->def_eat[i]) != 0)
		return (-6);
	philo->eat_t[i] = philo->pers[i].eat_end;
	philo->eat_i[i] = philo->pers[i].i_eat;
	if (pthread_mutex_unlock(&philo->def_eat[i]) != 0)
		return (-6);
	return (1);
}

void	ft_mutex_loop2(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->wait) != 0)
		ft_error_philo(-8);
	philo->all_ok = 0;
	if (pthread_mutex_unlock(&philo->wait) != 0)
		ft_error_philo(-8);
}

int	ft_mutex_philo1(t_philo *philo)
{
	int	i;

	if (pthread_mutex_lock(&philo->wait_i) != 0)
		return (-1);
	i = philo->inc;
	if (pthread_mutex_unlock(&philo->wait_i) != 0)
		return (-1);
	if (pthread_mutex_lock(&philo->def_eat[i]) != 0)
		return (-1);
	philo->pers[i].eat_end = ft_get_time();
	if (pthread_mutex_unlock(&philo->def_eat[i]) != 0)
		return (-1);
	return (i);
}

int	ft_mutex_philo2(t_philo *philo, int i)
{
	if (pthread_mutex_lock(&philo->wait) != 0)
		return (-1);
	if (philo->all_ok == 0)
	{
		if (pthread_mutex_unlock(&philo->wait) != 0)
			return (-1);
		if (ft_unlock_fork(philo, i) < 0)
			return (-1);
		return (2);
	}
	if (pthread_mutex_unlock(&philo->wait) != 0)
		return (-1);
	if (ft_print_time(philo, "is eating", i) < 0)
		return (-1);
	return (1);
}

int	ft_mutex_philo3(t_philo *philo, int i)
{
	if (pthread_mutex_lock(&philo->def_eat[i]) != 0)
		return (-1);
	philo->pers[i].eat_end = ft_get_time();
	philo->pers[i].i_eat++;
	if (pthread_mutex_unlock(&philo->def_eat[i]) != 0)
		return (-1);
	if (ft_print_time(philo, "is sleeping", i) < 0)
		return (-1);
	if (ft_unlock_fork(philo, i) < 0)
		return (-1);
	return (1);
}
