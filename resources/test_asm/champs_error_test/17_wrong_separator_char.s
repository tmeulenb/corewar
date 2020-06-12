.name	 "wrong_separator_char"
.comment "wrong_separator_char"

l2:	sti	r1.%:live,%0
	and	r1,%0,r1
live:	live	%1
	zjmp	%:live
