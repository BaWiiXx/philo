/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:00:40 by bdany             #+#    #+#             */
/*   Updated: 2024/09/03 16:56:16 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long int	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t m_sec, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	if ((philo->data->t_to_eat
			+ philo->data->t_to_sleep) > philo->data->t_to_die)
		usleep(philo->data->t_to_die * 1000);
	while ((get_current_time() - start) < m_sec)
		usleep(50);
	return (0);
}
