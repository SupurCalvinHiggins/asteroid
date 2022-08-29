#ifndef ASTROGC_INCLUDED
#define ASTROGC_INCLUDED

// initiliaze garbage collector
void AstroMem_init();
// returns a pointer to uninitialized memory of size 'size'  
void* AstroMem_new(unsigned long size);
// returns a pointer to initialized memory(all 0's) of size 'size'
void* AstroMem_newInit(unsigned long size);

#endif