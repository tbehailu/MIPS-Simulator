#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"

void decode_instruction(Instruction instruction) {
    
    /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
    switch(instruction.opcode) {
        case 0x0: // opcode == 0x0 (SPECIAL)
            switch(instruction.rtype.funct) {
                case 0xc: // funct == 0xc (SYSCALL)
                    printf("syscall\n");
                    break;
                case 0x24: // funct == 0x24 (AND)
                    printf("and\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
                    break;
                default: // undefined funct
                    fprintf(stderr,"%s: illegal function: %08x\n",__FUNCTION__,instruction.bits);
                    exit(-1);
                    break;
            }
            break;
        case 0xd: // opcode == 0xd (ORI)
            printf("ori\t$%d,$%d,0x%x\n",instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
            break;
        case 0x2: // opcode == 0x2 (J)
            printf("j\t0x%x\n",instruction.jtype.addr*4);
            break;
        default: // undefined opcode
            fprintf(stderr,"%s: illegal instruction: %08x\n",__FUNCTION__,instruction.bits);
            exit(-1);
            break;
    }
}
