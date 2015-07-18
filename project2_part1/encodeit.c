
//
// simple encoding example for IA-32 validation project
//

#include <stdio.h>
#include <stdlib.h>
#include <time>
#include "ia32_encode.h"

// globals to aid debug to start
volatile char *mptr=0,*next_ptr=0;
int num_inst=0;

main(int argc, char *argv[])
{

	int ibuilt=0;


	/* allocate buffer to build instructions into */

	mptr=malloc(MAX_INSTR_BYTES);
	next_ptr=mptr;                  // init next_ptr

	ibuilt=build_instructions();  	// build instructions

	fprintf(stderr,"generation program complete, instructions generated: %d\n",ibuilt);
}

//
// Routine:  build_instructions
//
// Description:
//
// INPUTS: none yet
// 
// OUTPUT: returns the number of instructions built
// 
int build_instructions() {

	// example instruction generation..

	// test move ecx into ebx
	next_ptr=build_mov_register_to_register(ISZ_4, REG_ECX ,REG_EBX, next_ptr);
	num_inst++;

	fprintf(stderr,"next ptr is now 0x%lx\n", (long) next_ptr);


	// test move edx into edi
	next_ptr=build_mov_register_to_register(ISZ_4, REG_EDX ,REG_EDI, next_ptr);
	num_inst++;

	fprintf(stderr,"next ptr is now 0x%lx\n", (long) next_ptr);
	
	/************** EDITS START HERE *****************/
	next_ptr=build_imm_to_regiser(ISZ_4, 0xbabecafe, REG_EBX, next_ptr);
	num_inst++;

	fprintf(stderr,"next ptr is now 0x%lx\n", (long) next_ptr);
	
	next_ptr=build_imm_to_regiser(ISZ_4, 0xbeefface, REG_ECX, next_ptr);
	num_inst++;

	fprintf(stderr,"next ptr is now 0x%lx\n", (long) next_ptr);
	
	next_ptr=build_imm_to_regiser(ISZ_2, 0xfeed, REG_EDX, next_ptr);
	num_inst++;

	fprintf(stderr,"next ptr is now 0x%lx\n", (long) next_ptr);
	
	next_ptr=build_imm_to_regiser(ISZ_1, 0xa5, REG_EAX, next_ptr);
	num_inst++;

	fprintf(stderr,"next ptr is now 0x%lx\n", (long) next_ptr);
	
	/*
	next_ptr=build_reg_to_memory(ISZ_1, REG_EAX, int dest_reg, next_ptr);
	num_inst++;

	fprintf(stderr,"next ptr is now 0x%lx\n", (long) next_ptr);
	
	next_ptr=build_reg_to_memory(ISZ_2, REG_EBX, int dest_reg, next_ptr);
	num_inst++;

	fprintf(stderr,"next ptr is now 0x%lx\n", (long) next_ptr);
	
	next_ptr=build_reg_to_memory(ISZ_2, REG_ECX, int dest_reg, next_ptr);
	num_inst++;

	fprintf(stderr,"next ptr is now 0x%lx\n", (long) next_ptr);
	
	next_ptr=build_reg_to_memory(ISZ_4, REG_EDX, int dest_reg, next_ptr);
	num_inst++;

	fprintf(stderr,"next ptr is now 0x%lx\n", (long) next_ptr);
	*/	
	
	return (num_inst);
}
