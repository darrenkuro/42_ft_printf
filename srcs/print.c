/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:58:18 by dlu               #+#    #+#             */
/*   Updated: 2023/05/06 21:51:03 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(char c, int *count, t_format format)
{
	if (!format.minus)
		*count += print_padding(format.padding, format.width - 1);
	write(1, &c, 1);
	(*count)++;
	if (format.minus)
		*count += print_padding(format.padding, format.width - 1);
}

/* Handles output for %s, %c, %%. */
int	print_str(char *s, int *count, t_format format)
{
	int	len;
	int	i;

	if (!s && !format.dot && print_str(NULL_STR, count, format))
		return (0);
	else if (!s && format.precision >= 6 && print_str(NULL_STR, count, format))
		return (0);
	len = ft_strlenf(s, format);
	if (!format.minus)
		*count += print_padding(format.padding, format.width - len);
	i = -1;
	while (++i < len)
		write(1, &s[i], 1);
	*count += len;
	if (format.minus)
		*count += print_padding(format.padding, format.width - len);
	return (1);
}

void	print_nbr(t_ll n, char *base, int *count, t_format format)
{
	format.nbr = n;
	parse_nbr(format.nbr, base, &format);
	print_str(format.num, count, format);
	free(format.num);
}

void	print_ptr(void *p, int *count, t_format format)
{
	if (!p && print_str(NULL_PTR, count, format))
		return ;
	format.nbr = (t_ll) p;
	parse_nbr(format.nbr, HEXL, &format);
	print_str(format.num, count, format);
	free(format.num);
}

void	print_arg(va_list *args, t_format format, int *count)
{
	if (format.type == 'c')
		print_char(va_arg(*args, int), count, format);
	else if (format.type == 's')
		print_str(va_arg(*args, char *), count, format);
	else if (format.type == 'p')
		print_ptr(va_arg(*args, void *), count, format);
	else if (format.type == 'd' || format.type == 'i')
		print_nbr((t_ll) va_arg(*args, int), DEC, count, format);
	else if (format.type == 'x')
		print_nbr((t_ll) va_arg(*args, unsigned int), HEXL, count, format);
	else if (format.type == 'X')
		print_nbr((t_ll) va_arg(*args, unsigned int), HEXU, count, format);
	else if (format.type == 'u')
		print_nbr((t_ll) va_arg(*args, unsigned int), DEC, count, format);
	else if (format.type == '%')
		print_char('%', count, format);
}
