#ifndef ASTRONODE_INCLUDED
#define ASTRONODE_INCLUDED
#include <stdbool.h>

// Parent struct, contains a single member which will decribe what the
// rest of the struct will look like.
typedef struct astronode_s {
    char type;
} AstroNode;

typedef struct astrointeger_s {
    AstroNode super;
    long value;
} AstroInteger;

typedef struct astroreal_s {
    AstroNode super;
    double value;
} AstroReal;

typedef struct astroboolean_s {
    AstroNode super;
    bool value;
} AstroBoolean;

typedef struct astrostring_s {
    AstroNode super;
    char* value;
} AstroString;

typedef struct astrolineinfo_s {
    AstroNode super;
    char* module_name;
    unsigned long line_number;
} AstroLineInfo;

typedef struct astronone_s {
    AstroNode super;
} AstroNone;

typedef struct astronil_s {
    AstroNode super;
} AstroNil;

typedef struct astrolist_s {
    AstroNode super;
    unsigned long length;
    AstroNode** contents;
} AstroList;

typedef struct astrotuple_s {
    AstroNode super;
    unsigned long length;
    AstroNode** contents;
} AstroTuple;

typedef struct astrotolist_s {
    AstroNode super;
    AstroNode* start;
    AstroNode* stop;
    AstroNode* stride;    
} AstroToList;

typedef struct astroheadtail_s {
    AstroNode super;
    AstroNode* head;
    AstroNode* tail;
} AstroHeadTail;

typedef struct astrorawtolist_s {
    AstroNode super;
    AstroNode* start;
    AstroNode* stop;
    AstroNode* stride;
} AstroRawToList;

typedef struct astrorawheadtail_s {
    AstroNode super;
    AstroNode* head;
    AstroNode* tail;
} AstroRawHeadTail;

typedef struct astrosequence_s {
    AstroNode super;
    AstroNode* first;
    AstroNode* second;
} AstroSequence;

typedef struct astrofunction_s {
    AstroNode super;
    AstroList* body_list;
    void* closure;
} AstroFunction;

typedef struct astroeval_s {
    AstroNode super;
    AstroNode* expression;
} AstroEval;

typedef struct astroquote_s {
    AstroNode super;
    AstroNode* expression;
} AstroQuote;

typedef struct astroconstraint_s {
    AstroNode super;
    AstroNode* expression;
} AstroConstraint;

typedef struct astrotypematch_s {
    AstroNode super;
    AstroNode* expression;
} AstroTypeMatch;

typedef struct astroforeign_s {
    AstroNode super;
    void* content;
} AstroForeign;

typedef struct astroid_s {
    AstroNode super;
    char* name;
} AstroID;

typedef struct astroobject_s {
    AstroNode super;
    AstroID* struct_id;  
    AstroList* object_memory;
} AstroObject;

typedef struct astroapply_s {
    AstroNode super;
    AstroNode* function;
    AstroNode* argument;
} AstroApply;

typedef struct astroindex_s {
    AstroNode super;
    AstroNode* structure;
    AstroNode* index_exp;
} AstroIndex;

typedef struct astroescape_s {
    AstroNode super;
    void* content;
} AstroEscape;

typedef struct astrois_s {
    AstroNode super;
    AstroNode* pattern;
    AstroNode* term;
} AstroIs;

typedef struct astroin_s {
    AstroNode super;
    AstroNode* expression;
    AstroNode* expression_list;
} AstroIn;

typedef struct astroif_s {
    AstroNode super;
    AstroNode* cond_exp;
    AstroNode* then_exp;
    AstroNode* else_exp;
} AstroIf;

typedef struct astronamedpattern_s {
    AstroNode super;
    AstroID* name;
    AstroNode* pattern;
} AstroNamedPattern;

typedef struct astroderef_s {
    AstroNode super;
    AstroNode* expression;
} AstroDeref;

AstroNode* AstroNode_new(char type);
char AstroNode_peek(AstroNode* node);
void AstroNode_setType(AstroNode* node, char newType);
bool AstroNode_compare(AstroNode* first, AstroNode* second);
AstroInteger* AstroInteger_new(long value);
void AstroInteger_setValue(AstroInteger* node, long value);
long AstroInteger_getValue(AstroInteger* node);
bool AstroInteger_compare(AstroInteger* first,AstroInteger* second);
AstroReal* AstroReal_new(double value);
void AstroReal_setValue(AstroReal* node, double value);
double AstroReal_getValue(AstroReal* node);
bool AstroReal_compare(AstroReal* first,AstroReal* second);
AstroBoolean* AstroBoolean_new(bool value);
void AstroBoolean_setValue(AstroBoolean* node, bool value);
bool AstroBoolean_getValue(AstroBoolean* node);
bool AstroBoolean_compare(AstroBoolean* first,AstroBoolean* second);
AstroString* AstroString_new(char* value);
void AstroString_setValue(AstroString* node, char* value);
char* AstroString_getValue(AstroString* node);
bool AstroString_compare(AstroString* first,AstroString* second);
AstroLineInfo* AstroLineInfo_new(char* module_name, unsigned long line_number);
void AstroLineInfo_setModule(AstroLineInfo* node, char* module_name);
void AstroLineInfo_setLine(AstroLineInfo* node, unsigned long line_number);
char* AstroLineInfo_getModule(AstroLineInfo* node);
unsigned long AstroLineInfo_getLine(AstroLineInfo* node);
bool AstroLineInfo_compare(AstroLineInfo* first, AstroLineInfo* second);
AstroNone* AstroNone_new();
bool AstroNone_compare(AstroNone* first,AstroNone* second);
AstroNil* AstroNil_new();
bool AstroNil_compare(AstroNil* first,AstroNil* second);
AstroList* AstroList_new(unsigned long length, AstroNode** contents);
unsigned long AstroList_getLength(AstroList* node);
void AstroList_setLength(AstroList* node,unsigned long length);
AstroNode** AstroList_getContents(AstroList* node);
void AstroList_setContents(AstroList* node, AstroNode** contents);
AstroNode* AstroList_getElement(AstroList* node, unsigned long index);
void AstroList_setElement(AstroList* node, unsigned long index, AstroNode* element);
bool AstroList_compare(AstroList* first, AstroList* second);
AstroTuple* AstroTuple_new(unsigned long length, AstroNode** contents);
unsigned long AstroTuple_getLength(AstroTuple* node);
void AstroTuple_setLength(AstroTuple* node, unsigned long length);
AstroNode** AstroTuple_getContents(AstroTuple* node);
void AstroTuple_setContents(AstroTuple* node, AstroNode** contents);
AstroNode* AstroTuple_getElement(AstroTuple* node, unsigned long index);
void AstroTuple_setElement(AstroTuple* node, unsigned long index, AstroNode* element);
bool AstroTuple_compare(AstroTuple* first,AstroTuple* second);
AstroToList* AstroToList_new(AstroNode* start, AstroNode* stop, AstroNode* stride);
AstroNode* AstroToList_getStart(AstroToList* node);
AstroNode* AstroToList_getStop(AstroToList* node);
AstroNode* AstroToList_getStride(AstroToList* node);
bool AstroToList_compare(AstroToList* first,AstroToList* second);
AstroHeadTail* AstroHeadTail_new(AstroNode* head, AstroNode* tail);
AstroNode* AstroHeadTail_getHead(AstroHeadTail* node);
AstroNode* AstroHeadTail_getTail(AstroHeadTail* node);
void AstroHeadTail_setHead(AstroHeadTail* node, AstroNode* head);
void AstroHeadTail_setTail(AstroHeadTail* node, AstroNode* tail);
bool AstroHeadTail_compare(AstroHeadTail* first, AstroHeadTail* second);
AstroRawToList* AstroRawToList_new(AstroNode* start, AstroNode* stop, AstroNode* stride);
bool AstroRawToList_compare(AstroRawToList* first, AstroRawToList* second);
AstroRawHeadTail* AstroRawHeadTail_new(AstroNode* head, AstroNode* tail);
bool AstroRawHeadTail_compare(AstroRawHeadTail* first, AstroRawHeadTail* second);
AstroSequence* AstroSequence_new(AstroNode* first, AstroNode* second);
AstroNode* AstroSequence_getFirst( AstroSequence* node);
AstroNode* AstroSequence_getSecond( AstroSequence* node);
void AstroSequence_setFirst( AstroSequence* node, AstroNode* first);
void AstroSequence_setSecond( AstroSequence* node, AstroNode* second);
bool AstroSequence_compare(AstroSequence* first,AstroSequence* second);
AstroFunction* AstroFunction_new( AstroList* body_list );
void AstroFunction_setBodyList( AstroFunction* node, AstroList* body_list);
AstroList* AstroFunction_getBodyList( AstroFunction* node );
void AstroFuction_setClosure( AstroFunction* node, void* closure);
void* AstroFunction_getClosure( AstroFunction* node); 
bool AstroFunction_compare(AstroFunction* first,AstroFunction* second);
AstroObject* AstroObject_new( AstroID* struct_id, AstroList* object_memory);
AstroList* AstroObject_getMemory( AstroObject* node);
void AstroObject_setMemory( AstroObject* node, AstroList* object_memory);
AstroID* AstroObject_getID( AstroObject* node);
void AstroObject_setID( AstroObject* node, void* struct_id);
bool AstroObject_compare(AstroObject* first, AstroObject* second);
AstroEval* AstroEval_new( AstroNode* expression);
AstroNode* AstroEval_getExpression( AstroEval* node);
void AstroEval_setExpression( AstroEval* node, AstroNode* expression);
bool AstroEval_compare( AstroEval* first, AstroEval* second);
AstroQuote* AstroQuote_new( AstroNode* expression);
AstroNode* AstroQuote_getExpression( AstroQuote* node);
void AstroQuote_setExpression( AstroQuote* node, AstroNode* expression);
bool AstroQuote_compare( AstroQuote* first, AstroQuote* second);
AstroConstraint* AstroConstraint_new( AstroNode* expression);
AstroNode* AstroConstraint_getExpression( AstroConstraint* node);
void AstroConstraint_setExpression( AstroConstraint* node, AstroNode* expression);
bool AstroConstraint_compare( AstroConstraint* first, AstroConstraint* second );
AstroTypeMatch* AstroTypeMatch_new( AstroNode* expression);
AstroNode* AstroTypeMatch_getExpression( AstroTypeMatch* node);
void AstroTypeMatch_setExpression( AstroTypeMatch* node, AstroNode* expression);
bool AstroTypeMatch_compare( AstroTypeMatch* first, AstroTypeMatch* second);
AstroForeign* AstroForeign_new( void* content );
void* AstroForeign_getContent( AstroForeign* node);
void AstroForeign_setContent( AstroForeign* node, void* content);
bool AstroForeign_compare( AstroForeign* first, AstroForeign* second);
AstroID* AstroID_new(char* name );
char* AstroID_getName(AstroID* node);
void AstroID_setName(AstroID* node, char* name);
bool AstroID_compare( AstroID* first, AstroID* second);
AstroApply* AstroApply_new( AstroNode* function, AstroNode* argument);
AstroNode* AstroApply_getFunction( AstroApply* node);
void AstroApply_setFunction( AstroApply* node, AstroNode* function);
AstroNode* AstroApply_getArgument(AstroApply* node);
void AstroApply_setArgument( AstroApply* node, AstroNode* argument);
bool AstroApply_compare( AstroApply* first, AstroApply* second);
AstroIndex* AstroIndex_new( AstroNode* structure, AstroNode* index_exp);
AstroNode* AstroIndex_getStructure( AstroIndex* node);
void AstroIndex_setStructure( AstroIndex* node, AstroNode* structure);
AstroNode* AstroIndex_getIndex( AstroIndex* node);
void AstroIndex_setIndex( AstroIndex* node, AstroNode* index_exp);
bool AstroIndex_compare( AstroIndex* first, AstroIndex* second);
AstroEscape* AstroEscape_new( void* content);
AstroIs* AstroIs_new(AstroNode* pattern, AstroNode* term);
AstroNode* AstroIs_getPattern(AstroIs* node);
AstroNode* AstroIs_getTerm(AstroIs* node);
void AstroIs_setPattern(AstroIs* node, AstroNode* pattern);
void AstroIs_setTerm(AstroIs* node, AstroNode* term);
bool AstroIs_compare(AstroIs* first, AstroIs* second);
AstroIn* AstroIn_new(AstroNode* expression,AstroNode* expression_list);
AstroNode* AstroIn_getExpression(AstroIn* node);
AstroNode* AstroIn_getExpressionList(AstroIn* node);
void AstroIn_setExpresssion(AstroIn* node, AstroNode* expression);
void AstroIn_setExpressionList(AstroIn* node, AstroNode* expression_list);
bool AstroIn_compare( AstroIn* first, AstroIn* second);
AstroIf* AstroIf_new( AstroNode* cond_exp, AstroNode* then_exp, AstroNode* else_exp);
AstroNode* AstroIf_getCondition( AstroIf* node);
AstroNode* AstroIf_getThen( AstroIf* node);
AstroNode* AstroIf_getElse( AstroIf* node);
void AstroIf_setCondition( AstroIf* node, AstroNode* cond_exp);
void AstroIf_setThen( AstroIf* node, AstroNode* then_exp);
void AstroIf_setElse( AstroIf* node, AstroNode* else_exp);
AstroNamedPattern* AstroNamedPattern_new( AstroID* name, AstroNode* pattern);
AstroID* AstroNamedPattern_getName( AstroNamedPattern* node);
AstroNode* AstroNamedPattern_getPattern( AstroNamedPattern* node);
void AstroNamedPattern_setName(AstroNamedPattern* node, AstroID* name);
void AstroNamedPattern_setPattern(AstroNamedPattern* node, AstroNode* pattern);
AstroDeref* AstroDeref_new( AstroNode* expression );
AstroNode* AstroDeref_getExpression( AstroDeref* node);
void AstroDeref_setExpression( AstroDeref* node, AstroNode* expression);
#endif