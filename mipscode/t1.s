.data

failstring:    .asciiz "owntest1 failed!"

.text

# _start is the entry point into any program.
.global _start
.ent    _start 
_start:

#
#  The header ends here, and code goes below
#

    addiu $19, $0, 999
    addiu $20, $0, 1097
    addiu $21, $0, 1097
    sw    $19, 0($20)       #this line should cause and error
    lw    $22, 0($21)
    bne   $19, $22, fail
    
# exit the simulation (v0 = 10, syscall)
	ori   $v0, $zero, 10
	syscall
    
fail:
    ori $a0, $0, %lo(failstring)
    ori $v0, $0, 4
    syscall

.end _start
