#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "p1_memory.h"

void MInit(Memory * memory, int len, void (*pageReplacementAlgorithm)(Memory*, char)){
	int i = 0;
	
	memory->cur = 0;
	memory->len = len;
	memory->inputCount = 0;
	
	for(i=0;i<memory->len;i++){
		memory->refBits[i] = 0;
	}

	for(i=0;i<memory->len;i++){
		memory->mem[i] = 0;
	}

	memory->pageReplacementAlgorithm = pageReplacementAlgorithm;

	memory->pageReferenceString = 0x0;
}

int MIsFull(Memory * memory){
	if(memory->inputCount >= memory->len) return 1;
	else return 0;
}

int moveCur(Memory * memory){
	(memory->cur)++;
	if(memory->cur == memory->len)
		memory->cur = 0;
}

int MInsert(Memory * memory, char item){
	if(MIsFull(memory)){
		fprintf(stderr, "memory is full\n");
		exit(0);
	}
	
	memory->mem[memory->cur] = item;
	
	memory->refBits[memory->cur] = 1;

	moveCur(memory);
	memory->inputCount++;

	return 1;
}

void MShowMemory(Memory * memory){
	int i=0;
	
	for(i=0;i<memory->len;i++){
		printf("%c ", memory->mem[i]);
	}

	printf("| ");

	for(i=0;i<memory->len;i++){
		printf("%d ", memory->refBits[i]);
	}

	printf("\n");	
}

//for MRederence
int sequentialSearch(char * string, char target){
	int idx=0;

	while(string[idx]!='\0'){
		if(string[idx] == target) return idx;
		else idx++;
	}
	
	return -1;
}

void pageReplacement_FIFO(Memory * memory, char page){
	memory->mem[memory->cur] = page;
	
	moveCur(memory);
}

void pageReplacement_secondChance(Memory * memory, char page){
	//implement LRU - secondChance algorithm
	while(1){
		if(memory->refBits[memory->cur] == 1){
			memory->refBits[memory->cur] = 0;
			moveCur(memory);
		}
		else if(memory->refBits[memory->cur] == 0){
			memory->mem[memory->cur] = page;
			memory->refBits[memory->cur] = 1;
			moveCur(memory);
			break;
		}
		else{
			fprintf(stderr, "refBits are set to value other than bool\n");
			exit(0);
		}
	}
}

int MReference(Memory * memory, char page){
	int idx;

	//search memory 
	if((idx = sequentialSearch(memory->mem, page))!=-1){
	//if exist
		memory->refBits[idx] = 1;
		return 0;
	}
	//if not exist
	else{
		//if memory is full
		if(memory->inputCount >= memory->len){
			//page replacement
			memory->pageReplacementAlgorithm(memory, page);
			return 1;
		}
		//if memory is not full
		else{
			MInsert(memory, page);
			return 1;
		}
	}
	return 0;
}


//for optimal page replacement
void MSetPageReferenceString(Memory * memory, char * pageReferenceString){
	memory->pageReferenceString = pageReferenceString;
}

void pageReplacement_optimal(Memory * memory, char page){
	
	int i=0;
	int h=0;

	//check if memory->pageRerenceString is set
	if(memory->pageReferenceString == 0x0){
		fprintf(stderr, "pageReferenceString is not set.\n Use MSetPageReferenceString() to set the pageReferenceString");
	


}

