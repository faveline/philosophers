/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:03:05 by faveline          #+#    #+#             */
/*   Updated: 2023/12/12 10:40:03 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_unlock_fork(t_philo *philo, int i)
{
	if (pthread_mutex_unlock(&philo->fork[i]) != 0)
		return (-5);
	if (i != philo->nbr_p - 1)
	{
		if (pthread_mutex_unlock(&philo->fork[i + 1]) != 0)
			return (-5);
	}
	else if (philo->nbr_p != 1)
	{
		if (pthread_mutex_unlock(&philo->fork[0]) != 0)
			return (-5);
	}
	return (0);
}

static int	ft_2nd_fork(t_philo *philo, int i)
{
	if (i != philo->nbr_p - 1 && i != 0)
	{
		if (pthread_mutex_lock(&philo->fork[i + 1]) != 0)
			return (-5);
		if (ft_print_time(philo, "has taken a fork", i) < 0)
			return (-5);
	}
	else if (i == philo->nbr_p - 1)
	{
		if (pthread_mutex_lock(&philo->fork[0]) != 0)
			return (-5);
		if (ft_print_time(philo, "has taken a fork", i) < 0)
			return (-5);
	}
	return (1);
}

static int	ft_lock_fork(t_philo *philo, int i)
{
	if (philo->nbr_p == 1)
	{
		if (pthread_mutex_lock(&philo->fork[0]) != 0)
			return (-5);
		if (ft_print_time(philo, "has taken a fork", i) < 0)
			return (-5);
		if (philo->nbr_p == 1)
			return (usleep(1100 * philo->t_death));
	}
	if (i == 0)
	{
		if (pthread_mutex_lock(&philo->fork[1]) != 0)
			return (-5);
		if (ft_print_time(philo, "has taken a fork", i) < 0)
			return (-5);
	}
	if (pthread_mutex_lock(&philo->fork[i]) != 0)
		return (-5);
	if (ft_print_time(philo, "has taken a fork", i) < 0)
		return (-5);
	if (ft_2nd_fork(philo, i) < 0)
		return (-5);
	return (0);
}

static void	*ft_philo(void *ptr)
{
	t_philo	*philo;
	int		i;
	int		error;

	philo = (t_philo *)ptr;
	i = ft_mutex_philo1(philo);
	if (i < 0)
		return (philo->all_ok = 0, ft_error_philo(-8), NULL);
	while (1)
	{
		if (ft_lock_fork(philo, i) < 0)
			return (philo->all_ok = 0, ft_error_philo(-8), NULL);
		error = ft_mutex_philo2(philo, i);
		if (error < 0)
			return (philo->all_ok = 0, ft_error_philo(-8), NULL);
		else if (error == 2)
			return (NULL);
		usleep(philo->t_eat * 1000);
		if (ft_mutex_philo3(philo, i) < 0)
			return (philo->all_ok = 0, ft_error_philo(-8), NULL);
		usleep(philo->t_sleep * 1000);
		if (ft_print_time(philo, "is thinking", i) < 0)
			return (philo->all_ok = 0, ft_error_philo(-8), NULL);
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
		if (pthread_mutex_lock(&philo->wait_i) != 0)
			return (philo->all_ok = 0, -8);
		philo->inc = i;
		if (pthread_mutex_unlock(&philo->wait_i) != 0)
			return (philo->all_ok = 0, -8);
		philo->pers[i].i_eat = 0;
		if (pthread_create(&philo->pers[i].thread, NULL, ft_philo, philo) != 0)
			return (philo->all_ok = 0, -6);
		if (ft_mutex_loop_philo(philo) < 0)
			return (philo->all_ok = 0, -8);
	}
	return (1);
}
