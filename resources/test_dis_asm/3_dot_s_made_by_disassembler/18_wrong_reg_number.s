.name		"wrong_reg_number"
.comment	"wrong_reg_number"

sti r1, %15, %0
and r1, %0, r17
live %1
zjmp %-5
