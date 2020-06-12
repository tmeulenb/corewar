.name	 "no_new_line_at_end_of_instructions"
.comment "no_new_line_at_end_of_instructions"

l2:	sti	r1,%:live,%0
	and	r1,%0,r1
live:	live	%1
	zjmp	%:live
