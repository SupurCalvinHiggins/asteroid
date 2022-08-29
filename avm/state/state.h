/* $Id$ */
#ifndef STATE_INCLUDED
#define STATE_INCLUDED
#include "seq.h"
#include "astronode.h"
#include "symtab.h"

typedef struct state_s {
	SymTab_T symbol_table;
	Seq_T modules; // loaded modules
	void* AST;
	bool eval_redundancy;
	bool ignore_quote;           // used to evaluate quoted expressions
	bool cond_warning;           // used to indicate if conditional subsumption
                                 // warning has been displayed
	unsigned long constraint_lvl;// used to evaluate constraint-only patterns
	AstroLineInfo *current_line; // holds module and line number/ ASTRONODE TYPE
} State;

State* State_new ();
void State_warning(State* state, char *message);
Seq_T State_getModules(State* state);
void State_addModule(State* state, char* module);
void State_setIgnoreQuote(State* state, bool value);
void State_setEvalRedundancy(State* state, bool value);
void State_setCondWarning(State* state, bool value);
bool State_getIgnoreQuote( State* state);
bool State_getEvalRedundancy(State* state);
bool State_getCondWarning(State* state);
unsigned long State_getContaintLvl(State* state);
void State_incConstraintLvl(State* state);
void State_decConstraintLvl(State* state);
void* State_getAST(State* state);
void State_setAST(State* state, void* AST);
AstroLineInfo* State_getLineInfo(State* state);
void State_setLineInfo(State* state,AstroLineInfo* line);
void State_setLine(State* state, unsigned long line);
unsigned long State_getLine(State* state);
void* State_lookupSym(State* state, char* id);
#endif