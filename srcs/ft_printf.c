/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:58:18 by dlu               #+#    #+#             */
/*   Updated: 2023/05/03 13:52:51 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

typedef struct 

void	print_char(char **s, int *count)
{
	write(1, (*s)++, 1);
	++count;
}

void	print_arg(char **s, va_list *args, int *count)
{
	t_flag	flag;

	(*s)++;
	parse_flag(s, args, &flag);

}

int	parse(char *s, va_list *args)
{
	int		count;

	count = 0;
	while (*s)
	{
		if (*s != '%')
			print_char(&s, &count);
		else
			print_arg(&s, args, &count);
	}
	return (count);
}

int	ft_printf(const char *s, ...)
{
	int		count;
	va_list	args;

	va_start(args, s);
	count = parse((char *) s, &args);
	va_end(args);
	return (count);
}

int	main(void)
{
	ft_printf("abcdefg", "abcd");
	return (0);
}
