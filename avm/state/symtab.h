#ifndef SYMTAB_INCLUDED
#define SYMTAB_INCLUDED
#include <stdbool.h>
#include "table.h"
#define T SymTab_T
typedef struct T *T;
T       SymTab_new ();
void    SymTab_enterSym(T symbol_table, const void *key, void *value);
Table_T SymTab_findSym(T symbol_table, const void *key);
void   *SymTab_lookupSym(T symbol_table, const void *key, bool strict);
void    SymTab_updateSym(T symbol_table, const void *key, void *value);
void    SymTab_pushScope(T symbol_table, Table_T scope);
Table_T SymTab_popScope(T symbol_table);
bool    SymTab_isSymbolLocal(T symbol_table, const void *key);
bool    SymTab_isSymbolGlobal(T symbol_table, const void *key);
void    SymTab_enterGlobal(T symbol_table, const void *key);
void    SymTab_dumb(T symbol_table);
#undef T
#endif