/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:05:43 by faveline          #+#    #+#             */
/*   Updated: 2023/12/07 16:34:18 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_time(t_philo *philo, char *str, int i)
{
	struct timeval	tv;
	long			time;

	sem_wait(philo->print);
	gettimeofday(&tv, NULL);
	i++;
	time = (useconds_t)tv.tv_usec / 1000 + tv.tv_sec * 1000 - philo->t0;
	printf("%ld %d %s\n", time, i, str);
	sem_post(philo->print);
	return (1);
}

static void	*ft_check_all(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	sem_wait(philo->sema_ok);
	sem_post(philo->check);
	return (NULL);
}

static void	*ft_check_nbr(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)ptr;
	i = 0;
	while (i < (philo->nbr_eat * philo->nbr_p))
	{
		sem_wait(philo->sema_nbr);
		i++;
	}
	sem_post(philo->check);
	return (NULL);
}

int	ft_loop_philo(t_philo *philo)
{
	int			i;
	pthread_t	check_nbr;
	pthread_t	check_all;

	if (pthread_create(&check_all, NULL, ft_check_all, philo) != 0)
		return (-6);
	if (philo->nbr_eat != -1)
	{
		if (pthread_create(&check_nbr, NULL, ft_check_nbr, philo) != 0)
			return (-6);
	}
	i = -1;
	sem_wait(philo->check);
	while (++i < philo->nbr_p)
		kill(philo->pers[i].child, SIGKILL);
	sem_post(philo->sema_ok);
	pthread_join(check_all, NULL);
	if (philo->nbr_eat != -1)
	{
		i = -1;
		while (++i < (philo->nbr_eat * philo->nbr_p))
			sem_post(philo->sema_nbr);
		pthread_join(check_nbr, NULL);
	}
	return (1);
}
