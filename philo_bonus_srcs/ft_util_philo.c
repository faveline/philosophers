/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:55:34 by faveline          #+#    #+#             */
/*   Updated: 2023/12/05 16:47:57 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error_philo(int error)
{
	if (error == -1)
		printf("Wrong number of argument\n");
	if (error == -2)
		printf("The numbers should be ints\n");
	if (error == -3)
		printf("Characters other than digit are refuse\n");
	if (error == -4)
		printf("Only strictly positive integers are accepted\n");
	if (error == -5)
		printf("A malloc failed\n");
	if (error == -6)
		printf("Thread creation failed\n");
	if (error == -7)
		printf("Problem getting the time\n");
	if (error == -9)
		printf("Problem while creating child\n");
	if (error == -10)
		printf("Problem inside child\n");
}

void	ft_exterminate(t_philo *philo)
{
	sem_close(philo->sema_fork);
	sem_unlink("semafork");
	sem_close(philo->sema_ok);
	sem_unlink("semaok");
	if (philo->nbr_eat > 0)
	{	
		sem_close(philo->sema_nbr);
		sem_unlink("semanbr");
	}
	free(philo->pers);
}