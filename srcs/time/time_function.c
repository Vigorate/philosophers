/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:56:17 by ambelkac          #+#    #+#             */
/*   Updated: 2021/12/07 18:00:07 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void		custom_usleep(long int usec)
{
	long int	timestamp;

	timestamp = get_elapsed_time() + usec;
	while (get_elapsed_time() < timestamp)
	{
		usleep(1);
	}
}

long int	get_elapsed_time(void)
{
	static long long int	start_time = 0;
	struct timeval	tp;

	if (!start_time)
	{
		gettimeofday(&tp, NULL);
		start_time = tp.tv_sec * 1000000 + tp.tv_usec;
		return (0);
	}
	else
	{
		gettimeofday(&tp, NULL);
		return ((tp.tv_sec * 1000000 + tp.tv_usec) - start_time);
	}
}