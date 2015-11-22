#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


void printConf(bool a[16]);
int readNextInt(FILE *fp);
void getNextConf(char hit, bool current[16], bool (*new)[16]);
unsigned short boolToShort(bool currentAr[16]);
void enqueue(unsigned short number);
unsigned short dequeue();


typedef struct queueElement{
  unsigned short num;
  struct queueElement *next;
}queueElement;

queueElement *qBack = NULL;
queueElement *qFront = NULL;


int main(void){
  FILE *fp = fopen("input.txt","r");
  if(fp == NULL){
    printf("No file found.\n");
    for(;;);
  }

  int nextInt;
  bool currentAr[16];
  int i, j, temp = 0;
  bool found = false;
  unsigned short current = 1;
  unsigned short first;
  bool seen[65536];
  unsigned short parent[65536];
  char hitPosition[65536];
  bool conf[65536][16];


  for (i=0; i<16; i++) *(currentAr + i) = false;
  nextInt=readNextInt(fp);

  while (nextInt != 0){
    printf("%d\t", nextInt);
    currentAr[nextInt-1] = true;
    nextInt = readNextInt(fp);
  }
  
  first=boolToShort(currentAr);
  parent[first] = first;
  hitPosition[first] = 0;
  for (i=0; i<16;i++)
    conf[first][i] = currentAr[i];

  enqueue(first); //start BFS
  while (!found){
    current = dequeue();
    seen[current]=true;
    found=true;
    for (i = 0; i < 16; i++){
      bool  new[16];
      if (conf[current][i])
      {
	found=false;
	getNextConf(i, conf[current], &new);
	unsigned short newVal=0;
	newVal = boolToShort(new);
	if (!(seen[newVal]))
	{
	  parent[newVal] = current;
	  hitPosition[newVal] = i;
	  for (j = 0; j < 16; j++) 
	    conf[newVal][j]  = new[j];
	  enqueue(newVal);
	}
      }
    }
  }

  while(current != first){
    printf("%d\t",hitPosition[current]+1);
    current = parent[current];
  }
  printf("\n");
  fclose(fp);
  return 0;
}


void enqueue(unsigned short number){
  queueElement *new = malloc(sizeof(queueElement));
  new -> num = number;
  new -> next = NULL;

  if (qBack == NULL){ //Zero elements
    qBack = new;
    qFront= new;
  } else { //More than zero elements
    qBack -> next = new;
    qBack = new;
  }
}


unsigned short dequeue(){
  if (qFront == NULL) //Queue underflow
    return 0;
  queueElement *ptr = qFront;
  unsigned short retval = qFront -> num;
  if(qFront -> next == NULL) //One element
	qFront = qBack = NULL;
  else //More than one element
    qFront = qFront -> next;
  free(ptr);
  return retval;
}



int readNextInt(FILE *fp){
  int in = fgetc(fp);
  int out = 0;
  if(!isdigit(in)){
    while(in != -1 && !isdigit(in))
      in = fgetc(fp);
  }
  while(in != -1 && isdigit(in)){
    out=10*out + (in-48);
    in = fgetc(fp);
  }
  return out;
}


void getNextConf(char hit, bool current[16], bool (*new)[16]){
  int i;
  //printf("HITING AT %d\n", hit);
  for(i = 0; i < 16; i++) 
    (*new)[i] = current[i];
  (*new)[hit] = !((*new)[hit]);
  if(hit >= 4)
    (*new)[hit - 4]= !((*new)[hit - 4]);
  if(hit <= 11)
    (*new)[hit + 4]= !((*new)[hit + 4]);
  if(hit % 4 != 0)
    (*new)[hit - 1]= !((*new)[hit - 1]);
  if(hit % 4 != 3)
    (*new)[hit + 1]= !((*new)[hit + 1]);

  //  printConf(*new);
}

unsigned short boolToShort(bool a[16]){
  unsigned short retval=0;
  int i;
  for(i=15; i>=0; i--){
    if(a[i])
      retval++;
    retval*=2;
  }
  return retval;
}

void printConf(bool a[16]){
  int i;
  printf("\n");
  for (i=0; i<16; i++){
    if(a[i] == 1)
      printf("%d\t", i);
  }
  printf("\n");
  for (i=0; i<16; i++){
    if (a[i] == 1)
      printf("1");
    else
      printf("0");
    if (i%4 == 3)
      printf("\n");
  }
  printf("\n");
}

