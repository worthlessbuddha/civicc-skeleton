/**
 * @file
 *
 * Traversal: StrengthReduction
 * UID      : SR
 * Name     : U. Buran
 * UvANetID : 13420828
 * Course   : Compiler Construction
 * srenthreduction.c:
 * This file contains the implementation of the Strength Reduction. It checks if
 * the left and right node of a multiplication are a number and a variable.
 * If so, it replaces the multiplication with a series of additions.
 *
 */

#include <stdio.h>

#include "ccn/ccn.h"
#include "ccn/dynamic_core.h"
#include "ccngen/actions.h"
#include "ccngen/ast.h"
#include "ccngen/enum.h"
#include "ccngen/trav.h"
#include "palm/str.h"

/**
 * @fn SRbinop
 */
node_st *SRbinop(node_st *node) {
  if (BINOP_TYPE(node) == BO_mul) {

    /* Check if the left and right node are a number and a variable */
    if ((NODE_TYPE(BINOP_LEFT(node)) == NT_NUM &&
         NODE_TYPE(BINOP_RIGHT(node)) == NT_VAR) ||
        (NODE_TYPE(BINOP_LEFT(node)) == NT_VAR &&
         NODE_TYPE(BINOP_RIGHT(node)) == NT_NUM)) {
      TRAVchildren(node);
      /* Get the number and variable */
      node_st *number = NODE_TYPE(BINOP_LEFT(node)) == NT_NUM
                            ? BINOP_LEFT(node)
                            : BINOP_RIGHT(node);
      node_st *variable = NODE_TYPE(BINOP_LEFT(node)) == NT_VAR
                              ? BINOP_LEFT(node)
                              : BINOP_RIGHT(node);
      /* Replace the multiplication with a series of additions */
      for (int i = 0; i < NUM_VAL(number) - 1; i++) {
        if (i == 0) {
          node = ASTbinop(CCNcopy(variable), CCNcopy(variable), BO_add);
          continue;
        }
        node = ASTbinop(CCNcopy(node), CCNcopy(variable), BO_add);
      }
    }
  }
  return node;
}
