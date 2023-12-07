/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:01:40 by faveline          #+#    #+#             */
/*   Updated: 2023/12/07 12:15:06 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_get_t0(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	philo->t0 = (useconds_t)tv.tv_usec / 1000 + tv.tv_sec * 1000;
}

long	ft_get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (useconds_t)tv.tv_usec / 1000 + tv.tv_sec * 1000;
	return (time);
}

int	ft_print_die(t_philo *philo, int i)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_usec / 1000 + tv.tv_sec * 1000 - philo->t0;
	if (pthread_mutex_lock(&philo->wait) != 0)
		return (-1);
	if (philo->all_ok == 0)
	{
		if (pthread_mutex_unlock(&philo->wait) != 0)
			return (-1);
		return (0);
	}
	philo->all_ok = 0;
	if (pthread_mutex_unlock(&philo->wait) != 0)
		return (-1);
	printf("%ld %d died\n", time, i + 1);
	return (1);
}

int	ft_creat_malloc(t_philo *philo)
{
	philo->pers = (t_person *)malloc(philo->nbr_p * sizeof(t_person));
	if (philo->pers == NULL)
		return (-5);
	philo->fork = (pthread_mutex_t *)malloc(philo->nbr_p
			* sizeof(pthread_mutex_t));
	if (philo->fork == NULL)
		return (-5);
	philo->def_eat = (pthread_mutex_t *)malloc(philo->nbr_p
			* sizeof(pthread_mutex_t));
	if (philo->def_eat == NULL)
		return (-5);
	philo->all_ok = 1;
	return (1);
}

int	ft_ini_mutex(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nbr_p)
	{	
		if (pthread_mutex_init(&philo->fork[i], NULL) < 0)
			return (-6);
		if (pthread_mutex_init(&philo->def_eat[i], NULL) < 0)
			return (-6);
	}
	if (pthread_mutex_init(&philo->wait, NULL) < 0)
		return (-6);
	if (pthread_mutex_init(&philo->wait_i, NULL) < 0)
		return (-6);
	return (1);
}
