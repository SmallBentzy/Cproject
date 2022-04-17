
#include <stdlib.h>
#include "main.h"
#include "MargeSortList.h"
#include"Utilities.h"
//#define DEBUG 0

// Sorts the linked list by changing
// next pointers (not data)
void MergeSort( Node** headRef)
{
     Node* head = *headRef;
     Node* a;
     Node* b;

    // Base case -- length 0 or 1
    if ((head == NULL) ||
        (head->next == NULL))
    {
        return;
    }

    // Split head into 'a' and 'b' sublists
    FrontBackSplit(head, &a, &b);

    // Recursively sort the sublists
    MergeSort(&a);
    MergeSort(&b);

    /* answer = merge the two sorted
       lists together */
    *headRef = SortedMerge(a, b);
}

 Node* SortedMerge( Node* a,  Node* b)
{
     Node* result = NULL;
     //char aName[MAX_NAME], bName[MAX_NAME];
    // Base cases
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);


    if (strcicmp(a->course_data->lastN, b->course_data->lastN) <= 0)
    {
        //printf(" %s  is before %s \n", a->course_data->lastN, b->course_data->lastN);
        result = a;
        result->next =
            SortedMerge(a->next, b);
    }
    else
    {
#ifdef DEBUG
        printf(" line %d in func  %s file %s\n", __LINE__, __func__, __FILE__);
        printf(" %s  is before %s \n", b->course_data->lastN, a->course_data->lastN);
#endif // DEBUG

        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

// UTILITY FUNCTIONS
/* Split the nodes of the given list into
   front and back halves, and return the
   two lists using the reference parameters.
   If the length is odd, the extra node should
   go in the front list.Uses the fast/slow
   pointer strategy. */
void FrontBackSplit( Node* source, Node** frontRef, Node** backRef)
{
     Node* fast;
     Node* slow;
    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes, and
       advance 'slow' one node */
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* 'slow' is before the midpoint in the
        list, so split it in two at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}