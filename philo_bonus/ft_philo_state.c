/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:05:43 by faveline          #+#    #+#             */
/*   Updated: 2023/12/05 15:34:00 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_time(t_philo *philo, char *str, int i)
{
	struct timeval	tv;
	long			time;

	if (philo->all_ok == 0)
		return (1);
	gettimeofday(&tv, NULL);
	i++;
	time = (useconds_t)tv.tv_usec + tv.tv_sec * 1000000 - philo->t0;
	printf("%ld %d %s\n", time, i, str);
	return (1);
}

void	*ft_check_all(void *ptr)
{
	t_philo *philo;
	int		i;

	i = 0;
	philo = (t_philo *)ptr;
	sem_wait(philo->sema_ok);
	while (i < philo->nbr_p && philo->pers[i].ok != 1)
	{
		kill(philo->pers[i].child, SIGKILL);
		i++;
	}
	philo->all_ok = 0;
	return (NULL);
}

static void	*ft_check_nbr(void *ptr)
{
	t_philo *philo;
	int		i;

	philo = (t_philo *)ptr;
	i = 0;
	while (i < (philo->nbr_eat * philo->nbr_p) && philo->all_ok == 1)
	{
		sem_wait(philo->sema_nbr);	
		i++;
	}
	i = 0;
	while (i < philo->nbr_p)
	{
		kill(philo->pers[i].child, SIGKILL);
		i++;
	}
	philo->nbr_ok = 1;
	return (NULL);
}

int	ft_loop_philo(t_philo *philo)
{
	int			i;
	pthread_t	check_nbr;

	i = 0;
	philo->nbr_ok = 0;
	if (philo->nbr_eat != -1)
	{
		if (pthread_create(&check_nbr, NULL, ft_check_nbr, philo) != 0)
			return (-6);
	}
	while (philo->all_ok == 1 && philo->nbr_ok == 0)
		i = i;
	return (1);
}
