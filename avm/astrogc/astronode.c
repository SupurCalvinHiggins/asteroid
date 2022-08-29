#include "gc.h"

// initiliaze garbage collector
void AstroMem_init(){
    GC_INIT();      /* Optional on Linux/X86*/
}

// returns a pointer to uninitialized memory of size 'size'  
void* AstroMem_new( unsigned long size ){
    //assert(size);

    return GC_MALLOC_ATOMIC( size );
}

// returns a pointer to initialized memory(all 0's) of size 'size'
void* AstroMem_newInit( unsigned long size ){
    //assert(size);

    return GC_MALLOC( size );
}
