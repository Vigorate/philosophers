/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:30:10 by ambelkac          #+#    #+#             */
/*   Updated: 2022/01/19 16:51:05 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_pgen	*data;

	data = parse_arg(av, ac);
	if (!data)
		return (1);
	dispatch_thread(data);
	return (0);
}
