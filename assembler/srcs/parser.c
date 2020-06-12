/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/02 18:21:04 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/30 21:49:03 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

/*
**	saves the name of the warrior program
*/

static void	get_name(t_corewar *data, int fd, char *line, int i)
{
	int		start_count[2];
	char	*str;

	start_count[0] = i;
	start_count[1] = 1;
	while (1)
	{
		if (start_count[1] > PROG_NAME_LENGTH + 1)
			ft_error("name is too long");
		if (line[i] == '\0' || line[i] == '"')
		{
			str = ft_strsub(line, start_count[0], i - start_count[0]);
			ft_strlcat(data->name, str, PROG_NAME_LENGTH + 1);
			free(str);
			if (line[i] == '"')
				return (free(line));
			free(line);
			ft_strlcat(data->name, "\n", PROG_NAME_LENGTH + 1);
			start_count[0] = 0;
			i = -1;
			get_next_line(fd, &line);
		}
		i++;
		start_count[1]++;
	}
}

static void	double_name_or_comment(int name_or_comment)
{
	if (name_or_comment == 1)
		ft_error("multiple instances of .name is not allowed");
	if (name_or_comment == 2)
		ft_error("multiple instances of .comment is not allowed");
}

/*
**	saves the description (comment) of the warrior program
*/

static void	get_comment(t_corewar *data, int fd, char *line, int i)
{
	int		start_count[2];
	char	*str;

	start_count[0] = i;
	start_count[1] = 1;
	while (1)
	{
		if (start_count[1] > COMMENT_LENGTH + 1)
			ft_error("warrior comment (description) is too long");
		if (line[i] == '\0' || line[i] == '"')
		{
			str = ft_strsub(line, start_count[0], i - start_count[0]);
			ft_strlcat(data->comment, str, COMMENT_LENGTH + 1);
			free(str);
			if (line[i] == '"')
				return (free(line));
			free(line);
			ft_strlcat(data->comment, "\n", COMMENT_LENGTH + 1);
			start_count[0] = 0;
			i = -1;
			get_next_line(fd, &line);
		}
		i++;
		start_count[1]++;
	}
}

/*
**	checks if the part of the line that starts with '.' is '.name' or
**	'.comment', otherwise its an error
*/

static void	get_descriptives(t_corewar *data, int fd, char *line, int i)
{
	if (ft_strncmp(line + i, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
	{
		if (data->got_name == 1)
			double_name_or_comment(1);
		i = skip_whitespace(line, i + ft_strlen(NAME_CMD_STRING));
		if (line[i] != '"')
			ft_error(".name must be followed by \" on the same line");
		get_name(data, fd, line, i + 1);
		data->got_name = 1;
	}
	else if (ft_strncmp(line + i, COMMENT_CMD_STRING,
			ft_strlen(COMMENT_CMD_STRING)) == 0)
	{
		if (data->got_comment == 1)
			double_name_or_comment(2);
		i = skip_whitespace(line, i + ft_strlen(COMMENT_CMD_STRING));
		if (line[i] != '"')
			ft_error(".comment must be followed by \" on the same line");
		get_comment(data, fd, line, i + 1);
		data->got_comment = 1;
	}
	else
		wrong_syntax(line);
}

/*
**	parsing function
*/

void		parser(t_corewar *data, int fd)
{
	char	*line;
	int		i;

	data->linenum = 0;
	while (get_next_line(fd, &line) > 0)
	{
		i = skip_whitespace(line, 0);
		if (line[i] == '\0' || line[i] == COMMENT_CHAR ||
							line[i] == ALT_COMMENT_CHAR)
		{
			free(line);
			continue ;
		}
		else if (line[i] == COMMENT_CMD_STRING[0] ||
						line[i] == NAME_CMD_STRING[0])
			get_descriptives(data, fd, line, i);
		else if (data->got_name == 1 && data->got_comment == 1)
		{
			get_tokens(data, line);
			data->linenum++;
			free(line);
		}
		else
			free(line);
	}
}
