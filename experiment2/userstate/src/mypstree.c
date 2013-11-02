#include "mypstree.h"

int hasChild(Dirstruct *current) {
	return (current->child!=NULL);
}
Dirstruct* getChild(Dirstruct *current) {
	assert(hasChild(current));
	return current->child;
}
int hasNext(Dirstruct *current) {
	return (current->next!=NULL);
}
Dirstruct* getNext(Dirstruct *current) {
	assert(hasNext(current));
	return current->next;
}
void insertNeighbour(Dirstruct *current, Dirstruct *root) {
	assert(root!=NULL && current!=NULL);
	current->next = root->next;
	root->next = current;
}
void insertChild(Dirstruct *current, Dirstruct *parent) {
	assert(parent!=NULL && current != NULL);
	current->next = parent->child;
	parent->child = current;
}
void insertChildByPPid(Dirstruct *current, int ppid) {
	Dirstruct *parent = searchByPid(head, ppid);
	printf("parrentAddress:%p\n",parent);
	if (parent == NULL) {
		parent = (Dirstruct*)malloc(sizeof(Dirstruct));
		parent->pid = ppid;
		insertChild(parent, head);
		insertChild(current, parent);
	}
	else {
		assert(ppid == parent->pid);
		insertChild(current,parent);
	}
	assert(parent->child == current);
}
void removeHeadLink(Dirstruct *current) {
	assert(hasChild(head));
	Dirstruct *temp;
	Dirstruct *temp_before = head;
	for (temp = head->child;;temp = getNext(temp)) {
		if (temp == current) {
			if (temp_before == head) {
				temp_before->child = temp->next;
			}
			else {
				temp_before->next = temp->next;
			}
			return;
		}
		temp_before = temp;
	}
}


Dirstruct* searchByPid(Dirstruct *current, int pid) {
	Dirstruct* temp= NULL;
	Dirstruct* temp_result = NULL;
	assert(current != NULL);
	if (current->pid == pid) return current;	
	else if (!hasChild(current)) return NULL;
	else {
		for (temp = getChild(current);temp_result==NULL;temp=temp->next) {
			if (temp == NULL) {
				return NULL;
			}
			printf("%d\t",temp->pid);
			getchar();
			printf("recursion begin");
			temp_result = searchByPid(temp,pid);	
		}
		return temp_result;
	}
	/* should never reach */
	assert(1==2);
}

/* filter the directory that only named with digits  */
int filterdir(const struct dirent* dirstruct) {
	char *p;
	strtol(dirstruct->d_name, &p, 10);
	if (dirstruct->d_type == DT_DIR && !(*p)) {
		return 1;
	}
	return 0;
}
void analysefile(char* dirname) {
	char statuspath[80];
	int pid = 0;
	int ppid = 0;
	char *line = NULL;
	char *name = malloc(100);
	size_t len = 0;
	ssize_t read;
	strcpy (statuspath, "/proc/");
	strcat (statuspath, dirname);
	strcat (statuspath, "/status");
	FILE *statusfile = fopen(statuspath,"r");
	assert(statusfile!=NULL);
	while ((read = getline(&line, &len, statusfile)) != -1) {
		sscanf(line, "Pid:\t%d", &pid);
		sscanf(line, "PPid:\t%d", &ppid);
		sscanf(line, "Name:\t%s", name);
	}
	assert(pid != 0);
	printf("%d\t%d\t%s\n",pid,ppid,name);
	free(line);
	fclose(statusfile);

	Dirstruct *dirnode = searchByPid(head, pid);
	if (dirnode != NULL) {
		dirnode->name = name;
		removeHeadLink(dirnode);
		insertChildByPPid(dirnode, ppid);
	}
	else {
		dirnode = (Dirstruct*)malloc(sizeof(Dirstruct));
		dirnode->pid = pid;
		dirnode->name = name;
		dirnode->next = NULL;
		dirnode->child = NULL;
		insertChildByPPid(dirnode, ppid);
	}
}
void printList() {
	assert((head->child)!=NULL);
	printNode(head->child);
}
void printNode(Dirstruct* node) {
	printf("%d\t%s\n",node->pid,node->name);
	if (hasChild(node)) 
		printNode(node->child);
	if (hasNext(node))
		printNode(node->next);
	return;
}
