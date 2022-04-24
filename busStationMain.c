#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#pragma warning(disable:4996)

#define FOREVER for(;;)

const int MCities = 193;
const int MStops = 300;
const int MBuses = 100;
const int N = 100;
char stops[MStops][N] = {};
char cities2[MCities][N] = {};



struct cities {
	int id;
	char name[100];
	struct cities* next;
};
struct cities* CHead;
struct cities* CTail;

struct stops {
	int id;
	char number[50];
	char name[100];
	struct stops* next;
};
struct stops* SHead;
struct stops* STail;

struct buses {
	int id;
	char number[20];
	struct buses* next;
};
struct buses* BHead;
struct buses* BTail;

void lastinsertCity(char* data, int id) {
	struct cities* ptr = (struct cities*)malloc(sizeof(struct cities));

	if (ptr == NULL)
	{
		printf("\nOVERFLOW\n");
	}
	else {
		ptr->id = id;
		strcpy(ptr->name, data);
		if (CHead == NULL) {
			ptr->next = CHead;
			CHead = ptr;
			CTail = CHead;
		}
		else {
			ptr->next = NULL;
			CTail->next = ptr;
			CTail = ptr;
		}
	}
}

void lastinsertStop(char* number, char* data, int id) {
	struct stops* ptr = (struct stops*)malloc(sizeof(struct stops));

	if (ptr == NULL)
	{
		printf("\nOVERFLOW\n");
	}
	else {
		ptr->id = id;
		strcpy(ptr->number, number);
		strcpy(ptr->name, data);
		if (SHead == NULL) {
			ptr->next = SHead;
			SHead = ptr;
			STail = SHead;
		}
		else {
			ptr->next = NULL;
			STail->next = ptr;
			STail = ptr;
		}
	}
}

void lastinsertBus(char* data, int id) {
	struct buses* ptr = (struct buses*)malloc(sizeof(struct buses));

	if (ptr == NULL)
	{
		printf("\nOVERFLOW\n");
	}
	else {
		ptr->id = id;
		strcpy(ptr->number, data);
		if (SHead == NULL) {
			ptr->next = BHead;
			BHead = ptr;
			BTail = BHead;
		}
		else {
			ptr->next = NULL;
			BTail->next = ptr;
			BTail = ptr;
		}
	}
}

void printCityList() {
	struct cities* temp;
	temp = CHead;
	printf("cities:\n");
	while (temp) {
		printf("%d: %s", temp->id, temp->name);
		printf("\n");
		temp = temp->next;
	}
	printf("\n");
	
}

void printStopList() {
	struct stops* temp;
	temp = SHead;
	printf("stops:\n");
	while (temp) {
		printf("%d: %s (%s)",
			temp->id,
			temp->name,
			temp->number);
		printf("\n");
		temp = temp->next;
	}
	printf("\n");

}

void printBusList() {
	struct buses* temp;
	temp = BHead;
	printf("buses:\n");
	while (temp) {
		printf("%d: %d", temp->id, temp->number);
		printf("\n");
		temp = temp->next;
	}
	printf("\n");
}


int isEqual(char col[], char value[]) {
	bool  flage = false;
	int clen = strlen(col);
	int vlen = strlen(value);
	if (vlen == clen) {
		//printf("%s", value);
		for (int i = 0; i < strlen(value); i++) {
			//printf("i=%d", i);
			if (col[i] == value[i])
			{
				flage = true;
			}
			else
			{
				return 0;
			}
		}
		if (flage)
		{
			return 1;
		}
	}
	return 0;
}

int findIndexOfColumnByName(char col[], FILE* fp) {
	char buffer[1024];
	int row = 0;
	int column = 0;

	while (fgets(buffer,
		1024, fp)) {
		column = 0;
		row++;

		// To avoid printing of column
		// names in file can be changed
		// according to need
		if (row == 1) {
			// Splitting the data
			char* value = strtok(buffer, ",");

			while (value) {
				bool flag = false;

				int isE = isEqual(col, value);

				if (isE == 1)
				{
					return column;
				}

				value = strtok(NULL, ",");
				column++;
			}
		}
	}
	return 0;
}

// this function returns 0 if the value(val[]) exists in
// cities array(cities[][]), and returns 1 if it doesn't exists
// strcmp() function makes the compare.
int isExist(char arr[MCities][N], char val[], int size) {
	for (int i = 0; i < size; i++) {
		if (!strcmp(arr[i], val))
			return 0;
	}
	return 1;
}

void printCities(char arr[MCities][N], int size) {
	printf("cities: \n");
	for (int i = 0; i < size; i++) {
		printf("%d: %s\n", i + 1, arr[i]);
	}
	printf("\n\n");
}

int isExist2(char arr[MStops][N], char val[], int size) {
	for (int i = 0; i < size; i++) {
		if (!strcmp(arr[i], val))
			return 0;
	}
	return 1;
}

void printStops(char arr[MStops][N], int size, int num) {
	printf("stops of %s:\n\n",cities2[num]);
	for (int i = 0; i < size; i++) {
		printf("%d: %s\n", i + 1, arr[i]);
	}
}

int isExist3(char arr[MStops][N], char val[], int size) {
	for (int i = 0; i < size; i++) {
		if (!strcmp(arr[i], val))
			return 0;
	}
	return 1;
}

void printBuses(char arr[MBuses][N], int size) {
	printf("buses that stops here:\n\n");
	for (int i = 0; i < size; i++) {
		printf("%d: %s\n", i + 1, arr[i]);
	}
}

void showCities() {
	//system("cls");

	FILE* fp;
	fp = fopen("stations.csv", "r");

	if (fp == NULL)
	{
	printf("Can not open file!");
	}
	else {
	char buffer[1024];

	int row = 0;
	int column = 0;
	char col[50] = "City";
	int size = sizeof(cities2) / sizeof(cities2[0]);
	int numOfCol = findIndexOfColumnByName(col, fp);
	int isE;
	int i = 0;
	int counter = 1;

	//printf("index of column= %d\n", numOfCol);

	while (fgets(buffer, 1024, fp)) {
		//printf("buffer %s", buffer);
		column = 0;
		row++;

		// To avoid printing of column
		// names in file can be changed
		// according to need
		if (row == 1)
			continue;

		// Splitting the data
		char* value = strtok(buffer, ",");

		while (value) {
			if (column == numOfCol)//colmn which i need
			{
				isE = isExist(cities2, value, size);
				if (isE)
				{
					lastinsertCity(value, i + 1);
					strcpy(cities2[i], value);
					i++;
				}
				//printf("row= %d, value =  %s\n",row, value);
			}

			value = strtok(NULL, ",");
			column++;
		}
		//printf("counter %d\n", counter++);
	}
	printCityList();
	//printCities(cities2, size);
	//printf("row = %d", row);
	// Close the file
	fclose(fp);
	}
}

void showBusStops(int cityNum) {
	system("cls");

	FILE* fp;
	fp = fopen("stations.csv", "r");

	if (fp == NULL)
	{
		printf("Can not open file!");
	}
	else {
		char buffer[1024];

		int row = 0;
		int column = 0;
		char col[50] = "Station name";
		int numOfCol = findIndexOfColumnByName(col, fp);
		int stopNumCol = 8;
		int citiesCol = 17;
		int size = sizeof(stops) / sizeof(stops[0]);
		int isE;
		int i = 0;
		int counter = 1;
		char currentStop[100] = {};
		char currentStopNum[50];

		//printf("index of column= %d\n", numOfCol);

		while (fgets(buffer, 1024, fp)) {
			//printf("buffer %s", buffer);
			column = 0;
			row++;

			// To avoid printing of column
			// names in file can be changed
			// according to need
			if (row == 1)
				continue;

			// Splitting the data
			char* value = strtok(buffer, ",");

			while (value) {
				if (column == stopNumCol){//statoins number column
					strcpy(currentStopNum, value);
				}

				if (column == numOfCol)//statoins name column
				{
					strcpy(currentStop, value);
				}

				if (column == citiesCol) {// cities column
					if (!strcmp(cities2[cityNum], value))
					{
						isE = isExist2(stops, currentStopNum, size);
						if (isE)
						{
							lastinsertStop(currentStopNum, 
								currentStop, 
								i + 1);
							strcpy(stops[i], currentStopNum);
							i++;
						}
					}
				}

				value = strtok(NULL, ",");
				column++;
			}
			//printf("counter %d\n", counter++);
		}
		printStopList();
		//printStops(stops, size, cityNum);
		//printf("row = %d", row);
		// Close the file
		fclose(fp);
	}
}

void showBuses(int stopNum) {
	system("cls");

	FILE* fp;
	fp = fopen("stations.csv", "r");

	if (fp == NULL)
	{
		printf("Can not open file!");
	}
	else {
		char buffer[1024];

		int row = 0;
		int column = 0;
		char col[50] = "line";
		int numOfCol = findIndexOfColumnByName(col, fp);
		int stopsCol = 8;
		char buses[MStops][N] = {};
		int size = sizeof(buses) / sizeof(buses[0]);
		int isE;
		int i = 0;
		int counter = 1;
		char currentBus[N] = {};

		//printf("index of column= %d\n", numOfCol);

		while (fgets(buffer, 1024, fp)) {
			//printf("buffer %s", buffer);
			column = 0;
			row++;

			// To avoid printing of column
			// names in file can be changed
			// according to need
			if (row == 1)
				continue;

			// Splitting the data
			char* value = strtok(buffer, ",");

			while (value) {
				if (column == numOfCol)//buses column
				{
					strcpy(currentBus, value);
				}

				if (column == stopsCol) {// stops column
					if (!strcmp(stops[stopNum], value))
					{
						isE = isExist3(buses, currentBus, size);
						if (isE)
						{
							lastinsertBus(value, i + 1);
							strcpy(buses[i], currentBus);
							i++;
						}
					}
				}

				value = strtok(NULL, ",");
				column++;
			}
			//printf("counter %d\n", counter++);
		}
		printBusList();
		//printBuses(buses, size);
		//printf("row = %d", row);
		// Close the file
		fclose(fp);

		printf("press any key to go back to cities");
		getchar();
	}
}

int main() {
	int cityNum, stopNum;

	FOREVER{
		showCities();
		printf("please choose a city: ");
		scanf("%d", &cityNum);
		getchar();
		if (cityNum <= MCities && cityNum>0)
		{
			showBusStops(cityNum);
		}
		else {
			do {
				printf("\n\ncan't find city!\n\n");
				printf("please choose another city: ");
				scanf("%d", &cityNum);
				getchar();
			} while (cityNum > MCities || cityNum <= 0);
			showBusStops(cityNum - 1);
		}
		printf("please choose a stop: ");
		scanf("%d", &stopNum);
		getchar();
		if (stopNum <= MStops && stopNum > 0)
		{
			showBuses(stopNum );
		}else {
			do {
				printf("\n\ncan't find stop!\n\n");
				printf("please choose another stop: ");
				scanf("%d", &stopNum);
				getchar();
			} while (stopNum > MBuses || stopNum <= 0);
			showBuses(stopNum );
		}
	}
	return 0;
}