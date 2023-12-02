/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:03:05 by faveline          #+#    #+#             */
/*   Updated: 2023/12/02 18:08:58 by faveline         ###   ########.fr       */
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
	ft_print_fork(philo, i);
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
	ft_print_fork(philo, i);
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
	philo->pers[i].eat_end = ft_get_time(philo);
	philo->inc = -1;
	while (philo->all_ok == 1)
	{
		if (ft_lock_fork(philo, i) < 0)
			return (philo->all_ok = 0, ft_error_philo(-8), NULL);
		ft_print_eat(philo, i);
		usleep(philo->t_eat);
		philo->pers[i].eat_end = ft_get_time(philo);
		ft_print_sleep(philo, i);
		if (ft_unlock_fork(philo, i) < 0)
			return (philo->all_ok = 0, ft_error_philo(-8), NULL);
		philo->pers[i].i_eat++;
		usleep(philo->t_sleep);
		ft_print_think(philo, i);
		usleep(1);
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
	philo->t0 = 0;
	while (i < philo->nbr_p)
	{
		philo->inc = i;
		philo->pers[i].i_eat = 0;
		if (pthread_mutex_init(&philo->fork[i], NULL) < 0)
			return (-6);
		if (philo->t0 == 0)
			ft_get_t0(philo);	
		if (pthread_create(&philo->pers[i].thread, NULL, ft_philo, philo) != 0)
			return (-6);
		while (philo->inc != -1)
			i = i * 1;	
		if (ft_check_early(philo, i) < 0)
			return (0);
		i++;
	}
	return (1);
}
