/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:03:05 by faveline          #+#    #+#             */
/*   Updated: 2023/12/04 17:43:10 by faveline         ###   ########.fr       */
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
	i = philo->inc;
	philo->pers[i].eat_end = ft_get_time();
	philo->inc = -1;
	while (philo->all_ok == 1)
	{
		if (ft_lock_fork(philo, i) < 0)
			return (philo->all_ok = 0, ft_error_philo(-8), NULL);
		ft_print_time(philo, "is eating", i);
		usleep(philo->t_eat);
		philo->pers[i].eat_end = ft_get_time();
		ft_print_time(philo, "is sleeping", i);
		if (ft_unlock_fork(philo, i) < 0)
			return (philo->all_ok = 0, ft_error_philo(-8), NULL);
		philo->pers[i].i_eat++;
		usleep(philo->t_sleep);
		ft_print_time(philo, "is thinking", i);
	}
	return (NULL);
}

static void	*ft_check_early(void *ptr)
{
	t_philo	*philo;
	int		i;
	long	time;

	philo = (t_philo *)ptr;
	philo->early_end = 1;
	while (philo->all_ok == 1 && philo->early_end == 1)
	{
		i = 0;
		while (i < philo->nbr_p && philo->pers[i].i_eat != -1)
		{
			time = ft_get_time();
			if (time - philo->pers[i].eat_end > philo->t_death)
				ft_print_die(philo, i);
			i++;
		}	
	}
	return (NULL);
}

int	ft_creat_philos(t_philo *philo)
{
	int	i;

	if (ft_creat_malloc(philo) < 0)
		return (-5);
	i = -1;
	if (pthread_create(&philo->early, NULL, ft_check_early, philo) != 0)
		return (-6);
	ft_get_t0(philo);
	while (++i < philo->nbr_p)
	{
		philo->inc = i;
		philo->pers[i].i_eat = 0;
		if (pthread_mutex_init(&philo->fork[i], NULL) < 0)
			return (-6);
		if (pthread_create(&philo->pers[i].thread, NULL, ft_philo, philo) != 0)
			return (-6);
		while (philo->inc != -1)
			i = i * 1;
	}
	return (1);
}
