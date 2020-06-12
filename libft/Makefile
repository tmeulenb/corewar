# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ayundina <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/02/07 12:38:25 by ayundina       #+#    #+#                 #
#    Updated: 2019/11/12 21:06:27 by tide-jon      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS_LIB = ft_atoi.c \
	   ft_bzero.c \
	   ft_isalnum.c \
	   ft_isalpha.c \
	   ft_isascii.c \
	   ft_isdigit.c \
	   ft_isprint.c \
	   ft_itoa.c \
	   ft_memalloc.c \
	   ft_memccpy.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_memcpy.c \
	   ft_memdel.c \
	   ft_memmove.c \
	   ft_memset.c \
	   ft_putchar_fd.c \
	   ft_putchar.c \
	   ft_putendl_fd.c \
	   ft_putendl.c \
	   ft_putnbr_fd.c \
	   ft_putnbr.c \
	   ft_putstr_fd.c \
	   ft_putstr.c \
	   ft_strcat.c \
	   ft_strchr.c \
	   ft_strclr.c \
	   ft_strcmp.c \
	   ft_strcpy.c \
	   ft_strdel.c \
	   ft_strdup.c \
	   ft_strequ.c \
	   ft_striter.c \
	   ft_striteri.c \
	   ft_strjoin.c \
	   ft_strlcat.c \
	   ft_strlen.c \
	   ft_strmap.c \
	   ft_strmapi.c \
	   ft_strncat.c \
	   ft_strncmp.c \
	   ft_strncpy.c \
	   ft_strnequ.c \
	   ft_strnew.c \
	   ft_strnstr.c \
	   ft_strrchr.c \
	   ft_strsplit.c \
	   ft_strstr.c \
	   ft_strsub.c \
	   ft_strtrim.c \
	   ft_tolower.c \
	   ft_toupper.c \
	   ft_lstnew.c \
	   ft_lstdelone.c \
	   ft_lstdel.c \
	   ft_lstadd.c \
	   ft_lstiter.c \
	   ft_lstmap.c \
	   ft_intlen.c \
	   ft_getnum.c \
	   ft_dupword.c \
	   ft_getwords.c \
	   ft_countwords.c \
	   ft_beg_sp.c ft_end_sp.c \
	   get_next_line.c \
	   ft_isint.c \
	   ft_error.c \
	   ft_modulo.c \
	   ft_iswhitespace.c

SRCS_PRINTF = ft_printf.c \
	   ft_read_flags.c \
	   ft_upply_options.c \
	   ft_fl_hh.c \
	   ft_fl_h.c \
	   ft_fl_l.c \
	   ft_fl_ll.c \
	   ft_fl_capitll.c \
	   ft_fl_hash.c \
	   ft_conv_csp.c \
	   ft_conv_dibouxf.c \
	   ft_conv_none.c \
	   ft_fl_hash.c \
	   ft_fl_plus.c \
	   ft_fl_sp.c \
	   ft_fl_precision.c \
	   ft_fl_minus.c \
	   ft_fl_zero.c \
	   ft_fl_width.c \
	   ft_ulltoa_base.c \
	   ft_dtoa.c \
	   ft_arandomtoi.c 
	  

OBJ_LIB = ${SRCS_LIB:c=o}

OBJ_PRINTF = ${SRCS_PRINTF:c=o}

all: $(NAME)

$(NAME):
	@gcc -g -Wall -Wextra -Werror -c $(SRCS_LIB) $(addprefix ./ft_printf/, $(SRCS_PRINTF))
	@ar rc $(NAME) $(OBJ_LIB) $(OBJ_PRINTF)
	@ranlib $(NAME)

clean:
	@/bin/rm -f $(OBJ_LIB) $(OBJ_PRINTF)

fclean: clean
	@/bin/rm -f $(NAME)

re: clean fclean all
