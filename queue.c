#include "ex5.h"

void enqueue(unsigned short number);
unsigned short dequeue();

typedef struct queueElement {
	unsigned short num;
	struct queueElement *next;
} queueElement;

static queueElement *qFront = NULL; // foremost element in queue
static queueElement *qBack = NULL; // rearmost element in queue

void enqueue(unsigned short number) {
	
	queueElement *new = malloc(sizeof(queueElement));
	new->num = number;
	new->next = NULL;

	if (qFront == NULL) {
		qFront = new;
	} else {
		qBack->next = new;
	}

	qBack = new;
	
}

unsigned short dequeue() {

	if (qFront == NULL)
		//    printf("queue underflow!\n");
		return 0;

	queueElement *ptr = qFront;
	unsigned short retval = qFront->num;

	if(ptr->next == NULL)
		qFront = qBack  = NULL;
	else
		qFront = ptr->next;
	
	free(ptr);
	return retval;

}
