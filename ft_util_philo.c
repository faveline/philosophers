/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:55:34 by faveline          #+#    #+#             */
/*   Updated: 2023/12/01 15:54:34 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error_philo(int error)
{
	if (error == -1)
		printf("Wrong number of argument");
	if (error == -2)
		printf("The numbers should be ints");
	if (error == -3)
		printf("Characters other than digit are refuse");
	if (error == -4)
		printf("Only positive integers are accepted");
	if (error == -5)
		printf("A malloc failed");
	if (error == -6)
		printf("Thread creation failed");
	if (error == -7)
		printf("Problem getting the time");
	if (error == -8)
		printf("Problem while de.locking mutex");
}

void	ft_exterminate(t_philo *philo)
{
	int	i;

	i = -1;
	while (i < philo->nbr_p)
		pthread_mutex_destroy(&philo->fork[i]);
	free(philo->fork);
	free(philo->pers);	
}
