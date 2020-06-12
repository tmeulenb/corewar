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

ASM_PATH=../../assembler
NRM_ERR=$(norminette $ASM_PATH | grep -v 'Not a valid file' | grep 'Error: ' | \
			wc -l | tr -d ' ')
NRM_WARN=$(norminette $ASM_PATH | grep -v 'Not a valid file' | grep 'Warning: ' | \
			wc -l | tr -d ' ')

if [ $NRM_ERR -eq '0' ] && [ $NRM_WARN -eq '0' ]; then
	echo "\n${BOLD}norminette check\
				${CLR_STYLE}${BG_GREEN}${BLACK} passed ${CLR_STYLE}"
else
	echo "\n${BOLD}norminette check\
				${CLR_STYLE}${BG_RED}${BLACK} failed ${CLR_STYLE}"
fi

#__________________________________________________________Cleaning_is_important

rm -rf ./champs_compare_test/*.cor
rm -rf ./champs_error_test/*.cor
rm -rf ./original_asm_cor/*
rm -rf ./test_asm_cor/*
rm -rf ./original_err_cor/*
rm -rf ./test_err_cor/*
rm -rf test_asm

#__________________________________________________________Variables_declaration

COMPARE_CHAMPS=./champs_compare_test/*.s
ERROR_CHAMPS=./champs_error_test/*.s

#_______________________________________Compiling champs with original assembler

OR_ASM_PATH=../asm
echo "\n${DIM}Compiling champs with original assembler to \
/original_asm_cor and /original_err_cor${CLR_STYLE}"

for champ in $COMPARE_CHAMPS
do
	$OR_ASM_PATH $champ >/dev/null
	if [ -f ${champ/.s/.cor} ]; then
		xxd -b ${champ/.s/.cor} > ${champ/.s/.bin}
		mv ${champ/.s/.bin} original_asm_cor/
		rm ${champ/.s/.cor}
	fi
done

for champ in $ERROR_CHAMPS
do
	$OR_ASM_PATH $champ >/dev/null
	if [ -f ${champ/.s/.cor} ]; then
		xxd -b ${champ/.s/.cor} > ${champ/.s/.bin}
		mv ${champ/.s/.bin} ./original_err_cor
		rm ${champ/.s/.cor}
	fi
done

#___________________________________________Compiling champs with test assembler

echo "${DIM}Compiling champs with test assembler to \
/test_asm_cor and /test_err_cor${CLR_STYLE}"
make -C $ASM_PATH fclean #>/dev/null
make -C $ASM_PATH #>/dev/null
mv $ASM_PATH/asm ./test_asm

for champ in $COMPARE_CHAMPS
do
	echo $champ
	./test_asm $champ #>/dev/null
	printf "\n"
	#echo ${champ/.s/.cor}
	if [ -f ${champ/.s/.cor} ]; then
		#echo "hey"
		xxd -b ${champ/.s/.cor} > ${champ/.s/.bin}
		mv ${champ/.s/.bin} test_asm_cor/
		rm ${champ/.s/.cor}
	fi
done

for champ in $ERROR_CHAMPS
do
	echo $champ
	./test_asm $champ #>/dev/null
	printf "\n"
	if [ -f ${champ/.s/.cor} ]; then
		xxd -b ${champ/.s/.cor} > ${champ/.s/.bin}
		mv ${champ/.s/.bin} ./test_err_cor
		rm ${champ/.s/.cor}
	fi
done

#__________________________________________Compare_original_and_test_asm_outputs

diff -q ./original_asm_cor/ ./test_asm_cor/ >diff_comp_test_message

if [ -s ./diff_comp_test_message ]; then
	echo "\n${BOLD}compare difference check\
			${CLR_STYLE}${BG_RED}${BLACK} failed ${CLR_STYLE}\n"
else
	echo "\n${BOLD}compare difference check\
			${CLR_STYLE}${BG_GREEN}${BLACK} passed ${CLR_STYLE}"
fi

for file in ./original_asm_cor/*.bin
do
	if [ ! -f "${file/original_asm_cor/test_asm_cor}" ]; then
		printf "File ${file/original_asm_cor/test_asm_cor} wasn't found\n"
        LAUNCH=${file/original_asm_cor/champs_compare_test}
        printf "Message from test_assembler about ${LAUNCH/.bin/.s}:\n"
		./test_asm ${LAUNCH/.bin/.s}
        printf "\n"
	else
		diff "$file" "${file/original_asm_cor/test_asm_cor}" >cmp_message
        if [ -s ./cmp_message ]; then
            printf "Files: $file ${file/original_asm_cor/test_asm_cor} differ:\n"
            cat cmp_message
            printf "\n"
        fi
	fi
done

for file in ./test_asm_cor/*.bin
do
	if [ ! -f "${file/test_asm_cor/original_asm_cor}" ]; then
		printf "File ${file/test_asm_cor/original_asm_cor} wasn't found\n"
		LAUNCH=${file/test_asm_cor/champs_compare_test}
		printf "Message from original_assembler about ${LAUNCH/.bin/.s}:\n"
		$OR_ASM_PATH ${LAUNCH/.bin/.s}
        printf "\n"
	fi
done

#________________________________________Compare_champions_with_erroneous_syntax

diff -q ./original_err_cor/ ./test_err_cor/ >diff_err_test_message

if [ -s ./diff_err_test_message ]; then
	echo "${BOLD}compare erroneous champs check\
			${CLR_STYLE}${BG_RED}${BLACK} failed ${CLR_STYLE}\n"
else
	echo "${BOLD}compare erroneous champs check\
			${CLR_STYLE}${BG_GREEN}${BLACK} passed ${CLR_STYLE}"
fi

for file in ./original_err_cor/*.bin
do
	if [ ! -f "${file/original_err_cor/test_err_cor}" ]; then
		printf "File ${file/original_err_cor/test_err_cor} wasn't found\n"
        LAUNCH=${file/original_err_cor/champs_error_test}
        printf "Message from test_assembler about ${LAUNCH/.bin/.s}:\n"
		./test_asm ${LAUNCH/.bin/.s}
        printf "\n"
	else
		diff "$file" "${file/original_err_cor/test_err_cor}" >cmp_message
        if [ -s ./cmp_message ]; then
            printf "Files: $file ${file/original_err_cor/test_err_cor} differ:\n"
            cat cmp_message
            printf "\n"
        fi
	fi
done

for file in ./test_err_cor/*.bin
do
	if [ ! -f "${file/test_err_cor/original_err_cor}" ]; then
		printf "File ${file/test_err_cor/original_err_cor} wasn't found\n"
		LAUNCH=${file/test_err_cor/champs_error_test}
		printf "Message from original_assembler about ${LAUNCH/.bin/.s}:\n"
		$OR_ASM_PATH ${LAUNCH/.bin/.s}
        printf "\n"
	fi
done
