/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:42:46 by ambelkac          #+#    #+#             */
/*   Updated: 2022/01/19 16:56:13 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	interrupt(int type, pthread_mutex_t *m_value)
{
	static int	is_interrupt = 0;

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
	if (i == data->nbr_of_philo - 1)
	{
		pdata->left = &(data->forks[data->nbr_of_philo - 1]);
		pdata->right = &(data->forks[0]);
	}
	else
	{
		pdata->left = &(data->forks[i]);
		pdata->right = &(data->forks[i + 1]);
	}
}

int	eat_count_check(t_pgen *data, t_pdata *pdata, int *eat_count)
{
	pthread_mutex_lock(pdata->m_eat_count);
	if (pdata->must_eat == 0)
	{
		(*eat_count)++;
		pdata->must_eat = -1;
	}
	pthread_mutex_unlock(pdata->m_eat_count);
	if ((*eat_count) >= data->nbr_of_philo)
	{
		interrupt(0, &data->m_interrupt);
		return (1);
	}
	return (0);
}

void	death_loop(t_pgen *data, t_pdata **pdata, long int start_time)
{
	int	i;
	int	eat_count;

	i = 0;
	eat_count = 0;
	while (1)
	{
		if (i == data->nbr_of_philo)
			i = 0;
		if (data->must_eat > 0 && eat_count_check(data, pdata[i], &eat_count))
			return ;
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
	pthread_t	*threads;
	int			i;
	t_pdata		**pdata;
	long int	start_time;

	i = 0;
	pdata = malloc(sizeof(t_pdata *) * data->nbr_of_philo);
	threads = malloc(sizeof(pthread_t) * data->nbr_of_philo);
	if (!pdata || !threads || allocate_tab_philo_data(pdata, data))
		return (1);
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
