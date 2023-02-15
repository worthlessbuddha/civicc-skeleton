/**
 * @file
 *
 * Traversal: HashTable
 * UID      : HT
 * Name     : U. Buran
 * UvANetID : 13420828
 * Course   : Compiler Construction
 * hashtable.c:
 * This file contains the implementation of the HashTable. It counts the number
 * of times an identifier is used in a module.
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "palm/memory.h"
#include <stdio.h>

void HTprint(void *key, void *value) {
  printf("%s: %dx\n", key, *(int *)value);
  return;
}

void HTinit() {
  DATA_HT_GET()->id_table = HTnew_String(1);
  return;
}

void HTfini() {
  /* Print the hash table and delete it */
  printf("ASSIGNMENT 1.6:\n");
  HTmapWithKey(DATA_HT_GET()->id_table, (mapk_ft)HTprint);
  printf("\n");
  HTdelete(DATA_HT_GET()->id_table);
  return;
}

void HTincrement(void *key) {
  int *value;
  /* If the key is not in the hash table, insert it */
  if (HTlookup(DATA_HT_GET()->id_table, key) == NULL) {
    int *tmp = MEMmalloc(sizeof(int));
    *tmp = 1;
    HTinsert(DATA_HT_GET()->id_table, key, tmp);
  }
  /* If the key is in the hash table, increment the value */
  else {
    value = HTlookup(DATA_HT_GET()->id_table, key);
    ++*value;
  }
}

/**
 * @fn HTvar
 */
node_st *HTvar(node_st *node) {
  HTincrement(VAR_NAME(node));
  return node;
}

/**
 * @fn HTvarlet
 */
node_st *HTvarlet(node_st *node) {
  HTincrement(VARLET_NAME(node));
  return node;
}
