#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"

void decode_instruction(Instruction instruction) {
    
    /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
    switch(instruction.opcode) {
        case 0x0: // opcode == 0x0 (SPECIAL)
            switch(instruction.rtype.funct) {
                case 0xc: // funct == 0xc (SYSCALL) ***GIVEN***
                    printf("syscall\n");
                    break;
                case 0x0: // funct == 0x00 (SLL) sll rd, rt, shamt
                    printf("sll\t$%d,$%d,%d\n",instruction.rtype.rd,instruction.rtype.rt,instruction.rtype.shamt);
                    break;
                case 0x2: // funct == 0x02 (SRL) srl rd, rt, shamt
                    printf("srl\t$%d,$%d,%d\n",instruction.rtype.rd,instruction.rtype.rt,instruction.rtype.shamt);
                    break;
                case 0x3: // funct == 0x03 (SRA) sra rd, rt, shamt
                    printf("sra\t$%d,$%d,%d\n",instruction.rtype.rd,instruction.rtype.rt,instruction.rtype.shamt);
                    break;
                case 0x8: // funct == 0x08 (JR) jr rs ******TODO: multiply by 4?**********
                    printf("jr\t$%d\n",instruction.rtype.rs);
                    break;
                case 0x9: // funct == 0x09 (JALR) jalr rd, rs
                    printf("jalr\t$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs);
                    break;
                case 0x10: // funct == 0x10 (MFHI) mfhi rd
                    printf("mfhi\t$%d\n",instruction.rtype.rd);
                    break;
                case 0x12: // funct == 0x12 (MFLO) mflo rd
                    printf("mflo\t$%d\n",instruction.rtype.rd);
                    break;
                case 0x18: // funct == 0x18 (MULT) mult rs, rt
                    printf("mult\t$%d,$%d\n",instruction.rtype.rs,instruction.rtype.rt);
                    break;
                case 0x19: // funct == 0x19 (MULTU) multu rs, rt
                    printf("multu\t$%d,$%d\n",instruction.rtype.rs,instruction.rtype.rt);
                    break;
                case 0x21: // funct == 0x21 (ADDU) addu rd, rs, rt
                    printf("addu\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
                    break;
                case 0x23: // funct == 0x23 (SUBU) subu rd, rs, rt
                    printf("subu\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
                    break;
                case 0x24: // funct == 0x24 (AND) ***GIVEN***
                    printf("and\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
                    break;
                case 0x25: // funct == 0x25 (OR) or rd, rs, rt
                    printf("or\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
                    break;
                case 0x26: // funct == 0x26 (XOR) xor rd, rs, rt
                    printf("xor\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
                    break;
                case 0x27: // funct == 0x27 (NOR) nor rd, rs, rt
                    printf("nor\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
                    break;
                case 0x2a: // funct == 0x2a (SLT) slt rd, rs, rt
                    printf("slt\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
                    break;
                case 0x2b: // funct == 0x2b (SLTU) sltu rd, rs, rt
                    printf("sltu\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
                    break;
                default: // undefined funct
                    fprintf(stderr,"%s: illegal function: %08x\n",__FUNCTION__,instruction.bits);
                    exit(-1);
                    break;
            }
            break;
        case 0x2: // opcode == 0x2 (J)  ***GIVEN***
            printf("j\t0x%x\n",instruction.jtype.addr*4);
            break;
        case 0x3: // opcode == 0x3 (JAL)  jal address
            printf("jal\t0x%x\n",instruction.jtype.addr*4);
            break;
        case 0x4: // opcode == 0x4 (BEQ)  beq rs, rt, offset ****TODO: Multiply imm by 4?? ***
            printf("beq\t$%d,$%d,%d\n",instruction.itype.rs,instruction.itype.rt,instruction.itype.imm*4);
            break;
        case 0x5: // opcode == 0x5 (BNE)  bne rs, rt, offset
            printf("bne\t$%d,$%d,%d\n",instruction.itype.rs,instruction.itype.rt,instruction.itype.imm*4);
            break;
        case 0x9: // opcode == 0x9 (ADDIU)  addiu rt, rs, imm
            printf("addiu\t$%d,$%d,%d\n",instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
            break;
        case 0xa: // opcode == 0xa (SLTI)  slti rt, rs, imm
            printf("slti\t$%d,$%d,0x%x\n",instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
            break;
        case 0xb: // opcode == 0xb (SLTIU)  sltiu rt, rs, imm
            printf("sltiu\t$%d,$%d,0x%x\n",instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
            break;
        case 0xc: // opcode == 0xc (ANDI)  andi rt, rs, imm
            printf("andi\t$%d,$%d,0x%x\n",instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
            break;
        case 0xd: // opcode == 0xd (ORI) ***GIVEN***
            printf("ori\t$%d,$%d,0x%x\n",instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
            break;
        case 0xe: // opcode == 0xe (XORI)  xori rt, rs, imm
            printf("xori\t$%d,$%d,0x%x\n",instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
            break;
        case 0xf: // opcode == 0xf (LUI)  lui rt, imm ***** TODO: SHIFT IMM BY 16 *******
            printf("lui\t$%d,0x%x\n",instruction.itype.rt,instruction.itype.imm);
            break;
        case 0x20: // opcode == 0x20 (LB)  lb rt, offset(rs)
            printf("lb\t$%d,%x($%d)\n",instruction.itype.rt,instruction.itype.imm*4,instruction.itype.rs);
            break;
        case 0x21: // opcode == 0x21 (LH)  lh rt, offset(rs)
            printf("lh\t$%d,0x%x($%d)\n",instruction.itype.rt,instruction.itype.imm*4,instruction.itype.rs);
            break;
        case 0x23: // opcode == 0x23 (LW)  lw rt, offset(rs)
            printf("lw\t$%d,%d($%d)\n",instruction.itype.rt,instruction.itype.imm*4,instruction.itype.rs);
            break;
        case 0x24: // opcode == 0x24 (LBU)  lbu rt, offset(rs)
            printf("lbu\t$%d,0x%x($%d)\n",instruction.itype.rt,instruction.itype.imm*4,instruction.itype.rs);
            break;
        case 0x25: // opcode == 0x25 (LHU)  lhu rt, offset(rs)
            printf("lhu\t$%d,0x%x($%d)\n",instruction.itype.rt,instruction.itype.imm*4,instruction.itype.rs);
            break;
        case 0x28: // opcode == 0x28 (SB)  sb rt, offset(rs)
            printf("sb\t$%d,0x%x($%d)\n",instruction.itype.rt,instruction.itype.imm*4,instruction.itype.rs);
            break;
        case 0x29: // opcode == 0x29 (SH)  sh rt, offset(rs)
            printf("sh\t$%d,0x%x($%d)\n",instruction.itype.rt,instruction.itype.imm*4,instruction.itype.rs);
            break;
        case 0x2b: // opcode == 0x2b (SW)  sw rt, offset(rs)
            printf("sw\t$%d,%d($%d)\n",instruction.itype.rt,instruction.itype.imm*4,instruction.itype.rs);
            break;
        default: // undefined opcode ***GIVEN***
            fprintf(stderr,"%s: illegal instruction: %08x\n",__FUNCTION__,instruction.bits);
            exit(-1);
            break;
    }
}
