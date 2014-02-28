#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <string.h>
#include <string>

using namespace std;

#define MAX_RESULT 50000
#define FORMAT_LENGTH 80
#define DIRECTORY "C:\\Users\\Lab\\"
#define COMMAND_PATTERN "(%d %d->%d %d);"
#define N 21
#define M 20
#define S 15

/*
	FILE OPERATION
*/

char* createAsolutePath(char *path) {
	char *result = new char[MAX_RESULT];
	strcpy(result, "");
	strcat(result,	DIRECTORY);
	strcat(result,	path);
	return result;
}

int** generateTables(int n, int s, int rangeRandom);
char* getFormatTable(int **table, int n, int m, int s);
/*
	Read File
*/

char* readFromFile(char *path, char *pattern) {
	char result[MAX_RESULT];
	
	path = createAsolutePath(path);
	FILE *file;
	file = fopen(path, "r");
	if (file == NULL) {
		return "";
	}

	int name;
	while (fscanf(file, pattern, &name) == 1) {
		printf("%d\n", name);
	}
	
	fclose(file);

	return result;
}

/*
	1. Read Command
*/
int** transitionTable;
int** stateTable;
void readCommand(char *path, int n, int m, int s) {
	transitionTable = generateTables(n, s, m);
	stateTable = generateTables(n, s, s);
	
	path = createAsolutePath(path);
	FILE *file;
	file = fopen(path, "r");
	if (file == NULL) {
		return;
	}

	int x = 0;
	int y = 0;
	int q1 = 0;
	int q2 = 0;
	while (fscanf(file, COMMAND_PATTERN, &x, &q1, &y, &q2) == 4) {
		transitionTable[x][q1] = y;
		stateTable[x][q1] = q2;
	}
	fclose(file);
}

/*
	2. Read Table
*/
void readTable(char *path, int n, int m, int s) {
	transitionTable = generateTables(n, s, m);
	stateTable = generateTables(n, s, s);

	path = createAsolutePath(path);
	FILE *file;
	file = fopen(path, "r");
	if (file == NULL) {
		return;
	}

	int number;
	int i = 0;
	int j = 0;

	while (fscanf(file, "%d", &number) == 1) {
		if (j >= s) {
			j = 0;
			i++;
			if (i >= n) {
				break;
			}
		}
		transitionTable[i][j] = number;
		j++;
	}

	char *res = getFormatTable(transitionTable, n, m, s);
	printf(res);
	printf("\n");

	stateTable[0][0] = number;
	number = 0;
	i = 0;
	j = 1;

	while (fscanf(file, "%d", &number) == 1) {
		if (j >= s) {
			j = 0;
			i++;
			if (i >= n) {
				break;
			}
		}
		stateTable[i][j] = number;
		j++;
	}

	fclose(file);
}

void readStateList(char *path, int n, int m, int s) {
	transitionTable = generateTables(n, s, 1);
	stateTable = generateTables(n, s, 1);

	path = createAsolutePath(path);
	FILE *file;
	file = fopen(path, "r");
	if (file == NULL) {
		return;
	}
	
	int q1 = 0;
	int q2 = 0;
	int x = 0;
	int y = 0;

	while (true) {
		if (fscanf(file, "%d %d", &q1, &q2) == 2) {
			printf("%d %d", q1, q2);
			//empty	
		} else if (fscanf(file, "(%d %d)", &x, &y) == 2) {
			printf("(%d %d)", x, y);
			transitionTable[x][q1] = y;
			stateTable[x][q1] = q2;
		} else if (fscanf(file, "%c") == 1) {
			printf("#");
			//empty
		} else {
			break;
		}
	}

	
	char *res = getFormatTable(transitionTable, n, m, s);
	printf(res);
	printf("\n");
	res = getFormatTable(stateTable, n, m, s);
	printf(res);
	
}


/*
	Write To File
*/

void writeToFile(char *path, char *data) {
	path = createAsolutePath(path);
	printf(data);
	FILE *file = fopen(path, "a+");
	if (file == NULL) {
		return;
	}
	
	fprintf(file, "%s", data);
	fflush(file);
	fclose(file);
}

void writeToFileWithStandart(char *path, char *data) {	
	path = createAsolutePath(path);
	FILE *file = fopen(path, "a+");
	if (file == NULL) {
		return;
	}

	int i = 1;
	int j = 0;

	while (*data != '\0') {
		if (i % (FORMAT_LENGTH + 1) == 0) {
			fprintf(file, "%c", '\n');
		} else {
			fprintf(file, "%c", *data);
			data++;
		}
		i++;
	}
		
	fflush(file);
	fclose(file);
}

void cleanFile(char *path) {
	path = createAsolutePath(path);
	FILE *file = fopen(path, "w");
	if (file == NULL) {
		return;
	}
	fflush(file);
	fclose(file);
}

/*
	Generated Data
*/

/** 
	Generate table @param n x @param s with random values int range of [0, rangeRandom]
*/
int** generateTables(int n, int s, int rangeRandom) {
	int **table = new int*[n];
	for (int i = 0; i < n; i++) {
		table[i] = new int[s];
		for (int j = 0; j < s; j++) {
			table[i][j] = rand() % rangeRandom;
		}
	}
	return table;
}

bool** generateBoolTables(int n, int s) {
	bool **table = new bool*[n];
	for (int i = 0; i < n; i++) {
		table[i] = new bool[s];
		for (int j = 0; j < s; j++) {
			table[i][j] = false;
		}
	}
	return table;
}

char*** generateCharTable(int n, int s) {
	char ***table = new char**[n];
	for (int i = 0; i < n; i++) {
		table[i] = new char*[s];
		for (int j = 0; j < s; j++) {
			table[i][j] = new char[MAX_RESULT];
			table[i][j][0] = 0;
		}
	}
	return table;
}




/*
	Transformation
*/

/*
	1.CommandFormat
*/

char* getCommandFormat(int **transitionTable, int **stateTable, int n, int s) {
	char result[MAX_RESULT];
	strcpy(result, "");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < s; j++) {
			int newValue = transitionTable[i][j];
			int newState = stateTable[i][j];
			sprintf(&result[strlen(result)], COMMAND_PATTERN, i, j, newValue, newState);
		}
	}
	return result;	
}

/*
	2. Format Table
*/


int countSignInNumber(int value) {
	int k = 0;

	if (value == 0) { return 1; }

	while (value != 0) {
		value = value / 10; 
		k++; 
	}
	return k;
}

char* getFormatTable(int **table, int n, int m, int s) {
	char result[MAX_RESULT];
	strcpy(result, "");
	int countM = countSignInNumber(m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < s; j++) {
			int val = table[i][j];

			int diff = countM - countSignInNumber(val); // calculate a indent
			for (int k = 0; k < diff; k++) {
				strcat(result, " ");
			}
			
			sprintf(&result[strlen(result)], " %d", val);

		}
		strcat(result, "\n");
	}
	return result;
}

char* getFormatTable(bool **table, int n, int m, int s) {
	char result[MAX_RESULT];
	strcpy(result, "");
	int countM = countSignInNumber(m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < s; j++) {
			bool val = table[i][j];
			
			int diff = countM - countSignInNumber(val); // calculate a indent
			for (int k = 0; k < diff; k++) {
				strcat(result, " ");
			}
			
			sprintf(&result[strlen(result)], " %d", val);
		}
		strcat(result, "\n");
	}
	return result;
}


/*
	3.Adjancy Matrix and StateList
*/

bool** getAdjancyMatrix(int **stateTable, int n, int m, int s) {
	bool **matrix = generateBoolTables(s, s);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < s; j++) {
			int val = stateTable[i][j];
			matrix[j][val] = true;
		}
	}
	return matrix;
}


char*** getStateList(int **transitionTable, int **stateTable, int n, int m, int s) {
	char*** stateList = generateCharTable(s, s);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < s; j++) {
			int newValue = transitionTable[i][j];
			int newState = stateTable[i][j];

			char *ch = new char;
			sprintf(ch, "(%d %d)", i, newValue); 
			strcat(stateList[j][newState], ch);
		}
	}
	return stateList;
}

/////////////////////////////////////////////////////////////////////////////////////
void performTranparent(char *file, int n, int m, int s,int x);

void writeCommandToFile(char *file, int n, int m, int s);
void writeTablesToFile(char *file, int n, int m, int s) ;
void writeAdjMatrixAndStateList(char *file, int n, int m, int s);


void initialize(char *file, int n, int m, int s, int from, int to) {
		srand(time(NULL));
		transitionTable = generateTables(n, s, m);
		stateTable  = generateTables(n, s, s);

		cleanFile(file);
		performTranparent(file, n, m, s, from);
		performTranparent(file, n, m, s, to);
}

void inputData(char *file, int n, int m, int s, int from) {
		srand(time(NULL));
		transitionTable = generateTables(n, s, m);
		stateTable = generateTables(n, s, s);
		
		cleanFile(file);
		performTranparent(file, n, m, s, from);
}

void readGeneratedFile(char *file, int n, int m, int s, int from);

void outputData(char *file, char *output, int n, int m, int s, int from, int to) {
	readGeneratedFile(file, n, m, s, from);
}

void readGeneratedFile(char *file, int n, int m, int s, int from) {
	switch(from) {
	case 1:
		readCommand(file, n, m, s);
		break;
	case 2:
		readTable(file, n, m, s);
		break;
	case 3:
		readStateList(file, n, m, s);
		break;
	}
}

void performTranparent(char *file, int n, int m, int s, int to) {
	switch(to) {
	case 1:
		writeCommandToFile(file, n, m, s);
		break;
	case 2:
		writeTablesToFile(file, n, m, s);
		break;
	case 3:
		writeAdjMatrixAndStateList(file, n, m, s);
		break;
	}
}

void writeCommandToFile(char *file, int n, int m, int s) {
		char *command = getCommandFormat(transitionTable, stateTable, n, s);
		writeToFileWithStandart(file, command);
		writeToFile(file, "\n");
		writeToFile(file, "\n");
}

void writeTablesToFile(char *file, int n, int m, int s) {
		char* formatTable1 = getFormatTable(transitionTable, n, m, s);
		printf(formatTable1);
		writeToFile(file, formatTable1);
		writeToFile(file, "\n");
		
		printf("\n");
		char* formatTable2 = getFormatTable(stateTable, n, m, s);
		printf(formatTable2); 
		writeToFile(file, formatTable2);
		writeToFile(file, "\n");
}

void writeAdjMatrixAndStateList(char *file, int n, int m, int s) {
		char ***stateList = getStateList(transitionTable, stateTable, n, m, s);
		for (int i = 0; i < s; i++) {
			for(int j = 0; j < s; j++) {
				char *result = new char[MAX_RESULT];
				char *ch = stateList[i][j];
				if (*ch == '\0') {
					sprintf(result, "%d %d #\n", i, j);
				} else {
					sprintf(result, "%d %d %s\n", i, j, ch);
				}
				
				writeToFile(file, result);
			}
		}	
}

void main(int args, char * argv[]) {
	char *input = argv[1];
	int from = atoi(argv[2]);
	inputData(input, N, M, S, from);
}