.name	 "invalid_spacing"
.comment "invalid_spacing"

l2:	stir	r1,%:live,%0
	and	r1,%0,r17
live:	live	%1
	zjmp	%:live
