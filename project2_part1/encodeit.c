
//
// simple encoding example for IA-32 validation project
//

#include <stdio.h>
#include <stdlib.h>
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

	return (num_inst);
}
