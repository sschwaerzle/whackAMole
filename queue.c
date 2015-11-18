#include "ex5.h"

queueElement **qBack = NULL;
queueElement **qFront = NULL;

qBack = (queueElement **)malloc(sizeof(queueElement **));
qFront = (queueElement **)malloc(sizeof(queueElement **));
(*qFront)= NULL;
(*qBack) = NULL;
(*qFront) = (*qBack);

void enqueue(unsigned short number){
  queueElement * new = NULL;
  new = (queueElement *)malloc(sizeof(queueElement *));
  new -> num = number;
  new -> next = NULL;

  if ((*qBack) == NULL){
    (*qBack) = new;
    (*qFront) = new;
  } else {
    (*qBack) -> next = new;
    (*qBack) = new;
  }
}

unsigned short dequeue(){
  unsigned short retval = (*qFront) -> num;
  queueElement * ptr = (*qFront);
  if ((*qFront) == NULL){
    //    printf("queue underflow!\n");
    return 0;
  }
  if((*qFront) -> next == NULL){
	free(ptr);
	(*qFront) = NULL;
	(*qBack)  = NULL;
      }
  else{
    (*qFront) = (*qFront) -> next;
    free(ptr);
  }
  return retval;
}

