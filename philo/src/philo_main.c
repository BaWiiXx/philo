/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:00:52 by bdany             #+#    #+#             */
/*   Updated: 2024/09/03 14:31:46 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("usage: ./philo [n_philo] [t_to_die]"
			" [t_to_eat] [t_to_sleep] [n_meals]\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (check_argument(argv))
		return (write(2, "arguments must be numbers only\n", 31));
	init_data(&data, argv);
	philo = ft_calloc(data.n_philo, sizeof(t_philo));
	if (!philo)
		return (-1);
	data.forks = ft_calloc(data.n_philo, sizeof(t_fork));
	if (!data.forks)
		return (1);
	init_philo(philo, &data);
	handle_threads(philo);
	destroy_all_mutex(&data);
	free(philo);
	free(data.forks);
}
