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

int hasChild(Dirstruct *current) {
	return (current->child!=NULL);
}
Dirstruct* getChild(Dirstruct *current) {
	return current->child;
}
int hasNext(Dirstruct *current) {
	return (current->next!=NULL);
}
Dirstruct* getNext(Dirstruct *current) {
	return current->next;
}
void insertNeighbour(Dirstruct *current, Dirstruct *root) {
	assert(root!=NULL && current!=NULL);
	current->next = root->next;
	root->next = current;
}
void insertChild(Dirstruct *current, Dirstrut *parent) {
	assert(parent!=NULL && current != NULL);
	current->next = parent->child;
	parent->child = current;
}


Dirstruct* searchByPid(Dirstruct *current, int pid) {
	Dirstruct* temp= NULL;
	Dirstruct* temp_result = NULL;
	if (current->pid == pid) return current;	
	else if (!hasChild(current)) return NULL;
	else {
		for (temp = getChild(current);temp_result==NULL;temp=temp->next) {
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

	if (searchByPid(head, pid) != NULL) {
		
	}
	else {
		Dirstruct *dirnode = (Dirstruct*)malloc(sizeof(Dirstruct));

	}
	
}
int main(){
	/* Head init */
	head = (Dirstruct*)malloc(sizeof(Dirstruct));
	head->pid=0;
	head->name="never appeared";
	head->next=NULL;
	head->child=NULL;
	char* procdir = "/proc";
	struct dirent **namelist;
	int n = 0;
	n = scandir(procdir,&namelist,filterdir,alphasort);
	if (n < 0)
		printf("scandir");
	else {
		while (n--) {
			analysefile(namelist[n]->d_name);
			free(namelist[n]);
		}
		free(namelist);
	}
	return 0;
}
