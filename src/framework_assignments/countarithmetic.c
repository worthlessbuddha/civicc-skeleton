/**
 * @file
 *
 * Traversal: CountArithmetic
 * UID      : CA
 * Name     : U. Buran
 * UvANetID : 13420828
 * Course   : Compiler Construction
 * countarithmetic.c:
 * This file contains the implementation of the CountArithmetic. It counts the
 * number of additions, subtractions, multiplications, divisions and modulo
 * operations in a module.
 */

#include "ccn/ccn.h"
#include "ccn/dynamic_core.h"
#include "ccngen/actions.h"
#include "ccngen/ast.h"
#include "ccngen/enum.h"
#include "ccngen/trav.h"
#include "palm/str.h"
#include <stdio.h>

void CAinit() { return; }
void CAfini() { return; }

/**
 * @fn CAmodule
 */
node_st *CAmodule(node_st *node) {
  /* Set the counters to the root node */
  TRAVchildren(node);
  struct data_ca *data = DATA_CA_GET();
  MODULE_ADD(node) = data->add;
  MODULE_SUB(node) = data->sub;
  MODULE_MUL(node) = data->mul;
  MODULE_DIV(node) = data->div;
  MODULE_MOD(node) = data->mod;
  return node;
}

/**
 * @fn CAbinop
 */
node_st *CAbinop(node_st *node) {
  TRAVchildren(node);
  struct data_ca *data = DATA_CA_GET();
  /* Count the number of arithmetic operations */
  if (BINOP_TYPE(node) == BO_add) {
    data->add += 1;
  } else if (BINOP_TYPE(node) == BO_sub) {
    data->sub += 1;
  } else if (BINOP_TYPE(node) == BO_mul) {
    data->mul += 1;
  } else if (BINOP_TYPE(node) == BO_div) {
    data->div += 1;
  } else if (BINOP_TYPE(node) == BO_mod) {
    data->mod += 1;
  }
  return node;
}
