/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:36:29 by ambelkac          #+#    #+#             */
/*   Updated: 2022/01/13 00:14:27 by amine            ###   ########.fr       */
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
	if (pdata->nbr % 2)
	{
		pthread_mutex_lock(pdata->right);
		display_status(pdata, "has taken a fork");
		pthread_mutex_lock(pdata->left);
		display_status(pdata, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(pdata->left);
		display_status(pdata, "has taken a fork");
		pthread_mutex_lock(pdata->right);
		display_status(pdata, "has taken a fork");
	}
	display_status(pdata, "is eating");

	pthread_mutex_lock(pdata->timestamp);
	pdata->time_stamp = get_elapsed_time();
	pthread_mutex_unlock(pdata->timestamp);

	custom_usleep(pdata->time_to_eat);

	pthread_mutex_unlock(pdata->right);
	pthread_mutex_unlock(pdata->left);
}

void	sleeping(t_pdata *pdata)
{
	display_status(pdata, "is sleeping");
	custom_usleep(pdata->time_to_sleep);
}

void	*philo_job(void *ptr)
{
	t_pdata	*pdata;

	pdata = (t_pdata *)ptr;
	if (!pdata->nbr % 2)
		custom_usleep(10);

	while (1)
	{
		eating(pdata);
		sleeping(pdata);
		display_status(pdata, "is thinking");
	}
	return (0);
}