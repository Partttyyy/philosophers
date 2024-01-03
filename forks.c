/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 05:15:23 by frapp             #+#    #+#             */
/*   Updated: 2023/12/29 19:24:32 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	pickup_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex_used);
	while(philo->left_fork->used)
	{
		pthread_mutex_unlock(&philo->left_fork->mutex_used);
		if (check_exit(philo))
			return (false);
		pthread_mutex_lock(&philo->left_fork->mutex_used);
	}
	philo->left_fork->used = true;
	pthread_mutex_unlock(&philo->left_fork->mutex_used);

	pthread_mutex_lock(&philo->left_fork->mutex);
	//philo->current_time = my_gettime();
	if (!print_status(philo, "has taken the left fork"))
		return (false);
	return (true);
}

bool	pickup_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex_used);
	while (philo->right_fork->used)
	{
		pthread_mutex_unlock(&philo->right_fork->mutex_used);
		if (check_exit(philo))
			return (false);
		pthread_mutex_lock(&philo->right_fork->mutex_used);
	}
	philo->right_fork->used = true;
	pthread_mutex_unlock(&philo->right_fork->mutex_used);

	pthread_mutex_lock(&philo->right_fork->mutex);
	//philo->current_time = my_gettime();
	if (!print_status(philo, "has taken the right fork"))
		return (false);
	return (true);
}

void	drop_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex_used);
	philo->right_fork->used = false;
	pthread_mutex_unlock(&philo->right_fork->mutex_used);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	drop_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex_used);
	philo->left_fork->used = false;
	pthread_mutex_unlock(&philo->left_fork->mutex_used);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

bool drop_forks(t_philo *philo)
{
	drop_right_fork(philo);
	drop_left_fork(philo);
	if (check_exit(philo))
		return (false);
	return (true);
}


// 59737 70 has taken the left fork
// 59737 70 is eating
// 59937 70 is sleeping
// 60137 70 is thinking
// 60137 70 died
// next eat 60137
