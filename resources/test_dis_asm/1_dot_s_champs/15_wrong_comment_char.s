.name	 "wrong_comment_char"
.comment "wrong_comment_char"

l2:	sti	r1,%:live,%0	:#this is wrong comment char
	and	r1,%0,r1
live:	live	%1
	zjmp	%:live
