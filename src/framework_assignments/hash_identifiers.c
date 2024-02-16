/**
 * @file
 *
 * Traversal: HashIdentifiers
 * UID      : HI
 *
 * Solution 1.6 by Thijs Vromen 12026069
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"
#include "palm/memory.h"
#include "palm/hash_table.h"
#include <stdio.h>

// Create the hash table to be used in the traversal, with size 42 (always the answer).
void HIinit() { 
    struct data_hi *data = DATA_HI_GET();
    data->hash = HTnew_String(42);
    return; }

// Free the hash table after the traversal ends.
void HIfini() { 
    struct data_hi *data = DATA_HI_GET();
    HTdelete(data->hash);
    return; }

/**
 * @fn HIprogram
 * Print the number of times each identifier occurs in the program.
 * Also already frees the values, because that is more convenient than doing it in HIfini.
 */
node_st *HIprogram(node_st *node)
{
    TRAVchildren(node);
    struct data_hi *data = DATA_HI_GET();
    for (htable_iter_st *iter = HTiterate(data->hash); iter; iter = HTiterateNext(iter)) {
        void *key = HTiterKey(iter);
        int *value = (int *)HTiterValue(iter);
        printf("The identifier %s occurs %d time(s).\n", (char *)key, *value);
        MEMfree(value);
    }
    return node;
}

/**
 * @fn HIvar
 * When encountering a variable, increase the counter of its identifier in the hash table
 * if it already exists. Otherwise insert it in the table.
 */
node_st *HIvar(node_st *node)
{
    TRAVchildren(node);
    struct data_hi *data = DATA_HI_GET();
    char *identifier = VAR_NAME(node);
    int *repeats = (int *)HTlookup(data->hash, identifier);
    if (repeats){
        *repeats += 1;
    } else{
        int *new = MEMmalloc(sizeof(int));
        *new = 1;
        HTinsert(data->hash, identifier, new);
    }
    return node;
}

/**
 * @fn HIvarlet
 * This function is the same as HIvar, since varlet and var both represent variables 
 * (with identifiers) that can thus be treated the same. 
 */
node_st *HIvarlet(node_st *node)
{
    return HIvar(node);
}