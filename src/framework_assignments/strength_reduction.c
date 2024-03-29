/**
 * @file
 *
 * Traversal: StrengthReduction
 * UID      : SR
 *
 * Solution 1.4 !including bonus! by Thijs Vromen 12026069
 * Example of using the bonus: ./build-debug/civicc ./test/test2_edited.cvc -r 8
 * For the bonus changes were also made in main.c and in globals.
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"
#include "global/globals.h"

// The reduction helper function.
// Takes the variable and number nodes and returns a new node with the strength reduction applied.
node_st *reduce(node_st *node_var, node_st *node_num){
    int number = NUM_VAL(node_num);
    node_st *new_node;
    if (number == 0) {
        new_node = ASTnum(0);
    } else if (number == 1){
        new_node = CCNcopy(node_var);
    } else {
        // Create the first binop node with addition instead of multiplication.
        new_node = ASTbinop(CCNcopy(node_var), CCNcopy(node_var), BO_add);
        number -= 2;
        // Reduce the rest of the additions.
        while (number > 0) {
            new_node = ASTbinop(CCNcopy(node_var), new_node, BO_add);
            number -= 1;
        }
    }
    return new_node;
}

/**
 * @fn SRbinop
 * If the left child is an integer and the right a variable or vice versa, implement strength reduction.
 * Works for all nonnegative numbers. Strengh reduction is not applied if a maximum strength is set and
 * the number exceeds that maximum.
 */
node_st *SRbinop(node_st *node)
{
    TRAVchildren(node);
    if (BINOP_OP(node) == BO_mul) {
        if ((NODE_TYPE(BINOP_LEFT(node)) == NT_VAR) &&
            (NODE_TYPE(BINOP_RIGHT(node)) == NT_NUM) &
            // Only apply reduction if the max strength is negative (the default value is -1) 
            // or the strength is within the limit.
            (global.max_strenght < 0 || (NUM_VAL(BINOP_RIGHT(node)) <= global.max_strenght))){
                node_st *new_node = reduce(BINOP_LEFT(node), BINOP_RIGHT(node));
                CCNfree(node);
                return new_node;
        } else if ((NODE_TYPE(BINOP_LEFT(node)) == NT_NUM) &&
            (NODE_TYPE(BINOP_RIGHT(node)) == NT_VAR) &&
            (global.max_strenght < 0 || (NUM_VAL(BINOP_LEFT(node)) <= global.max_strenght))){
                node_st *new_node = reduce(BINOP_RIGHT(node), BINOP_LEFT(node));
                CCNfree(node);
                return new_node;
        }
    }
    return node;
}
