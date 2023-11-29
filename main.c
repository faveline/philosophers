/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:05:17 by faveline          #+#    #+#             */
/*   Updated: 2023/11/29 13:50:10 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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


int	main(void)
{
	pthread_t thread1;
	pthread_create(&thread1, NULL, thread_1, NULL);
	pthread_join(thread1, NULL);
	return (0);
}
