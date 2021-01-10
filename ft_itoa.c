/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:45:24 by syudai            #+#    #+#             */
/*   Updated: 2020/11/03 18:05:30 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_insert(char *ans, unsigned int n)
{
	if (n < 10)
	{
		*ans = n + '0';
		return ;
	}
	ft_insert(ans - 1, n / 10);
	*ans = n % 10 + '0';
}

char		*ft_itoa(int n)
{
	char			*ans;
	int				i;
	unsigned int	size;

	if (n < 0)
		size = -n;
	else
		size = n;
	i = 1;
	while (n >= 10 || n <= -10)
	{
		n /= 10;
		i++;
	}
	if (n < 0)
		i++;
	if (!(ans = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (n < 0)
		*ans = '-';
	ft_insert(ans + i - 1, size);
	*(ans + i) = '\0';
	return (ans);
}
