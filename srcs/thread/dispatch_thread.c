/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:42:46 by ambelkac          #+#    #+#             */
/*   Updated: 2022/01/18 22:39:29 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int		interrupt(int type, pthread_mutex_t *m_value)
{
	static int is_interrupt = 0;

	pthread_mutex_lock(m_value);
	if (type == 1 && is_interrupt == 1)
	{
		pthread_mutex_unlock(m_value);
		return (1);
	}
	if (type == 0)
	{
		is_interrupt = 1;
	}
	pthread_mutex_unlock(m_value);
	return (0);
}

void	dispatch_forks(t_pdata *pdata, t_pgen *data, int i)
{
	if (!i)
	{
		pdata->right = &(data->forks[i]);
		pdata->left = &(data->forks[data->nbr_of_philo - 1]);
	}
	else
	{
		pdata->right = &(data->forks[i]);
		pdata->left = &(data->forks[i - 1]);
	}
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
	pdata->m_eat_count = &(data->m_eat_count[i]);
	dispatch_forks(pdata, data, i);
	return (pdata);
}

void	death_loop(t_pgen *data, t_pdata **pdata, long int start_time)
{
	int	i;
	int	eat_count;

	i = 0;
	eat_count = 0;
	while(1)
	{
		if (i == data->nbr_of_philo)
			i = 0;

		pthread_mutex_lock((pdata[i])->m_eat_count);
		if (pdata[i]->must_eat < 0)
			eat_count++;
		pthread_mutex_unlock((pdata[i])->m_eat_count);
		if (eat_count >= data->nbr_of_philo)
		{
			interrupt(0, &data->m_interrupt);
			return ;
		}
		pthread_mutex_lock((pdata[i])->timestamp);
		if (get_elapsed_time() - pdata[i]->time_stamp > data->time_to_die)
		{
			interrupt(0, &data->m_interrupt);
			pthread_mutex_unlock((pdata[i])->timestamp);
			pthread_mutex_lock((pdata[i]->display));
			printf("%ld %d died\n", get_elapsed_time() - start_time, i + 1);
			pthread_mutex_unlock((pdata[i]->display));
			return ;
		}
		pthread_mutex_unlock((pdata[i])->timestamp);
		++i;
	}
}

int	dispatch_thread(t_pgen *data)
{
	pthread_t	threads[data->nbr_of_philo];
	int			i;
	t_pdata		*pdata[data->nbr_of_philo];
	long int	start_time;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		pdata[i] = allocate_philo_data(data, i);
		if (!pdata[i])
			return (1);
		++i;
	}
	i = 0;
	start_time = get_elapsed_time();
	while (i < data->nbr_of_philo)
	{
		pdata[i]->start_time = start_time;
		pdata[i]->time_stamp = start_time;
		pthread_create(&(threads[i]), NULL, philo_job, pdata[i]);
		++i;
	}
	death_loop(data, pdata, start_time);
	clean_exit(data, pdata, threads);
	return (0);
}