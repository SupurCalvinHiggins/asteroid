#include "astronode.h"
#include "assert.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "astrogc.h"
/******************************************************************************/
AstroNode* AstroNode_new(char type){
    assert(type);

    AstroNode* new = AstroMem_new(sizeof(struct astronode_s));
    assert(new);

    new->type = type;
    return new;
}
/******************************************************************************/
char AstroNode_peek(AstroNode* node){
    return node->type;
}
/******************************************************************************/
void AstroNode_setType(AstroNode* node, char newType){
    node->type = newType;
}
/******************************************************************************/
bool AstroNode_compare(AstroNode* first, AstroNode* second){
    assert(first);
    assert(second);
    char type1,type2;

    type1 = AstroNode_peek(first);
    type2 = AstroNode_peek(second);

    if (type1 != type2){
        return false;
    }

    switch(type1){
        case 'i':                                       // INTEGER
            return AstroInteger_compare((AstroInteger*)first,(AstroInteger*)second);
        case 'r':                                       // REAL
            return AstroReal_compare((AstroReal*)first,(AstroReal*)second);
        case 'b':                                       // BOOLEAN
            return AstroBoolean_compare((AstroBoolean*)first,(AstroBoolean*)second);
        case 's':                                       // STRING
            return AstroString_compare((AstroString*)first,(AstroString*)second);
        case 'N':                                       // NONE
            return AstroNone_compare((AstroNone*)first,(AstroNone*)second);
        case 'n':                                       // NIL
            return AstroNil_compare((AstroNil*)first,(AstroNil*)second);
        case 'L':                                       // LIST
            return AstroList_compare((AstroList*)first,(AstroList*)second);
        case 't':                                       // TUPLE
            return AstroTuple_compare((AstroTuple*)first,(AstroTuple*)second); 
        case 'T':                                      // TO LIST
            return AstroToList_compare((AstroToList*)first,(AstroToList*)second); 
        case 'h':                                      // HEAD TAIL
            return AstroHeadTail_compare((AstroHeadTail*)first,(AstroHeadTail*)second); 
        case 'R':                                      // RAW TO LIST
            return AstroRawToList_compare((AstroRawToList*)first,(AstroRawToList*)second); 
        case 'H':                                      // RAW HEAD TAIL
            return AstroRawHeadTail_compare((AstroRawHeadTail*)first,(AstroRawHeadTail*)second);
        case 'S':                                      // SEQUENCE
            return AstroSequence_compare((AstroSequence*)first,(AstroSequence*)second);
        case 'f':                                      // FUNCTION
            return AstroFunction_compare((AstroFunction*)first,(AstroFunction*)second);
        case 'o':                                      // OBJECT
            return AstroObject_compare((AstroObject*)first,(AstroObject*)second);
        case 'e':                                      // EVAL
            return AstroEval_compare((AstroEval*)first,(AstroEval*)second);
        case 'q':                                      // QUOTE
            return AstroQuote_compare((AstroQuote*)first,(AstroQuote*)second);
        case 'c':                                      // CONSTRAINT 
        case 'C':                                      // TYPEMATCH
            return AstroConstraint_compare((AstroConstraint*)first,(AstroConstraint*)second);
        case 'F':                                      // FOREIGN
            return AstroForeign_compare((AstroForeign*)first,(AstroForeign*)second);
        case 'I':                                      // ID
            return AstroID_compare((AstroID*)first,(AstroID*)second);
        case 'a':                                      // APPLY
            return AstroApply_compare((AstroApply*)first,(AstroApply*)second);
        case 'x':                                     // INDEX
            return AstroIndex_compare((AstroIndex*)first,(AstroIndex*)second);
        case 'E':                                      // ESCAPE
            // TODO escape compare?
            return false;
            //return AstroEscape_compare((AstroEscape*)first,(AstroEscape*)second);
        case 'X':                                      // IS
            return AstroIs_compare((AstroIs*)first,(AstroIs*)second);
        case 'A':                                      // IN
            return AstroIn_compare((AstroIn*)first,(AstroIn*)second);
        default:                                       // UNKNOWN
            fprintf(stdout,"ERROR: walk function: Node type %c is unrecognized.\n",type1);
            // TODO error unknown node type
            return NULL;

  }
}
/******************************************************************************/
AstroInteger* AstroInteger_new(long value){
    //assert(value); can be 0

    AstroInteger* new = AstroMem_new(sizeof(struct astrointeger_s));
    assert(new);
    
    AstroNode_setType( (AstroNode*)new, 'i');
    new->value = value;
    return new;
}
/******************************************************************************/
void AstroInteger_setValue(AstroInteger* node, long value){
    node->value = value;
}
/******************************************************************************/
long AstroInteger_getValue(AstroInteger* node){
    return node->value;
}
/******************************************************************************/
bool AstroInteger_compare(AstroInteger* first,AstroInteger* second){
    assert(first);
    assert(second);
    unsigned long num1,num2;

    num1 = AstroInteger_getValue(first);
    num2 = AstroInteger_getValue(second);

    if (num1 == num2){
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroReal* AstroReal_new(double value){
    //assert(value); can be 0

    AstroReal* new = AstroMem_new(sizeof(struct astroreal_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'r');

    new->value = value;
    return new;
}
/******************************************************************************/
void AstroReal_setValue(AstroReal* node, double value){
    //assert(value); can be 0
    assert(node);
    node->value = value;
}
/******************************************************************************/
double AstroReal_getValue(AstroReal* node){
    return node->value;
}
/******************************************************************************/
bool AstroReal_compare(AstroReal* first,AstroReal* second){
    assert(first);
    assert(second);
    double num1,num2;

    num1 = AstroReal_getValue(first);
    num2 = AstroReal_getValue(second);

    if (num1 == num2){
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroBoolean* AstroBoolean_new(bool value){
    //assert(value); can be false

    AstroBoolean* new = AstroMem_new(sizeof(struct astroboolean_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'b');
    new->value = value;
    return new;
}
/******************************************************************************/
void AstroBoolean_setValue(AstroBoolean* node, bool value){
    //assert(value); can be false
    assert(node);
    node->value = value;
}
/******************************************************************************/
bool AstroBoolean_getValue(AstroBoolean* node){
    return node->value;
}
/******************************************************************************/
bool AstroBoolean_compare(AstroBoolean* first,AstroBoolean* second){
    assert(first);
    assert(second);
    bool val1,val2;

    val1 = AstroBoolean_getValue(first);
    val2 = AstroBoolean_getValue(second);

    if (val1 == val2){
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroString* AstroString_new(char* value){
    assert(value);

    AstroString* new = AstroMem_new(sizeof(struct astrostring_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 's');
    new->value = value;
    return new;
}
/******************************************************************************/
void AstroString_setValue(AstroString* node, char* value){
    assert(value);
    assert(node);
    node->value = value;
}
/******************************************************************************/
char* AstroString_getValue(AstroString* node){
    assert(node);
    return node->value;
}
/******************************************************************************/
bool AstroString_compare(AstroString* first,AstroString* second){
    assert(first);
    assert(second);
    char* str1,*str2;

    str1 = AstroString_getValue(first);
    str2 = AstroString_getValue(second);

    if (strcmp(str1,str2) == 0){
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroLineInfo* AstroLineInfo_new(char* module_name, unsigned long line_number){
    assert(module_name);
    assert(line_number);

    AstroLineInfo* new = AstroMem_new(sizeof(struct astrolineinfo_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'l');
    new->module_name = module_name;
    new->line_number = line_number;
    return new;
}
/******************************************************************************/
void AstroLineInfo_setModule(AstroLineInfo* node, char* module_name){
    assert(module_name);
    assert(node);
    node->module_name = module_name;
}
/******************************************************************************/
void AstroLineInfo_setLine(AstroLineInfo* node, unsigned long line_number){
    assert(line_number); // cant be zero right?
    assert(node);
    node->line_number = line_number;
}
/******************************************************************************/
char* AstroLineInfo_getModule(AstroLineInfo* node){
    assert(node);
    return node->module_name;
}
/******************************************************************************/
unsigned long AstroLineInfo_getLine(AstroLineInfo* node){
    assert(node);
    return node->line_number;
}
/******************************************************************************/
bool AstroLineInfo_compare(AstroLineInfo* first, AstroLineInfo* second){
    assert(first);
    assert(second);
    char* name1,*name2;
    unsigned long num1,num2;

    name1 = AstroLineInfo_getModule(first);
    name2 = AstroLineInfo_getModule(second);
    num1 = AstroLineInfo_getLine(first);
    num2 = AstroLineInfo_getLine(second);

    if ((strcmp(name1,name2) == 0) && (num1 == num2)){
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroNone* AstroNone_new(){
    AstroNone* new = AstroMem_new(sizeof(struct astrolineinfo_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'N');
    return new;
}
/******************************************************************************/
bool AstroNone_compare(AstroNone* first,AstroNone* second){
    assert(first);
    assert(second);
    return true;
}
/******************************************************************************/
AstroNil* AstroNil_new(){
    AstroNil* new = AstroMem_new(sizeof(struct astronil_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'n');
    return new;
}
/******************************************************************************/
bool AstroNil_compare(AstroNil* first,AstroNil* second){
    assert(first);
    assert(second);
    return true;
}
/******************************************************************************/
AstroList* AstroList_new(unsigned long length, AstroNode** contents){
    assert(length);

    AstroList* new = AstroMem_new(sizeof(struct astrolist_s));
    assert(new);

    new->length = length;
    new->contents = contents;
    AstroNode_setType((AstroNode*)new, 'L');
    return new;
}
/******************************************************************************/
unsigned long AstroList_getLength(AstroList* node){
    assert(node);
    return node->length;
}
/******************************************************************************/
void AstroList_setLength(AstroList* node,unsigned long length){
    assert(node);
    node->length = length;
}
/******************************************************************************/
AstroNode** AstroList_getContents(AstroList* node){
    assert(node);
    return node->contents;
}
/******************************************************************************/
void AstroList_setContents(AstroList* node, AstroNode** contents){
    assert(node);
    assert(contents);
    node->contents = contents;
}
/******************************************************************************/
AstroNode* AstroList_getElement(AstroList* node, unsigned long index){
    assert(node);
    return node->contents[index];
}
/******************************************************************************/
void AstroList_setElement(AstroList* node, unsigned long index, AstroNode* element){
    assert(node);
    node->contents[index] = (AstroNode*)element;
}
/******************************************************************************/
bool AstroList_compare(AstroList* first, AstroList* second){
    assert(first);
    assert(second);
    unsigned long len1,len2,i;

    len1 = AstroList_getLength(first);
    len2 = AstroList_getLength(second);

    if (len1 != len2){
        return false;
    }

    for (i=0;i < len1;++i){
        if (! AstroNode_compare( AstroList_getElement(first,i),AstroList_getElement(second,i))){
            return false;
        }
    }
    return true;
}
/******************************************************************************/
AstroTuple* AstroTuple_new(unsigned long length, AstroNode** contents){
    assert(length);

    AstroTuple* new = AstroMem_new(sizeof(struct astrolist_s));
    assert(new);

    new->length = length;
    new->contents = contents;
    AstroNode_setType((AstroNode*)new, 't');
    return new;
}
/******************************************************************************/
unsigned long AstroTuple_getLength(AstroTuple* node){
    assert(node);
    return node->length;
}
/******************************************************************************/
void AstroTuple_setLength(AstroTuple* node, unsigned long length){
    assert(node);
    node->length = length;
}
/******************************************************************************/
AstroNode** AstroTuple_getContents(AstroTuple* node){
    assert(node);
    return node->contents;
}
/******************************************************************************/
void AstroTuple_setContents(AstroTuple* node, AstroNode** contents){
    assert(node);
    //assert(contents);
    node->contents = contents;
}
/******************************************************************************/
AstroNode* AstroTuple_getElement(AstroTuple* node, unsigned long index){
    assert(node);
    return node->contents[index];
}
/******************************************************************************/
void AstroTuple_setElement(AstroTuple* node, unsigned long index, AstroNode* element){
    assert(node);
    node->contents[index] = element;
}
/******************************************************************************/
bool AstroTuple_compare(AstroTuple* first,AstroTuple* second){
    assert(first);
    assert(second);
    unsigned long len1,len2,i;

    len1 = AstroTuple_getLength(first);
    len2 = AstroTuple_getLength(second);

    if (len1 != len2){
        return false;
    }

    for (i=0;i < len1;++i){
        if (! AstroNode_compare(AstroTuple_getElement(first,i), AstroTuple_getElement(second,i))){
            return false;
        }
    }
    return true;
}
/******************************************************************************/
AstroToList* AstroToList_new(AstroNode* start, AstroNode* stop, AstroNode* stride){
    assert(start);
    assert(stop);
    assert(stride);

    AstroToList* new = AstroMem_new(sizeof(struct astrotolist_s));
    assert(new);

    AstroNode_setType((AstroNode*)new, 'T');
    new->start = start;
    new->stop = stop;
    new->stride = stride;
    return new;
}
/******************************************************************************/
AstroNode* AstroToList_getStart(AstroToList* node){
    assert(node);
    return node->start;
}
/******************************************************************************/
AstroNode* AstroToList_getStop(AstroToList* node){
    assert(node);
    return node->stop;
}
/******************************************************************************/
AstroNode* AstroToList_getStride(AstroToList* node){
    assert(node);
    return node->stride;
}
/******************************************************************************/
bool AstroToList_compare(AstroToList* first,AstroToList* second){
    assert(first);
    assert(second);
    unsigned long num1,num2,num3,num4,num5,num6;

    // TODO Review
    num1 = AstroInteger_getValue( (AstroInteger*)AstroToList_getStart(first));
    num2 = AstroInteger_getValue( (AstroInteger*)AstroToList_getStart(second)); 

    num3 = AstroInteger_getValue( (AstroInteger*)AstroToList_getStop(first));
    num4 = AstroInteger_getValue( (AstroInteger*)AstroToList_getStop(second));

    num5 = AstroInteger_getValue( (AstroInteger*)AstroToList_getStride(first));
    num6 = AstroInteger_getValue( (AstroInteger*)AstroToList_getStride(second));

    if ((num1 == num2)&&(num3 == num4)&&(num5 == num6)){
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroHeadTail* AstroHeadTail_new(AstroNode* head, AstroNode* tail){
    
    AstroHeadTail* new = AstroMem_new(sizeof(struct astroheadtail_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'h');
    new->head = head;
    new->tail = tail;

    return new;
}
/******************************************************************************/
AstroNode* AstroHeadTail_getHead(AstroHeadTail* node){
    assert(node);
    return node->head;
}
/******************************************************************************/
AstroNode* AstroHeadTail_getTail(AstroHeadTail* node){
    assert(node);
    return node->tail;
}
/******************************************************************************/
void AstroHeadTail_setHead(AstroHeadTail* node, AstroNode* head){
    assert(node);
    node->head = head;
}
/******************************************************************************/
void AstroHeadTail_setTail(AstroHeadTail* node, AstroNode* tail){
    assert(node);
    node->tail = tail;
}
/******************************************************************************/
bool AstroHeadTail_compare(AstroHeadTail* first, AstroHeadTail* second){
    assert(first);
    assert(second);

    if ( AstroNode_compare( AstroHeadTail_getHead(first),AstroHeadTail_getHead(second)) &&
         AstroNode_compare( AstroHeadTail_getTail(first),AstroHeadTail_getTail(second))  ){

        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroRawToList* AstroRawToList_new(AstroNode* start, AstroNode* stop, AstroNode* stride){
    assert(start);
    assert(stop);
    assert(stride);

    AstroRawToList* new = AstroMem_new(sizeof(struct astrotolist_s));
    assert(new);

    AstroNode_setType((AstroNode*)new, 'R');
    new->start = start;
    new->stop = stop;
    new->stride = stride;
    return new;
}
/******************************************************************************/
bool AstroRawToList_compare(AstroRawToList* first, AstroRawToList* second){
    assert(first);
    assert(second);
    unsigned long num1,num2,num3,num4,num5,num6;

    // TODO Review
    num1 = AstroInteger_getValue( (AstroInteger*)AstroToList_getStart( (AstroToList*)first));
    num2 = AstroInteger_getValue( (AstroInteger*)AstroToList_getStart( (AstroToList*)second)); 

    num3 = AstroInteger_getValue( (AstroInteger*)AstroToList_getStop( (AstroToList*)first));
    num4 = AstroInteger_getValue( (AstroInteger*)AstroToList_getStop( (AstroToList*)second));

    num5 = AstroInteger_getValue( (AstroInteger*)AstroToList_getStride( (AstroToList*)first));
    num6 = AstroInteger_getValue( (AstroInteger*)AstroToList_getStride( (AstroToList*)second));

    if ((num1 == num2)&&(num3 == num4)&&(num5 == num6)){
        return true;
    } else {
        return false;
    }

}
/******************************************************************************/
AstroRawHeadTail* AstroRawHeadTail_new(AstroNode* head, AstroNode* tail){
    
    AstroRawHeadTail* new = AstroMem_new(sizeof(struct astrorawheadtail_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'H');
    new->head = head;
    new->tail = tail;

    return new;
}
/******************************************************************************/
bool AstroRawHeadTail_compare(AstroRawHeadTail* first, AstroRawHeadTail* second){
    assert(first);
    assert(second);

    if ( AstroNode_compare( AstroHeadTail_getHead((AstroHeadTail*)first),AstroHeadTail_getHead((AstroHeadTail*)second)) &&
         AstroNode_compare( AstroHeadTail_getTail((AstroHeadTail*)first),AstroHeadTail_getTail((AstroHeadTail*)second))  ){

        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroSequence* AstroSequence_new(AstroNode* first, AstroNode* second){

    AstroSequence* new = AstroMem_new(sizeof(struct astrosequence_s ));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'S');
    new->first = first;
    new->second = second;

    return new;
}
/******************************************************************************/
AstroNode* AstroSequence_getFirst( AstroSequence* node){
    assert(node);
    return node->first;
}
/******************************************************************************/
AstroNode* AstroSequence_getSecond( AstroSequence* node){
    assert(node);
    return node->second;
}
/******************************************************************************/
void AstroSequence_setFirst( AstroSequence* node, AstroNode* first){
    assert(node);
    node->first = first;
}
/******************************************************************************/
void AstroSequence_setSecond( AstroSequence* node, AstroNode* second){
    assert(node);
    node->second = second;
}
/******************************************************************************/
bool AstroSequence_compare(AstroSequence* first,AstroSequence* second){
    assert(first);
    assert(second);

    if ( AstroNode_compare( AstroSequence_getFirst(first),AstroSequence_getFirst(second)) &&
         AstroNode_compare( AstroSequence_getSecond(first),AstroSequence_getSecond(second))  ){

        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroFunction* AstroFunction_new( AstroList* body_list ){

    AstroFunction* new = AstroMem_new(sizeof(struct astrofunction_s ));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'f');
    new->body_list = body_list;
    new->closure = NULL;

    return new;
}
/******************************************************************************/
void AstroFunction_setBodyList( AstroFunction* node, AstroList* body_list){
    assert(node);
    node->body_list = body_list;
}
/******************************************************************************/
AstroList* AstroFunction_getBodyList( AstroFunction* node ){
    assert(node);
    return node->body_list;
}
/******************************************************************************/
void AstroFuction_setClosure( AstroFunction* node, void* closure){
    assert(node);
    node->closure = closure;
}
/******************************************************************************/
void* AstroFunction_getClosure( AstroFunction* node){
    assert(node);
    return node->closure;
}
/******************************************************************************/
bool AstroFunction_compare(AstroFunction* first,AstroFunction* second){
    assert(first);
    assert(second);
    bool comp;

    // TODO review
    comp = AstroList_compare( AstroFunction_getBodyList(first),AstroFunction_getBodyList(second));

    if (comp){
        return true;
    } else {
        return false;
    }

}
/******************************************************************************/
AstroObject* AstroObject_new( AstroID* struct_id, AstroList* object_memory){

    AstroObject* new = AstroMem_new(sizeof(struct astroobject_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'o');
    new->struct_id = struct_id;
    new->object_memory = object_memory;

    return new;
}
/******************************************************************************/
AstroList* AstroObject_getMemory( AstroObject* node){
    assert(node);
    return node->object_memory;
}
/******************************************************************************/
void AstroObject_setMemory( AstroObject* node, AstroList* object_memory){
    assert(node);
    node->object_memory = object_memory;
}
/******************************************************************************/
AstroID* AstroObject_getID( AstroObject* node){
    assert(node);
    return node->struct_id;
}
/******************************************************************************/
void AstroObject_setID( AstroObject* node, void* struct_id){
    assert(node);
    node->struct_id = struct_id;
}
/******************************************************************************/
bool AstroObject_compare(AstroObject* first, AstroObject* second){
    assert(first);
    assert(second);
    bool c1,c2;

    c1 = AstroList_compare( AstroObject_getMemory(first), AstroObject_getMemory(second));
    c2 = AstroID_compare( AstroObject_getID(first), AstroObject_getID(second));

    if (c1 && c2){
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroEval* AstroEval_new( AstroNode* expression){

    AstroEval* new = AstroMem_new(sizeof( struct astroeval_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'e');
    new->expression = expression;

    return new;
}
/******************************************************************************/
AstroNode* AstroEval_getExpression( AstroEval* node){
    assert(node);
    return node->expression;
}
/******************************************************************************/
void AstroEval_setExpression( AstroEval* node, AstroNode* expression){
    assert(node);
    node->expression = expression;
}
/******************************************************************************/
bool AstroEval_compare( AstroEval* first, AstroEval* second){
    assert(first);
    assert(second);

    if ( AstroNode_compare(AstroEval_getExpression(first),AstroEval_getExpression(second))){
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroQuote* AstroQuote_new( AstroNode* expression){

    AstroQuote* new = AstroMem_new(sizeof(struct astroquote_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'q');
    new->expression = expression;

    return new;
}
/******************************************************************************/
AstroNode* AstroQuote_getExpression( AstroQuote* node){
    assert(node);
    return node->expression;
}
/******************************************************************************/
void AstroQuote_setExpression( AstroQuote* node, AstroNode* expression){
    assert(node);
    node->expression = expression;
}
/******************************************************************************/
bool AstroQuote_compare( AstroQuote* first, AstroQuote* second){
    assert(first);
    assert(second);

    if ( AstroNode_compare(AstroQuote_getExpression(first),AstroQuote_getExpression(second))){
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroConstraint* AstroConstraint_new( AstroNode* expression){

    AstroConstraint* new = AstroMem_new(sizeof(struct astroconstraint_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'c');
    new->expression = expression;

    return new;
}
/******************************************************************************/
AstroNode* AstroConstraint_getExpression( AstroConstraint* node){
    assert(node);
    return node->expression;
}
/******************************************************************************/
void AstroConstraint_setExpression( AstroConstraint* node, AstroNode* expression){
    assert(node);
    node->expression = expression;
}
/******************************************************************************/
bool AstroConstraint_compare( AstroConstraint* first, AstroConstraint* second ){
    assert(first);
    assert(second);

    if ( AstroNode_compare(AstroConstraint_getExpression(first),AstroConstraint_getExpression(second))){
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroTypeMatch* AstroTypeMatch_new( AstroNode* expression){

    AstroTypeMatch* new = AstroMem_new(sizeof(struct astrotypematch_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'C');
    new->expression = expression;

    return new;
}
/******************************************************************************/
AstroNode* AstroTypeMatch_getExpression( AstroTypeMatch* node){
    assert(node);
    return node->expression;
}
/******************************************************************************/
void AstroTypeMatch_setExpression( AstroTypeMatch* node, AstroNode* expression){
    assert(node);
    node->expression = expression;
}
/******************************************************************************/
bool AstroTypeMatch_compare( AstroTypeMatch* first, AstroTypeMatch* second){
    assert(first);
    assert(second);

    if ( AstroNode_compare(AstroTypeMatch_getExpression(first),AstroTypeMatch_getExpression(second))){
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroForeign* AstroForeign_new( void* content ){

    AstroForeign* new = AstroMem_new(sizeof(struct astroforeign_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'F');
    new->content = content;

    return new;
}
/******************************************************************************/
void* AstroForeign_getContent( AstroForeign* node){
    assert(node);
    return node->content;
}
/******************************************************************************/
void AstroForeign_setContent( AstroForeign* node, void* content){
    assert(node);
    node->content = content;
}
/******************************************************************************/
bool AstroForeign_compare( AstroForeign* first, AstroForeign* second){
    assert(first);
    assert(second);
    void *c1,*c2;
    
    c1 = AstroForeign_getContent(first);
    c2 = AstroForeign_getContent(second);

    if ((long)c1 == (long)c2){
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroID* AstroID_new(char* name ){

    AstroID* new = AstroMem_new(sizeof(struct astroid_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'I');
    new->name = name;

    return new;
}
/******************************************************************************/
char* AstroID_getName(AstroID* node){
    assert(node);
    return node->name;
}
/******************************************************************************/
void AstroID_setName(AstroID* node, char* name){
    assert(node);
    node->name = name;
}
/******************************************************************************/
bool AstroID_compare( AstroID* first, AstroID* second){
    assert(first);
    assert(second);
    char *str1,*str2;

    str1 = AstroID_getName(first);
    str2 = AstroID_getName(second);

    if (strcmp(str1,str2) == 0){
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroApply* AstroApply_new( AstroNode* function, AstroNode* argument){

    AstroApply* new = AstroMem_new(sizeof(struct astroapply_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'a');
    new->function = function;
    new->argument = argument;

    return new;
}
/******************************************************************************/
AstroNode* AstroApply_getFunction( AstroApply* node){
    assert(node);
    return node->function;
}
/******************************************************************************/
void AstroApply_setFunction( AstroApply* node, AstroNode* function){
    assert(node);
    node->function = function;
}
/******************************************************************************/
AstroNode* AstroApply_getArgument(AstroApply* node){
    assert(node);
    return node->argument;
}
/******************************************************************************/
void AstroApply_setArgument( AstroApply* node, AstroNode* argument){
    assert(node);
    node->argument = argument;
}
/******************************************************************************/
bool AstroApply_compare( AstroApply* first, AstroApply* second){
    assert(first);
    assert(second);

    if (AstroNode_compare( AstroApply_getArgument(first), AstroApply_getArgument(second))  &&
        AstroNode_compare( AstroApply_getFunction(first), AstroApply_getFunction(second))   ){

        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroIndex* AstroIndexNew( AstroNode* structure, AstroNode* index_exp){

    AstroIndex* new = AstroMem_new(sizeof(struct astroindex_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'x');
    new->structure = structure;
    new->index_exp= index_exp;

    return new;
}
/******************************************************************************/
AstroNode* AstroIndex_getStructure( AstroIndex* node){
    assert(node);
    return node->structure;
}
/******************************************************************************/
void AstroIndex_setStructure( AstroIndex* node, AstroNode* structure){
    assert(node);
    node->structure = structure;
}
/******************************************************************************/
AstroNode* AstroIndex_getIndex( AstroIndex* node){
    assert(node);
    return node->index_exp;
}
/******************************************************************************/
void AstroIndex_setIndex( AstroIndex* node, AstroNode* index_exp){
    assert(node);
    node->index_exp = index_exp;
}
/******************************************************************************/
bool AstroIndex_compare( AstroIndex* first, AstroIndex* second){
    assert(first);
    assert(second);

    if (AstroNode_compare( AstroIndex_getStructure(first), AstroIndex_getStructure(second))  &&
        AstroNode_compare( AstroIndex_getIndex(first), AstroIndex_getIndex(second))   ){
            
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroEscape* AstroEscape_new( void* content){
    
    AstroEscape* new = AstroMem_new( sizeof( struct astroescape_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'E');
    new->content = content;

    return new;
}
/******************************************************************************/
AstroIs* AstroIs_new(AstroNode* pattern, AstroNode* term){

    AstroIs* new = AstroMem_new(sizeof(struct astrois_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'X');
    new->pattern = pattern;
    new->term = term;

    return new;
}
/******************************************************************************/
AstroNode* AstroIs_getPattern(AstroIs* node){
    assert(node);
    return node->pattern;
}
/******************************************************************************/
AstroNode* AstroIs_getTerm(AstroIs* node){
    assert(node);
    return node->term;
}
/******************************************************************************/
void AstroIs_setPattern(AstroIs* node, AstroNode* pattern){
    assert(node);
    node->pattern = pattern;
}
/******************************************************************************/
void AstroIs_setTerm(AstroIs* node, AstroNode* term){
    assert(node);
    node->term = term;
}
/******************************************************************************/
bool AstroIs_compare(AstroIs* first, AstroIs* second){
    assert(first);
    assert(second);

    if (AstroNode_compare( AstroIs_getPattern(first), AstroIs_getPattern(second))  &&
        AstroNode_compare( AstroIs_getTerm(first), AstroIs_getTerm(second))   ){
            
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroIn* AstroIn_new(AstroNode* expression,AstroNode* expression_list){

    AstroIn* new = AstroMem_new(sizeof(struct astroin_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'A');
    new->expression = expression;
    new->expression_list = expression_list;

    return new;
}
/******************************************************************************/
AstroNode* AstroIn_getExpression(AstroIn* node){
    assert(node);
    return node->expression;
}
/******************************************************************************/
AstroNode* AstroIn_getExpressionList(AstroIn* node){
    assert(node);
    return node->expression_list;
}
/******************************************************************************/
void AstroIn_setExpresssion(AstroIn* node, AstroNode* expression){
    assert(node);
    node->expression = expression;
}
/******************************************************************************/
void AstroIn_setExpressionList(AstroIn* node, AstroNode* expression_list){
    assert(node);
    node->expression_list = expression_list;
}
/******************************************************************************/
bool AstroIn_compare( AstroIn* first, AstroIn* second){
    assert(first);
    assert(second);

    if (AstroNode_compare( AstroIn_getExpression(first), AstroIn_getExpression(second))  &&
        AstroNode_compare( AstroIn_getExpressionList(first), AstroIn_getExpressionList(second))   ){
            
        return true;
    } else {
        return false;
    }
}
/******************************************************************************/
AstroIf* AstroIf_new( AstroNode* cond_exp, AstroNode* then_exp, AstroNode* else_exp){
    
    AstroIf* new = AstroMem_new(sizeof( struct astroif_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'w');
    new->cond_exp = cond_exp;
    new->then_exp = then_exp;
    new->else_exp= else_exp;

    return new;    
}
/******************************************************************************/
AstroNode* AstroIf_getCondition( AstroIf* node){
    assert(node);
    return node->cond_exp;
}
/******************************************************************************/
AstroNode* AstroIf_getThen( AstroIf* node){
    assert(node);
    return node->then_exp;
}
/******************************************************************************/
AstroNode* AstroIf_getElse( AstroIf* node){
    assert(node);
    return node->else_exp;
}
/******************************************************************************/
void AstroIf_setCondition( AstroIf* node, AstroNode* cond_exp){
    assert(node);
    node->cond_exp = cond_exp;
}
/******************************************************************************/
void AstroIf_setThen( AstroIf* node, AstroNode* then_exp){
    assert(node);
    node->then_exp = then_exp;
}
/******************************************************************************/
void AstroIf_setElse( AstroIf* node, AstroNode* else_exp){
    assert(node);
    node->else_exp = else_exp;
}
/******************************************************************************/
AstroNamedPattern* AstroNamedPattern_new( AstroID* name, AstroNode* pattern){

    AstroNamedPattern* new = AstroMem_new(sizeof(struct astronamedpattern_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'W');
    new->name = name;
    new->pattern = pattern;

    return new;
}
/******************************************************************************/
AstroID* AstroNamedPattern_getName( AstroNamedPattern* node){
    assert(node);
    return node->name;
}
/******************************************************************************/
AstroNode* AstroNamedPattern_getPattern( AstroNamedPattern* node){
    assert(node);
    return node->pattern;
}
/******************************************************************************/
void AstroNamedPattern_setName(AstroNamedPattern* node, AstroID* name){
    assert(node);
    node->name = name;
}
/******************************************************************************/
void AstroNamedPattern_setPattern(AstroNamedPattern* node, AstroNode* pattern){
    assert(node);
    node->pattern = pattern;
}
/******************************************************************************/
AstroDeref* AstroDeref_new( AstroNode* expression ){

    AstroDeref* new = AstroMem_new(sizeof(struct astroderef_s));
    assert(new);

    AstroNode_setType( (AstroNode*)new, 'd');
    new->expression = expression;

    return new;
}
/******************************************************************************/
AstroNode* AstroDeref_getExpression( AstroDeref* node){
    assert(node);
    return node->expression;
}
/******************************************************************************/
void AstroDeref_setExpression( AstroDeref* node, AstroNode* expression){
    assert(node);
    node->expression = expression;
}
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/