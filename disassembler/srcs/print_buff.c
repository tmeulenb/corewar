/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_buff.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ayundina <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 12:25:06 by ayundina      #+#    #+#                 */
/*   Updated: 2019/10/29 12:25:12 by ayundina      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disassembler.h"

void		print_buff(unsigned char *buff, int prog_size)
{
	int	i;

	i = 0;
	while (i <= prog_size)
	{
		ft_printf("%x	%d	%08b\n", buff[i], buff[i], buff[i]);
		i++;
	}
}
