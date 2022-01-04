/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:36:29 by ambelkac          #+#    #+#             */
/*   Updated: 2022/01/04 17:56:25 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	eating(t_pdata *pdata)
{
	pthread_mutex_lock(&(pdata->time));
	pthread_mutex_lock(&(pdata->timestamp));
	pdata->time_stamp = get_elapsed_time();
	pthread_mutex_unlock(&(pdata->time));
	pthread_mutex_unlock(&(pdata->timestamp));

	pthread_mutex_lock(&(pdata->left));
	pthread_mutex_lock(&(pdata->display));
	printf("%ld %d has taken a fork\n", pdata->time_stamp, pdata->nbr + 1);
	pthread_mutex_unlock(&(pdata->display));

	pthread_mutex_lock(&(pdata->right));
	pthread_mutex_lock(&(pdata->display));
	printf("%ld %d has taken a fork\n", pdata->time_stamp, pdata->nbr + 1);
	pthread_mutex_unlock(&(pdata->display));

	pthread_mutex_lock(&(pdata->display));
	printf("%ld %d is eating\n", pdata->time_stamp, pdata->nbr + 1);
	pthread_mutex_unlock(&(pdata->display));

	pthread_mutex_lock(&(pdata->eating));
	pdata->is_eating = 1;
	pthread_mutex_unlock(&(pdata->eating));

	usleep(pdata->time_to_eat);

	pthread_mutex_lock(&(pdata->eating));
	pdata->is_eating = 0;
	pthread_mutex_unlock(&(pdata->eating));
	pthread_mutex_unlock(&(pdata->left));
	pthread_mutex_unlock(&(pdata->right));
}

void	sleeping(t_pdata *pdata)
{
	pthread_mutex_lock(&(pdata->time));
	pthread_mutex_lock(&(pdata->timestamp));
	pdata->time_stamp = get_elapsed_time();
	pthread_mutex_unlock(&(pdata->timestamp));
	pthread_mutex_unlock(&(pdata->time));

	pthread_mutex_lock(&(pdata->display));
	printf("%ld %d is sleeping\n", pdata->time_stamp, pdata->nbr + 1);
	pthread_mutex_unlock(&(pdata->display));
	usleep(pdata->time_to_sleep);
}

void	*philo_job(void *ptr)
{
	t_pdata	*pdata;

	pdata = (t_pdata *)ptr;
//	if (pdata->nbr % 2)
//		usleep(10);
//	pthread_mutex_lock(&(pdata->time));
//	pthread_mutex_unlock(&(pdata->time));
//	if (!pdata->nbr % 2)
//		usleep(10);
	printf("start of thread : %d\n", pdata->nbr);
	while (1)
	{
		eating(pdata);
		sleeping(pdata);
		pthread_mutex_lock(&(pdata->display));
		printf("%ld %d is thinking\n", pdata->time_stamp, pdata->nbr + 1);
		pthread_mutex_unlock(&(pdata->display));
	}
}