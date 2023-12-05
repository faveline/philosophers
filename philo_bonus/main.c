/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:05:17 by faveline          #+#    #+#             */
/*   Updated: 2023/12/05 15:22:56 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	int		error;
	t_philo	philo;

	error = ft_creat_struct(argc, argv, &philo);
	if (error < 0)
		return (ft_error_philo(error), 1);
	error = ft_creat_philos(&philo);
	if (error < 0)
		return (ft_error_philo(error), ft_exterminate(&philo), 1);
	error = ft_loop_philo(&philo);
	if (error < 0)
		return (ft_error_philo(error), ft_exterminate(&philo), 1);
	ft_result(&philo);
	ft_exterminate(&philo);
	return (0);
}	
