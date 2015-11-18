#include "ex5.h"

bool seen[65536];
unsigned short parent[65536];
char whacked[65536];
bool conf[65536][16];
//short chainLength[65536];
void printConf(bool a[16]);


int main(void){
  FILE *fp = fopen("input.txt","r");

  int nextInt;
  bool currentAr[16];
  int i, j, temp = 0;
  for (i=0; i<16; i++) * (currentAr +i) = false;
  bool found = false;
  unsigned short current = 1;
  unsigned short first;
  for (i=0; i<16; i++){
    currentAr[i] = false;
  }
  nextInt=readNextInt(fp);
  while(nextInt != 0){
    currentAr[nextInt-1] = true;
    nextInt = readNextInt(fp);
  }
  first=boolToShort(currentAr);
  enqueue(first);
  parent[first] = first;
  for(i=0; i<16;i++)
    conf[first][i] = currentAr[i];
  whacked[first] = 0;
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
	  //	  printf("queuing %d\n", newVal);
	  parent[newVal] = current;
	  whacked[newVal] = i;
	  for (j = 0; j < 16; j++) 
	    conf[newVal][j]  = new[j];
	  enqueue(newVal);
	  //	  printf("qBack: %p\n", (*qBack));
	  //	  printf("qFront: %p\n", (*qFront) -> next -> num);
	}
      }
    }
  }
  while(current != first){
    printf("%d\t",whacked[current]+1);
    current = parent[current];
  }
  printf("\n");
//  scanf("%d", &i);
  fclose(fp);
  return 0;
}


int readNextInt(FILE *fp){
  int in = fgetc(fp);
  int out = 0;
  bool stopInt = false;
  bool notStarted = true;
  while(in!=-1 && !stopInt)
    {
      if(isdigit(in)){
	notStarted=false;
	out=10*out + (in-48);
      }
      if(!notStarted && !isdigit(in))
	stopInt=true;
      in = fgetc(fp);
    }
  return out;
}

void getNextConf(char whack, bool current[16], bool (*new)[16]){
  int i, tempval1=whack%4, tempval2=whack/4;
  int whatToChange[5];
  //printf("WHACKING AT %d\n", whack);
  whatToChange[0]=whack;
  for(i=1;i<6;i++)whatToChange[i]=-1;

  switch(tempval1){
  case 0:
    whatToChange[1]=whack+1;
    whatToChange[3]=-1;
    break;
  case 1:
  case 2:
    whatToChange[1]=whack+1;
    whatToChange[3]=whack-1;
    break;
  case 3:
    whatToChange[1]=-1;
    whatToChange[3]=whack-1;
    break;
  }
  switch(tempval2){
  case 0:
    whatToChange[2]=-1;
    whatToChange[4]=whack+4;
    break;
  case 1:
  case 2:
    whatToChange[2]=whack-4;
    whatToChange[4]=whack+4;
    break;
  case 3:
    whatToChange[2]=whack-4;
    whatToChange[4]=-1;
    break;
  }

    for (i = 0; i < 16; i++) (*new)[i]=current[i];

  for (i = 0; i < 6;i++){
    if(whatToChange[i] != -1){
      (*new)[whatToChange[i]] = !( (*new)[whatToChange[i]]);
    }
  }
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

