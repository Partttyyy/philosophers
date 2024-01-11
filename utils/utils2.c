/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 03:53:59 by frapp             #+#    #+#             */
/*   Updated: 2024/01/10 21:14:28 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// not performance critical
int64_t	ft_atoi(const char *str)
{
	int64_t	num;
	int64_t	sign;
	int64_t	digit;

	num = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
	{
		str++;
		sign = -1;
	}
	else if (*str == '+')
		str++;
	while ((*str >= 48 && *str <= 57))
	{
		num *= 10;
		digit = (int64_t)(*str - '0');
		if (digit < 0)
			digit = -digit;
		num += digit;
		str++;
	}
	return (num * sign);
}

// not performance critical
int	cleanup(t_general *const general)
{
	int	i;

	if (general->philos && general->threads)
	{
		i = 0;
		pthread_mutex_destroy(&(general->status_mutex));
		while (i < general->count)
		{
			if (((general->philos) + i)->eat_dur != FAIL_INIT)
				pthread_mutex_destroy(&((general->philos) + i)
					->main_fork.mutex);
			if ((general->philos)[i].starve_dur != FAIL_INIT)
				pthread_mutex_destroy(&((general->philos) + i)
					->main_fork.mutex_used);
			i++;
		}
	}
	if (general->philos)
		free(general->ptr_to_free_philos);
	general->philos = NULL;
	if (general->threads)
		free(general->threads);
	general->threads = NULL;
	return (0);
}

// not performance critical
void	align_ptr(int8_t **ptr)
{
	int		size_past_last_line;

	size_past_last_line = ((uintptr_t)((*ptr)) % CACHE_LINE_SIZE);
	if (!size_past_last_line)
		return ;
	*ptr = *ptr + CACHE_LINE_SIZE - size_past_last_line;
}

