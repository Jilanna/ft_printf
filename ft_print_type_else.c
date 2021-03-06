/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_type_else.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 09:04:51 by nvu               #+#    #+#             */
/*   Updated: 2021/03/01 09:07:30 by nvu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_print_str(char *str, int len, t_flags *flags)
{
	char	c;

	c = ' ';
	if (flags->zero == 1 && flags->minus == 0)
		c = '0';
	if (flags->precision < len && flags->precision > -1)
	{
		str[flags->precision] = '\0';
		len = flags->precision;
	}
	if (flags->width > len)
	{
		if (flags->minus == 1)
			str = ft_add_after(str, c, len, flags->width);
		else
			str = ft_add_before(str, c, len, flags->width - len);
	}
	return (str);
}

char	*ft_print_char(char *str, t_flags *flags)
{
	char	c;

	if (flags->width > 1)
	{
		c = ' ';
		if (flags->zero == 1 && flags->minus == 0)
			c = '0';
		if (flags->minus == 1)
			str = ft_add_after(str, c, 1, flags->width);
		else
			str = ft_add_before(str, c, 1, flags->width - 1);
	}
	else
		flags->width = 1;
	return (str);
}

char	*ft_print_ptr2(char *temp, int len, t_flags *flags)
{
	if (flags->width > len)
	{
		if (flags->minus == 1)
			temp = ft_add_after(temp, ' ', len, flags->width);
		else if ((flags->zero == 0)
			|| (flags->zero == 1 && flags->precision != -1))
			temp = ft_add_before(temp, ' ', len, flags->width - len);
		else
			temp = ft_add_before(temp, '0', len, flags->width - len);
	}
	return (temp);
}

char	*ft_print_ptr(char *str, int len, t_flags *flags)
{
	char		*temp;
	int			n;

	if (flags->precision > len)
	{
		if ((str = ft_add_before(str, '0', len,
			flags->precision - len)) == NULL)
			return (NULL);
		len = ft_strlen(str);
	}
	if (!(temp = malloc(sizeof(char) * (len + 3))))
		return (NULL);
	temp[0] = '0';
	temp[1] = 'x';
	n = 1;
	while (++n && str[n - 2])
		temp[n] = str[n - 2];
	temp[n] = '\0';
	free(str);
	temp = ft_print_ptr2(temp, len + 2, flags);
	return (temp);
}
