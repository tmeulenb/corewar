.name		"label_with_new_line_only"
.comment	"label_with_new_line_only"

sti r1, %15, %0
and r1, %0, r17
live %1
zjmp %-5
