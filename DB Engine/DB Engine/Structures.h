#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void* allocateMomoryBasedOnSizeAndType(int type,int size){
	void *val=NULL;
	switch (type){
	case 0:
		val = malloc(sizeof(int));
		break;
	case 1:
		val = malloc(sizeof(char)*size);
		break;
	case 2:
		val = malloc(sizeof(long int)*size);
		break;
	}
	return val;
}

typedef struct ColumnNode{
	char *value;
	int version;
	struct ColumnNode *previousVersion;
}CNode;
CNode* createCNode(int version,char *val){
	CNode *node = (CNode*)malloc(sizeof(CNode));
	node->value = (char*)malloc(sizeof(char)*strlen(val) + 10);
	strcpy(node->value, val);
	node->version = version;
	node->previousVersion = NULL;
	return node;
}
typedef struct Column{
	CNode *value;
	int columNumber;
	char *columnName;
	struct Column *nextColumn;
}Col;
Col *createCol(char *cn){
	Col *node = (Col*)malloc(sizeof(Col));
	node->columnName = (char*)malloc(sizeof(char)*strlen(cn) + 10);
	strcpy(node->columnName, cn);
	node->nextColumn = NULL;
	node->columNumber = cn;
	node->value = NULL;
	return node;
}
void insertCNode(Col *col, CNode *cn){
	CNode *cNode = col->value;
	cn->previousVersion = cNode;
	col->value = cn;
	return;
}


typedef struct RowNode{
	char *key;
	int commit;
	int current;
	Col *col;
}RN;

RN* createRN(Col *c,char *key){
	RN *node = (RN*)malloc(sizeof(RN));
	node->col=c;
	node->commit = 0;
	node->current = 0;
	node->key = (char*)malloc(sizeof(char)*strlen(key) + 10);
	strcpy(node->key, key);
	return node;
}

typedef struct TableNode{
	RN **nodes;
	int size;
	int ind;
	char *tableName;
}TN;
TN *createTN(char *tname,int size){
	TN *node = (TN*)malloc(sizeof(TN));
	node->nodes = (RN**)malloc(sizeof(RN*)*size);
	node->ind = 0;
	node->size = size;
	node->tableName = (char*)malloc(sizeof(char)*strlen(tname) + 10);
	strcpy(node->tableName, tname);
	return node;
}
void insertIntoTN(TN *tn, RN *rn){
	if (tn->ind >= tn->size - 1){
		tn->size = tn->size * 2;
		tn->nodes = (RN**)realloc(tn->nodes,sizeof(RN*)*tn->size);
	}
	tn->nodes[tn->ind] = rn;
	tn->ind = tn->ind + 1;
	return;
}
RN* searchKeyInTN(TN *tn, char*key){
	RN **r = tn->nodes;
	int i = 0;
	for (i = 0; i < tn->ind; i++){
		if (strcmp(r[i]->key, key) == 0){
			return r[i];
		}
	}
	return NULL;
}

void printCNode(CNode *c, int commit,char *cn){
	CNode *t = c;
	while (t->version > commit){
		t=t->previousVersion;
	}
	printf("%15s:%15s Version: %d\n", cn,t->value,t->version);
}

void displayRN(RN *r){
	if (r == NULL){
		return;
	}
	printf("\n");
	if (r != NULL){
		printf("%15s:", r->key);
		Col *t = r->col;
		while (t != NULL){
			printCNode(t->value,r->commit,t->columnName);
			printf("%16s", "");
			t=t->nextColumn;
		}
	}
	return;
}
void insertIntoRN(RN *r, Col *col){
	Col *t = r->col;
	while (t != NULL){
		if (t->columNumber == col->columNumber){
			CNode *c1 = t->value;
			CNode *c2 = col->value;
			c2->previousVersion = c1;
			c1->previousVersion;
			t->value = c2;
		}
		t = t->nextColumn;
		col=col->nextColumn;
	}
	return;
}
typedef struct Tables{
	TN **nodes;
	int size;
	int ind;
}TS;
TS* createTS(int size){
	TS *node = (TS*)malloc(sizeof(TS));
	node->ind = 0;
	node->size = size;
	node->nodes = (TN**)malloc(sizeof(TN*)*size);
	return node;
}
void insertIntoTS(TN* tn,TS* ts){
	if (ts->ind >= ts->size - 2){
		ts->size = ts->size * 2;
		ts->nodes = (TN**)realloc(ts->nodes,sizeof(TN*)*ts->size);
	}
	ts->nodes[ts->ind] = tn;
	ts->ind = ts->ind + 1;
	return;
}

TN** searchInTS(char *tn, TS *ts){
	if (ts == NULL){
		return NULL;
	}
	int i = 0;
	for (i = 0; i < ts->ind; i++){
		TN *t = ts->nodes[i];
		if (strcmp(tn, t->tableName) == 0){
			return t;
		}
	}
	return NULL;
}