/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deallocate_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:31:08 by ambelkac          #+#    #+#             */
/*   Updated: 2022/01/18 22:41:32 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	clean_exit(t_pgen *data, t_pdata **pdata, pthread_t *threads)
{
	int	i;

	i = 0;
	(void)pdata;
	while (i < data->nbr_of_philo)
	{
		pthread_join(threads[i], NULL);
		++i;
	}
	i = 0;
	while (i < data->nbr_of_philo)
	{
		pthread_mutex_destroy(&(data->timestamp)[i]);
		pthread_mutex_destroy(&(data->forks)[i]);
		pthread_mutex_destroy(&(data->m_eat_count)[i]);
		++i;
	}
	pthread_mutex_destroy(&data->m_interrupt);
	pthread_mutex_destroy(&data->display);
	exit(0);
}
