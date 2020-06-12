#!bin/sh

# usage: sh test_asm.sh

#____________________________________________________________________Text_styles

CLR_STYLE="\033[0m"
BOLD="\033[1m"
BG_RED="\033[101m"
BG_GREEN="\033[102m"
BLACK="\033[30m"
DIM="\033[2m"

#_______________________________________________________________Norminette_check

DIS_ASM_PATH=../../disassembler
NRM_ERR=$(norminette $DIS_ASM_PATH | grep -v 'Not a valid file' | grep 'Error: ' | \
			wc -l | tr -d ' ')
NRM_WARN=$(norminette $DIS_ASM_PATH | grep -v 'Not a valid file' | grep 'Warning: ' | \
			wc -l | tr -d ' ')

if [ $NRM_ERR -eq '0' ] && [ $NRM_WARN -eq '0' ]; then
	echo "\n${BOLD}norminette check\
			${CLR_STYLE}${BG_GREEN}${BLACK} passed ${CLR_STYLE}\n"
else
	echo "\n${BOLD}norminette check\
			${CLR_STYLE}${BG_RED}${BLACK} failed ${CLR_STYLE}\n"
fi

#__________________________________________________________Cleaning_is_important

echo "${DIM}Cleaning${CLR_STYLE}"

make -C $DIS_ASM_PATH/ clean >/dev/null
make -C $DIS_ASM_PATH/ fclean >/dev/null
rm -rf ./dis_asm*
rm -rf ./2_dot_cor_champs/*
rm -rf ./3_dot_s_made_by_disassembler/*
rm -rf ./4_dot_cor_form_disassembled_champs/*

#____________________________________________________Assemble_dot_cor_from_dot_s

echo "${DIM}Assembling ./1_dot_s_champs/*.s to ./2_dot_cor_champs/*.cor${CLR_STYLE}"

sleep 5s

DOT_S_CHAMPS=./1_dot_s_champs/*.s

for champ in $DOT_S_CHAMPS
do
	./asm $champ >/dev/null
done
mv ${DOT_S_CHAMPS/.s/.cor} ./2_dot_cor_champs

#___________________________________________________________Compile_disassembler

echo "${DIM}Compiling dis_asm${CLR_STYLE}"

make -C $DIS_ASM_PATH/ >/dev/null
cp $DIS_ASM_PATH/dis_asm ./dis_asm

#___________________________________________________Disassemble_dot_cor_to_dot_s

echo "${DIM}Disassembling ./2_dot_cor_champs/*.cor to ./3_dot_s_made_by_disassembler/*.s${CLR_STYLE}"

sleep 5s

DOT_COR_CHAMPS=./2_dot_cor_champs/*.cor

for champ in $DOT_COR_CHAMPS
do
	./dis_asm $champ
done
mv ${DOT_COR_CHAMPS/.cor/.s} ./3_dot_s_made_by_disassembler

#________________________________Assemble_dot_cor_from_disassembled_champs_AGAIN

echo "${DIM}Assembling ./3_dot_s_made_by_disassembler/*.s to ./4_dot_cor_form_disassembled_champs/*.cor${CLR_STYLE}"

sleep 5s

DOT_S_MADE_BY_DISASSEMBLER=./3_dot_s_made_by_disassembler/*.s

for champ in $DOT_S_MADE_BY_DISASSEMBLER
do
	./asm $champ >/dev/null
done
mv ${DOT_S_MADE_BY_DISASSEMBLER/.s/.cor} ./4_dot_cor_form_disassembled_champs

#______________Compare_champs_dot_cor_with_champs_dot_cor_that_were_disassembled

echo "${DIM}Comparing ./2_dot_cor_champs/*.cor to ./4_dot_cor_form_disassembled_champs/*.cor${CLR_STYLE}"

sleep 5s

diff -q ./2_dot_cor_champs/ ./4_dot_cor_form_disassembled_champs/ >diff_dot_cor_files

if [ -s ./diff_dot_cor_files ]; then
	echo "\n${BOLD}compare dot_cor check\
			${CLR_STYLE}${BG_RED}${BLACK} failed ${CLR_STYLE}\n"
else
	echo "\n${BOLD}compare dot_cor check\
			${CLR_STYLE}${BG_GREEN}${BLACK} passed ${CLR_STYLE}\n"
fi

sleep 5s

for file in ./2_dot_cor_champs/*.cor
do
	if [ ! -f "${file/2_dot_cor_champs/4_dot_cor_form_disassembled_champs}" ]; then
		printf "File ${file/2_dot_cor_champs/4_dot_cor_form_disassembled_champs} wasn't found\n"
        printf "Message from ./dis_asm about ${file}:\n"
		./dis_asm $file
		rm -rf ${file/.cor/.s}
        printf "\n"
	else
		cmp -bl "$file" "${file/2_dot_cor_champs/4_dot_cor_form_disassembled_champs}" >cmp_dot_cor_files
        if [ -s ./cmp_dot_cor_files ]; then
            printf "Files: $file ${file/2_dot_cor_champs/4_dot_cor_form_disassembled_champs} differ:\n"
            cat cmp_dot_cor_files
            printf "\n"
        fi
	fi
done

#___________________________________________________________________________Done
