.data

failstring:    .asciiz "owntest3 failed!"

.text

# _start is the entry point into any program.
.global _start
.ent    _start
_start:

#
#  The header ends here, and code goes below
#
#   Test for mipsaddr+size > MEM_SIZE

addiu $18, $0, 1024
mult  $18, $18
mfhi  $4
mflo  $5
or    $18, $4, $5       #$18 now contains MEM_SIZE
subu  $19, $18, 4       #$19 now contains MEM_SIZE - 4
addiu $20, $0, 888      #20 contains test value

sw    $20, 0($19)
lw    $21, 0($19)
bne   $20, $21, fail

sb    $20, 0($18)
lb    $22, 0($18)       #this line should cause an ERROR
bne   $20, $22, fail

# exit the simulation (v0 = 10, syscall)
ori   $v0, $zero, 10
syscall

fail:
ori $a0, $0, %lo(failstring)
ori $v0, $0, 4
syscall

.end _start
