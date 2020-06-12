/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_champs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 15:50:28 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/14 18:31:02 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void	faulty_warrior(t_champion *champ, int warrior_too_long)
{
	if (warrior_too_long)
	{
		ft_printf("Error: warrior %s has a ", champ->filename);
		ft_putstr("code size that differs from what it's header says.\n");
	}
	else
		ft_printf("Error: warrior %s is faulty\n", champ->filename);
	exit(0);
}

/*
**VALIDATE_CHAMP
** Reads and stores the following information:
** > Magic header			size: 4 bytes
** > Champion's name		size: PROG_NAME_LENGTH bytes
** > NULL					size: 4 bytes
** > Champion's size		size: 4 bytes
** > Champion's comment		size: COMMENT_LENGTH bytes
** > NULL					size: 4 bytes
*/

static void	validate_champ(int fd, t_champion *champ)
{
	int	header;
	int	zero;

	read(fd, &header, 4);
	if (header != reverse32(COREWAR_EXEC_MAGIC))
		faulty_warrior(champ, 0);
	champ->name = (char*)ft_memalloc(PROG_NAME_LENGTH + 1);
	read(fd, champ->name, PROG_NAME_LENGTH);
	champ->name[PROG_NAME_LENGTH] = '\0';
	zero = INT_MAX;
	read(fd, &zero, 4);
	if (zero != 0)
		faulty_warrior(champ, 0);
	read(fd, &(champ->size), 4);
	champ->size = reverse32(champ->size);
	if (champ->size >= CHAMP_MAX_SIZE)
		faulty_warrior(champ, 0);
	champ->comment = (char*)ft_memalloc(COMMENT_LENGTH + 1);
	read(fd, champ->comment, COMMENT_LENGTH);
	champ->comment[COMMENT_LENGTH] = '\0';
	zero = INT_MAX;
	read(fd, &zero, 4);
	if (zero != 0)
		faulty_warrior(champ, 0);
}

void		cpy_champ_into_mem(t_vm *vm, unsigned char *code, t_champion champ)
{
	int i;
	int pos;

	pos = calc_starting_position(vm, champ.id);
	i = 0;
	while (i < champ.size)
	{
		vm->memory[pos] = code[i];
		vm->color_mask[pos] = -1 * champ.id;
		pos = (pos + 1) % MEM_SIZE;
		i++;
	}
	return ;
}

void		load_champs(t_vm *vm)
{
	int				i;
	int				fd;
	unsigned char	*buff;

	i = 0;
	while (i < vm->champion_count)
	{
		fd = open(vm->champions[i].filename, O_RDONLY);
		validate_champ(fd, &(vm->champions[i]));
		buff = (unsigned char*)ft_memalloc(vm->champions[i].size);
		if (read(fd, buff, vm->champions[i].size) < vm->champions[i].size)
			faulty_warrior(&(vm->champions[i]), 0);
		cpy_champ_into_mem(vm, buff, vm->champions[i]);
		if (read(fd, buff, 1) > 0)
			faulty_warrior(&(vm->champions[i]), 1);
		free(buff);
		i++;
	}
}
