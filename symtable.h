 /*-------------------------------------------------------------------*/
/* intmath.h (Version 4)                                              */
/* Author: Devanna Ritchie                                            */
/*--------------------------------------------------------------------*/

#ifndef SYMTABLE_INCLUDED
#define SYMTABLE_INCLUDED
#include <stddef.h>

/* A SymTable_T is a collection of bindings, each binding consisting of a key and a value. */

typedef struct SymTable *SymTable_T;

/*--------------------------------------------------------------------*/
 
 /* return a new SymTable object that contains no bindings, or NULL 
 if insufficient memory is available */

 SymTable_T SymTable_new(void);

 /*--------------------------------------------------------------------*/

 /* free all memory occupied by oSymTable.*/

  void SymTable_free(SymTable_T oSymTable);

/*--------------------------------------------------------------------*/

/* return the number of bindings in oSymTable. */

  size_t SymTable_getLength(SymTable_T oSymTable);


/*--------------------------------------------------------------------*/

/* add a new binding to oSymTable consisting of key pcKey and value pvValue and return 1 (TRUE). 
Otherwise the function must leave oSymTable unchanged and return 0 (FALSE). 
If insufficient memory is available, then the function must leave oSymTable unchanged and return 0 (FALSE).*/

  int SymTable_put(SymTable_T oSymTable,
     const char *pcKey, const void *pvValue);
/*--------------------------------------------------------------------*/

/* If oSymTable contains a binding with key pcKey, 
replace the binding's value with pvValue and return the old value. 
Otherwise it must leave oSymTable unchanged and return NULL.*/

  void *SymTable_replace(SymTable_T oSymTable,
     const char *pcKey, const void *pvValue);
/*--------------------------------------------------------------------*/

/* return 1 (TRUE) if oSymTable contains a binding whose key is pcKey, and 0 (FALSE) otherwise.*/
  int SymTable_contains(SymTable_T oSymTable, const char *pcKey);
/*--------------------------------------------------------------------*/

/* return 1 (TRUE) if oSymTable contains a binding whose key is pcKey, and 0 (FALSE) otherwise.*/

  void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

/*--------------------------------------------------------------------*/

/* return the value of the binding within oSymTable whose key is pcKey, or NULL if no such binding exists.*/
  void *SymTable_remove(SymTable_T oSymTable, const char *pcKey);

/*--------------------------------------------------------------------*/

/* apply function *pfApply to each binding in oSymTable, passing pvExtra as an extra parameter. */
  void SymTable_map(SymTable_T oSymTable,
     void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
     const void *pvExtra);
/*--------------------------------------------------------------------*/

#endif

