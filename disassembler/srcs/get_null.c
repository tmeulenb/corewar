/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_null.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ayundina <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 12:25:06 by ayundina      #+#    #+#                 */
/*   Updated: 2019/10/29 12:25:12 by ayundina      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disassembler.h"

void	get_null(int fd)
{
	int				ret;
	char			buff[4];

	ret = (int)read(fd, buff, 4);
	check_if_return_of_read_is_valid(ret, 4);
	if (buff[0] != '\0' || buff[1] != '\0')
		error_messaging(4);
	return ;
}
