/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:36:29 by ambelkac          #+#    #+#             */
/*   Updated: 2022/01/04 20:49:07 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	eating(t_pdata *pdata)
{
	pthread_mutex_lock(&(pdata->timestamp));
	pdata->time_stamp = get_elapsed_time() - pdata->start_time;
	pthread_mutex_unlock(&(pdata->timestamp));

	pthread_mutex_lock(&(pdata->gen->forks[pdata->left]));
	pthread_mutex_lock(&(pdata->display));
	printf("%ld %d has taken a fork\n", get_elapsed_time() - pdata->start_time, pdata->nbr + 1);
	pthread_mutex_unlock(&(pdata->display));

	pthread_mutex_lock(&(pdata->gen->forks[pdata->right]));
	pthread_mutex_lock(&(pdata->display));
	printf("%ld %d has taken a fork\n", get_elapsed_time() - pdata->start_time, pdata->nbr + 1);
	pthread_mutex_unlock(&(pdata->display));

	pthread_mutex_lock(&(pdata->display));
	printf("%ld %d is eating\n", get_elapsed_time() - pdata->start_time, pdata->nbr + 1);
	pthread_mutex_unlock(&(pdata->display));

	pthread_mutex_lock(&(pdata->eating));
	pdata->is_eating = 1;
	pthread_mutex_unlock(&(pdata->eating));

	usleep(pdata->time_to_eat);

	pthread_mutex_unlock(&(pdata->gen->forks[pdata->left]));
	pthread_mutex_unlock(&(pdata->gen->forks[pdata->right]));
	pthread_mutex_lock(&(pdata->eating));
	pdata->is_eating = 0;
	pthread_mutex_unlock(&(pdata->eating));
}

void	sleeping(t_pdata *pdata)
{
	pthread_mutex_lock(&(pdata->timestamp));
	pdata->time_stamp = get_elapsed_time() - pdata->start_time;
	pthread_mutex_unlock(&(pdata->timestamp));

	pthread_mutex_lock(&(pdata->display));
	printf("%ld %d is sleeping\n", get_elapsed_time() - pdata->start_time, pdata->nbr + 1);
	pthread_mutex_unlock(&(pdata->display));
	usleep(pdata->time_to_sleep);
}

void	*philo_job(void *ptr)
{
	t_pdata	*pdata;

	pdata = (t_pdata *)ptr;
	if (!pdata->nbr % 2)
		usleep(50);
//	if (pdata->nbr % 2)
//		usleep(10);
//	pthread_mutex_lock(&(pdata->time));
//	pthread_mutex_unlock(&(pdata->time));
//	if (!pdata->nbr % 2)
//		usleep(10);

	printf("start %d : %ld\n", pdata->nbr + 1, get_elapsed_time() - pdata->start_time);

	while (1)
	{
		eating(pdata);
		sleeping(pdata);
		pthread_mutex_lock(&(pdata->display));
		printf("%ld %d is thinking\n", pdata->time_stamp, pdata->nbr + 1);
		pthread_mutex_unlock(&(pdata->display));
	}
	return (0);
}