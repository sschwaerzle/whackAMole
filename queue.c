#include "ex5.h"

queueElement **qBack = NULL;
queueElement **qFront = NULL;

void enqueue(unsigned short number){
  queueElement * new = NULL;
  new = (queueElement *)malloc(sizeof(queueElement *));
  new -> num = number;
  new -> next = NULL;

  if ((*qBack) == NULL){
    (*qBack) = new;
    (*qFront)= new;
  } else {
    (*qBack) -> next = new;
    (*qBack) = new;
  }
}

unsigned short dequeue(){
  queueElement * ptr = (*qFront);
  if ((*qFront) == NULL){
    //    printf("queue underflow!\n");
    return 0;
  }
  unsigned short retval = (*qFront) -> num;
  if((*qFront) -> next == NULL){
	free(ptr);
	(*qFront) = (*qBack) = NULL;
      }
  else{
    (*qFront) = (*qFront) -> next;
    free(ptr);
  }
  return retval;
}

