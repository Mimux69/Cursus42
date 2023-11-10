/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:02:42 by acronert          #+#    #+#             */
/*   Updated: 2023/11/10 14:50:21 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

int	ft_printf(const char *format, ...)
{
	va_list	args;
	va_start(args, format);

	while (*format)
	{
		if (*format != '%')
			write (1, format, 1);
		else
		{
			format++;
			if (*format == 'c')
			;
		}
		format++;
	}
	va_end(args);
	return (0);
}

int	main()
{
	int	*ptr;
	int	*ptr2;

	ptr = NULL;
	ptr2 = malloc(sizeof(int));
	printf("test1 - test%   i - test%+++i - ptr%p - ptr2%p - char%c\n", -1, 1, ptr, ptr2, 'f');
	//-0.
	printf("test% 10itest", 1);
	//# +
	ft_printf("Ceci est un test. :)");
	return (0);
}