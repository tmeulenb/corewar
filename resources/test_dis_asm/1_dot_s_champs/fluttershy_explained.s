#by zaz, it's not very good, but what did you expect, rainbowdash is way better
#2013

#	Light green values in vm -- recently printed
#	Highlighted in white -- recent alive declaration

#	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
#	"ld" - instruction title
#	2 - number of arguments needed
#	{T_DIR | T_IND, T_REG} - type arguments needed
#	2 - instruction code
#	5 - cycles cost
#	"load" - instruction meaning
#	1 - means types arguments code is needed (in binary)
#	0 - means direct arg (label) size == 4, otherwise == 2.

#	This file covers comands marked by "+":
#	t_op    op_tab[17] =
#	{
#		+{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
#		+{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
#		+{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
#		 {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
#		 {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
#		 {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
#			"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
#		 {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
#			"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
#		 {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
#			"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
#		 {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
#		 {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
#			"load index", 1, 1},
#		+{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
#			"store index", 1, 1},
#		+{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
#		 {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
#		 {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
#			"long load index", 1, 1},
#		 {"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
#		 {"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
#		 {0, 0, {0}, 0, 0, 0, 0, 0}
#	};
#
#

.name		"fluttershy"
.comment	"oh, my, what a scary project"

entry:
	fork	%:coregeni
#
#	Cycles will = 0 + 800 = 800.
#
#	vm execution: creates new cursor on byte address of the given label.
#	The current position let's say byte[0] and a new cursor will apper at byte[144].
#	Execution takes place on the cycle number == 800
#
# 1	 byte for -- fork opcode = 12 = 0x0c = 00001100
# 2 bytes for -- %:coregeni - direct number of bytes to the label = 144 =
#			= 0x00 0x90 = 00000000 10010000
#
# operation	in binary:	00001100	00000000	10010000
#			in hex:		0c			00			90
#			in decimal:	12						144
#
	st		r1, 6
#
#	Cycles will = 800 + 5 = 805.
#
#	Operation sets value of r1 (r1 == champ_num) into 4 bytes that are 6 bytes further
#	Current position is byte[0] and the values will be set at byte[6] ... byte[9]
#	This way operation at position byte[5] will report this champion alive.
#	After execution those 4 bytes become -1 =
#	0xff 0xff 0xff 0xff = 11111111 11111111 11111111 11111111.
#
# 1  byte for -- set opcode = 3 = 0x03 = 00000011
# 1  byte for -- set operation requires arguments types code = 112 = 0x70 =
#			= 01(reg_code=1)11(ind_code=3)0000
# 1  byte for -- reg number = 1 = 0x01 = 00000001
# 2 bytes for -- indirect argument = 6 = 0x06 = 00000000 00000110
#
# operation	in binary:	00000011	01110000	00000001	00000000	00000110
#			in hex:		03			70			01			00			06
#			in decimal:	3			112			1						6
#
	live	%42
#
#	Cycles will = 805 + 10 = 815.
#
#	"If cursor's r1 == Argument1, set player as last reported alive"
#	How %42 == value in r1? 42 is a random value. With previous "set" operation
#	the value of live argument was changed to r1 value.
#	The operation in vm since last operation is written as "01 ff ff ff ff"
#
#	Operations that reported live is now highlited in white (cycle == 815).
#	Last live == 815.
#	The higlight dissapear after 49 cycles (when cycle == 864).
#
# 1  byte for -- live opcode = 1 = 0x01 = 00000001
# 4 bytes for -- direct argument of live operation = 42 = 0x2a =
#			= 00000000 00000000 00000000 00101010
#
# operation	in binary:	00000001	00000000	00000000	00000000	00101010
#			in hex:		01			00			00			00			2a
#			in decimal:	1												42
#
	fork	%:torpgeni
#
#	Cycles will = 815 + 800 = 1615.
#
#	Current cycle == 815. Fork requires 800 more cycles and will be executed
#	on cycle number 815+800=1615(-1536=79(!) Why cycle didn't return
#	to 0 after 1536). Cursor won't die - it reported alive
#	in current cycle.
#
# 1	 byte for -- fork opcode = 12 = 0x0c = 00001100
# 2 bytes for -- %:torpgeni - direct number of bytes to the label = 369
#			= 0x01 0x71 = 00000001 01110001
#
# operation	in binary:	00001100	00000001	01110001
#			in hex:		0c			01			71
#			in decimal:	12			369
#
	st		r1, 6
#
#	Cycles will = 1615 + 5 = 1620.
#
#	Will set r1 value, as argument, of the following "live" operation
#
# 1  byte for -- set opcode = 3 = 0x03 = 00000011
# 1  byte for -- set operation requires arguments types code =
#			= 01(reg_code=1)11(ind_code=3)0000
# 1  byte for -- reg number = 1 = 0x01 = 00000001
# 2 bytes for -- indirect argument = 6 = 0x06 = 00000000 00000110
#
# operation	in binary:	00000011	01110000	00000001	00000000	00000110
#			in hex:		03			70			01			00			06
#			in decimal:	3			112			1						6
#
	live	%42
#
#	Cycles will = 1620 + 10 = 1630.
#
#	Live is reported on cycle 1630.
#
# 1  byte for -- live opcode = 1 = 0x01 = 00000001
# 4 bytes for -- direct argument of live operation = 42 = 0x2a =
#			= 00000000 00000000 00000000 00000110
#
# operation	in binary:	00000001	00000000	00000000	00000000	00101010
#			in hex:		01			00			00			00			2a
#			in decimal:	1												42
#
	fork	%:avdefgeni
#
#	Cycles will = 1630 + 800 = 2430.
#
# 1	 byte for -- fork opcode = 12 = 0x0c = 00001100
# 2 bytes for -- %:avdefgeni - direct number of bytes to the label = 241 =
#			= 0x00 0xf1 = 00000000 11110001
#
# operation	in binary:	00001100	00000000	11110001
#			in hex:		0c			00			f1
#			in decimal:	12						241
#

ardeftgt:

ardefgeni:
	st 		r1, 6
#
#	Cycles will = 2430 + 5 = 2435.
#
#	Will set r1 value, as argument, of the following "live" operation
#
# 1  byte for -- set opcode = 3 = 0x03 = 00000011
# 1  byte for -- set operation requires arguments types code =
#			= 01(reg_code=1)11(ind_code=3)0000
# 1  byte for -- reg number = 1 = 0x01 = 00000001
# 2 bytes for -- indirect argument = 6 = 0x06 = 00000000 00000110
#
# operation	in binary:	00000011	01110000	00000001	00000000	00000110
#			in hex:		03			70			01			00			06
#			in decimal:	3			112			1						6
#

ardefgen:
	live 	%213904
#
#	Cycles will = 2435 + 10 = 2445.
#
# 213904 % 512 = 400
# 1  byte for -- live opcode = 1 = 0x01 = 00000001
# 4 bytes for -- direct argument of live operation = 213904 = 0x03 0x43 0x90 =
#			= 00000000 00000011 01000011 10010000
#
# operation	in binary:	00000001	00000000	00000011	01000011	10010000
#			in hex:		01			00			03			43			90
#			in decimal:	1						213904
#
	fork 	%:ardefgen
#
#	Cycles will = 2445 + 800 = 3245.
#
# 1	 byte for -- fork opcode = 12 = 0x0c = 00001100
# 2 bytes for -- %:ardefgen - direct number of bytes to the previous operation =
#			= -5 (prev operation = 1+4 = 5 bytes, minus sign is to go back) =
#			= 0xff 0xfb = 11111111 11111011
#
# operation	in binary:	00001100	11111111	11111011
#			in hex:		0c			ff			fb
#			in decimal:	12			-5
#

ardefinit:
	sti		r1, %:ardefl1, %1
#
#	Cycles will = 3245 + 25 = 3270.
#
#	"Value from the Argument1 is written to the memory, to the address:
#	current_position + ((Argument2 + Argument3) % IDX_MOD).
#	If Argument2 is of type T_IND, value (4 bytes) for address calculation
#	is read from memory: current_position + (Argument2 % IDX_MOD)"
#
#	Value from r1 will be written as "live" argument in ardefl1 label
#	(after 52(arg1) + 1(arg2) bytes).
#
# 1  byte for -- store index opcode = 11 = 0x0b = 00001011
# 1  byte for -- store index operation requires arguments types code =
#			= 01(reg_code=1)10(dir_code=2)10(dir_code=2)00
# 1  byte for -- reg number = 1 = 0x01 = 00000001
# 2 bytes for -- direct argument = 52 = 0x34 = 00000000 00110100
# 2 bytes for -- direct argument = 1 = 0x01 = 00000000 00000001
#
# operation	in binary:	00001011	01101000	00000001	00000000	00110100	00000000	00000001
#			in hex:		0b			68			01			00			34			00			01
#			in decimal:	11			104			1						52						1
#
	st		r1, 6
#
#	Cycles will = 3270 + 5 = 3275.
#
#	Will set r1 value, as argument, of the following "live" operation
#
# 1  byte for -- set opcode = 3 = 0x03 = 00000011
# 1  byte for -- set operation requires arguments types code =
#			= 01(reg_code=1)11(ind_code=3)0000
# 1  byte for -- reg number = 1 = 0x01 = 00000001
# 2 bytes for -- indirect argument = 6 = 0x06 = 00000000 00000110
#
# operation	in binary:	00000011	01110000	00000001	00000000	00000110
#			in hex:		03			70			01			00			06
#			in decimal:	3			112			1						6
#
	live	%43123
#
#	Cycles will = 3275 + 10 = 3285.
#
# 43123 % 512 = 115
# 1  byte for -- live opcode = 1 = 0x01 = 00000001
# 4 bytes for -- direct argument of live operation = 43123 = 0xa8 0x73 =
#			= 00000000 00000000 01000011 10010000
#
# operation	in binary:	00000001	00000000	00000000	10101000	01110011
#			in hex:		01			00			00			a8			73
#			in decimal:	1									43123
#
	sti		r1, %:ardefchk, %1
#
#	Cycles will = 3285 + 25 = 3310.
#
#	"Value from the Argument1 is written to the memory, to the address:
#	current_position + ((Argument2 + Argument3) % IDX_MOD).
#	If Argument2 is of type T_IND, value (4 bytes) for address calculation
#	is read from memory: current_position + (Argument2 % IDX_MOD)"
#
#	Value from r1 will be written as "live" argument in ardefl1 label (after 53 bytes)
#	Set by index operation cost is 25 cycles.
#
# 1  byte for -- store index opcode = 11 = 0x0b = 00001011
# 1  byte for -- store index operation requires arguments types code =
#			= 01(reg_code=1)10(dir_code=2)10(dir_code=2)00
# 1  byte for -- reg number = 1 = 0x01 = 00000001
# 2 bytes for -- direct argument = 62 = 0x3e = 00000000 00111110
# 2 bytes for -- direct argument = 1 = 0x01 = 00000000 00000001
#
# operation	in binary:	00001011	01101000	00000001	00000000	00111110	00000000	00000001
#			in hex:		0b			68			01			00			3e			00			01
#			in decimal:	11			104			1						62						1
#
	ld		%-6, r2
#
#	Cycles will = 3310 + 5 = 3315.
#
#	"Load value from Argument1 into registry number Argument2.
#	If Argument1 type is T_IND, value to be loaded is read from memory.
#	Address is calculated as follows: current_position + (Argument1 % IDX_MOD)
#	If result is 0, set carry to 1. If result is !0, set carry to 0."
#
# 1  byte for -- store index opcode = 2 = 0x02 = 00000010
# 1  byte for -- store index operation requires arguments types code =
#			= 10(dir_code=2)01(reg_code=1)0000
# 4 bytes for -- direct argument of load operation = -6 = 0xff 0xff 0xff 0xfa
#			= 11111111 11111111 11111111 11111010
# 1  byte for -- reg number = 2 = 0x02 = 00000010
#
# operation	in binary:	00000010	10010000	11111111	11111111	11111111	11111010	00000010
#			in hex:		02			90			ff			ff			ff			fa			02
#			in decimal:	2			144												4294967290	2
#
	ld		%-6, r3
#
#	Cycles will = 3315 + 5 = 3320.
#
#	"Load value from Argument1 into registry number Argument2.
#	If Argument1 type is T_IND, value to be loaded is read from memory.
#	Address is calculated as follows: current_position + (Argument1 % IDX_MOD)
#	If result is 0, set carry to 1. If result is !0, set carry to 0."
#
# 1  byte for -- store index opcode = 2 = 0x02 = 00000010
# 1  byte for -- store index operation requires arguments types code =
#			= 10(dir_code=2)01(reg_code=1)0000
# 4 bytes for -- direct argument of load operation = -6 = 0xff 0xff 0xff 0xfa
#			= 11111111 11111111 11111111 11111010
# 1  byte for -- reg number = 3 = 0x03 = 00000011
#
# operation	in binary:	00000010	10010000	11111111	11111111	11111111	11111010	00000011
#			in hex:		02			90			ff			ff			ff			fa			03
#			in decimal:	2			144												4294967290	3
#
	ld		%150994953, r4
#
#	Cycles will = 3320 + 5 = 3325.
#
#	"Load value from Argument1 into registry number Argument2.
#	If Argument1 type is T_IND, value to be loaded is read from memory.
#	Address is calculated as follows: current_position + (Argument1 % IDX_MOD)
#	If result is 0, set carry to 1. If result is !0, set carry to 0."
#
# 1  byte for -- store index opcode = 2 = 0x02 = 00000010
# 1  byte for -- store index operation requires arguments types code =
#			= 10(dir_code=2)01(reg_code=1)0000
# 4 bytes for -- direct argument of load operation = 150994953 = 0x09 0x00 0x00 0x09
#			= 11111111 11111111 11111111 11111010
# 1  byte for -- reg number = 4 = 0x04 = 00000100
#
# operation	in binary:	00000010	10010000	00001001	00000000	00000000	00001001	00000100
#			in hex:		02			90			09			00			00			09			04
#			in decimal:	2			144												4294967290	4
#
	ld		%-186, r5
#
#	Cycles will = 3325 + 5 = 3330.
#
#	"Load value from Argument1 into registry number Argument2.
#	If Argument1 type is T_IND, value to be loaded is read from memory.
#	Address is calculated as follows: current_position + (Argument1 % IDX_MOD)
#	If result is 0, set carry to 1. If result is !0, set carry to 0."
#
# 1  byte for -- store index opcode = 2 = 0x02 = 00000010
# 1  byte for -- store index operation requires arguments types code =
#			= 10(dir_code=2)01(reg_code=1)0000
# 4 bytes for -- direct argument of load operation = -186 = 0xff 0xff 0xff 0x46
#			= 11111111 11111111 11111111 01000110
# 1  byte for -- reg number = 5 = 0x05 = 00000101
#
# operation	in binary:	00000010	10010000	11111111	11111111	11111111	01000110	00000101
#			in hex:		02			90			ff			ff			ff			46			05
#			in decimal:	2			144												-186		5
#

ardefwrite:
ardefl1:
	live	%295423
#
#	Cycles will = 3330 + 10 = 3340.
#
# 1  byte for -- live opcode = 1 = 0x01 = 00000001
# 4 bytes for -- direct argument of live operation = 295423 = 0x04 0x81 0xff =
#			= 00000000 00000100 10000001 11111111
#
# operation	in binary:	00000001	00000000	00000100	10000001	11111111
#			in hex:		01			00			04			81			ff
#			in decimal:	1												295423
#
	sti		r4, %:ardeftgt, r2
#
#	Cycles will = 3340 + 25 = 3365.
#
#	"Value from the Argument1 is written to the memory, to the address:
#	current_position + ((Argument2 + Argument3) % IDX_MOD).
#	If Argument2 is of type T_IND, value (4 bytes) for address calculation
#	is read from memory: current_position + (Argument2 % IDX_MOD)"
#
#	Value from r4 will be written to 4 bytes at ...
#	(65466 - 6) % 512 = 436
#
# 1  byte for -- store index opcode = 11 = 0x0b = 00001011
# 1  byte for -- store index operation requires arguments types code =
#			= 01(reg_code=1)10(dir_code=2)01(reg_code=1)00
# 1  byte for -- reg number = 4 = 0x04 = 00000100
# 2 bytes for -- direct argument = 62 = 0xff 0xba = 11111111 10111010
# 1  byte for -- reg argument = 2 = 0x02 = 00000010
#
# operation	in binary:	00001011	01100100	00000100	11111111	10111010	00000010
#			in hex:		0b			64			04			ff			ba			02
#			in decimal:	11			104			4						65466		2
#
	add		r2, r3, r2

	sti		r4, %:ardeftgt, r2
	add		r2, r3, r2
ardefchk:
	live	%3940641
	xor		r2, r5, r15
	zjmp	%:ardefinit
ardefloop:	
	ld		%0, r16
	zjmp	%:ardefwrite


coregeni:
	st		r1, 6

coregen:
	live	%123012
	fork	%:coregen

coreinit:
	st		r1, 58
	st		r1, 58
	st		r1, 58
	st		r1, 58
	st		r1, 58
	st		r1, 58
	st		r1, 58
	st		r1, 58
	st		r1, 58
	st		r1, 58
	ld		%0, r16

corelive:
	live	%985341
	live	%985341
	live	%985341
	live	%985341
	live	%985341
	live	%985341
	live	%985341
	live	%985341
	live	%985341
	live	%985341
	zjmp	%:corelive

avdefgeni:
	st 		r1, 6

avdefgen:
	live 	%213904
	fork 	%:avdefgen

avdefinit:
	sti		r1, %:avdefl1, %1
	st		r1, 6
	live	%43123
	sti		r1, %:avdefchk, %1
	ld		%0, r2
	ld		%6, r3
	ld		%150994953, r4
	ld		%180, r5

avdefwrite:
avdefl1:
	live	%295423
	sti		r4, %:avdeftgt, r2
	add		r2, r3, r2
	sti		r4, %:avdeftgt, r2
	add		r2, r3, r2
avdefchk:
	live	%3940641
	xor		r2, r5, r15
	zjmp	%:avdefinit
avdefloop:	
	ld		%0, r16
	zjmp	%:avdefwrite

torpgeni:
	st		r1, 6

torpgen:
	live	%96824
	fork	%:torpgen

torpinit:
	ld		%0, r2
	ld		%4, r3
	ld		%96, r5
	sti		r1, %:torpchk, %1
	st		r1, 6

torpwrite:
torpl1:
	live	%8008135
	ldi		%:torpinit, r2, r4
	sti		r4, %400, r2
	add		r2, r3, r2
	ldi		%:torpinit, r2, r4
	sti		r4, %383, r2
	add		r2, r3, r2
torpchk:
	live	%89523
	xor		r2, r5, r15	
	zjmp	%362
torploop:
	ld		%0, r15
	zjmp	%:torpwrite

avdeftgt:
