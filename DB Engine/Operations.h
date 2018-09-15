#include "ReadWrite.h"
#define TYPESIZE 3
char TYPE[10][20] = {"int","char","lint"};
char *removePart(char *c, int i){
	if (c == NULL||i==0){
		return NULL;
	}
	int j = 0;
	char *ret = (char*)malloc(sizeof(char)*strlen(c) + 5 - i);
	while (c[j + i] != '\0'){
		ret[j] = c[i + j];
		j++;
	}
	ret[j] = '\0';
	return ret;
}
char* stringTok(char *t, char dl){
	if (t == NULL){
		return NULL;
	}
	char *ret = (char*)malloc(sizeof(char)*strlen(t) + 5);
	int i = 0;
	while (t[i] != '\0'&&t[i] != dl){
		ret[i] = t[i];
		i++;
	}
	ret[i] = '\0';
	return ret;
}

void commandCreate(TN **tn,char *command){
	int i = 0;
	char *t;
	char c[50]="\0";
	t = stringTok(command, ' ');
	command = removePart(command, strlen(t) + 1);
	t = stringTok(command, ';');
	strcpy(c, t);
	command = removePart(command, strlen(t) + 1);
	*tn = createTN(c, 32);
	return;
}

int positionOfChar(char *c, char d){
	int i = 0;
	while (c[i] != '\0'){
		if (c[i] == d){
			return i;
		}
		i++;
	}
	return -1;
}




Col* addRow(char *tok,int current){
	Col*head=NULL;
	char *ct = (char*)malloc(sizeof(char)*strlen(tok) + 5);
	char cn[30] = "\0";
	strcpy(ct, tok);
	Col *col =head;
	char *k;
	while (ct != NULL){
		k = stringTok(ct, '=');
		ct = removePart(ct, strlen(k) + 1);
		strcpy(cn, k);
		if (ct == NULL){
			return NULL;
		}
		k = stringTok(ct, ' ');
		CNode *tc = createCNode(current, k);
		if (col == NULL){
			col = createCol(cn);
			col->value = tc;
			head = col;
			if (strcmp(k, ct) == 0){
				return head;
			}
			ct = removePart(ct, strlen(k) + 1);
			continue;
		}
		Col *tempc = createCol(cn);
		col->nextColumn = tempc;
		tempc->value = tc;
		col = col->nextColumn;
		if (strcmp(k, ct) == 0){
			return head;
		}
		ct = removePart(ct, strlen(k) + 1);
	}
	return head;
}

void updateRow(Col *des, Col *sou){
	Col *t = des;
	while (sou != NULL){
		Col *last = t;
		Col *pre = NULL;
		while (last!=NULL){
			if (strcmp(last->columnName, sou->columnName) == 0){
				insertCNode(last,sou->value);
				break;
			}
			pre = last;
			last = last->nextColumn;
		}
		if (last == NULL){
			pre->nextColumn = sou;
			sou=sou->nextColumn;
			pre->nextColumn->nextColumn=NULL;
			continue;
		}
		sou = sou->nextColumn;
	}
	return;
}

void commandPut(TS *ts, TN *t, char *command){
	int i = 0;
	char *tok;
	char *ct = (char*)malloc(sizeof(char)*strlen(command) + 5);
	strcpy(ct, command);
	char c[50] = "\0";
	char c1[50] = "\0";
	char c2[50] = "\0";
	tok = stringTok(ct, ' ');
	ct = removePart(ct, strlen(tok) + 1);
	tok = stringTok(ct, ' ');
	ct = removePart(ct, strlen(tok) + 1);
	strcpy(c1, tok);
	if (c1[strlen(c1) - 1] == ' ')
		c1[strlen(c1) - 1] = '\0';
	if (strcmp(c1, t->tableName) != 0){
		printf("\tTable Unknown.\n");
		return;
	}
	tok = stringTok(ct, '=');
	ct = removePart(ct, strlen(tok) + 1);
	c[0] = '\0';
	strcpy(c, tok);
	if (strcmp(c, "key") != 0){
		printf("\tKey is missing.\n");
		return;
	}
	tok = stringTok(ct, ' ');
	ct = removePart(ct, strlen(tok) + 1);
	c1[0] = '\0';
	strcpy(c1, tok);
	RN *r=searchKeyInTN(t,c1);
	Col *col = NULL;
	if (r == NULL){
		col= addRow(ct,1);
		if (col == NULL){
			return;
		}
		RN *r = createRN(col, c1);
		r->current = 1;
		insertIntoTN(t, r);
		r->commit = r->current;
		return;
	}
	if (r->commit - 2 >= r->current){
		return;
	}
	r->current = r->current + 1;
	col = addRow(ct,r->current);
	if (col == NULL){
		r->current = r->current -  1;
		return;
	}
	updateRow(r->col, col);
	r->commit = r->current;
	return;
}


void stringCopy(char *d, char *s){
	int i = 0;
	while (s[i] != '\0'){
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return;
}

void commandGet(TN *t, char *command){
	int i = 0;
	char *tok;
	RN *r = NULL;
	char *ct = (char*)malloc(sizeof(char)*strlen(command) + 5);
	stringCopy(ct, command);
	tok = stringTok(ct, ' ');
	ct = removePart(ct, strlen(tok) + 1);
	tok = stringTok(ct, ' ');
	ct = removePart(ct, strlen(tok) + 1);
	if (strcmp(t->tableName, tok)!= 0){
		return;
	}
	tok = stringTok(ct, ';');
	ct = removePart(ct, strlen(tok) + 1);
	if (strcmp(tok, "all")==0){
		RN **rn = t->nodes;
		int j = 0;
		for (i = 0; i < t->ind; i++){
			displayRN(rn[i]);
		}
		return ;
	}
	r = searchKeyInTN(t, tok);
	if (r == NULL){
		printf("\tInvalid Key.\n");
		return;
	}
	displayRN(r);
	return ;
}

void commandDelete(TN *t, char *command){
	int i = 0;
	char *tok;
	char *ct = (char*)malloc(sizeof(char)*strlen(command) + 5);
	stringCopy(ct, command);
	tok = stringTok(ct, ' ');
	ct = removePart(ct, strlen(tok) + 1);
	tok = stringTok(ct, ' ');
	ct = removePart(ct, strlen(tok) + 1);
	if (strcmp(t->tableName, tok) != 0){
		return;
	}
	tok = stringTok(ct, ';');
	ct = removePart(ct, strlen(tok) + 1);
	RN **r = t->nodes;
	int j = 0;
	for (i = 0; i < t->ind; i++){
		if (strcmp(r[i]->key, tok) == 0){
			if (t->ind == 1){
				t->ind = 0;
				return;
			}
			for (j = i; j < t->ind-1; j++){
				r[j] = r[j + 1];
			}
			t->ind = t->ind - 1;
		}
	}
	return;
}
