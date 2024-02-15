/**
 * @file
 *
 * Traversal: HashIdentifiers
 * UID      : HI
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"
#include <stdio.h>

void HIinit() { 
    struct data_hi *data = DATA_HI_GET();
    data->hash = HTnew_String(42);
    return; }
void HIfini() { 
    struct data_hi *data = DATA_HI_GET();
    for (htable_iter_st *iter = HTiterate(data->hash); iter; iter = HTiterateNext(iter)) { // MOET EIGENLIJK IN ROOT NODE???
        void *key = HTiterKey(iter);
        int *value = (int *)HTiterValue(iter);
        printf("The identifier %s occurs %d time(s).\n", (char *)key, *value);
    }
    HTdelete(data->hash);
    return; }

/**
 * @fn HIvar
 */
node_st *HIvar(node_st *node)
{
    TRAVchildren(node);
    struct data_hi *data = DATA_HI_GET();
    char *identifier = VAR_NAME(node);
    int *repeats = (int *)HTlookup(data->hash, identifier);
    if (repeats){
        *repeats += 1;
        HTinsert(data->hash, identifier, repeats);
    } else{
        int new = 1;
        HTinsert(data->hash, identifier, &new);
    }
    return node;
}

/**
 * @fn HIvarlet
 */
node_st *HIvarlet(node_st *node)
{
    return HIvar(node);
}