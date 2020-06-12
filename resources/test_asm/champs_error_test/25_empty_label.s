.name	 "empty_label"
.comment "empty_label"

sti	r1,%:live,%0
	and	r1,%0,r17
live:	live	%1
	zjmp	%:live
empty_label:
