#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "symtab.h"
#include "state.h"
#include "mem.h"
#include "assert.h"
#include "table.h"
#include "seq.h"
#include "array.h"
#include "astronode.h"
/******************************************************************************/
const int MODULES_HINT = 10; 
/******************************************************************************/

/******************************************************************************/
State* State_new() {

	State* new_state = malloc( sizeof( struct state_s ));
	SymTab_T new_symtab = SymTab_new();
	Seq_T module_list = Seq_new( MODULES_HINT);
	//ASTNode_lineinfo *init_line = malloc( sizeof(ASTNode_lineinfo));
	char *init_mname = malloc(8 * sizeof(char));

	assert(new_state);
	assert(new_symtab);
	assert(module_list);
	assert(init_mname);

	init_mname = "<input>";
	new_state->symbol_table = new_symtab;
	new_state->modules = module_list;
	new_state->AST = NULL;
	new_state->eval_redundancy = true;
	new_state->ignore_quote = false;
	new_state->cond_warning = false;
	new_state->current_line = AstroLineInfo_new( init_mname, 1);

	return new_state;
}
/******************************************************************************/
Seq_T State_getModules(State* state ){
	assert(state);
	return state->modules;
}
/******************************************************************************/
void State_addModule( State* state, char* module){
	assert(state);
	Seq_addlo( state->modules, module);
}
/******************************************************************************/
void State_setIgnoreQuote(State* state, bool value){
	assert(state);
	state->ignore_quote = value;
}
/******************************************************************************/
void State_setEvalRedundancy(State* state, bool value){
	assert(state);
	state->eval_redundancy = value;
}
/******************************************************************************/
void State_setCondWarning(State* state, bool value){
	assert(state);
	state->cond_warning = value;
}
/******************************************************************************/
bool State_getIgnoreQuote( State* state){
	assert(state);
	return state->ignore_quote;
}
/******************************************************************************/
bool State_getEvalRedundancy(State* state){
	assert(state);
	return state->eval_redundancy;
}
/******************************************************************************/
bool State_getCondWarning(State* state){
	assert(state);
	return state->cond_warning;
}
/******************************************************************************/
unsigned long State_getContaintLvl(State* state){
	assert(state);
	return state->constraint_lvl;
}
/******************************************************************************/
void State_incConstraintLvl(State* state){
	assert(state);
	++(state->constraint_lvl);
}
/******************************************************************************/
void State_decConstraintLvl(State* state){
	assert(state);
	--(state->constraint_lvl);
}
/******************************************************************************/
void* State_getAST(State* state){
	assert(state);
	return state->AST;
}
/******************************************************************************/
void State_setAST(State* state, void* AST){
	assert(state);
	state->AST = AST;
}
/******************************************************************************/
void State_warning(State* state, char *message) {
	AstroLineInfo *line = state->current_line;
	fprintf(stdout,"Warning: %s: %lu: %s\n",AstroLineInfo_getModule(line),
									AstroLineInfo_getLine(line),message);
}
/******************************************************************************/
AstroLineInfo* State_getLineInfo(State* state){
	assert(state);
	return state->current_line;
}
/******************************************************************************/
void State_setLineInfo(State* state,AstroLineInfo* line){
	assert(line);
	state->current_line = line;
}
/******************************************************************************/
void State_setLine(State* state, unsigned long line){
	assert(state);
	AstroLineInfo_setLine( State_getLineInfo(state), line);
}
/******************************************************************************/
unsigned long State_getLine(State* state){
	assert(state);
	return AstroLineInfo_getLine( State_getLineInfo(state));
}
/******************************************************************************/
void* State_lookupSym(State* state, char* id){
	assert(state);
	assert(id);
	return SymTab_lookupSym(state->symbol_table, id, true);
}
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/