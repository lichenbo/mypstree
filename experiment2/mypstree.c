#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <assert.h>
struct dirstruct {
	int pid;
	struct distruct *next;
	struct distruct *child;
};
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
	strcpy (statuspath, "/proc/");
	strcat (statuspath, dirname);
	strcat (statuspath, "/status");
	FILE *statusfile = fopen(statuspath,"r");
	while (!feof(statusfile)) {
		fscanf(statusfile, "Pid:\t%d", &pid);
		fscanf(statusfile, "PPid:\t%d", &ppid);
	}
	assert(pid != 0);
	assert(ppid != 0);
	printf("%d\t%d",pid,ppid);
	fclose(statusfile);

}
int main(){
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
