/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 06:14:33 by dlu               #+#    #+#             */
/*   Updated: 2023/05/04 06:46:52 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Returns the length to be printed for string or base for number. */
int	ft_strlen(char *s, t_format format)
{
	int	i;

	if (!s || (format.type == 's' && format.dot && format.precision == 0))
		return (0);
	i = -1;
	while (s[++i])
		if (format.type =='s' && i >= format.precision)
			return (i);
	return (i);
}

/* Return the length of the padding. */
int	print_padding(char c, int len)
{
	int	i;

	if (len <= 0)
		return (0);
	i = -1;
	while (++i < len)
		write(1, &c, 1);
	return (len);
}
