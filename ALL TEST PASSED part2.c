#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "mips.h" // for execute_syscall()
#include "types.h"

void execute_instruction(Instruction instruction,Processor* processor,Byte *memory) {
    
    /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
    long temp;
    long x;
    switch(instruction.opcode) {
        case 0x0: // opcode == 0x0(SPECIAL)
            switch(instruction.rtype.funct) {
                    /**************/
                    
                /***GIVEN***/
                case 0xc: // funct == 0xc (SYSCALL)
                    execute_syscall(processor);
                    processor->PC += 4;
                    break;
                case 0x0: // funct == 0x00 (SLL)
                    // R[rd] ← R[rt] << shamt
                    processor->R[instruction.rtype.rd] = (processor->R[instruction.rtype.rt] << instruction.rtype.shamt);
                    processor->PC += 4;
                    break;
                case 0x2: // funct == 0x02 (SRL)
                    // R[rd] ← R[rt] >> shamt
                    processor->R[instruction.rtype.rd] = (processor->R[instruction.rtype.rt] >> instruction.rtype.shamt);
                    processor->PC += 4;
                    break;
                case 0x3: // funct == 0x03 (SRA)
                    // R[rd] ← (signed)R[rt] >> shamt
                    processor->R[instruction.rtype.rd] = (((sWord) processor->R[instruction.rtype.rt]) >> instruction.rtype.shamt);
                    break;
                case 0x8: // funct == 0x08 (JR)
                    // PC ← R[rs]
                    // processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs];
                    processor->PC = processor->R[instruction.rtype.rs];
                    break;
                case 0x9: // funct == 0x09 (JALR)  /**** Double check ***/
                    /*  
                    tmp ← PC + 4
                    PC ← R[rs]
                    R[rd] ← tmp 
                    */
                    
                    temp = processor->PC + 4;
                    processor->PC = processor->R[instruction.rtype.rs];
                    processor->R[instruction.rtype.rd] = temp;
                    
                    break;
                case 0x10: // funct == 0x10 (MFHI)
                    processor->R[instruction.rtype.rd] = processor->RHI;
                    processor->PC += 4;  
                    break;
                case 0x12: // funct == 0x12 (MFLO)
                    processor->R[instruction.rtype.rd] = processor->RLO;
                    processor->PC += 4;
                    break;
                case 0x18: { // funct == 0x18 (MULT)
                    /*  
                    tmp ← (signed)R[rs] * (signed)R[rt]
                    RLO ← {lower 32 bits of tmp}
                    RHI ← {upper 32 bits of tmp}
                    */
                    
                    temp = (((sDouble) processor->R[instruction.rtype.rs]) *  processor->R[instruction.rtype.rt]);
                  
                    processor->RLO = (Word) temp;
                    processor->RHI = (Word) (temp >> 32);
                    processor->PC += 4;
                    
                    break;
                }
                case 0x19: // funct == 0x19 (MULTU)
                    /*
                    tmp ← R[rs] * R[rt]
                    RLO ← {lower 32 bits of tmp}
                    RHI ← {upper 32 bits of tmp}
                    */
                    
                    temp = (((Double) processor->R[instruction.rtype.rs]) * processor->R[instruction.rtype.rt]);
                    
                    processor->RLO = (Word) temp;
                    processor->RHI = (Word) (temp >> 32);
                    processor->PC += 4;
                    
                    break;
                case 0x21: // funct == 0x21 (ADDU)
                    processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] + processor->R[instruction.rtype.rt];
                    processor->PC += 4;
                    break;
                case 0x23: // funct == 0x23 (SUBU)
                    processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] - processor->R[instruction.rtype.rt];
                    processor->PC += 4;
                    break;
                /***GIVEN***/
                case 0x24: // funct == 0x24 (AND)
                    processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] & processor->R[instruction.rtype.rt];
                    processor->PC += 4;
                    break;
                case 0x25: // funct == 0x25 (OR)
                    processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] | processor->R[instruction.rtype.rt];
                    processor->PC += 4;
                    break;
                case 0x26: // funct == 0x26 (XOR)
                    processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] ^ processor->R[instruction.rtype.rt];
                    processor->PC += 4;
                    break;
                case 0x27: // funct == 0x27 (NOR)
                    /* R[rd] ← ~(R[rs] | R[rt]) */
                    processor->R[instruction.rtype.rd] = ~(processor->R[instruction.rtype.rs] | processor->R[instruction.rtype.rt]);
                    processor->PC += 4;
                    break;
                case 0x2a: // funct == 0x2a (SLT)
                    /* R[rd] ← (signed)R[rs] < (signed)R[rt] */
                    processor->R[instruction.rtype.rd] = (((signed) processor->R[instruction.rtype.rs]) < ((signed) processor->R[instruction.rtype.rt])) ? 1 : 0;
                    processor->PC += 4;
                    break;
                case 0x2b: // funct == 0x2b (SLTU)
                    /* R[rd] ← R[rs] < R[rt] */
                    processor->R[instruction.rtype.rd] = (processor->R[instruction.rtype.rs] < processor->R[instruction.rtype.rt]) ? 1 : 0;
                    processor->PC += 4;
                    break;
                default: // undefined funct
                    fprintf(stderr,"%s: pc=%08x,illegal function=%08x\n",__FUNCTION__,processor->PC,instruction.bits);
                    exit(-1);
                    break;
                    
                    /**************/
                        
            }
            break;
       
            
        /***GIVEN***/    
        case 0x2: // opcode == 0x2 (J)
            processor->PC = ((processor->PC+4) & 0xf0000000) | (instruction.jtype.addr << 2);
            break;
            
        case 0x3: // opcode == 0x3 (JAL)
//            R[31] ← PC + 4
//            PC ← {(upper 4 bits of PC + 4), address*4}
            
            processor->R[31] = processor->PC+4;
            processor->PC = ((processor->PC+4) & 0xf0000000) | (instruction.jtype.addr << 2);
            //processor->PC = ((processor->R[31]) & 0xf0000000) | (instruction.jtype.addr << 2);
            break;
        case 0x4: // opcode == 0x4 (BEQ)
            // if(R[rs] == R[rt]): PC ← PC + 4 + SignExt(offset)*4
            if (processor->R[instruction.itype.rt] == processor->R[instruction.itype.rs]) {
                processor->PC = processor->PC + 4 +  ((sWord) instruction.itype.imm << 2);
            } else {
                processor->PC += 4;
            }
            break;
        case 0x5: // opcode == 0x5 (BNE)
            // if(R[rs] != R[rt]): PC ← PC + 4 + SignExt(offset)*4
            if (processor->R[instruction.itype.rt] != processor->R[instruction.itype.rs]) {
                processor->PC = processor->PC + 4 +  ((sWord) instruction.itype.imm << 2);
            } else {
                processor->PC += 4;
            }
            break;
        case 0x9: // opcode == 0x9 (ADDIU)
            processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] +  ((sWord) instruction.itype.imm);
            processor->PC += 4;
            break;
        case 0xa: // opcode == 0xa (SLTI)
            // R[rt] ← (signed)R[rs] < SignExt(imm)
            processor->R[instruction.itype.rt] = ((sWord) processor->R[instruction.itype.rs]) < (sWord) ((sHalf) instruction.itype.imm) ? 1 : 0;
            processor->PC += 4;
            break;
        case 0xb: // opcode == 0xb (SLTIU)
            processor->R[instruction.itype.rt] =  processor->R[instruction.itype.rs] <  (Word) ((Half) instruction.itype.imm) ? 1 : 0;
            processor->PC += 4;
            break;
        case 0xc: // opcode == 0xc (ANDI)
            processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] & instruction.itype.imm;
            processor->PC += 4;
            break;
            
        /***GIVEN***/
        case 0xd: // opcode == 0xd (ORI)
            processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] | instruction.itype.imm;
            processor->PC += 4;
            break;
        case 0xe: // opcode == 0xe (XORI)
            processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] ^ (Word) instruction.itype.imm;
            // or ^ (unsigned int) instruction.itype.imm
            processor->PC += 4;
            break;
        case 0xf: // opcode == 0xf (LUI) 
            processor->R[instruction.itype.rt] = (instruction.itype.imm << 16);
            processor->PC += 4;
            break;
        case 0x20: // opcode == 0x20 (LB) 
            // R[rt] ← SignExt(LoadMem(R[rs] + SignExt(offset), byte))
            
            x = processor->R[instruction.itype.rs] + ((sWord) ((sHalf) instruction.itype.imm));
            processor->R[instruction.itype.rt] = (sWord) load(memory, x, LENGTH_BYTE);
            processor->PC += 4;
            break;
        case 0x21: // opcode == 0x21 (LH)
            // R[rt] ← SignExt(LoadMem(R[rs] + SignExt(offset), half))
            
            x = processor->R[instruction.itype.rs] + ((sWord) ((sHalf) instruction.itype.imm));
            
            processor->R[instruction.itype.rt] = (sWord) load(memory, x, LENGTH_HALF_WORD);
            processor->PC += 4;
            break;
        case 0x23: // opcode == 0x23 (LW)
            // R[rt] ← LoadMem(R[rs] + SignExt(offset), word)
            
            x = processor->R[instruction.itype.rs] + ((sWord) ((sHalf) instruction.itype.imm));
           
            processor->R[instruction.itype.rt] = load(memory, x, LENGTH_WORD);
            
            processor->PC += 4;
            break;
        case 0x24: // opcode == 0x24 (LBU)
            // R[rt] ← ZeroExt(LoadMem(R[rs] + SignExt(offset), byte))
            
            x = processor->R[instruction.itype.rs] + ((sWord) ((sHalf) instruction.itype.imm));
            processor->R[instruction.itype.rt] = (Word) load(memory, x, LENGTH_BYTE);
            processor->PC += 4;
            break;
            
        case 0x25: // opcode == 0x25 (LHU) 
            // R[rt] ← ZeroExt(LoadMem(R[rs] + SignExt(offset), half))
            
            x = processor->R[instruction.itype.rs] + ((sWord) ((sHalf) instruction.itype.imm));
            processor->R[instruction.itype.rt] = (Word) load(memory, x, LENGTH_HALF_WORD);
            processor->PC += 4;
            break;
            
        case 0x28: // opcode == 0x28 (SB)
            // StoreMem(R[rs] + SignExt(offset), byte, R[rt])
            
            store(memory, processor->R[instruction.itype.rs] + ((sWord) ((sHalf) instruction.itype.imm)),LENGTH_BYTE, processor->R[instruction.itype.rt]);
            processor->PC += 4;
            break;
            
        case 0x29: // opcode == 0x29 (SH)
            // StoreMem(R[rs] + SignExt(offset), half, R[rt])
            
            store(memory, processor->R[instruction.itype.rs] + ((sWord) ((sHalf) instruction.itype.imm)),LENGTH_HALF_WORD, processor->R[instruction.itype.rt]);
            processor->PC += 4;
            
            break;
        case 0x2b: // opcode == 0x2b (SW)
            // StoreMem(R[rs] + SignExt(offset), word, R[rt])
            
            store(memory, processor->R[instruction.itype.rs] + ((sWord) ((sHalf) instruction.itype.imm)),LENGTH_WORD, processor->R[instruction.itype.rt]);
            processor->PC += 4;
            
            break;
        default: // undefined opcode ***GIVEN***
            fprintf(stderr,"%s: pc=%08x,illegal instruction: %08x\n",__FUNCTION__,processor->PC,instruction.bits);
            exit(-1);
            break;

    }
}


int check(Address address,Alignment alignment) {

    /* YOUR CODE HERE */
    
    if ((address <= 0) | ((address + alignment) > MEMORY_SPACE) | (address % alignment != 0)) {
        return 0;
    }
    return 1;
}

void store(Byte *memory,Address address,Alignment alignment,Word value) {
    if(!check(address,alignment)) {
        fprintf(stderr,"%s: bad write=%08x\n",__FUNCTION__,address);
        exit(-1);
    }
    
    /* YOUR CODE HERE */
    
    if (alignment == LENGTH_BYTE) {
        *(Byte *)(memory + address) = (Byte) value;
    }
    if (alignment == LENGTH_HALF_WORD){
        *(Half *)(memory + address) = (Half) value;
    }
    if (alignment == LENGTH_WORD){
        *(Word *)(memory + address) = (Word) value;
    }

}

Word load(Byte *memory,Address address,Alignment alignment) {

    
    if(!check(address,alignment)) {
        fprintf(stderr,"%s: bad read=%08x\n",__FUNCTION__,address);
        exit(-1);
    }
    
    /* YOUR CODE HERE */
    
    // incomplete stub to let "simple" execute
    // (only handles size == SIZE_WORD correctly)
    // feel free to delete and implement your own way
    
    Byte *ptr = (memory + address);
    if (alignment == LENGTH_BYTE){
        return *ptr;
    } else if (alignment == LENGTH_HALF_WORD){
        return *(Half*)(ptr);
    }
    return *(Word*)(ptr);
}