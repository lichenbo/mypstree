#include "mypstree.h"
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
	printList();
	return 0;
}
