/**
 * @file
 *
 * Traversal: StrengthReduction
 * UID      : SR
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"

// WHAT TO DO IF BOTH NUMBERS OR IF THE NUMBER IS NEGATIVE?

node_st *reduce(node_st *node_var, node_st *node_num){
    int number = NUM_VAL(node_num);
    node_st *new_node;
    //CCNfree(node_num);
    if (number == 0) {
        new_node = ASTnum(0);
        //CCNfree(node_var);
    } else if (number == 1){
        new_node = CCNcopy(node_var);
    } else {
        new_node = ASTbinop(CCNcopy(node_var), CCNcopy(node_var), BO_add);
        number -= 2;
        while (number > 0) {
            new_node = ASTbinop(CCNcopy(node_var), new_node, BO_add);
            number -= 1;
        }
        //CCNfree(node_var);
    }
    return new_node;
}

/**
 * @fn SRbinop
 */
node_st *SRbinop(node_st *node)
{
    TRAVchildren(node);
    if (BINOP_OP(node) == BO_mul) {
        if ((NODE_TYPE(BINOP_LEFT(node)) == NT_VAR) &&
            (NODE_TYPE(BINOP_RIGHT(node)) == NT_NUM)){
                node_st *new_node = reduce(BINOP_LEFT(node), BINOP_RIGHT(node));
                CCNfree(node);
                return new_node;
        } else if ((NODE_TYPE(BINOP_LEFT(node)) == NT_NUM) &&
            (NODE_TYPE(BINOP_RIGHT(node)) == NT_VAR)){
                node_st *new_node = reduce(BINOP_RIGHT(node), BINOP_LEFT(node));
                CCNfree(node);
                return new_node;
        }
        
    }
    return node;
}