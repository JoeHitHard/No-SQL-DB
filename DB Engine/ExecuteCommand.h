#include "Operations.h"
#define COMMANDSIZE 4
char COMMANDS[10][100] = { "create", "put","get","delete" };
int getCommandCode(char *command){
	int i = 0;
	for (i = 0; i < COMMANDSIZE; i++){
		if (strcmp(COMMANDS[i], command) == 0){
			return i;
		}
	}
	return -1;
}
void executeCommand(TS **ts,char *command){
	char tok[100] = "\0";
	char table[100] = "\0";
	sscanf(command, "%s%s", tok,table);
	TN *tn = searchInTS(table,*ts);
	int cc = getCommandCode(tok);
	switch (cc){
	case 0:
		if (tn != NULL){
			printf("\tTable Already Exists.\n");
			return;
		}
		commandCreate(&tn, command);
		insertIntoTS(tn, *ts);
		printf("\tTable \"%s\" Has been created.\n",table);
		break;
	case 1:
		if (tn == NULL){
			printf("\tTable dose not Exists.\n");
			return;
		}
		commandPut(*ts, tn, command);
		printf("\tRow Inserted.\n");
		break;
	case 2:
		if (tn == NULL){
			printf("\tTable dose not Exists.\n");
			return;
		}
		commandGet(tn, command);
		printf("\n");
		break;
	case 3:
		if (tn == NULL){
			printf("\tTable dose not Exists.\n");
			return;
		}
		commandDelete(tn, command);
		printf("\tRow Deleted.\n");
		break;
	}
	int i = 0;
	return 1;
}
/*
create users;
put users key=joe id=joe1 age=18;
*/