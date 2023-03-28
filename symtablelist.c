/*--------------------------------------------------------------------*/
/* symtablelist.c                                                     */
/* Author: Devanna Ritchie                                            */
/*--------------------------------------------------------------------*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"


/* node structure which contains pointer to the defensive copy of the key,
the pointer to the client's value, and the pointer to the next node in the list*/
struct node {
    /* pointer to the defensive copy of the key*/
    const char *key; 
    /* pointer to the client's value*/
    const void *value;
    /* pointer to the next node*/
    struct node *nextNode;
};

/* SymTable structure that contains the pointer to the first node of the list 
and the length of the symbol table*/
struct SymTable {
   /* The address of the first node. */
  struct node *first;

  /* how many nodes inside the symbol table*/
  size_t length;
  
};


SymTable_T SymTable_new(void) {
    SymTable_T oSymTable;
    
/* allocate space for the managing structure */
   oSymTable = (SymTable_T) malloc(sizeof(struct SymTable));
   if (oSymTable == NULL)
      return NULL;

   oSymTable->first = NULL;
   oSymTable->length = 0;
   return oSymTable;
}

void SymTable_free(SymTable_T oSymTable) {
    
   struct node *currentNode;
   struct node *nextNode;
   assert(oSymTable != NULL);

   for (currentNode = oSymTable->first;
        currentNode != NULL;
        currentNode = nextNode)
   {
      nextNode = currentNode->nextNode;
      free((char*) currentNode->key);
      free(currentNode);
   }

   free(oSymTable);
}

size_t SymTable_getLength(SymTable_T oSymTable) {
    assert(oSymTable != NULL);
   return oSymTable->length;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) {
    struct node *currentNode;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    /* loops through all the nodes in search for pcKey*/
    for (currentNode = oSymTable->first; currentNode != NULL; 
            currentNode = currentNode -> nextNode) {
        if (strcmp(currentNode->key, pcKey) == 0) {
            return 0;
        } 
    }
    /*new key found*/
    /* allocating enough space for new node*/
    currentNode = (struct node*) malloc(sizeof(struct node));

    if (currentNode == NULL) {
        return 0;
    }
    currentNode->key = (char*) malloc(strlen(pcKey) + 1);
    if (currentNode->key == NULL) {
        free(currentNode);
        return 0;
    }
    /*ready to fill the node*/
    currentNode->key = strcpy((char*) currentNode->key, pcKey);
    currentNode->value = pvValue;
    /* adds p to the beginning of the list*/
    currentNode->nextNode = oSymTable->first;
    oSymTable->first = currentNode;
    oSymTable->length++;
    return 1;
}

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, const void *pvValue) {
    /* traveling node*/
    struct node *currentNode;
    const void* oldValue;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);

/* loops through all the nodes in search for pcKey*/
for (currentNode = oSymTable->first; currentNode != NULL; 
        currentNode = currentNode -> nextNode) {
        if (strcmp(currentNode->key, pcKey) == 0) {
            oldValue = currentNode->value;
            currentNode->value = pvValue;
            return (void*) oldValue;
        } 
    }
    return NULL;

}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey) {
    struct node *currentNode;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    for (currentNode = oSymTable->first; currentNode != NULL; 
            currentNode = currentNode -> nextNode) {
        if (strcmp(currentNode->key, pcKey) == 0) {
            return 1;
        }
    }
    return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey) {
    struct node *currentNode;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    /* loops through all the nodes in search for pcKey*/
    for (currentNode = oSymTable->first; currentNode != NULL; 
            currentNode = currentNode -> nextNode) {
        if (strcmp(currentNode->key, pcKey) == 0) {
            return (void*) currentNode->value;
        } 
    }
    return NULL;
}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey) {
    /*traveling node*/
    struct node *currentNode;
    struct node *prevNode = NULL;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);
     /* loops through all the nodes in search for pcKey*/
    for (currentNode = oSymTable->first; currentNode != NULL; 
            currentNode = currentNode -> nextNode) {
        if (strcmp(currentNode->key, pcKey) == 0) {
            const void* oldValue;
            /*save the currentNode's value*/
            oldValue = currentNode->value;
            /* relink the list*/
            /*if prevNode is at the beginning of the list*/
            if (prevNode == NULL) {
                oSymTable->first = currentNode->nextNode;
            }
            else {
                prevNode->nextNode = currentNode->nextNode;
            }
            free((char*) currentNode->key);
            free(currentNode);
            oSymTable->length--;

            return (void*) oldValue;
        } 
        prevNode = currentNode;
    }
    return NULL;
 
    }

 void SymTable_map(SymTable_T oSymTable,
     void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
     const void *pvExtra) {
        /* traveling node*/
        struct node *currentNode;
        assert(oSymTable != NULL);
        assert(pfApply != NULL);
        
        for (currentNode = oSymTable->first;
        currentNode != NULL;
        currentNode = currentNode->nextNode)
      (*pfApply)(currentNode->key, (void*)currentNode->value, (void*)pvExtra);
     }