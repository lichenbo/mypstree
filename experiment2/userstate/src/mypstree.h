#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <assert.h>

typedef struct dirstruct Dirstruct;
struct dirstruct {
	int pid;
	char* name;
	Dirstruct *next;
	Dirstruct *child;
};

Dirstruct *head;

Dirstruct* searchByPid(Dirstruct *current, int pid);
void printNode(Dirstruct* node, int level);
int hasChild(Dirstruct* current);
Dirstruct* getChild(Dirstruct* current);
int hasNext(Dirstruct* current);
Dirstruct* getNext(Dirstruct* current);
void insertNeighbour(Dirstruct* current, Dirstruct* root);
void insertChild(Dirstruct* current, Dirstruct* parent);
void insertChildByPPid(Dirstruct* current, int ppid);
void removeHeadLink(Dirstruct* current);
Dirstruct* searchByPid(Dirstruct* current, int pid);
int filterdir(const struct dirent* dirstruct);
void analysefile(char* dirname);
void printList();
void printNode(Dirstruct* node, int level);