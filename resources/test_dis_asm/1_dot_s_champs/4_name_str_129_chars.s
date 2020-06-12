.name    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque pena"
.comment "name_str_129_chars"
		
l2:	sti	r1,%:live,%0
	and	r1,%0,r1
live:	live	%1
	zjmp	%:live
