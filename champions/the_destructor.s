.name		"the destructor"
.comment	"A lesson of how to be a man"

# Anna's champ attempt

load_byte_0:
#r2 = 01 00 00 00 (live opcode)
ld	%1, r2 # - 7 byte
#r3 = 03 70 03 01 (set set in 256 bytes)
ld %57672449, r3 # - 7 byte
#r4 = 03 70 02 01 (set set live op in 256 bytes)
ld %57672193, r4 # - 7 byte

byte_21:
st r3, 255 # - 5 byte
st r4, 255 # - 5 byte
st r1, 510 # - 5 byte
st r2, 254 # - 5 byte
st r1, 253 # - 5 byte
st r1, 6 # - 5 bytes
live %42 # - 5 bytes
fork %:byte_21 # - 3 bytes

byte_59:
st r3, 255 # - 5 byte
st r4, 255 # - 5 byte
st r1, 510 # - 5 byte
st r2, 254 # - 5 byte
st r1, 253 # - 5 byte
st r1, 6 # - 5 bytes
live %42 # - 5 bytes

byte_94:
st r3, 255 # - 5 byte
st r4, 255 # - 5 byte
st r1, 510 # - 5 byte
st r2, 254 # - 5 byte
st r1, 253 # - 5 byte
st r1, 6 # - 5 bytes
live %42 # - 5 bytes

byte_129:
st r3, 255 # - 5 byte
st r4, 255 # - 5 byte
st r1, 510 # - 5 byte
st r2, 254 # - 5 byte
st r1, 253 # - 5 byte
st r1, 6 # - 5 bytes
live %42 # - 5 bytes

byte_164:
st r3, 255 # - 5 byte
st r4, 255 # - 5 byte
st r1, 510 # - 5 byte
st r2, 254 # - 5 byte
st r1, 253 # - 5 byte
st r1, 6 # - 5 bytes
live %42 # - 5 bytes

byte_199:
st r3, 255 # - 5 byte
st r4, 255 # - 5 byte
st r1, 510 # - 5 byte
st r2, 254 # - 5 byte
st r1, 253 # - 5 byte
st r1, 6 # - 5 bytes
live %42 # - 5 bytes

byte_234:
st r3, 255 # - 5 byte
st r4, 255 # - 5 byte
st r1, 510 # - 5 byte
st r2, 254 # - 5 byte
st r1, 253 # - 5 byte
st r1, 6 # - 5 bytes
live %42 # - 5 bytes

byte_269:
