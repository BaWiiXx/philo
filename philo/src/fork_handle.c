/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:21:15 by bdany             #+#    #+#             */
/*   Updated: 2024/08/30 18:23:07 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// impair
void	lock_fork_odd(t_philo *philo)
{
	while (1)
	{
		if (stop_all(philo))
			return ;
		pthread_mutex_lock(&philo->left_forks->fork_mutex);
		pthread_mutex_lock(&philo->right_forks->fork_mutex);
		if (philo->left_forks->is_available && philo->right_forks->is_available)
		{
			print_action(philo, "take a fork");
			print_action(philo, "take a fork");
			philo->left_forks->is_available = false;
			philo->right_forks->is_available = false;
			break ;
		}
		pthread_mutex_unlock(&philo->right_forks->fork_mutex);
		pthread_mutex_unlock(&philo->left_forks->fork_mutex);
	}
	print_action(philo, "is eating");
	pthread_mutex_unlock(&philo->right_forks->fork_mutex);
	pthread_mutex_unlock(&philo->left_forks->fork_mutex);
}

// pair
void	lock_fork_even(t_philo *philo)
{
	while (1)
	{
		if (stop_all(philo))
			return ;
		pthread_mutex_lock(&philo->right_forks->fork_mutex);
		pthread_mutex_lock(&philo->left_forks->fork_mutex);
		if (philo->left_forks->is_available && philo->right_forks->is_available)
		{
			print_action(philo, "take a fork");
			print_action(philo, "take a fork");
			philo->left_forks->is_available = false;
			philo->right_forks->is_available = false;
			break ;
		}
		pthread_mutex_unlock(&philo->left_forks->fork_mutex);
		pthread_mutex_unlock(&philo->right_forks->fork_mutex);
	}
	print_action(philo, "is eating");
	pthread_mutex_unlock(&philo->left_forks->fork_mutex);
	pthread_mutex_unlock(&philo->right_forks->fork_mutex);
}

void	release_fork(t_philo *philo)
{
	if (philo->philo_id % 2)
		pthread_mutex_lock(&philo->left_forks->fork_mutex);
	pthread_mutex_lock(&philo->right_forks->fork_mutex);
	if (!(philo->philo_id % 2))
		pthread_mutex_lock(&philo->left_forks->fork_mutex);
	philo->left_forks->is_available = true;
	philo->right_forks->is_available = true;
	if (!(philo->philo_id % 2))
		pthread_mutex_unlock(&philo->left_forks->fork_mutex);
	pthread_mutex_unlock(&philo->right_forks->fork_mutex);
	if (philo->philo_id % 2)
		pthread_mutex_unlock(&philo->left_forks->fork_mutex);
}
