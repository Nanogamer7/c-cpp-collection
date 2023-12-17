// This file is a collection of linked list functions using double pointers

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>

typedef struct node{
	int n;
	struct node* next;
} node;

typedef struct timeval timeval;

node** getIndexHead(node** head, int index);
int getLength(node** head);

void printList(node** head);
void addFirst(node** head, node input);
void addFirstScan(node** head);
void addLast(node** head, node input);
void addLastScan(node** head);
void addIndex(node** head, int index, node input);
void addIndexScan(node** head, int index);
void removeFirst(node** head);
void deleteList(node** head);
void removeIndex(node** head, int index);
void swapFirst(node** head);
void swapNextIndex(node** head, int index);
void swapIndexes(node** head, int index, int index2);
void moveIndex(node** head, int index, int newIndex);
void reverseList(node** head);

timeval timer(void (*func)(node**), node** head);

void shuffle(node** head);
void bubbleSort(node** head);
void bogoSort(node** head);
void selectionSort(node** head);
void mergeSort(node** head);
void countingSort(node** head);

int main() {

	srand((unsigned) time(0)); // seed for shuffle

	node* head = NULL;
	void (*nodeFunctions[5])(node**) = {&printList, &reverseList, &deleteList, &addFirstScan, &addLastScan};
	void (*nodeIndexFunctions[3])(node**, int) = {&addIndexScan, &removeIndex, &swapNextIndex};
	void (*nodeDoubleIndexFunctions[2])(node**, int, int) = {&swapIndexes, &moveIndex};
	void (*nodeSortFunctions[6])(node**) = {&shuffle, &bubbleSort, &bogoSort, &selectionSort, &mergeSort, &countingSort};

	while(1) {
		int option = 0;
		printf("\nWhatcha gonna do? "
			"exit [-1], "
			"print [0], "
			"reverseList [1], "
			"delete list [2], "
			"add first [3], "
			"add last [4], "
			"add at index [5], "
			"remove at index [6], "
			"swap with next at index [7], "
			"swap two at indexes [8], "
			"move from/to index [9], "
			"shuffle [10], "
			"bubble sort [11], "
			"bogo sort [12], "
			"selection sort [13], "
			"merge sort [14], "
			"counting sort [15], "
			"make a random list [98], "
			"make test list 0-9 [99]"
			": ");
		scanf("%d", &option);
		if(option < 0)
			break;
		else if(option < 5)
			(*nodeFunctions[option])(&head);
		else if(option < 8) {
			printf("\nPlease enter an index: ");
			int index;
			scanf("%d", &index);
			(*nodeIndexFunctions[option-5])(&head, index);
		}else if(option < 10) {
			printf("\nPlease enter two indexes: ");
			int indexA, indexB;
			scanf("%d%d", &indexA, &indexB);
			(*nodeDoubleIndexFunctions[option-8])(&head, indexA, indexB);
		}else if(option < 16) {
			timeval exec_time = timer(nodeSortFunctions[option-10], &head);
			printf("\nOperation took %ld.%06ld microseconds", (long int)exec_time.tv_sec, (long int)exec_time.tv_usec);
		}else if(option == 98) {
			printf("\nPlease enter length and max value: ");
			int length, max;
			scanf("%d%d", &length, &max);
			for(int i = 0; i < length; i++) {
				node node = { .n = rand()%(max+1) };
				addFirst(&head, node);
			}
		}else if(option == 99) {
			for(int i = 9; i >= 0; i--) {
				node node = { .n = i };
				addFirst(&head, node);
			}
		}
	}

	(*nodeFunctions[2])(&head);

	return 0;
}

node** getIndexHead(node** head, int index) {
	node** headPt = head;
	for(int i = 0; i < index; i++) {
		headPt = &((*headPt)->next);
	}
	return headPt;
}

int getLength(node** head) {
	int length = 1;
	for(node** headPt = head; (*headPt)->next; headPt = &((*headPt)->next))
		length++;

	return length;
}

void printList(node** head) {
	node* temp = *head;
	if(!(temp)) {
		printf("This list is empty!\n");
	}
	while((temp)) {
		printf("%d ", (temp)->n);
		temp = (temp)->next;
	}
}

void addFirst(node** head, node input) {
	node* newHead = malloc(sizeof(node));
	*newHead = input;
	newHead->next = *head;
	*head = newHead;
}

void addFirstScan(node** head) {
	node input;
	scanf("%d", &input.n);
	addFirst(head, input);
}

void addLast(node** head, node input) {
	node** tempHead;
	for(tempHead = head; *tempHead; tempHead = &((*tempHead)->next));
	addFirst(tempHead, input);
}

void addLastScan(node** head) {
	node input;
	scanf("%d", &input.n);
	addLast(head, input);
}

void addIndex(node** head, int index, node input) {
	addFirst(getIndexHead(head, index), input);
}

void addIndexScan(node** head, int index) {
	node input;
	scanf("%d", &input.n);
	addIndex(head, index, input);
}

void removeFirst(node** head) {
	node* temp = *head;
	*head = (*head)->next;
	free(temp);
}

void deleteList(node** head) {
	while(*head) {
		removeFirst(head);
	}
	*head = NULL;
}

void removeIndex(node** head, int index) {
	removeFirst(getIndexHead(head, index));
}

void swapFirst(node** head) {
	node* temp = (*head)->next;
	(*head)->next = temp->next;
	temp->next = *head;
	*head = temp;
}

void swapNextIndex(node** head, int index) {
	node** headPt = getIndexHead(head, index);

	if(!(*headPt)->next)
		return;

	swapFirst(headPt);
}

void swapIndexes(node** head, int indexA, int indexB) {
	if(indexA == indexB)
		return;
	if(indexB < indexA) {
		int temp = indexA;
		indexA = indexB;
		indexB = temp;
	}
	if(indexB - indexA == 1) {
		swapNextIndex(head, indexA);
		return;
	}

	node** headPtA = getIndexHead(head, indexA);
	node** headPtB = getIndexHead(head, indexB);

	if(!(*headPtB))
		return;

	int i = 2;
	while(i) {
		i--;
		node* temp = *headPtA;
		*headPtA = *headPtB;
		*headPtB = temp;

		if(!i)
			break;

		headPtA = &((*headPtA)->next);
		headPtB = &((*headPtB)->next);
	}
}

void moveIndex(node** head, int index, int newIndex) {
	if(index == newIndex)
		return;
	node temp = **getIndexHead(head, index);
	removeIndex(head, index);
	addIndex(head, newIndex, temp);
}

void reverseList(node** head) {
	node* currentNode = *head;
	node* nextNode = currentNode->next;
	node* lastNode = NULL;

	while(nextNode) {
		nextNode = currentNode->next;
		currentNode->next = lastNode;

		lastNode = currentNode;
		currentNode = nextNode;
	}
	*head = lastNode;
}

timeval timer(void (*func)(node**),node** head) {
	timeval tval_before, tval_after, tval_result;
	gettimeofday(&tval_before, NULL);

	(*func)(head);

	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);
	return tval_result;
}

void shuffle(node** head) {
	int length = getLength(head);

	node** array = malloc(sizeof(node*) * (length + 1));
	array[length] = NULL;

	for(node** p = array; *head; p++) {
		*p = *head;
		*head = (*head)->next;
	}

	for(int i = length-1; i > 0; i--) {
		int r = rand()%(i+1);
		node* temp = array[i];
		array[i] = array[r];
		array[r] = temp;
	}

	node** workingHead = head;
	for(node** p = array; p < array + length; p++) {
		*workingHead = *p;
		(*workingHead)->next = *(p+1);
		workingHead = &((*workingHead)->next);
	}
	free(array);
}

void bubbleSort(node** head) {
	int loop;
	do{
		loop = 0;
		for(node** headPt = head; (*headPt)->next; headPt = &((*headPt)->next)) {
			if((*headPt)->n > (*headPt)->next->n) {
				swapFirst(headPt);
				loop = 1;
			}
		}
	}while(loop);
}

void bogoSort(node** head) {
	int loop;
	do{
		loop = 0;
		for(node** headPt = head; (*headPt)->next; headPt = &((*headPt)->next))
			if((*headPt)->n > (*headPt)->next->n) {
				shuffle(headPt);
				loop = 1;
				break;
			}
	}while(loop);
}

void selectionSort(node** head) {
	node** unsortedHead = head;
	int indexSmallest, loop, smallest, index;

	do{
		loop = 0;
		index = 0;
		smallest = INT_MAX;

		for(node** pt = unsortedHead; *pt; pt = &((*pt)->next)) {
			if((*pt)->n < smallest) {
				indexSmallest = index;
				smallest = (*pt)->n;
				loop = 1;
			}
			index++;
		}

		swapIndexes(unsortedHead, indexSmallest, 0);
		unsortedHead = &((*unsortedHead)->next);
	}while(loop);
}

void mergeSort(node** head) {
	int length = getLength(head);
	if(length < 2) {
		printf("%d", length);
		return;
	}
	node** sortedHead = head;

	node* headA = *head;
	node** headPtA = &headA;
	node** temp = getIndexHead(headPtA, (length-1)/2);
	node* headB = (*temp)->next;
	node** headPtB = &headB;
	(*temp)->next = NULL;

	if((*headPtA)->next)
		mergeSort(headPtA);
	if((*headPtB)->next)
		mergeSort(headPtB);

	while(*headPtA || *headPtB) {
		if(*headPtA && *headPtB) {
			if((*headPtA)->n < (*headPtB)->n) {
				*sortedHead = *headPtA;
				*headPtA = (*headPtA)->next;
			}else{
				*sortedHead = *headPtB;
				*headPtB = (*headPtB)->next;
			}
		}else if(*headPtA) {
			*sortedHead = *headPtA;
			*headPtA = (*headPtA)->next;
			break;
		}else{
			*sortedHead = *headPtB;
			*headPtB = (*headPtB)->next;
			break;
		}
		sortedHead = &((*sortedHead)->next);
	}
}

void countingSort(node** head) {
	long int length = getLength(head);
	node** array = malloc(sizeof(node*) * length);
	node** p = array;
	for(node* q = *head; q; q = q->next) {
		*p = q;
		p++;
	}

	// assuming min value to be 0
	int max = 0;
	for(p = array; p < array + length; p++)
		max = (*p)->n > max ? (*p)->n : max;

	int* values = malloc(sizeof(int) * (max + 1));
	for(int* q = values; q < values + max + 1; q++)
		*q = 0;

	for(p = array; p < array + length; p++)
		values[(*p)->n]++;

	for(int* q = values + 1; q < values + max + 1; q++)
		*q += *(q-1);

	node** output = malloc(sizeof(node*) * length);
	for(p = array; p < array + length; p++) {
		output[values[(*p)->n] - 1] = *p;
		values[(*p)->n]--;
	}

	p = output + length - 1;
	(*p)->next = NULL;
	for(1; p > output; p--)
		(*(p-1))->next = *p;
	*head = *p;

	free(array);
	free(values);
	free(output);
}