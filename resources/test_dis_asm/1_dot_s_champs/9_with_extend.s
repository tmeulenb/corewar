.name	 "with_extend"
.comment "extend_command_should_not_compile"
.extend
		
l2:	sti	r1,%:live,%0
	and	r1,%0,r1
live:	live	%1
	zjmp	%:live
