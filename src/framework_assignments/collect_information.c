/**
 * @file
 *
 * Traversal: CollectInformation
 * UID      : CI
 *
 * Solution 1.5 by Thijs Vromen 12026069.
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"

void CIinit() { return; }
void CIfini() { return; }

/**
 * @fn CIprogram
 * When the traverse is done, store the values in the program node so it can be accessed 
 * in the print.
 */
node_st *CIprogram(node_st *node)
{
    TRAVchildren(node);
    struct data_ci *data = DATA_CI_GET();
    PROGRAM_ADD(node) = data->add;
    PROGRAM_DIV(node) = data->div;
    PROGRAM_MOD(node) = data->mod;
    PROGRAM_MUL(node) = data->mul;
    PROGRAM_SUB(node) = data->sub;
    return node;
}

/**
 * @fn CIbinop
 * Increase the counter of the operation in the traversal attribute struct, 
 * if it is one of the fiver arithmetic operators.
 */
node_st *CIbinop(node_st *node)
{
    TRAVchildren(node);
    struct data_ci *data = DATA_CI_GET();
    switch (BINOP_OP(node)){
        case BO_add:
            data->add += 1;
            break;
        case BO_mul:
            data->mul += 1;
            break;
        case BO_div:
            data->div += 1;
            break;
        case BO_mod:
            data->mod += 1;
            break;
        case BO_sub:
            data->sub += 1; 
            break;
        default:
            break;
    }
    return node;
}

