/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:21:15 by bdany             #+#    #+#             */
/*   Updated: 2024/09/05 16:50:09 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	lock_fork(t_philo *philo)
{
	while (!stop_all(philo))
	{
		pthread_mutex_lock(&philo->left_forks->fork_mutex);
		if (philo->left_forks->is_available)
		{
			print_action(philo, "has taken a fork");
			philo->left_forks->is_available = false;
			pthread_mutex_unlock(&philo->left_forks->fork_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->left_forks->fork_mutex);
	}
	while (!stop_all(philo))
	{
		pthread_mutex_lock(&philo->right_forks->fork_mutex);
		if (philo->right_forks->is_available)
		{
			print_action(philo, "has taken a fork");
			philo->right_forks->is_available = false;
			pthread_mutex_unlock(&philo->right_forks->fork_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->right_forks->fork_mutex);
	}
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_forks->fork_mutex);
	philo->left_forks->is_available = true;
	pthread_mutex_unlock(&philo->left_forks->fork_mutex);
	pthread_mutex_lock(&philo->right_forks->fork_mutex);
	philo->right_forks->is_available = true;
	pthread_mutex_unlock(&philo->right_forks->fork_mutex);
}
