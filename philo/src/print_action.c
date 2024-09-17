/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:00:37 by bdany             #+#    #+#             */
/*   Updated: 2024/09/05 17:15:15 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_action(t_philo *philo, char *str)
{
	unsigned long	time;

	if (!stop_all(philo))
	{
		pthread_mutex_lock(&philo->data->dead_mutex);
		if (!(philo->data->dead_philo))
		{
			time = get_current_time() - philo->data->start;
			printf("%zu %d %s\n", time, philo->philo_id, str);
		}
		pthread_mutex_unlock(&philo->data->dead_mutex);
	}
}
