# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmeulenb <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/04 15:06:49 by tmeulenb       #+#    #+#                 #
#    Updated: 2019/11/12 21:12:26 by tide-jon      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VM_NAME =		vm

ASM_NAME = 		asm

DIS_ASM_NAME =	dis_asm


all : $(VM_NAME) $(ASM_NAME) $(DIS_ASM_NAME)

vm :
				@ echo "virtual machine"
				@ make -C ./virtual_machine

asm :
				@ echo "assembler"
				@ make -C ./assembler

dis_asm :
				@ echo "disassembler"
				@ make -C ./disassembler

test :
				@ cp -r ./resources/test_asm ./assembler
				@ cp -r ./resources/test_dis_asm ./disassembler
				
clean :
				@ echo "virtual machine"
				@ make clean -C ./virtual_machine
				@ echo "assembler"
				@ make clean -C ./assembler
				@ echo "disassembler"
				@ make clean -C ./disassembler

fclean :
				@ echo "virtual machine"
				@ make fclean -C ./virtual_machine
				@ echo "assembler"
				@ make fclean -C ./assembler
				@ echo "disassembler"
				@ make fclean -C ./disassembler

re : fclean all

.PHONY: clean fclean all re corewar asm dis_asm
