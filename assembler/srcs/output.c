/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   output.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/10 17:32:13 by tide-jon       #+#    #+#                */
/*   Updated: 2019/11/12 21:44:17 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

static void	write_warrior(t_corewar data, int fd)
{
	t_tokens		*token;
	t_instruction	inst;

	token = data.tokens;
	while (token)
	{
		if (token->type == seperator || token->type == label)
			;
		else if (token->type == instruction)
		{
			inst = token->instruction;
			write_instr(token, fd);
		}
		else if (token->type == regist)
			write_regist(token, fd);
		else if (token->type == direct || token->type == dir_label)
			write_direct(token, fd, inst);
		else if (token->type == indirect || token->type == ind_label)
			write_indirect(token, fd);
		token = token->next;
	}
}

static int	create_file(char *filename)
{
	int		fd;
	int		i;
	char	*out_name;

	out_name = (char*)ft_memalloc(sizeof(char) * (ft_strlen(filename) + 3));
	ft_strcpy(out_name, filename);
	i = 0;
	while (out_name[i] != '\0')
		i++;
	out_name[i - 1] = 'c';
	out_name[i] = 'o';
	out_name[i + 1] = 'r';
	out_name[i + 2] = '\0';
	fd = open(out_name, O_CREAT | O_RDWR | O_EXCL | O_APPEND, 0777);
	if (fd < 0)
	{
		ft_printf("file: %s already exists\n", out_name);
		exit(0);
	}
	ft_printf("created warrior file %s\n", out_name);
	return (fd);
}

void		write_output(t_corewar data, char *filename)
{
	int		header;
	int		fd;
	int		zero;

	if (data.found_first_op == 0)
		ft_error("no operations found");
	zero = 0;
	fd = create_file(filename);
	header = reverse32(COREWAR_EXEC_MAGIC);
	data.total_bytes = reverse32(data.total_bytes);
	write(fd, &header, 4);
	write(fd, data.name, PROG_NAME_LENGTH);
	write(fd, &zero, 4);
	write(fd, &(data.total_bytes), 4);
	write(fd, data.comment, COMMENT_LENGTH);
	write(fd, &zero, 4);
	write_warrior(data, fd);
}
