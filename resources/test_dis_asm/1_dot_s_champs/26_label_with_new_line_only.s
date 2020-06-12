.name	 "label_with_new_line_only"
.comment "label_with_new_line_only"

l2:	sti	r1,%:live,%0
	and	r1,%0,r17
live:	live	%1
	zjmp	%:live
empty_label:
