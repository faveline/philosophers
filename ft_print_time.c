/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:02:55 by faveline          #+#    #+#             */
/*   Updated: 2023/12/02 18:07:02 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_fork(t_philo *philo, int i)
{
	struct timeval	tv;
	long			time;

	if (philo->all_ok == 0)
		return ;
	gettimeofday(&tv, NULL);
	time = tv.tv_usec + tv.tv_sec * 1000000 - philo->t0;
	printf("%ld %d has taken a fork\n", time, i + 1);
}

void	ft_print_eat(t_philo *philo, int i)
{
	struct timeval	tv;
	long			time;

	if (philo->all_ok == 0)
		return ;
	gettimeofday(&tv, NULL);
	time = tv.tv_usec + tv.tv_sec * 1000000 - philo->t0;
	printf("%ld %d is eating\n", time, i + 1);
}

void	ft_print_sleep(t_philo *philo, int i)
{
	struct timeval	tv;
	long			time;

	if (philo->all_ok == 0)
		return ;
	gettimeofday(&tv, NULL);
	time = tv.tv_usec + tv.tv_sec * 1000000 - philo->t0;
	printf("%ld %d is sleeping\n", time, i + 1);
}

void	ft_print_think(t_philo *philo, int i)
{
	struct timeval	tv;
	long			time;

	if (philo->all_ok == 0)
		return ;
	gettimeofday(&tv, NULL);
	time = tv.tv_usec + tv.tv_sec * 1000000 - philo->t0;
	printf("%ld %d is thinking\n", time, i + 1);
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
