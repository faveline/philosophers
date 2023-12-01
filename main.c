/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:05:17 by faveline          #+#    #+#             */
/*   Updated: 2023/12/01 11:14:54 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
void	*thread_1(void *arg)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ft_printf("%d\n", tv.tv_usec);
	gettimeofday(&tv, NULL);
	ft_printf("%d\n", tv.tv_usec);
	gettimeofday(&tv, NULL);
	ft_printf("%d\n", tv.tv_usec);
	gettimeofday(&tv, NULL);
	ft_printf("%d\n", tv.tv_usec);
	pthread_exit(0);
}
*/

int	main(int argc, char *argv[])
{
	int		error;
	t_philo	philo;

	if (error = ft_creat_struct(argc, argv, &philo) < 0)
		return (ft_error_philo(error), 1);
	if (error = ft_creat_philos(&philo) < 0)
		return (ft_error_philo(error), ft_exterminate(&philo), 1);

	//pthread_join(thread1, NULL);
	ft_exterminate(&philo);
	return (0);
}
