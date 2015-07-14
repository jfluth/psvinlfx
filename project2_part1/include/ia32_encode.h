/*
 * GENERAL Instruction Format
 *
 * -----------------------------------------------------------------
 * | Instruction    |   Opcode | ModR/M | Displacement | Immediate |
 * | Prefixes       |          |        |              |           |
 * -----------------------------------------------------------------
 *
 *  7  6  5   3  2   0
 * --------------------
 * | Mod | Reg* | R/M |
 * --------------------
 */ 

#include <stdio.h>
#include <stdlib.h>
/*
 * definitions we need to support these functions.
 *
 * see Table 2-2 in SDM for register/MODRM encode usage
 *
 *
 */
#define PREFIX_16BIT   0x66
#define BASE_MODRM     0xc0
#define REG_SHIFT      0x3
#define MODRM_SHIFT    0x6
#define RM_SHIFT       0x0
#define REG_MASK       0x7
#define RM_MASK        0x7
#define MOD_MASK       0x3

// register defs based on MOD RM table
#define REG_EAX        0x0
#define REG_ECX        0x1
#define REG_EDX        0x2
#define REG_EBX        0x3
#define REG_ESP        0x4
#define REG_EBP        0x5
#define REG_ESI        0x6
#define REG_EDI        0x7

// byte offset
#define BYTE1_OFF      0x1
#define BYTE2_OFF      0x2
#define BYTE3_OFF      0x3
#define BYTE4_OFF      0x4

// ISIZE (instruction size in bytes, for move example 2byte = 16bit)

#define ISZ_1         0x1
#define ISZ_2         0x2
#define ISZ_4         0x4
#define ISZ_8         0x8


// code generation defines

#define MAX_INSTR_BYTES 10000
/*
 * Function: build_mov_register_to_register
 *
 * Description:
 *
 * Inputs: 
 *
 *  short mov_size               :  size of the move being requested
 *  int   src_reg                :  register source encoding 
 *  int   dest_reg               :  destination reg of move
 *  volatile char *tgt_addr      :  starting memory address of where to store instruction
 *
 * Output: 
 *
 *  returns adjusted address after encoding instruction
 *
 */


static inline volatile char *build_mov_register_to_register(short mov_size, int src_reg, int dest_reg, volatile char *tgt_addr)
{
	// for 16 bit mode we need to treat it special because it requires a prefix

	if (mov_size == 2) {
		(*tgt_addr ++) = PREFIX_16BIT;
	}

	// now lets look at each size and determine which opcode required

	switch(mov_size)  {

	case 1: 
		(*(short *) tgt_addr) = ((BASE_MODRM) + (dest_reg << REG_SHIFT) + src_reg) << 8 | 0x8a;
		 tgt_addr += BYTE2_OFF;
		 break;

	case 2:  // can overload this case because same opcode, but already set prefix
	case 4: 
		(*(short *) tgt_addr) = ((BASE_MODRM) + (dest_reg << REG_SHIFT) + src_reg) << 8 | 0x8b;
		 tgt_addr += BYTE2_OFF;
		 break;

	default:
		 fprintf(stderr,"ERROR: Incorrect size (%d) passed to register to register move\n", mov_size);
		 return (NULL);

	}
			
        return(tgt_addr);
}
