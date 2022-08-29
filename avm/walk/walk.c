#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "astronode.h"
#include "state.h"
#include "astrogc.h"

bool map2boolean( AstroNode* node);

AstroList* list_exp(AstroList* node, State* state);
AstroTuple* tuple_exp(AstroTuple* node, State* state);
AstroList* to_list_exp(AstroToList* node, State* state);  
AstroList* head_tail_exp(AstroHeadTail* node, State* state);
AstroSequence* sequence_exp(AstroSequence* node, State* state);
AstroFunction* function_exp(AstroFunction* node, State* state);
AstroNode* eval_exp( AstroEval* node, State* state);
AstroNode* quote_exp(AstroQuote* node, State* state);
AstroNode* constraint_exp(AstroConstraint* node, State* state); 
AstroNode* ID_exp(AstroID* node, State* state);
AstroNode* apply_exp(AstroApply* node, State* state);
AstroNode* index_exp(AstroIndex* node, State* state);
AstroNode* escape_exp(AstroEscape* node, State* state);
AstroNode* is_exp(AstroIs* node, State* state);
AstroBoolean* in_exp(AstroIn* node, State* state);
AstroNode* if_exp(AstroIf* node, State* state);
AstroNode* named_pattern_exp(AstroNamedPattern* node, State* state);
AstroNode* deref_exp(AstroDeref* node, State* state);

/******************************************************************************/
/*************************************   WALK   *******************************/
/******************************************************************************/
AstroNode* walk(AstroNode* node, State* state){
  assert(node);

  char type = AstroNode_peek(node);
  
  switch(type){
    case 'i':                                       // INTEGER
      printf("integer\n");
      return node;
    case 'r':                                       // REAL
      printf("real\n");
      return node;
    case 'b':                                       // BOOLEAN
      printf("boolean\n");
      return node;
    case 's':                                       // STRING
      printf("string\n");
      return node;
    case 'N':                                       // NONE
      printf("None\n");
      return node;
    case 'n':                                       // NIL
      printf("Nil\n");
      return node;
    case 'L':                                       // LIST
      printf("List\n");
      return (AstroNode*)list_exp( (AstroList*) node, state);
    case 't':                                       // TUPLE
      printf("tuple\n");
      return (AstroNode*)tuple_exp( (AstroTuple*) node, state);
    case 'T':                                      // TO LIST
      printf("ToList\n");
      return (AstroNode*)to_list_exp( (AstroToList*) node, state);
    case 'h':                                      // HEAD TAIL
      printf("Head-Tail\n");
      return (AstroNode*)head_tail_exp( (AstroHeadTail*) node, state);
    case 'R':                                      // RAW TO LIST
      printf("Raw To List\n");
      return (AstroNode*)to_list_exp( (AstroToList*) node, state);
    case 'H':                                      // RAW HEAD TAIL
      printf("Raw Head Tail\n");
      return (AstroNode*)head_tail_exp( (AstroHeadTail*) node, state);
    case 'S':                                      // SEQUENCE
      printf("Sequence\n");
      return (AstroNode*)sequence_exp( (AstroSequence*) node, state);
    case 'f':                                      // FUNCTION
      printf("Function\n");
      return (AstroNode*)function_exp( (AstroFunction*) node, state);
    case 'o':                                      // OBJECT
      printf("Object\n");
      return node;
    case 'e':                                      // EVAL
      printf("Eval\n");
      return (AstroNode*)eval_exp( (AstroEval*) node, state);
    case 'q':                                      // QUOTE
      printf("Quote\n");
      return (AstroNode*)quote_exp( (AstroQuote*) node, state);
    case 'c':                                      // CONSTRAINT 
      printf("Constraint exp\n");
      return (AstroNode*)constraint_exp( (AstroConstraint*) node, state);
    case 'C':                                      // TYPEMATCH
      printf("Type Match exp\n"); 
      return (AstroNode*)constraint_exp( (AstroConstraint*) node, state); 
    case 'F':                                      // FOREIGN
      printf("Foreign\n");
      return node;
    case 'I':                                      // ID
      printf("ID\n");
      return (AstroNode*)ID_exp( (AstroID*) node, state);
    case 'a':                                      // APPLY
      printf("Apply\n");
      return (AstroNode*)apply_exp( (AstroApply*) node, state);
    case 'x':                                     // INDEX
      printf("index\n");
      return (AstroNode*)index_exp( (AstroIndex*) node, state);
    case 'E':                                      // ESCAPE
      printf("Escape\n");
      return (AstroNode*)escape_exp( (AstroEscape*) node, state);
    case 'X':                                      // IS
      printf("Is\n");
      return (AstroNode*)is_exp( (AstroIs*) node, state);
    case 'A':                                      // IN
      printf("In\n");
      return (AstroNode*)in_exp( (AstroIn*) node, state);
    case 'w':                                      // IF
      printf("If\n");
      return (AstroNode*)if_exp( (AstroIf*) node, state);  
    case 'W':                                      // NAMED-PATTERN
      printf("Named-pattern\n");
      return (AstroNode*)named_pattern_exp( (AstroNamedPattern*) node, state);  
    case 'd':                                      // DEREF
      printf("Deref\n");
      return (AstroNode*)deref_exp( (AstroDeref*) node, state);          
    default:                                       // UNKNOWN
      fprintf(stdout,"ERROR: walk function: Node type %c is unrecognized.\n",type);
      // TODO error unknown node type
      return NULL;
  }
}
/******************************************************************************/
/******************************************************************************/
AstroList* list_exp(AstroList* node, State* state){

  assert(node);
  assert(AstroNode_peek((AstroNode*) node) == 'L');
  unsigned long i;
  unsigned long len = AstroList_getLength(node);

  for (i=0;i < len;++i){
    AstroList_setElement( node, i, walk( (AstroNode*)AstroList_getElement(node,i), state));
  } 

  return node;
}
/******************************************************************************/
/******************************************************************************/
AstroTuple* tuple_exp(AstroTuple* node, State* state){

  assert(node);
  assert(AstroNode_peek((AstroNode*) node) == 't');
  unsigned long i;
  unsigned long len = AstroTuple_getLength(node);

  for (i=0;i < len;++i){
    AstroTuple_setElement( node, i, walk( (AstroNode*)AstroTuple_getElement(node,i), state));
  } 

  return node;
}
/******************************************************************************/
/******************************************************************************/
// NOTE: 'to-list' is not a semantic value and should never appear in
//       any tests.  It is a constructor and should be expanded by the
//       walk function before semantic processing.
AstroList* to_list_exp(AstroToList* node, State* state){
  assert(node);

  char head1,head2,head3;
  unsigned long start,stop,stride,i,index;
  AstroNode** arrayContents = NULL;
  AstroNode* node1;
  AstroNode* node2;
  AstroNode* node3;

  node1 = walk( AstroToList_getStart( node), state);
  node2 = walk( AstroToList_getStop( node), state);
  node3 = walk( AstroToList_getStride( node), state);

  head1 = AstroNode_peek( (AstroNode*)node1 );
  head2 = AstroNode_peek( (AstroNode*)node2 );
  head3 = AstroNode_peek( (AstroNode*)node3 );

  assert(head1 == 'i');
  assert(head2 == 'i');
  assert(head3 == 'i');

  start = AstroInteger_getValue( (AstroInteger*)node1);
  stop = AstroInteger_getValue( (AstroInteger*)node2);
  stride = AstroInteger_getValue( (AstroInteger*)node3);

  index = 0;
  if (stop>start){
    arrayContents = AstroMem_new((stop-start)/stride * sizeof(AstroNode*));

    for (i = start;i < stop;i += stride){
      arrayContents[index++] = (AstroNode*)AstroInteger_new(i);
    }
    return AstroList_new( (stop-start)/stride, arrayContents);

  } else {
    arrayContents = AstroMem_new(((start-stop)/stride) * sizeof(AstroNode*));

    for (i = start;i > stop;i -= stride){
      arrayContents[index++] = (AstroNode*)AstroInteger_new(i);
    }
    return AstroList_new( (start-stop)/stride, arrayContents);
  }
}
/******************************************************************************/
/******************************************************************************/
// NOTE: this is the value view of the head tail constructor, for the
//       pattern view of this constructor see unify.
AstroList* head_tail_exp(AstroHeadTail* node, State* state){
  assert(node);
  AstroNode** array_contents;
  unsigned long tail_length,i;
  char tail_type;

  AstroHeadTail_setHead( node, walk( AstroHeadTail_getHead(node), state));
  AstroHeadTail_setTail( node, walk( AstroHeadTail_getTail(node), state));

  tail_type = AstroNode_peek( (AstroNode*)AstroHeadTail_getTail(node));

  assert( tail_type == 'L');
  tail_length = AstroList_getLength( (AstroList*)AstroHeadTail_getTail(node));

  // Construct the return AstroList
  array_contents = AstroMem_new((1 + tail_length) * sizeof(AstroNode*));
  for (i=1;i<=tail_length;++i){
    array_contents[i] = AstroList_getElement( (AstroList*) AstroHeadTail_getTail(node), (i - 1) );
  }
  array_contents[0] = AstroHeadTail_getHead( node );

  return AstroList_new( 1 + tail_length, array_contents);
}
/******************************************************************************/
/******************************************************************************/
AstroSequence* sequence_exp(AstroSequence* node, State* state){
  assert(node);

  AstroSequence_setFirst( node, walk( (AstroNode*)AstroSequence_getFirst(node), state));
  AstroSequence_setSecond( node, walk( (AstroNode*)AstroSequence_getSecond(node), state));

  return node;
}
/******************************************************************************/
/******************************************************************************/
AstroFunction* function_exp(AstroFunction* node, State* state){
  assert(node);

  // STATE TODO


  return node;
}
/******************************************************************************/
/******************************************************************************/
// Note: eval is essentially a macro call - that is a function
// call without pushing a symbol table record.  That means
// we have to first evaluate the argument to 'eval' before
// walking the term.  This is safe because if the arg is already
// the actual term it will be quoted and nothing happens if it is
// a variable it will be expanded to the actual term.
AstroNode* eval_exp( AstroEval* node, State* state){
  assert(node);
  AstroNode* exp = NULL;

  exp = walk( AstroEval_getExpression(node), state);

  State_setIgnoreQuote( state, true);

  // Now walk the actual term
  exp = walk( exp, state);
  State_setIgnoreQuote( state, true);

  return exp;
}
/******************************************************************************/
/******************************************************************************/
AstroNode* quote_exp(AstroQuote* node, State* state){
  assert(node);

  if (State_getIgnoreQuote(state)){
    return walk( AstroQuote_getExpression(node), state );
  } else {
    return (AstroNode*)node;
  }
}
/******************************************************************************/
/******************************************************************************/
AstroNode* constraint_exp(AstroConstraint* node, State* state){
  assert(node);

  // TODO ERROR 
  printf("ERROR: constraint pattern: cannot be used as a constructor.\n");
  return NULL;
}
/******************************************************************************/
/******************************************************************************/
AstroNode* ID_exp(AstroID* node, State* state){
  assert(node);

  return (AstroNode*)State_lookupSym(state, AstroID_getName(node));
}
/******************************************************************************/
/******************************************************************************/
AstroNode* apply_exp(AstroApply* node, State* state){
  assert(node);

  // STATE TODO
  return (AstroNode*)node;
}
/******************************************************************************/
/******************************************************************************/
AstroNode* index_exp(AstroIndex* node, State* state){
  assert(node);

  AstroNode* structure_val = walk( AstroIndex_getStructure(node), state);

  

  // STATE TODO
  return (AstroNode*)node;
}
/******************************************************************************/
/******************************************************************************/
AstroNode* escape_exp(AstroEscape* node, State* state){
  assert(node);

  // TODO ESCAPE
  printf("ESCAPE NOT IMPLEMENTED\n");
  return (AstroNode*)node;
}
/******************************************************************************/
/******************************************************************************/
AstroNode* is_exp(AstroIs* node, State* state){
  assert(node);

  // TODO UNIFY
  return (AstroNode*)node;
}
/******************************************************************************/
/******************************************************************************/
AstroNode* if_exp(AstroIf* node, State* state){
  assert(node);
  bool val;

  val = map2boolean( walk (AstroIf_getCondition(node), state));

  if (val){
    return walk(AstroIf_getThen(node), state);
  } else {
    return walk(AstroIf_getElse(node), state);
  }
}
/******************************************************************************/
/******************************************************************************/
AstroBoolean* in_exp(AstroIn* node, State* state){
  assert( node );
  char type;
  unsigned long len,i;
  AstroList* list;

  AstroIn_setExpresssion( node, walk( AstroIn_getExpression(node), state));
  AstroIn_setExpressionList( node, walk( AstroIn_getExpressionList(node), state));

  type = AstroNode_peek( (AstroNode*)AstroIn_getExpressionList(node));
  printf("here\n");

  if (type != 'L'){ // Must be a list
    // TODO ERROR not a list in in
    printf("ERROR: Right argument to in operator has to be a list.\n");
    return AstroBoolean_new(false);
  }

  list = (AstroList*)AstroIn_getExpressionList(node);
  len = AstroList_getLength( list);

  for (i=0;i < len;++i){
    if (AstroNode_compare( AstroIn_getExpression(node), (AstroNode*)AstroList_getElement(list,i))){
      return AstroBoolean_new(true);
    }                    
  }
  return AstroBoolean_new(false);
}  
/******************************************************************************/
/******************************************************************************/
AstroNode* named_pattern_exp(AstroNamedPattern* node, State* state){
  assert(node);

  return walk( AstroNamedPattern_getPattern(node) ,state);
}
/******************************************************************************/
/******************************************************************************/
AstroNode* deref_exp(AstroDeref* node, State* state){
  assert(node);
  return walk( walk( AstroDeref_getExpression( node), state), state);
}
/******************************************************************************/
/******************************************************************************/
bool map2boolean( AstroNode* node){
  assert(node);
  char type;

  type = AstroNode_peek(node);

  // false is false
  if ((type == 'b') && AstroBoolean_getValue((AstroBoolean*)node) == false){
    return false;
  }

  // nil and none type are false
  if ((type == 'N') || (type == 'n')){
    return false;
  } 

  // 0 is false
  if  (((type == 'i') && (AstroInteger_getValue((AstroInteger*)node) == 0))  ||
      ((type == 'r') && (AstroReal_getValue((AstroReal*)node) == 0.0)))       {

    return false;
  }

  // empty structure
  if (((type == 'L') && (AstroList_getLength((AstroList*)node) == 0)) ||
     ((type == 't') && (AstroTuple_getLength((AstroTuple*)node) == 0))){

    return false;
  }
  return true;
}
/******************************************************************************/
/******************************************************************************/
AstroNode* read_at_id(AstroNode* structure_val, AstroNode* ix){
  assert(structure_val);
  assert(ix);
  char structType,ixType;

  structType = AstroNode_peek((AstroNode*)structure_val);
  ixType = AstroNode_peek((AstroNode*)ix);

  // if the stuct is a list,tuple,or string
  if ((structType == 'L')||(structType == 't')||(structType == 's')){
    if ((ixType == 'I')&&(1)){  // TODO strig member functions 
      return NULL;
    } 
  }

  return NULL;
}
/******************************************************************************/
/******************************************************************************/


// ****************   TESTING      ********************************
// ****************************************************************
/*
int main(int argc, char* argv[]){

  printf("Hello world!\n");
  AstroNode* test = AstroNode_new('a');
  AstroInteger* x = AstroInteger_new( 0 );
  AstroReal* y =    AstroReal_new( 987.654321 );
  AstroReal* y1 =    AstroReal_new( 1.1 );
  AstroReal* y2 =    AstroReal_new( 2.2 );
  AstroReal* y3 =    AstroReal_new( 3.3 );
  AstroBoolean* z = AstroBoolean_new( true );

  AstroNode** rawTuple = AstroMem_new( 3 * sizeof( AstroNode* ));
  rawTuple[0] = (AstroNode*)y1;
  rawTuple[1] = (AstroNode*)y2;
  rawTuple[2] = (AstroNode*)y3;
  AstroTuple* tup = AstroTuple_new( 3, NULL );
  AstroTuple_setContents(tup,rawTuple );

  walk( (AstroNode*)tup );
  walk( (AstroNode*)tup );
  walk( (AstroNode*)tup );

  AstroNode** rawArray = AstroMem_new( 3 * sizeof( AstroNode* ));
  rawArray[0] = (AstroNode*)y1;
  rawArray[1] = (AstroNode*)y2;
  rawArray[2] = (AstroNode*)y3;
  AstroList* list = AstroList_new( 3, NULL);
  AstroList_setContents(list,rawArray);

  AstroInteger* s1 = AstroInteger_new( 10 );
  AstroInteger* s2 = AstroInteger_new( 1 );
  AstroInteger* s3 = AstroInteger_new( 1 );
  AstroToList* newTest = AstroToList_new((AstroNode*)s1,(AstroNode*)s2,(AstroNode*)s3);

  walk( (AstroNode*) list );
  AstroList* l2 = (AstroList*)walk( (AstroNode*) newTest );

  walk( (AstroNode*)l2 );
  walk( (AstroNode*)l2 );
  //printf("ELEMENT TEST: %lu\n",AstroInteger_getValue( (AstroInteger*)AstroList_getElement(l2,3)));


  printf("PASSED!\n");

  AstroHeadTail* new = AstroHeadTail_new( (AstroNode*)x, (AstroNode*)list );
  //AstroHeadTail_setHead( new, (AstroNode*)x );
  //AstroHeadTail_setTail( new, (AstroNode*)newTest );
  AstroList* output = (AstroList*)walk( (AstroNode*)new );

  walk( (AstroNode*)output );

  AstroRawToList* list2 = AstroRawToList_new( (AstroNode*)s1,(AstroNode*)s2 ,(AstroNode*)s3);

  AstroList* list3 = (AstroList*)walk( (AstroNode*)list2 );

  walk((AstroNode*)list3);
  walk((AstroNode*)list3);

  AstroRawHeadTail* list4 = AstroRawHeadTail_new( (AstroNode*)x, (AstroNode*)list );

  AstroList* list5 = (AstroList*)walk( (AstroNode*)list4 );

  walk( (AstroNode*)list5);

  AstroSequence* list6 = AstroSequence_new( (AstroNode*)x, (AstroNode*)z );
  walk( (AstroNode*)z);
  walk( (AstroNode*)list6);

  AstroObject* u = AstroObject_new( NULL, list5);

  walk( (AstroNode*)u);

  AstroEval* u2 = AstroEval_new( (AstroNode*)list );

  walk( (AstroNode*)u2);

  AstroIn* u3 = AstroIn_new( (AstroNode*)y2,(AstroNode*)list );

  printf("%i\n",AstroBoolean_getValue( (AstroBoolean*)walk(walk((AstroNode*)u3))));

  AstroIf* u4 = AstroIf_new( (AstroNode*)x,(AstroNode*)tup,(AstroNode*)newTest );

  walk((AstroNode*)u4);
  
  return 0;
}
*/