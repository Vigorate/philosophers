/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:36:29 by ambelkac          #+#    #+#             */
/*   Updated: 2022/01/19 16:53:22 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	display_status(t_pdata *pdata, char *msg)
{
	if (interrupt(1, pdata->m_interrupt))
		return ;
	pthread_mutex_lock(pdata->display);
	printf("%ld %d %s\n", get_elapsed_time()
		- pdata->start_time, pdata->nbr + 1, msg);
	pthread_mutex_unlock(pdata->display);
}

void	take_forks(t_pdata *pdata)
{
	if (pdata->nbr % 2)
	{
		pthread_mutex_lock(pdata->left);
		display_status(pdata, "has taken a fork");
		pthread_mutex_lock(pdata->right);
		display_status(pdata, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(pdata->right);
		display_status(pdata, "has taken a fork");
		pthread_mutex_lock(pdata->left);
		display_status(pdata, "has taken a fork");
	}	
}

void	eating(t_pdata *pdata)
{
	take_forks(pdata);
	display_status(pdata, "is eating");
	pthread_mutex_lock(pdata->timestamp);
	pdata->time_stamp = get_elapsed_time();
	pthread_mutex_unlock(pdata->timestamp);
	custom_usleep(pdata->time_to_eat);
	pthread_mutex_unlock(pdata->right);
	pthread_mutex_unlock(pdata->left);
	if (pdata->m_eat_count)
	{
		pthread_mutex_lock(pdata->m_eat_count);
		if (pdata->must_eat > 0)
			--(pdata->must_eat);
		pthread_mutex_unlock(pdata->m_eat_count);
	}	
}

int	solo_philo(t_pdata *pdata)
{
	if (pdata->solo_philo)
	{
		display_status(pdata, "has taken a fork");
		while (1)
		{
			if (interrupt(1, pdata->m_interrupt))
				return (1);
		}
	}
	return (0);
}

void	*philo_job(void *ptr)
{
	t_pdata	*pdata;

	pdata = (t_pdata *)ptr;
	if (solo_philo(pdata))
		return (NULL);
	if (pdata->nbr % 2)
		custom_usleep(10);
	while (1)
	{
		eating(pdata);
		if (interrupt(1, pdata->m_interrupt))
			return (NULL);
		display_status(pdata, "is sleeping");
		custom_usleep(pdata->time_to_sleep);
		if (interrupt(1, pdata->m_interrupt))
			return (NULL);
		display_status(pdata, "is thinking");
		if (interrupt(1, pdata->m_interrupt))
			return (NULL);
	}
	return (NULL);
}
