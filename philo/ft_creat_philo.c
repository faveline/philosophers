/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:03:05 by faveline          #+#    #+#             */
/*   Updated: 2023/12/07 12:32:22 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_unlock_fork(t_philo *philo, int i)
{
	if (pthread_mutex_unlock(&philo->fork[i]) != 0)
		return (-5);
	if (i != philo->nbr_p - 1)
	{
		if (pthread_mutex_unlock(&philo->fork[i + 1]) != 0)
			return (-5);
	}
	else
	{
		if (pthread_mutex_unlock(&philo->fork[0]) != 0)
			return (-5);
	}
	return (0);
}

static int	ft_lock_fork(t_philo *philo, int i)
{
	if (pthread_mutex_lock(&philo->fork[i]) != 0)
		return (-5);
	ft_print_time(philo, "has taken a fork", i);
	if (i != philo->nbr_p - 1)
	{
		if (pthread_mutex_lock(&philo->fork[i + 1]) != 0)
			return (-5);
	}
	else
	{
		if (pthread_mutex_lock(&philo->fork[0]) != 0)
			return (-5);
	}
	ft_print_time(philo, "has taken a fork", i);
	return (0);
}

static void	*ft_philo(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)ptr;
	i = ft_mutex_philo1(philo);
	if (i < 0)
		return (philo->all_ok = 0, ft_error_philo(-8), NULL);
	while (1)
	{
		if (ft_lock_fork(philo, i) < 0)
			return (philo->all_ok = 0, ft_error_philo(-8), NULL);
		pthread_mutex_lock(&philo->wait);
		if (philo->all_ok == 0)
		{
			if (ft_unlock_fork(philo, i) < 0)
				return (ft_error_philo(-8), NULL);
			pthread_mutex_unlock(&philo->wait);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->wait);
		ft_print_time(philo, "is eating", i);
		usleep(philo->t_eat * 1000);
		pthread_mutex_lock(&philo->def_eat[i]);
		philo->pers[i].eat_end = ft_get_time();
		philo->pers[i].i_eat++;
		pthread_mutex_unlock(&philo->def_eat[i]);
		ft_print_time(philo, "is sleeping", i);
		if (ft_unlock_fork(philo, i) < 0)
			return (philo->all_ok = 0, ft_error_philo(-8), NULL);
		usleep(philo->t_sleep * 1000);
		ft_print_time(philo, "is thinking", i);
	}
	return (NULL);
}

int	ft_creat_philos(t_philo *philo)
{
	int	i;

	if (ft_creat_malloc(philo) < 0)
		return (-5);
	if (ft_ini_mutex(philo) < 0)
		return (-6);
	i = -1;
	ft_get_t0(philo);
	while (++i < philo->nbr_p)
	{
		pthread_mutex_lock(&philo->wait_i);
		philo->inc = i;
		pthread_mutex_unlock(&philo->wait_i);
		philo->pers[i].i_eat = 0;
		if (pthread_create(&philo->pers[i].thread, NULL, ft_philo, philo) != 0)
			return (-6);
		usleep(100);
	}
	return (1);
}
