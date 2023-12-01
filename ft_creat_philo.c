/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:03:05 by faveline          #+#    #+#             */
/*   Updated: 2023/12/01 18:11:26 by faveline         ###   ########.fr       */
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
	ft_print_time(philo, 1, i);
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
	ft_print_time(philo, 1, i);
	return (0);
}

static void	*ft_philo(void *ptr)
{
	t_philo	*philo;
	int		error;
	int		i;


	error = 0;
	philo = (t_philo *)ptr;
	i = philo->inc;
	philo->inc = -1;

	if ((philo->pers[i].eat_end = ft_get_t0(philo, 1)) < 0)
		return (ft_error_philo(-7), philo->all_ok = 0, NULL);
	while (philo->all_ok == 1)
	{
		if (ft_lock_fork(philo, i) < 0)
			return (ft_error_philo(-8), philo->all_ok = 0, NULL);
		ft_print_time(philo, 2, i);
		usleep((useconds_t)philo->t_eat);
		if ((philo->pers[i].eat_end = ft_get_t0(philo, 1)) < 0)
			return (ft_error_philo(-7), philo->all_ok = 0, NULL);
		ft_unlock_fork(philo, i);
		philo->pers[i].i_eat++;
		ft_print_time(philo, 3, i);
		usleep(philo->t_sleep);
		ft_print_time(philo, 4, i);
	}
	return (NULL);
}

int	ft_creat_philos(t_philo *philo)
{
	int	i;

	philo->pers = (t_person *)malloc(philo->nbr_p * sizeof(t_person));
	if (philo->pers == NULL)
		return (-5);
	philo->fork = (pthread_mutex_t *)malloc(philo->nbr_p * sizeof(pthread_mutex_t));
	if (philo->fork == NULL)
		return (-5);
	i = 0;

	philo->all_ok = 1;

	if (ft_get_t0(philo, 0) < 0)
		return (-7);
	while (i < philo->nbr_p)
	{
		philo->inc = i;
		philo->pers[i].i_eat = 0;
		if (pthread_mutex_init(&philo->fork[i], NULL) < 0)
			return (-6);
		if (pthread_create(&philo->pers[i].thread, NULL, ft_philo, philo) != 0)
			return (-6);
		while (philo->inc != -1)
			i = i * 1;	
		i++;
	}


	return (1);
}
