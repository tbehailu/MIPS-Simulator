.data

failstring:    .asciiz "owntest2 failed!"

.text

# _start is the entry point into any program.
.global _start
.ent    _start 
_start:

#
#  The header ends here, and code goes below
#

    #Test for store and load, with and without offset

    addiu $18, $0, 888
    addiu $19, $0, 999
    addiu $20, $0, 1028
    addiu $21, $20, 16
    addiu $22, $0, 1024
    
    #Test 1: Store without offset
    sw    $19, 0($20)
    
    #  Test 1(a): Load without offset
    lw    $23, 0($20)
    bne   $19, $23, fail
    
    #  Test 1(b): Load with offset
    lw    $24, 4($22)
    bne   $19, $24, fail
    
    #Test 2: Store with offset
    sw    $18, 16($20)
    
    #  Test 2(a) Load without offset
    lw    $25, 0($21)
    bne   $18, $25, fail
    
    #  Test 2(b) Load with offset
    lw    $26, 20($22)
    bne   $18, $26, fail 

# exit the simulation (v0 = 10, syscall)
	ori   $v0, $zero, 10
	syscall
    
fail:
    ori $a0, $0, %lo(failstring)
    ori $v0, $0, 4
    syscall

.end _start
