#include "ex5.h"


// void printConf(bool a[HOLES]);
int readNextInt(FILE *fp);
unsigned short getNextConf(int hit, unsigned short current);

int main(int argc, char *argv[]) {

	//---------------------- INITIALISATION PART ----------------------//
	
	FILE *fp = fopen("input.txt","r");
	if (fp == NULL) {
		printf("No file found.\n");
		while ((fp = fopen("input.txt","r")) == NULL )
			sleep(3);
	}

	int nextInt, i, whacked[MAXVAL];
	unsigned short first = 0, parent[MAXVAL], current = 1;
	bool seen[MAXVAL], found = false;
		
	while((nextInt = readNextInt(fp)) != 0)
		SET(first, nextInt);

	parent[first] = first;

	whacked[first] = 0;

	//------------------------ ALGORITHM PART ------------------------ //

	enqueue(first);
	while (!found){
		
		current = dequeue();
		seen[current] = true;
		found = true;
		
		for (i=0; i < HOLES; i++) {

			if ((current >> i) & 1) {

				found = false;
				unsigned short new = getNextConf(i+1, current);
				
				if (!(seen[new])) {
					
					// printf("queuing %d\n", new);
					parent[new] = current;
					whacked[new] = i+1;
						
					enqueue(new);
					
				}
				
			}
			
		}
		
	}
	
	while(current != first)	{
		
		printf("%i\t", whacked[current]);
		current = parent[current];
	
	}
	
	printf("\n");
	//  scanf("%d", &i);
	fclose(fp);
	return 0;
	
}

// readNextInt: Return next integer from input file
int readNextInt(FILE *fp) {
	
	int in, out = 0;

	for (in = fgetc(fp); !isdigit(in) && in != EOF ; in = fgetc(fp))
		;

	for ( ; isdigit(in); in = fgetc(fp))
		out = 10*out + (in-'0');
		
	return out;
	
}

// getNextConf: Return the result of hitting current at hit 
unsigned short getNextConf(int hit, unsigned short current) {
	
	//printf("HITING AT %d\n", hit);
	
	TOGGLE(current, hit);
	
	if(hit > 4)
		TOGGLE(current, (hit-4));
	if(hit < 13)
		TOGGLE(current, (hit+4));
	if(hit % 4 != 1)
		TOGGLE(current, (hit-1));
	if(hit % 4 != 0)
		TOGGLE(current, (hit+1));

	return current;
	
}

/*
 * printConf: print current visibility of moles in a[]
 * 
 *void printConf(bool a[HOLES]) {
 *	
 *	int i;
 *	
 *	printf("\n");
 *	
 *	for (i = 0; i < HOLES; i++)
 *		if(a[i] == 1)
 *			printf("%d\t", i);
 *	
 *	printf("\n");
 *	
 *	for (i = 0; i < HOLES; i++) {
 *		
 *		if (a[i] == 1)
 *			printf("1");
 *		else
 *			printf("0");
 *			
 *		if (i%4 == 3)
 *			printf("\n");
 *			
 *	}
 *	
 *	printf("\n");
 *
 *}
 */

