# Corewar
In this game which is based on the 1984 game Core Wars, warrior programs written in the assembly language Redcode will fight each other in a virtual arena.
Writing this project was an exercise in coding:

- A Virtual Machine (which will host the game as well as act as the jury) with instructions it recognizes, registers, etc.
- An assembler to translate Redcode into bytecode.
- A disassembler which translates bytecode into Redcode.
- Some warriors to fight in the arena.
- A visualizer using the ncurses library

Core War was inspired by a malicious virus written in the 80’s. To deal with the self-replicating virus, a white hat hacker invented Reaper. It was a virus designed to spread and eliminate the malware. He fought fire with fire.

This inspired A. K. Dewdney to coin the idea for Core War.

The idea was simple. You compete by designing viruses to overtake a computer. You win by protecting your own program and overwriting your opponent's programs. This is all happening on a virtual machine that simulates how a cpu works.

See https://en.wikipedia.org/wiki/Core_War for more information.

This is what is looks like in action:

![corewar.gif](https://github.com/jongdetim/Corewar/blob/master/resources/191115_1702_corewar.gif)

**1. Game board.**<br/>
The memory of our virtual computer. It’s represented in a 64 X 64 grid of bytes. Every byte, the pairs of numbers or letters, are represented in hexadecimal. Each hexadecimal has the value of a digit, from 0 to 255. The values represent commands and command's arguments. There are 16 commands.<br/>
<br/>
**2. Players.**<br/>
Small programs represented in different colors. The white parts have blank memory.<br/>
<br/>
**3. Cursors.**<br/>
The moving parts with inverted color. They read from the game board.
The cursors have a couple of features. They can jump on the game board, store and write values, and clone themselves. The cursors belong to no-one, they just read from the game board.When the game starts, all players have one cursor at the beginning of their program. The game advances as the cursors read the commands stored in their programs. If a cursor ends up on a faulty command or a blank memory, it moves to the next byte.
<br/>
<br/>
**Player wins if he is the last one to declare himself alive.**<br/>
If a cursor reads a players life command from the game board, it stays alive for one round. Every game round is measured in cycles. "Cycles to die" determine how much each cursor can read from the game board within one round. Cycles to die gradually decrese, until it reaches zero. At that point game ends and a winner is announced.

# Usage

To download, build and launch the game:

```
git clone https://github.com/jongdetim/corewar.git
cd corewar/
make
./virtual_machine/corewar -ncurses ./champions/the_destructor.cor ./resources/champs/examples/bee_gees.cor
```
Press 'space' key to pause.<br/>
Press 'q' key when the game is over, to exit the visual mode.<br/>
To view usage message, launch without arguments:
```
./virtual_machine/corewar
Usage:	./corewar [-v | -ncurses | -d N | -help] [-n N] champion1.cor [-n N] champion2.cor [-n N] champion3.cor [-n N] champion4.cor
	-v	: verbose mode. Shows cursor's execution details
	-ncurses: visual mode. Visualizes the game | can't be used with -v or -dump together
	-d N	: dump flag. Dumps memory after N cycles and exits
	-n N	: player's order. Sets N's ID number of the next player. N is min. 1 and max. 4
```
