/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:00:29 by bdany             #+#    #+#             */
/*   Updated: 2024/09/03 14:36:48 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	is_think(t_philo *philo)
{
	if (stop_all(philo))
		return ;
	print_action(philo, "is thinking");
}

static void	is_sleep(t_philo *philo)
{
	if (stop_all(philo))
		return ;
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->t_to_sleep, philo);
}

void	is_eating(t_philo *philo)
{
	if (!(stop_all(philo)))
	{
		if (!(philo->philo_id % 2))
			lock_fork_even(philo);
		else
			lock_fork_odd(philo);
		pthread_mutex_lock(&philo->data->last_m_mutex);
		philo->last_meal_time = get_current_time() - philo->data->start;
		pthread_mutex_unlock(&philo->data->last_m_mutex);
		ft_usleep(philo->data->t_to_eat, philo);
		pthread_mutex_lock(&philo->data->eat_c_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->eat_c_mutex);
		release_fork(philo);
	}
}

int	*routine(t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
		ft_usleep(philo->data->t_to_eat, philo);
	if (philo->data->n_philo == 1)
	{
		print_action(philo, "has taken left fork");
		return (NULL);
	}
	while (1)
	{
		is_eating(philo);
		if (stop_all(philo))
			return (NULL);
		is_sleep(philo);
		if (stop_all(philo))
			return (NULL);
		is_think(philo);
		usleep(100);
	}
	return (0);
}
