/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:42:46 by ambelkac          #+#    #+#             */
/*   Updated: 2022/01/08 18:12:38 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

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
	pdata->eating = &(data->eating[i]);
	pdata->is_eating = 0;
	dispatch_forks(pdata, data, i);
	return (pdata);
}

void	death_loop(t_pgen *data, t_pdata **pdata)
{
	int	i;
	long int	start_time;

	i = 0;
	start_time = get_elapsed_time();
	usleep(100);
	while(1)
	{
		// pthread_mutex_lock((pdata[i])->eating);
		// if (pdata[i]->is_eating)
		// {
		// 	pthread_mutex_unlock((pdata[i])->eating);
		// 	++i;
		// 	continue ;
		// }
		// pthread_mutex_unlock((pdata[i])->eating);
		pthread_mutex_lock((pdata[i])->timestamp);
		if (get_elapsed_time() - pdata[i]->time_stamp > data->time_to_die)
		{
			pthread_mutex_lock(&(data->display));
			printf("%ld %d died\n", get_elapsed_time() - start_time, i + 1);
			return ;
		}
		pthread_mutex_unlock((pdata[i])->timestamp);
		++i;
		if (i == data->nbr_of_philo)
			i = 0;
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
		pthread_create(&(threads[i]), NULL, philo_job, pdata[i]);
		++i;
	}

	death_loop(data, pdata);
	// Loop on mutexed value of philo elasped time since last action
	// Return on detected philo death
	return (0);
}