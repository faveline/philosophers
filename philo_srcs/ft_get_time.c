/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:01:40 by faveline          #+#    #+#             */
/*   Updated: 2023/12/04 17:33:54 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_get_t0(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	philo->t0 = (useconds_t)tv.tv_usec + tv.tv_sec * 1000000;
}

long	ft_get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (useconds_t)tv.tv_usec + tv.tv_sec * 1000000;
	return (time);
}

void	ft_print_die(t_philo *philo, int i)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_usec + tv.tv_sec * 1000000 - philo->t0;
	philo->all_ok = 0;
	printf("%ld %d died\n", time, i + 1);
}

int	ft_creat_malloc(t_philo *philo)
{
	int	i;

	philo->pers = (t_person *)malloc(philo->nbr_p * sizeof(t_person));
	if (philo->pers == NULL)
		return (-5);
	philo->fork = (pthread_mutex_t *)malloc(philo->nbr_p
			* sizeof(pthread_mutex_t));
	if (philo->fork == NULL)
		return (-5);
	i = 0;
	while (i < philo->nbr_p)
	{
		philo->pers[i].eat_end = 9223372036854775807;
		philo->pers[i].i_eat = -1;
		i++;
	}
	philo->all_ok = 1;
	return (1);
}
