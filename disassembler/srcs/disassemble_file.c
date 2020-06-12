/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   disassemble_file.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ayundina <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 12:25:06 by ayundina      #+#    #+#                 */
/*   Updated: 2019/10/29 12:25:12 by ayundina      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disassembler.h"

static void	check_magic_header(int fd)
{
	unsigned char	buff[4];
	int				ret;
	int				magic_header;

	ret = (int)read(fd, buff, 4);
	if (ret == -1)
		error_messaging(3);
	if (ret == 0)
		error_messaging(2);
	magic_header = (int)buff[0] << 24 | buff[1] << 16 | buff[2] << 8 | buff[3];
	if (magic_header != COREWAR_EXEC_MAGIC)
		error_messaging(1);
	return ;
}

static void	get_champion_name(int fd, t_header *header)
{
	int				ret;

	ret = (int)read(fd, header->prog_name, PROG_NAME_LENGTH);
	check_if_return_of_read_is_valid(ret, PROG_NAME_LENGTH);
	header->prog_name[ret] = '\0';
	return ;
}

static void	get_champion_exec_size(int fd, t_header *header)
{
	int				ret;
	unsigned char	buff[4];

	ret = (int)read(fd, buff, 4);
	check_if_return_of_read_is_valid(ret, 4);
	header->prog_size = (int)buff[0] << 24 | buff[1] << 16 \
							| buff[2] << 8 | buff[3];
	return ;
}

static void	get_champion_comment(int fd, t_header *header)
{
	int			ret;

	ret = (int)read(fd, header->comment, COMMENT_LENGTH);
	check_if_return_of_read_is_valid(ret, COMMENT_LENGTH);
	header->comment[ret] = '\0';
	return ;
}

void		disassemble_file(char *filename)
{
	t_exec		exec;
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_messaging(3);
	init_exec(&exec);
	check_magic_header(fd);
	get_champion_name(fd, &exec.header);
	get_null(fd);
	get_champion_exec_size(fd, &exec.header);
	get_champion_comment(fd, &exec.header);
	get_null(fd);
	get_champion_exec_code(fd, &exec);
	close(fd);
	fd = create_file_dot_s(filename);
	disassemble_exec_code(fd, &exec);
	free((void *)exec.code);
	exec.code = NULL;
	close(fd);
	return ;
}
