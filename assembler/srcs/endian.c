/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   endian.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/10 17:34:46 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/10 17:35:45 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

short	reverse16(short value)
{
	return (((value & 0x00FF) << 8) |
			((value & 0xFF00) >> 8));
}

int		reverse32(int value)
{
	return (((value & 0x000000FF) << 24) |
			((value & 0x0000FF00) << 8) |
			((value & 0x00FF0000) >> 8) |
			((value & 0xFF000000) >> 24));
}
