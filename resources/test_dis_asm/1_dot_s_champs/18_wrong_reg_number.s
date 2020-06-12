.name	 "wrong_reg_number"
.comment "wrong_reg_number"

l2:	sti	r1,%:live,%0
	and	r1,%0,r17
live:	live	%1
	zjmp	%:live
