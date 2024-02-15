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
    TRAVchildren(node);
    

    return node;
}

/**
 * @fn CIbinop
 */
node_st *CIbinop(node_st *node)
{
    TRAVchildren(node);
    return node;
}

