#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "p1_memory.h"

#define PAGE_REFERENCE_STRING_LENGTH 128
#define PAGE_REFERENCE_RANGE 10

//I) FIFO

//2. create page reference generator
//be advicsed it always generates page reference number in range [0,9] as defined in PAGE_REFERENCE_RANGE
//page reference number is stored as char
char * pageReferenceGenerator(){
	//create int array
	char * pageReferenceString = (char*)calloc(sizeof(char), PAGE_REFERENCE_STRING_LENGTH);
	
	//initialize srand
	int i, n;
	time_t t;

	srand((unsigned) time(&t));
	//for each idx in int array, insert rand number beween 1 to PAGE_REFERENCE_STRING_LENGTH
	for(i=0;i<PAGE_REFERENCE_STRING_LENGTH;i++){
		n = rand() % PAGE_REFERENCE_RANGE;
		pageReferenceString[i] = n + '0';
	}
	pageReferenceString[i] = '\0';

	//return int array
	return pageReferenceString;
}

//4. page replacement
int simulate_pageReplacement(Memory * memory, char * pageReferenceString){
	int i=0;
	int pageFaultCount = 0;
	
	//for each reference string
	for(i=0;i<strlen(pageReferenceString);i++){
		//show memory
		sleep(1);

		pageFaultCount += MReference(memory, pageReferenceString[i]);
		MShowMemory(memory);
		printf("page Fault count : %d\n", pageFaultCount);
		
		printf("\n");

		//reference
	}
	//printf("page Fault count : %d\n", pageFaultCount);
	return pageFaultCount;

}

//7. main function
int main(int argc, char * argv[]){
	int iter = 100000;
	char ch=0;
	int i=0;
	
	char * pageReferenceString;

	Memory memory1;
	MInit(&memory1, 5, pageReplacement_FIFO);
	long int pgFaultCount_FIFO = 0;

	Memory memory2;
	MInit(&memory2, 5, pageReplacement_secondChance);
	long int pgFaultCount_secondChance = 0;
/*
	for(i=0;i<iter;i++){
		pageReferenceString = pageReferenceGenerator();

		pgFaultCount_FIFO += simulate_pageReplacement(&memory1, pageReferenceString);

		pgFaultCount_secondChance += simulate_pageReplacement(&memory2, pageReferenceString);
	
		free(pageReferenceString);
	}

	//print stats
	printf("stat of %d iterations:\n", iter);
	printf("FIFO page Fault average : %ld\n", pgFaultCount_FIFO / iter);
	printf("SecondChance page Fault average : %ld\n", pgFaultCount_secondChance / iter);
*/

	//show pageReferenceString
	pageReferenceString = pageReferenceGenerator();
	printf("page reference string generated!\n");
	for(i=0;i<strlen(pageReferenceString);i++){
		printf("%d ", pageReferenceString[i] - '0');
	}
	printf("\n");

	simulate_pageReplacement(&memory2, pageReferenceString);

/*
	char string[10] = {
		'9', '5', '6', '0',
		'4', '4', '9', '8',
		'5', '3'
		};
	
	//show pageReferenceString
	printf("page reference string generated!\n");
	for(i=0;i<strlen(string);i++){
		printf("%d ", string[i] - '0');
	}
	printf("\n");

	simulate_pageReplacement(&memory, string);
*/
	free(pageReferenceString);
}


