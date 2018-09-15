#include "ExecuteCommand.h"
int main(){
	char command[100] = "\0";
	TS *ts = createTS(32);
	FILE *writeLog = fopen("log.txt", "a");
	while (1){
		printf("\n\n\t$");
		fflush(stdin);
		command[0] = "\0";
		scanf("%[^;]s", &command);
		printf("\n");
		executeCommand(&ts , command);
		fprintf(writeLog, "%s %ld", command,time(NULL));
	}
}