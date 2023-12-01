/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:03:05 by faveline          #+#    #+#             */
/*   Updated: 2023/12/01 12:44:07 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_unlock_fork(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->fork[philo->pers->inc]) != 0)
		return (-5);
	if (philo->inc != philo->nbr_p - 1)
	{
		if (pthread_mutex_unlock(philo->fork[philo->inc + 1]) != 0)
			return (-5);
	}
	else
	{
		if (pthread_mutex_unlock(philo->fork[0]) != 0)
			return (-5);
	}
	return (0);
}

static int	ft_lock_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->fork[philo->inc]) != 0)
		return (-5);
	if (philo->inc != philo->nbr_p - 1)
	{
		if (pthread_mutex_lock(philo->fork[philo->inc + 1]) != 0)
			return (-5);
	}
	else
	{
		if (pthread_mutex_lock(philo->fork[0]) != 0)
			return (-5);
	}
	return (0);
}

static void	*ft_philo(void *ptr)
{
	t_philo	*philo;
	int		error;

	error = 0;
	philo = (t_philo *)ptr;
	while (philo->all_ok == 1)
	{
		ft_lock_fork(philo);




		ft_unlock_fork(philo);
	}
}

static t_person	ft_pers_ini(void)
{
	t_person	pers;

	pers.alive = 1;
	pers.eating = 0;
	pers.sleeping = 0;
	pers.thinking = 1;
	pers.i_eat = 0;
	return (pers);
}

int	ft_creat_philos(t_philo *philo)
{
	int	i;

	philo->pers = (t_person *)malloc(philo->nbr_p * sizeof(t_person));
	if (philo->pers == NULL)
		return (-5);
	philo->fork = (pthread_mutex_t *)malloc(philo->nbr * sizeof(pthread_mutex_t));
	if (philo->fork == NULL)
		return (-5);
	i = 0;
	philo->all_ok = 1;
	memset(&philo->fork, 0, philo->nbr_p);
	while (i < philo->nbr_p)
	{
		philo->pers[i]->inc = i;
		philo->pers[i] = ft_pers_ini();
		if (pthread_mutex_init(philo->fork[i], NULL) < 0)
			return (-6);
		if (pthread_creat(&philo->pers[i]->thread, NULL, ft_philo, &philo) != 0)
			return (-6);
		i++;
	}
	return (1);
}
