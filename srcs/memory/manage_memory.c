/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:31:08 by ambelkac          #+#    #+#             */
/*   Updated: 2022/01/19 16:49:44 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	allocate_tab_philo_data(t_pdata **pdata, t_pgen *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		pdata[i] = allocate_philo_data(data, i);
		if (!pdata[i])
			return (1);
		++i;
	}
	return (0);
}

t_pdata	*allocate_philo_data(t_pgen *data, int i)
{
	t_pdata	*pdata;

	pdata = malloc(sizeof(t_pdata));
	if (!pdata)
		return (NULL);
	pdata->nbr = i;
	pdata->time_stamp = 0;
	pdata->must_eat = data->must_eat;
	pdata->time_to_die = data->time_to_die;
	pdata->time_to_eat = data->time_to_eat;
	pdata->time_to_sleep = data->time_to_sleep;
	pdata->display = &data->display;
	pdata->timestamp = &(data->timestamp[i]);
	pdata->m_interrupt = &(data->m_interrupt);
	if (data->nbr_of_philo == 1)
		pdata->solo_philo = 1;
	else
		pdata->solo_philo = 0;
	if (data->must_eat > 0)
		pdata->m_eat_count = &(data->m_eat_count[i]);
	else
		pdata->m_eat_count = NULL;
	dispatch_forks(pdata, data, i);
	return (pdata);
}

void	clean_exit(t_pgen *data, t_pdata **pdata, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		pthread_join(threads[i], NULL);
		++i;
	}
	i = 0;
	while (i < data->nbr_of_philo)
	{
		free(pdata[i]);
		pthread_mutex_destroy(&(data->timestamp)[i]);
		pthread_mutex_destroy(&(data->forks)[i]);
		pthread_mutex_destroy(&(data->m_eat_count)[i]);
		++i;
	}
	free(pdata);
	free(threads);
	pthread_mutex_destroy(&data->m_interrupt);
	pthread_mutex_destroy(&data->display);
	exit(0);
}
