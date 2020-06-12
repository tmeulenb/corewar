/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   corewar.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jheeresm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/24 11:55:05 by jheeresm       #+#    #+#                */
/*   Updated: 2019/11/13 17:19:51 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/time.h>
# include <ncurses.h>
# include "op.h"
# include "../../libft/libft.h"
# include "bass.h"

# define TIME_INTERVAL_MILISEC 0.5

# define NO_CHAMP_AFTER_N_FLAG i + 2 == vm->argc
# define NO_NUMBER_AFTER_FLAG i + 1 == vm->argc

# define BYTE(byte, i) !!((byte << i) & 0x80)
# define VALID_OPCODE(x) (x >= 1 && x <= 16)
# define VALID_REG(x) (x >= 1 && x <= REG_NUMBER)
# define MOD(x) ft_modulo(x, MEM_SIZE)

# define CHECK_LIVE(x) (x[0] == 2 && !x[1] && !x[2])
# define CHECK_LD(x) (x[0] > 1 && x[1] == 1 && !x[2])
# define CHECK_ST(x) (x[0] == 1 && (x[1] == 1 || x[1] == 3) && !x[2])
# define CHECK_ADD(x) (x[0] == 1 && x[1] == 1 && x[2] == 1)
# define CHECK_SUB(x) (x[0] == 1 && x[1] == 1 && x[2] == 1)
# define CHECK_AND(x) (x[0] > 0 && x[1] > 0 && x[2] == 1)
# define CHECK_OR(x) (x[0] > 0 && x[1] > 0 && x[2] == 1)
# define CHECK_XOR(x) (x[0] > 0 && x[1] > 0 && x[2] == 1)
# define CHECK_ZJMP(x) (x[0] == 2 && !x[1] && !x[2])
# define CHECK_LDI(x) (x[0] > 0 && x[1] > 0 && x[1] < 3 && x[2] == 1)
# define CHECK_STI(x) (x[0] == 1 && x[1] > 0 && x[2] > 0 && x[2] < 3)
# define CHECK_FORK(x) (x[0] == 2 && !x[1] && !x[2])
# define CHECK_LLD(x) (x[0] > 1 && x[1] == 1 && !x[2])
# define CHECK_LLDI(x) (x[0] > 0 && x[1] > 0 && x[1] < 3 && x[2] == 1)
# define CHECK_LFORK(x) (x[0] == 2 && !x[1] && !x[2])
# define CHECK_AFF(x) (x[0] == 1 && !x[1] && !x[2])

# define FIRST_ARG cursor->operation.arg[0]
# define SECOND_ARG cursor->operation.arg[1]
# define THIRD_ARG cursor->operation.arg[2]
# define ARGUMENT cursor->operation.arg[i]
# define ARGUMENT_TYPE cursor->operation.check[i]

# define CURRENT_COLOR vm->color_mask[cursor->position + 1]

typedef enum		e_op_index
{
	live_index = 0,
	ld_index = 1,
	st_index = 2,
	add_index = 3,
	sub_index = 4,
	and_index = 5,
	or_index = 6,
	xor_index = 7,
	zjmp_index = 8,
	ldi_index = 9,
	sti_index = 10,
	fork_index = 11,
	lld_index = 12,
	lldi_index = 13,
	lfork_index = 14,
	aff_index = 15
}					t_op_index;

typedef enum		e_opcode
{
	live_code = 1,
	ld_code = 2,
	st_code = 3,
	add_code = 4,
	sub_code = 5,
	and_code = 6,
	or_code = 7,
	xor_code = 8,
	zjmp_code = 9,
	ldi_code = 10,
	sti_code = 11,
	fork_code = 12,
	lld_code = 13,
	lldi_code = 14,
	lfork_code = 15,
	aff_code = 16
}					t_opcode;

typedef enum		e_input_error
{
	no_dot_cor = 0,
	bad_flag = 1,
	champ_nmbr = 2,
	bad_arg = 3,
	flag_nmbr = 4,
	id_no_champ = 5,
	n_too_big = 6,
	same_id = 7,
	double_dump = 8,
	champ_too_long = 9
}					t_input_error;

typedef enum		e_flag
{
	n = 1,
	dump = 2
}					t_flag;

typedef struct		s_champion
{
	char			*filename;
	char			*name;
	char			*comment;
	int				id;
	int				size;
	int				last_live;
	int				amount_of_lives;
}					t_champion;

typedef struct		s_operation
{
	int				check[4];
	int				arg[3];
	int				n_args;
}					t_operation;

typedef struct		s_cursor
{
	int				id;
	int				carry;
	int				opcode;
	int				last_live;
	int				wait_cycles;
	int				position;
	int				reg[REG_NUMBER];
	t_operation		operation;
	void			*next;
}					t_cursor;

typedef struct		s_game
{
	int				cycles;
	int				cycles_to_die;
	int				check;
	int				nbr_live;
	int				total_cursors;
	int				last_alive_champ;
}					t_game;

typedef struct		s_color
{
	int				pos;
	int				size;
	int				color;
}					t_color;

typedef struct		s_visual
{
	WINDOW			*memory_display;
	WINDOW			*game_variables;
	WINDOW			*corewar_header;
}					t_visual;

typedef struct		s_vm
{
	int				argc;
	char			**argv;
	t_champion		champions[4];
	t_game			game;
	t_cursor		*cursors;
	unsigned char	*memory;
	unsigned char	*color_mask;
	int				champion_count;
	int				dump_flag;
	int				verbose;
	int				visualizer;
	int				n_flag[4];
	int				wait[16];
	int				t_dir[16];
	int				n_arg[16];
	void			*op_functions[16];
	t_visual		v;
}					t_vm;

void				init_visuals(t_vm *vm);
void				update_game_variables(WINDOW *game_variables, t_vm *vm);
void				change_color(t_vm *vm, int color, int position, int size);
void				init_memory_colors(t_vm *vm);
void				update_cursor(t_vm *vm, t_cursor *cursor, int jump);
void				fill_corewar_header(WINDOW *corewar_header);
void				fill_game_variables_help(WINDOW *game_variables);
void				fill_game_variables(WINDOW *game_variables, t_vm *vm);
void				update_memory(WINDOW *memory_display, t_vm *vm);
void				end_of_game(t_vm *vm);
void				pauze_visualizer(WINDOW *game_variables);

/*
** verbose.c
*/
void				verbose_operation(t_vm *vm, t_cursor *cursor);
void				verbose_new_cursor(t_cursor *cursor);
void				verbose_cursor_died(t_vm *vm, t_cursor *cursor);

/*
** init_vm.c
*/
void				init_vm(t_vm *vm, int argc, char **argv);

/*
** game.c
*/
void				introduce_champions(t_vm *vm, t_champion *champ);
void				game(t_vm *vm, t_game *game);

/*
** error.c
*/
void				display_help(void);
void				input_error(char *arg, t_input_error choice);

/*
** input_check.c
*/
int					check_for_champion(char *arg);
int					check_for_flags(t_vm *vm, char *arg);
void				save_dump_flag(t_vm *vm, int *i);
void				check_duplicate_n_flag(int *n_flag, int n);
void				save_n_flag(t_vm *vm, int *i);
void				check_arguments(t_vm *vm);

/*
** init_champions.c
*/
void				init_champions(t_vm *vm);

/*
** init_cursor.c
*/
void				add_to_cursor_list(t_vm *vm, t_cursor *new);
int					calc_starting_position(t_vm *vm, int player_id);
void				init_cursors(t_vm *vm);

/*
** exec_cursor_list.c
*/
void				reset_operation(t_cursor *cursor);
void				move_to_next_operation(t_vm *vm, t_cursor *cursor);
void				exec_cursor_list(t_vm *vm, t_cursor *cursor);

/*
** read_operation.c
*/
int					read_operation(t_vm *vm, t_cursor *cursor);
void				load_champs(t_vm *vm);
short				reverse16(short value);
int					reverse32(int value);
int					ft_modulo(int a, int b);
int					is_single_arg_op(t_cursor *cursor);
int					right_encoding_for_op(t_opcode op_code, int *check);

/*
** save_arguments.c
*/
int					save_arguments(t_vm *vm, t_cursor *cursor);

/*
** dump.c
*/
int					dump_check(t_vm vm);
void				dump_flag(unsigned char *mem);

/*
** reset_operation
*/
void				reset_operation(t_cursor *cursor);

/*
** operations
*/
void				live_op(t_vm *vm, t_cursor *cursor);
void				ld_op(t_vm *vm, t_cursor *cursor);
void				st_op(t_vm *vm, t_cursor *cursor);
void				add_op(t_cursor *cursor);
void				sub_op(t_cursor *cursor);
void				and_op(t_vm *vm, t_cursor *cursor);
void				or_op(t_vm *vm, t_cursor *cursor);
void				xor_op(t_vm *vm, t_cursor *cursor);
void				zjmp_op(t_vm *vm, t_cursor *cursor);
void				ldi_op(t_vm *vm, t_cursor *cursor);
void				sti_op(t_vm *vm, t_cursor *cursor);
void				fork_op(t_vm *vm, t_cursor *cursor);
void				lld_op(t_vm *vm, t_cursor *cursor);
void				lldi_op(t_vm *vm, t_cursor *cursor);
void				lfork_op(t_vm *vm, t_cursor *cursor);
void				aff_op(t_vm *vm, t_cursor *cursor);

/*
** operation help
*/
void				copy_cursor_variables(t_cursor *cursor, t_cursor *fork);
t_cursor			*duplicate_cursor(t_vm *vm, t_cursor *cursor, int pos);
int					get_value_at_address(unsigned char *memory, int pos);
void				get_indirect_arg_idx_mod(t_vm *vm, t_cursor *cursor);
void				get_indirect_arg_mem_size(t_vm *vm, t_cursor *cursor);
void				get_registry_argument(t_cursor *cursor);
void				write_value_in_memory(t_vm *vm, int value, int pos,
														unsigned char color);

/*
**	timing.c
*/
void				iwait(void);

/*
**	visualizer.c  &&  audio.c
*/
void				visualizer(t_vm *vm);
int					play_audio(char *exec_path);

#endif
