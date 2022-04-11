#pragma once

struct Node* SortedMerge(Node* a, Node* b);

void FrontBackSplit(struct Node* source, Node** frontRef, Node** backRef);

void MergeSort(Node** headRef);
