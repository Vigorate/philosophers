/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:36:29 by ambelkac          #+#    #+#             */
/*   Updated: 2022/01/08 18:11:53 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	display_status(t_pdata *pdata, char *msg)
{
	pthread_mutex_lock(pdata->display);
	printf("%ld %d %s\n", get_elapsed_time() - pdata->start_time, pdata->nbr + 1, msg);
	pthread_mutex_unlock(pdata->display);
}

void	eating(t_pdata *pdata)
{
	pthread_mutex_lock(pdata->right);
	display_status(pdata, "has taken a fork");


	pthread_mutex_lock(pdata->left);
	display_status(pdata, "has taken a fork");


	display_status(pdata, "is eating");

	pthread_mutex_lock(pdata->eating);
	pdata->is_eating = 1;
	pthread_mutex_unlock(pdata->eating);

	usleep(pdata->time_to_eat);

	pthread_mutex_lock(pdata->eating);
	pdata->is_eating = 0;
	pthread_mutex_unlock(pdata->eating);

	pthread_mutex_unlock(pdata->left);
	pthread_mutex_unlock(pdata->right);

	pthread_mutex_lock(pdata->timestamp);
	pdata->time_stamp = get_elapsed_time();
	pthread_mutex_unlock(pdata->timestamp);
}

void	sleeping(t_pdata *pdata)
{
	display_status(pdata, "is sleeping");
	usleep(pdata->time_to_sleep);
}

void	*philo_job(void *ptr)
{
	t_pdata	*pdata;

	pdata = (t_pdata *)ptr;
	pdata->start_time = get_elapsed_time();
	pdata->time_stamp = get_elapsed_time();
	if (!pdata->nbr % 2)
		usleep(10);

	printf("start %d : %ld\n", pdata->nbr + 1, get_elapsed_time() - pdata->start_time);

	while (1)
	{
		eating(pdata);
		sleeping(pdata);
		display_status(pdata, "is thinking");
	}
	return (0);
}