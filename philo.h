/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:07:31 by faveline          #+#    #+#             */
/*   Updated: 2023/11/29 18:09:35 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_philo
{
	int	nbr_p;
	int	t_death;
	int	t_eat;
	int	t_sleep;
	int	nbr_eat;
}					t_philo;

char	*ft_itoa_philo(int nbr);
int		ft_atoi_philo(const char *str);
int		ft_creat_struct(int argc, char *argv[]);

#endif
