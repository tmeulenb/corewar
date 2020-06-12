/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_vm.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jheeresm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 13:38:26 by jheeresm       #+#    #+#                */
/*   Updated: 2019/11/07 18:20:20 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		init_n_args(t_vm *vm)
{
	vm->n_arg[live_index] = 1;
	vm->n_arg[ld_index] = 2;
	vm->n_arg[st_index] = 2;
	vm->n_arg[add_index] = 3;
	vm->n_arg[sub_index] = 3;
	vm->n_arg[and_index] = 3;
	vm->n_arg[or_index] = 3;
	vm->n_arg[xor_index] = 3;
	vm->n_arg[zjmp_index] = 1;
	vm->n_arg[ldi_index] = 3;
	vm->n_arg[sti_index] = 3;
	vm->n_arg[fork_index] = 1;
	vm->n_arg[lld_index] = 2;
	vm->n_arg[lldi_index] = 3;
	vm->n_arg[lfork_index] = 1;
	vm->n_arg[aff_index] = 1;
	return ;
}

/*
** INIT_OP_FUNCTIONS
** Set all the functions for corresponding operations.
*/

static void	init_op_functions(t_vm *vm)
{
	vm->op_functions[live_index] = &live_op;
	vm->op_functions[ld_index] = &ld_op;
	vm->op_functions[st_index] = &st_op;
	vm->op_functions[add_index] = &add_op;
	vm->op_functions[sub_index] = &sub_op;
	vm->op_functions[and_index] = &and_op;
	vm->op_functions[or_index] = &or_op;
	vm->op_functions[xor_index] = &xor_op;
	vm->op_functions[zjmp_index] = &zjmp_op;
	vm->op_functions[ldi_index] = &ldi_op;
	vm->op_functions[sti_index] = &sti_op;
	vm->op_functions[fork_index] = &fork_op;
	vm->op_functions[lld_index] = &lld_op;
	vm->op_functions[lldi_index] = &lldi_op;
	vm->op_functions[lfork_index] = &lfork_op;
	vm->op_functions[aff_index] = &aff_op;
}

/*
** INIT_WAIT_CYCLES
** Set all the wait cycles for the corresponding opcodes (-1).
*/

void		init_wait_cycles(t_vm *vm)
{
	vm->wait[live_index] = 10;
	vm->wait[ld_index] = 5;
	vm->wait[st_index] = 5;
	vm->wait[add_index] = 10;
	vm->wait[sub_index] = 10;
	vm->wait[and_index] = 6;
	vm->wait[or_index] = 6;
	vm->wait[xor_index] = 6;
	vm->wait[zjmp_index] = 20;
	vm->wait[ldi_index] = 25;
	vm->wait[sti_index] = 25;
	vm->wait[fork_index] = 800;
	vm->wait[lld_index] = 10;
	vm->wait[lldi_index] = 50;
	vm->wait[lfork_index] = 1000;
	vm->wait[aff_index] = 2;
	return ;
}

/*
** INIT_T_DIR
** Set all the t_dir sizes for the corresponding opcodes (-1).
*/

void		init_t_dir_and_n_flag(t_vm *vm)
{
	vm->t_dir[live_index] = 4;
	vm->t_dir[ld_index] = 4;
	vm->t_dir[st_index] = 4;
	vm->t_dir[add_index] = 4;
	vm->t_dir[sub_index] = 4;
	vm->t_dir[and_index] = 4;
	vm->t_dir[or_index] = 4;
	vm->t_dir[xor_index] = 4;
	vm->t_dir[zjmp_index] = 2;
	vm->t_dir[ldi_index] = 2;
	vm->t_dir[sti_index] = 2;
	vm->t_dir[fork_index] = 2;
	vm->t_dir[lld_index] = 4;
	vm->t_dir[lldi_index] = 2;
	vm->t_dir[lfork_index] = 2;
	vm->t_dir[aff_index] = 4;
	vm->n_flag[0] = 0;
	vm->n_flag[1] = 0;
	vm->n_flag[2] = 0;
	vm->n_flag[3] = 0;
	return ;
}

void		init_vm(t_vm *vm, int argc, char **argv)
{
	vm->memory = malloc(sizeof(unsigned char) * MEM_SIZE + 1);
	ft_bzero(vm->memory, MEM_SIZE + 1);
	vm->color_mask = malloc(sizeof(unsigned char) * MEM_SIZE + 1);
	ft_bzero(vm->color_mask, MEM_SIZE + 1);
	vm->champion_count = 0;
	vm->dump_flag = -1;
	vm->argc = argc;
	vm->argv = argv;
	vm->cursors = NULL;
	vm->game.cycles = 1;
	vm->game.check = 0;
	vm->game.cycles_to_die = CYCLE_TO_DIE;
	vm->game.nbr_live = 0;
	vm->game.last_alive_champ = 0;
	vm->game.total_cursors = 0;
	vm->verbose = 0;
	vm->visualizer = 0;
	init_wait_cycles(vm);
	init_t_dir_and_n_flag(vm);
	init_op_functions(vm);
	init_n_args(vm);
	return ;
}
