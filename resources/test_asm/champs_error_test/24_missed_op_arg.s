.name	 "missed_op_arg"
.comment "missed_op_arg"

l2:	sti	r1,,%0
	and	r1,%0,r17
live:	live	%1
	zjmp	%:live
