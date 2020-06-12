/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assembler.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/02 18:33:01 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/30 21:43:23 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

# include "../../libft/libft.h"
# include "op.h"

typedef enum	e_type
{
	seperator = 0,
	label = 1,
	instruction = 2,
	regist = 3,
	direct = 4,
	indirect = 5,
	dir_label = 6,
	ind_label = 7,
}				t_type;

typedef enum	e_instruction
{
	live = 1,
	ld = 2,
	st = 3,
	add = 4,
	sub = 5,
	and = 6,
	or = 7,
	xor = 8,
	zjmp = 9,
	ldi = 10,
	sti = 11,
	fork_ = 12,
	lld = 13,
	lldi = 14,
	lfork = 15,
	aff = 16
}				t_instruction;

typedef struct	s_tokens
{
	char			*content;
	t_type			type;
	t_instruction	instruction;
	int				value;
	int				linenum;
	struct s_tokens	*next;
	int				position;
}				t_tokens;

typedef struct	s_corewar
{
	char		*buff;
	char		*name;
	int			champ_size;
	char		*comment;
	int			got_name;
	int			got_comment;
	int			found_first_op;
	t_tokens	*tokens;
	int			linenum;
	int			total_bytes;
}				t_corewar;

/*
** parser.c
*/
void			parser(t_corewar *data, int fd);

/*
** wrong_syntax.c
*/
void			wrong_syntax(char *line);

/*
** tools.c
*/
int				skip_whitespace(char *line, int i);
int				skip_chars_delim(char *line, int i);
char			*trim_comment(char *line);

/*
** tokens.c
*/
void			add_token(t_corewar *data, char *line, int start, int end);
void			get_tokens(t_corewar *data, char *line);
void			bad_token(char *str);

/*
** analyze.c
*/
void			analyze_tokens(t_corewar *data);

/*
** analyze_help.c
*/
void			byte_tracker(t_corewar *data, t_tokens *current);
void			check_instruction(t_tokens *token, t_corewar *data);
void			replace_labels(t_corewar *data);

/*
** check_arguments.c
*/
void			check_arguments(t_tokens *tokens);

/*
** endian.c
*/
short			reverse16(short value);
int				reverse32(int value);

/*
** output.c
*/
void			write_output(t_corewar data, char *filename);

/*
** get_coding_oct.c
*/
char			get_coding_oct(t_tokens *t, t_instruction inst);
int				oct_check(t_instruction inst);

/*
** output_help.c
*/
void			write_instr(t_tokens *token, int fd);
void			write_regist(t_tokens *token, int fd);
void			write_direct(t_tokens *token, int fd, t_instruction type);
void			write_indirect(t_tokens *token, int fd);

#endif
