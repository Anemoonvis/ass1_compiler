/**
 * @file
 *
 * Traversal: CollectInformation
 * UID      : CI
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"

// REMOVE WHEN NO LONGER USED!!
#include <stdio.h>

void CIinit() { return; }
void CIfini() { return; }

/**
 * @fn CIprogram
 */
node_st *CIprogram(node_st *node)
{
    struct data_ci *data = DATA_CI_GET();
    printf("%d", data->add);
    TRAVchildren(node);
    data = DATA_CI_GET();
    printf("%d", data->add);
    printf("%d", data->mul);
    printf("%d", data->div);
    printf("%d", data->mod);
    printf("%d", data->sub);

    return node;
}

/**
 * @fn CIbinop
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

