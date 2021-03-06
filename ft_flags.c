/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:23:21 by nvu               #+#    #+#             */
/*   Updated: 2021/03/01 09:51:32 by nvu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flags_init(t_flags *flags, const char *format, int *i)
{
	(*flags).minus = 0;
	(*flags).zero = 0;
	(*flags).width = -1;
	(*flags).precision = -2;
	(*flags).type = 'b';
	(*flags).other = 0;
	while (format[*i] == '-' || format[*i] == '0')
	{
		if (format[*i] == '0')
			flags->zero = 1;
		else
		{
			flags->minus = 1;
			flags->zero = 0;
		}
		(*i)++;
	}
}

int		ft_flags_star(int *j, int *i, va_list ap, t_flags *flags)
{
	(*j) = va_arg(ap, int);
	(*i)++;
	flags->other = 3;
	return (*j);
}

int		ft_flags_length(const char *format, int *i, va_list ap, t_flags *flags)
{
	int		j;
	char	*temp;

	if (format[*i] == '*')
		if (ft_flags_star(&j, i, ap, flags))
			return (j);
	j = -1;
	while ((++j >= 0) && (format[*i] >= '0') && (format[*i] <= '9'))
		(*i)++;
	if (j == 0)
		return (0);
	if (!(temp = malloc(sizeof(char) * (j + 1))))
		return (flags->other = -1);
	(*i) = (*i) - j;
	j = 0;
	while (format[*i] >= '0' && format[*i] <= '9')
	{
		temp[j] = format[*i];
		(*i)++;
		j++;
	}
	temp[j] = '\0';
	j = ft_atoi(temp);
	free(temp);
	return (j);
}

int		ft_flags_neg(t_flags *flags)
{
	if (flags->other == -1)
		return (-1);
	if (flags->other == 3 && flags->width < 0)
	{
		flags->width *= -1;
		flags->other = 0;
		flags->minus = 1;
		flags->zero = 0;
	}
	return (0);
}

int		ft_flags(t_flags *flags, const char *format, int *i, va_list ap)
{
	ft_flags_init(flags, format, i);
	flags->width = ft_flags_length(format, i, ap, flags);
	if (ft_flags_neg(flags) == -1)
		return (-1);
	if (format[*i] == '.')
	{
		(*i)++;
		flags->precision = ft_flags_length(format, i, ap, flags);
		if (flags->other == -1)
			return (-1);
		if (flags->other == 3 && flags->precision < 0)
			flags->precision = -2;
		flags->other = 0;
	}
	flags->type = format[*i];
	if ((flags->type != 'i') && (flags->type != 'd') && (flags->type != 'u')
		&& (flags->type != 'x') && (flags->type != 'X') && (flags->type != 'c')
		&& (flags->type != 's') && (flags->type != 'p')
		&& (flags->type != '%'))
		return (-1);
	return (0);
}
