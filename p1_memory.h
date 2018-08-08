#ifndef __p1_memory_h__
#define __p1_memory_h__

#define MAX_MEMORYLENGTH 32

typedef struct _memory{
	char mem[MAX_MEMORYLENGTH];
	int refBits[MAX_MEMORYLENGTH]; //for secondChance
	int cur;
	int len;
	int inputCount;
	void (*pageReplacementAlgorithm)(struct _memory*, char);
	
	//for optimal pageReplacement
	char * pageReferenceString;
	int pageReferenceString_cur;
	int found[MAX_MEMORYLENGTH];
	int foundCount;

} Memory;

void MInit(Memory * memory, int len, void (*pageReplacementAlgorithm)(Memory*, char));

int MIsFull(Memory * memory);

int MInsert(Memory * memory, char item);

void MShowMemory(Memory * memory);

int MReference(Memory * memory, char page);

void pageReplacement_FIFO(Memory * memory, char page);

void pageReplacement_secondChance(Memory * memory, char page);

#endif

