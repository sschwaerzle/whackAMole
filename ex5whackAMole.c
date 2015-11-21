#include "ex5.h"

// short chainLength[MAXVAL];
// void printConf(bool a[HOLES]);
int readNextInt(FILE *fp);
void getNextConf(int hit, bool current[16], bool (*new)[16]);
unsigned short boolToShort(bool currentAr[16]);


int main(int argc, char *argv[]) {
	
	FILE *fp = fopen("input.txt","r");
	if (fp == NULL) {
		printf("No file found.\n");
		while ((fp = fopen("input.txt","r")) == NULL )
			sleep(3);
	}

	int nextInt, i, j;
	bool conf[MAXVAL][HOLES], currentAr[HOLES], seen[MAXVAL], found = false;
	
	for (i = 0; i < HOLES; i++)
		currentAr[i] = false;

	while((nextInt = readNextInt(fp)) != 0)
		currentAr[nextInt-1] = true;
		
	unsigned short parent[MAXVAL], current = 1, first=boolToShort(currentAr);
	
	enqueue(first);
	parent[first] = first;
	
	for(i = 0; i < HOLES; i++)
		conf[first][i] = currentAr[i];

	char whacked[MAXVAL];		
	whacked[first] = 0;
	
	while (!found){
		
		current = dequeue();
		seen[current] = true;
		found = true;
		
		for (i = 0; i < HOLES; i++) {
			
			bool new[HOLES];
			
			if (conf[current][i]) {
				
				found = false;
				getNextConf(i, conf[current], &new);
				unsigned short newVal = 0;
				newVal = boolToShort(new);
				
				if (!(seen[newVal])) {
					
					//	  printf("queuing %d\n", newVal);
					parent[newVal] = current;
					whacked[newVal] = i;
				
					for (j = 0; j < HOLES; j++) 
						conf[newVal][j]  = new[j];
						
					enqueue(newVal);
					
				}
				
			}
			
		}
		
	}
	
	while(current != first)	{
		
		printf("%d\t",whacked[current]+1);
		current = parent[current];
	
	}
	
	printf("\n");
	//  scanf("%d", &i);
	fclose(fp);
	return 0;
	
}


int readNextInt(FILE *fp) {
	
	int in, out = 0;

	for (in = fgetc(fp); !isdigit(in) && in != EOF ; in = fgetc(fp))
		;

	for ( ; isdigit(in); in = fgetc(fp))
		out = 10*out + (in-'0');
		
	return out;
	
}

void getNextConf(int hit, bool current[HOLES], bool (*new)[HOLES]) {
	
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

unsigned short boolToShort(bool a[HOLES]) {
	
	unsigned short retval = 0;
	int i;
	
	for(i = HOLES-1; i >= 0; i--)
		retval = a[i] ? retval*2 + 2 : retval * 2;

	return retval;
	
}

/*
void printConf(bool a[HOLES]) {
	
	int i;
	
	printf("\n");
	
	for (i = 0; i < HOLES; i++)
		if(a[i] == 1)
			printf("%d\t", i);
	
	printf("\n");
	
	for (i = 0; i < HOLES; i++) {
		
		if (a[i] == 1)
			printf("1");
		else
			printf("0");
			
		if (i%4 == 3)
			printf("\n");
			
	}
	
	printf("\n");

}
*/

