#include <stdlib.h>
#include <stdio.h>

typedef struct foo_s {
    int a;
} foo;

typedef struct bar_s {
    foo super;
    int b;
} bar;

typedef struct astobject_s {
    char type;
} AstObject;

typedef struct astvalue_s {
    AstObject super;
    long value;
} AstValue;

int peek(AstObject *x) {
  printf("%c\n",x->type);
}

int setType(AstObject *x, char a){
    x->type = 'a';
}

int fooGetA(foo *x) {
  return x->a;
}

void fooSetA(foo *x, int a) {
  x->a = a;
}

int main() {
  bar* derived = (bar*) calloc(1, sizeof(bar));
  fooSetA((foo*) derived, 5);
  derived->b = 3;
  printf("result: %d\n", fooGetA((foo*) derived));

  AstValue* val = (AstValue*) calloc(1, sizeof(AstValue)); 
  //val->super.type = 'Z';
  setType((AstObject*) val, 'Z');
  void* data = &val;

  peek( (AstObject*) val);

  return 0;
}