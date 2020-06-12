.name	 "wrong_labels_char"
.comment "wrong_labels_char"

l2:	sti	r1,%:live,%0
	and	r1,%0,r1
liv-e:	live	%1
	zjmp	%:live
