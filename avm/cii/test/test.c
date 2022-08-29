#include <stdio.h>
#include "table.h"
#include "symtab.h"
#include "state.h"

int main(int argc,char **argv){

    Table_T table = Table_new(0, NULL, NULL);
    SymTab_T symTable = SymTab_new();

   /*

    char newKey[4] = "Tim";
    double d = 1.234;
    double *newValue = &d;
    SymTab_enterSym(symTable,newKey,newValue);
    void *outValue = NULL;
    SymTab_pushScope( symTable, Table_new(100,NULL,NULL));
    SymTab_pushScope( symTable, Table_new(100,NULL,NULL));
    SymTab_pushScope( symTable, Table_new(100,NULL,NULL));
    SymTab_pushScope( symTable, Table_new(100,NULL,NULL));
    SymTab_pushScope( symTable, Table_new(100,NULL,NULL));
    SymTab_pushScope( symTable, Table_new(100,NULL,NULL));
    SymTab_popScope( symTable);
    SymTab_popScope( symTable);
    SymTab_pushScope( symTable, Table_new(100,NULL,NULL));
    SymTab_pushScope( symTable, Table_new(100,NULL,NULL));
    SymTab_pushScope( symTable, Table_new(100,NULL,NULL));
    SymTab_enterGlobal( symTable, newKey);
    double e = 17.13;
    SymTab_enterSym(symTable,newKey,&e);
    SymTab_popScope( symTable);
    outValue = SymTab_lookupSym(symTable,newKey,true);

    if (outValue == NULL){
        printf("NULL\n");
    }
    if (SymTab_isSymbolGlobal(symTable, newKey)){
        printf("GLOBAL\n");
    }
    if (SymTab_isSymbolLocal(symTable, newKey)){
        printf("LOCAL\n");
    }

    printf("Hello World!\n");
    printf("Value recieved: %f\n",*(double*)outValue);

    SymTab_pushScope( symTable, Table_new(100,NULL,NULL));

    char newKey1[8] = "x_value";
    double d = 1.234;
    SymTab_enterSym(symTable,newKey1,&d);

    char newKey2[8] = "y_value";
    double e = 4.567;
    SymTab_enterSym(symTable,newKey2,&e);

    char newKey3[4] = "new";
    double f = 13.5;
    SymTab_enterSym(symTable,newKey3,&f);

    char newKey4[5] = "new2";
    double g = 13.123;
    SymTab_enterGlobal( symTable, newKey4);
    SymTab_enterSym( symTable, newKey4, &g);

    SymTab_pushScope( symTable, Table_new(100,NULL,NULL));

    char newKey5[8] = "x_value";
    double h = 11.1;
    SymTab_enterSym(symTable,newKey5,&h);

    SymTab_pushScope( symTable, Table_new(100,NULL,NULL));

    char newKey6[5] = "new4";
    double i = 99.99999;
    SymTab_enterGlobal( symTable, newKey6);
    SymTab_enterSym(symTable,newKey6,&i);

    SymTab_popScope( symTable);

    SymTab_dumb( symTable );

    */

    State* state = State_new();
    State_warning( state ,"This is a test of the warning system!");

    

    (void)state;
    (void)table;
    (void)symTable;
    return 0;
}