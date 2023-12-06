/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:01:40 by faveline          #+#    #+#             */
/*   Updated: 2023/12/06 14:12:02 by faveline         ###   ########.fr       */
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

void	ft_print_die(t_philo *philo, int i)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (useconds_t)tv.tv_usec / 1000 + tv.tv_sec * 1000 - philo->t0;
	philo->pers[i].ok = 0;
	printf("%ld %d died\n", time, i + 1);
	sem_post(philo->sema_ok);
}
