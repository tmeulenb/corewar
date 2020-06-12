.name	 "wrong_label_char_;"
.comment "wrong_label_char_;"

l2:	sti	r1,%;live,%0
	and	r1,%0,r1
live:	live	%1
	zjmp	%:live
