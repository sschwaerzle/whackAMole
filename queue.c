#include "ex5.h"

typedef struct queueElement{
  unsigned short num;
  struct queueElement * next;
}queueElement;

extern void enqueue(unsigned short number);
extern unsigned short dequeue();


queueElement **qBack = NULL;
queueElement **qFront = NULL;

void enqueue(unsigned short number){
  queueElement * new = NULL;
  new = (queueElement *)malloc(sizeof(queueElement *));
  new -> num = number;
  new -> next = NULL;

  if ((*qBack) == NULL){ //Zero elements
    (*qBack) = new;
    (*qFront)= new;
  } else { //More than zero elements
    (*qBack) -> next = new;
    (*qBack) = new;
  }
}

unsigned short dequeue(){
  queueElement * ptr = (*qFront);
  if ((*qFront) == NULL){ //Queue underflow
    return 0;
  }
  unsigned short retval = (*qFront) -> num;
  if((*qFront) -> next == NULL){ //One element
	free(ptr);
	(*qFront) = (*qBack) = NULL;
      }
  else{ //More than one element
    (*qFront) = (*qFront) -> next;
    free(ptr);
  }
  return retval;
}

