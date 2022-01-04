/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:33:18 by ambelkac          #+#    #+#             */
/*   Updated: 2022/01/04 20:24:59 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo_general
{
	int	nbr_of_philo;
	long int	time_to_die;
	long int	time_to_eat;
	long int	time_to_sleep;
	int	must_eat;
	pthread_mutex_t	time;
	pthread_mutex_t	display;
	pthread_mutex_t	timestamp[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	eating[200];
}				t_pgen;

typedef struct s_philo_data
{
	int left;
	int right;
	pthread_mutex_t	display;
	pthread_mutex_t	time;
	pthread_mutex_t	timestamp;
	pthread_mutex_t	eating;
	int	is_eating;
	int	nbr;
	long int	start_time;
	long int	time_stamp;
	long int	time_to_die;
	long int	time_to_eat;
	long int	time_to_sleep;
	int	must_eat;
	t_pgen		*gen;
}				t_pdata;

void	deallocate_structures(t_pgen *gen, t_pdata **pdata);
int	dispatch_thread(t_pgen *data);
void	*philo_job(void *ptr);
void		custom_usleep(long int usec);
long int	get_elapsed_time(void);
int	is_number(char const *str);
t_pgen	*parse_arg(char **av, int ac);
int	ft_atoi(const char *str);

#endif