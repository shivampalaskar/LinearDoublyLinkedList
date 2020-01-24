/*
 ============================================================================
 Name        : LinearDoublyLinkedList.c
 Author      : Shivam Palaskar
 Version     :
 Copyright   : Open source
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *nextNode;
	struct Node *PreNode;
}NODE;

NODE* createNode(int);
NODE* getLastNode();
NODE* get2ndLastNode();
void addNodeAtLast(int);
void addNodeAtFirst(int);
void addNodeAtGivenPos(int,int);
int isEmpty();
int getLength();
int verifyPos(int);
void delFirst();
void delLast();
void delAtPos(int);
void displayNodesRtoL();
void displayNodesLtoR();
int getData();

NODE* head = NULL;

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	int choice, num,pos;
	do {
		printf("\nChose operation to perform : ");
		printf("\n1) Add at First Position");
		printf("\n2) Add at Last Position");
		printf("\n3) Add at given Position");
		printf("\n4) Display Right to Left");
		printf("\n5) display Left to Right");
		printf("\n6) Delete First");
		printf("\n7) Delete Last");
		printf("\n8) Delete at Given Position");
		printf("\n9) Delete All");
		printf("\n10) Length");
		printf("\n11)Exit");
		printf("\n Enter Choice : ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			num = getData();
			addNodeAtFirst(num);
			printf("\n Added Successfully");
			break;
		case 2:
			num = getData();
			addNodeAtLast(num);
			printf("\n Added Successfully");
			break;
		case 3:
			printf("\n Enter Position Number : ");
			scanf("%d",&pos);
			if (verifyPos(pos)) {
				num = getData();
				addNodeAtGivenPos(num,pos);
				printf("\n Added Successfully at %d Position", pos);
			}else
				printf("\n Invalid Position");
			break;
		case 4:
			if(isEmpty())
				printf("\nLinked List is Empty");
			else
				displayNodesRtoL();
			break;
		case 5:
			if (isEmpty())
				printf("\nLinked List is Empty");
			else
				displayNodesLtoR();
			break;
		case 6:
			if (isEmpty())
				printf("\nLinked List is Empty");
			else {
				delFirst();
				printf("\n Successfully Deleted");
			}
			break;
		case 7:
			if (isEmpty())
				printf("\nLinked List is Empty");
			else {
				delLast();
				printf("\n Successfully Deleted");
			}
			break;
		case 8:
			if (isEmpty())
				printf("\nLinked List is Empty");
			else {
				printf("\n Enter Position Number : ");
				scanf("%d", &pos);
				if (verifyPos(pos)) {
					delAtPos(pos);
					printf("\n Successfully Deleted");
				} else
					printf("\n Invalid Position");
			}
			break;
		case 9:
			if (isEmpty())
				printf("\nLinked List is Empty");
			else {
				head=NULL;
				printf("\n Successfully Deleted");
			}
			break;
		case 10:
			printf("\n Length : %d",getLength());
		}
	} while (choice != 11);
	return EXIT_SUCCESS;
}

void delFirst(){
	head = head->nextNode;
}

void delLast(){
	if(getLength()==1)
		head=NULL;
	else {
		struct Node* sndLastNode;
		sndLastNode = get2ndLastNode();
		sndLastNode->nextNode = NULL;
	}
	/*printf("\n &lastNode : %u",&lastNode);
	printf("\n lastNode : %d",*lastNode);
	printf("\n lastNode->data : %d",lastNode->data);
	printf("\n lastNode->nextPtr : %u",lastNode->nextPtr);
	lastNode--;
	printf("\n &lastNode : %u",&lastNode);
	printf("\n lastNode : %d",*lastNode);
	printf("\n lastNode->data : %d",lastNode->data);
	printf("\n lastNode->nextPtr : %u",lastNode->nextPtr);*/
}

void delAtPos(int pos) {
	struct Node* tempPtr;
	tempPtr = head;
	if(pos==1){
		delFirst();
		return;
	} else {
		while ((--pos) > 1) {   // this will give (position-1)th index
			tempPtr = tempPtr->nextNode;
		}
		if (pos == 1) {
			((tempPtr->nextNode)->nextNode)->PreNode = tempPtr;
			tempPtr->nextNode = (tempPtr->nextNode)->nextNode;
		}
	}
}

int isEmpty(){
	if(head==NULL)
		return 1;
	else
		return 0;
}

int getData(){
	int num;
	printf("\n Enter Number : ");
	scanf("%d",&num);
	return num;
}

struct Node* createNode(int num){
	NODE *newNode = (NODE*)malloc(sizeof(NODE));
	newNode->data = num;
	newNode->nextNode=NULL;
	newNode->PreNode=NULL;
	return newNode;
}

void addNodeAtFirst(int num) {
	NODE* newNode;
	NODE* tempPtr;
	newNode = createNode(num);
	if (head == NULL)
		head = newNode;
	else {
		tempPtr = head;
		head = newNode;
		newNode->nextNode = tempPtr;
		tempPtr->PreNode=newNode;
	}
}
void addNodeAtLast(int num){
	struct Node* newNode;
	struct Node* tempPtr;
	newNode = createNode(num);
	if(head == NULL)
		head = newNode;
	else{
		tempPtr = getLastNode();
		tempPtr->nextNode = newNode;
		newNode->PreNode = tempPtr;
	}
}

int verifyPos(int pos){
	if (pos > 0 && pos <= getLength())
		return 1;
	else
		return 0;
}

void addNodeAtGivenPos(int num,int pos){
	struct Node* newNode;
	struct Node* tempPtr;
	newNode=createNode(num);
	tempPtr = head;
		if (pos == 1) {
			addNodeAtFirst(num);
			return;
		}
		while ((--pos) > 1) {  // this will give (position-1)th index
			tempPtr = tempPtr->nextNode;
		}
		if (pos == 1) {
			newNode->nextNode = tempPtr->nextNode;
			tempPtr->nextNode = newNode;
			newNode->PreNode = tempPtr;
		}
	return;
}

int getLength() {
	struct Node* tempPtr = head;
	int len=0;
	while (tempPtr != NULL) {
		len++;
		tempPtr = tempPtr->nextNode;
	}
	return len;
}

struct Node* getLastNode(){
	struct Node* tempPtr;
	tempPtr=head;
	struct Node *lastNode;
	while(tempPtr!=NULL){
		lastNode = tempPtr;
		tempPtr = tempPtr->nextNode;
	}
	return lastNode;
}

struct Node* get2ndLastNode(){
	struct Node* tempPtr=head;
	struct Node *sndLastNode=head;
		while ((tempPtr->nextNode) != NULL) {
			sndLastNode = tempPtr;
			tempPtr = tempPtr->nextNode;
		}
	return sndLastNode;
}

void displayNodesRtoL(){
	struct Node* tempPtr;
	tempPtr=head;
	while(tempPtr!=NULL){
		tempPtr = tempPtr->nextNode;
	}
}

void displayNodesLtoR(){
	struct Node* tempPtr;
	tempPtr=getLastNode();
	while(tempPtr!=NULL){
		printf("%d ",tempPtr->data);
		tempPtr = tempPtr->PreNode;
	}
}
/*
struct Node* createNode(int num){ // We can't create new node like this because new node will be created as local variable
	struct Node newNode;
	newNode.data = num;
	newNode.nextPtr = NULL;
	printf("\n &newNode : %u",&newNode);
	printf("\n newNode : %u",newNode);
	printf("\n &newNode.data : %u",&newNode.data);
	return &newNode;
}*/

