#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum node_type { // In theory a '#' or something similar would be sufficient for this program
	number_type = 1,     // but unfortunately the specifications are overly specific
	operator_type,
	parenthesis_type,
} node_type;

typedef struct node {
    char operator;  
    int number;
    node_type type;
    struct node* next;
} node;

node* inputToNode(const char *input); // creates a new node based on an input

node* createNumberNode(int number);
node* createParenthesisNode(char operator);
node* createOperatorNode(char operator);
node* createCharNode(char operator); // helper function without type specified

void populateList(node** head); // recursively scans for inputs
void solveRecursive(node** head, node** printHead); // solves a term or a partial term in parenthesis
	
void solveOperations(node** head, node** printHead, int point); // solves a given type of operations (point or dash)
void multiplication(node** leftSide);
void division(node** leftSide);
void addition(node** leftSide);
void subtraction(node** leftSide);



// helper functions for linked lists

node** getIndexHead(node** head, int index);
node** findOperator(node** head, char operator);
node** findOpenParenthesisHead(node** head);
node** findOperation(node** head, int point); // returns the next operations of a type (point or dash). NULL if none found

int getLength(node** head);

void printList(node** head);
void addFirst(node** head, node* input);
void addLast(node** head, node *input);
void removeFirst(node** head);
void deleteList(node** head);
void removeIndex(node** head, int index);



int main() {
	node* head = NULL;

	populateList(&head);
	solveRecursive(&head, &head);
	deleteList(&head);
}

node* inputToNode(const char *input) {
	// function was already given, won't explain

    int number = atoi(input);
    if (number != 0) {
        return createNumberNode(number);
    }
    if (input[0] == '0') {
        return createNumberNode(0);
    }
    if (strcmp(input, "(") == 0 ||
        strcmp(input, ")") == 0) {
        return createParenthesisNode(input[0]);
    }

    if (strcmp(input, "+") == 0 ||
        strcmp(input, "-") == 0 ||
        strcmp(input, "*") == 0 ||
        strcmp(input, "/") == 0) {
        return createOperatorNode(input[0]);
    }
    return NULL;
}

node* createParenthesisNode(char operator) {
	node* head = createCharNode(operator);
	head->type = 3;
	return head;
}

node* createOperatorNode(char operator) {
	node* head = createCharNode(operator);
	head->type = 2;
	return head;
}

node* createCharNode(char operator) {
	node* head = malloc(sizeof(node));
	head->operator = operator;
	return head;
}

node* createNumberNode(int number) {
	node* head = malloc(sizeof(node));
	head->number = number;
	head->type = 1;
	return head;
}

void populateList(node** head) {
	while(1) {
		char input[12]; // int can be -2147483648 to 2147483647, '-2147483648' is 11 characters
		printf("\nInput: ");
		scanf("%11s", input);
		if(*input == '=') {
			break;
		}
		addLast(head, inputToNode(input));
		printf("\nTerm: ");
		printList(head);
	}
}

void solveRecursive(node** head, node** printHead) { // printHead to have a printable head (i.e. the whole list) in recursive calls

	// rant below in German since it isn't code relevant but about the test itself

/* Dieser code dient zur normalen Berechnung, im Zwischentest wird aber rückwärts gerechnet 🤡
 *
 *  for(node** nextParenthesis = findOpenParenthesisHead(head); nextParenthesis; nextParenthesis = findOpenParenthesisHead(head)) {
 *		solveRecursive(&((*nextParenthesis)->next), printHead);
 *
 *		removeFirst(nextParenthesis);
 *		removeFirst(findOperator(head, ')'));
 *	}
 *  solveOperations(head, printHead, 1);
 *	solveOperations(head, printHead, 0);
 * 
 *
 *
 * ### Erklärung: ###
 *
 * Intuitiv macht es natürlich Sinn die Berchnung von hinten zu beginnen, um
 *   verschachtelte Klammern aufzulösen, allerdings hat das ganze den kleinen
 *   Schönheitsfehler, dass die Liste nur in eine Richtung verlinkt ist. Daher
 *   muss bei jeder Klammer die Liste wieder von vorne bis hinten durchgegangen
 *   werden, was extrem ineffizient ist.
 *
 * Der untenstehende Code besteht zwar die automatische Überprüfungen mit
 *   ähnlicher Effizients, es ist jedoch extrem Schade, dass ein Code wie der
 *   obige, der zu dem selben Endresultat führt, aber nicht unnötig genauen
 *   Bedienungen entspricht, nicht erlaubt ist, oder, eigentlich noch schlimmer,
 *   mit dem Vorschlag auf Moodle die Funktion "findLastParenthesisOpen()" ein
 *   - wie im obigen Absatz erläutet - extrem ineffiezienter Programierstil
 *   angeregt wird.
 *
 */

	// find next parenthesis, if there is one, call this function again starting from right after it
	node** nextParenthesis = findOpenParenthesisHead(head);
	if(nextParenthesis) {
		solveRecursive(&((*nextParenthesis)->next), printHead);
 
		removeFirst(nextParenthesis);
		removeFirst(findOperator(nextParenthesis, ')'));
	}

	// solve the last set of operations. code will only get here when next layer of recursion is solved

 	solveOperations(head, printHead, 1);
	solveOperations(head, printHead, 0);
}

void solveOperations(node** head, node** printHead, int point) {
	void (*operations[4])(node**) = {&multiplication, &division, &addition, &subtraction};

	for(node** operation = findOperation(head, point); operation; operation = findOperation(head, point)) {
		int type = 0;
		switch((*operation)->next->operator) { // position in array operations
			case '-': type++;
			case '+': type++;
			case '/': type++;
		}
		(*operations[type])(operation);

		removeIndex(operation, 2);
		removeIndex(operation, 1);

		printf("\nResulting term: ");
		printList(printHead);
	}
}

void multiplication(node** leftSide) {
	(*leftSide)->number *= (*leftSide)->next->next->number;
}

void division(node** leftSide) {
	if((*leftSide)->next->next->number == 0)
		(*leftSide)->next->next->number = 1;
	(*leftSide)->number /= (*leftSide)->next->next->number;
}

void addition(node** leftSide) {
	(*leftSide)->number += (*leftSide)->next->next->number;
}

void subtraction(node** leftSide) {
	(*leftSide)->number -= (*leftSide)->next->next->number;
}

node** getIndexHead(node** head, int index) {
	node** headPt = head;
	for(int i = 0; i < index; i++) {
		headPt = &((*headPt)->next);
	}
	return headPt;
}

node** findOperator(node** head, char operator) {
	node** headPt = head;
	for(; (*headPt); headPt = &((*headPt)->next)) {
		if((*headPt)->operator == operator) {
			return headPt;
		}
	}
	return NULL;
}

node** findOpenParenthesisHead(node** head) {
	for(node** headPt = head; *headPt; headPt = &((*headPt)->next)) {

	/*
	 *  Wegen Änderungen in solveRecursive nicht mehr erforderlich
	 *
	 *	if((*headPt)->operator == ')') {
	 *		break;
	 *	}
	 */

		if((*headPt)->operator == '(') {
			return headPt;
		}
	}
	return NULL;
}

node** findOperation(node** head, int point) {
	node** headPt = head;
	for(; (*headPt)->next; headPt = &((*headPt)->next)) {
		int type = 0;
		switch((*headPt)->next->operator) {
			default: continue; // default = a number
			case ')': return NULL; // out of scope for the current set of parenthesis
			case '-': type++;
			case '+': type++;
			case '/': type++;
			case '*':; // no default for '*'
		}

		if(type >= 2 - 2 * point && type <= 3 - 2 * point)
			return headPt;
	}
	return NULL; // no operation found
}

void printList(node** head) {
	for(node* temp = *head; temp; temp = temp->next) {
		if(temp->type == 1)
			printf("%d", temp->number);
		else
			printf("%c", temp->operator);
	}
}

void addFirst(node** head, node* input) {
	input->next = *head;
	*head = input;
}

void addLast(node** head, node* input) { 
	if(!*head)
		addFirst(head, input);
	else{
		node* tempHead;
		for(tempHead = *head; tempHead->next; tempHead = tempHead->next);
		input->next = NULL;
		tempHead->next = input;
	}
}

void removeFirst(node** head){
	node* temp = *head;
	*head = (*head)->next;
	free(temp);
}

void deleteList(node** head){
	while(*head) {
		removeFirst(head);
	}
	*head = NULL;
}

void removeIndex(node** head, int index) {
	removeFirst(getIndexHead(head, index));
}