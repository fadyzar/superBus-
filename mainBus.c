//
//  main.c
//  proj2debug
//
//  Created by fady zarka on 23/04/2022.
//
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAXNAME 150
#define SIZE 300
#define AMOUNTOFCITIES 193
#define  FILEPATH "/Users/fadyzarka/Desktop/busStaion/stations.csv"
#define FILE2PATH "Schedules.csv"
 



struct line
{
    char busLine[SIZE];
};


struct station
 {
   int stationNum;
   char stationName[MAXNAME];
    struct line Lines[SIZE];

 };

  struct city
 {
   char cityName[MAXNAME];
    int amountOfStations;
   struct station stations[SIZE];
 };

 

struct city citiesList[AMOUNTOFCITIES];

FILE* fp;
FILE* fp1;

void initAmountOfStations(){
  for(int i=0;i<AMOUNTOFCITIES;i++){
    citiesList[i].amountOfStations=0;
  }
}

bool isCityExist(char cityName[],char tempStation[],char tempLine[]){
 
  for(int i=0; i<AMOUNTOFCITIES;i++){
    if(strcmp(citiesList[i].cityName,cityName)==0){
        for(int j=0;j<citiesList[i].amountOfStations;j++){
            if(strcmp(citiesList[i].stations[j].stationName,tempStation)==0){
                for(int k=0;k<SIZE;k++){
                    if(strcmp(citiesList[i].stations[j].Lines[k].busLine,tempLine)==0)
                        return true;
                    if(strcmp(citiesList[i].stations[j].Lines[k].busLine,"")==0){
                        strcpy( citiesList[i].stations[j].Lines[k].busLine ,tempLine);
                        return true;
                    }
                }
            }
        }
        strcpy(citiesList[i].stations[citiesList[i].amountOfStations].stationName,tempStation);
            for(int k=0;k<SIZE;k++){
                if(strcmp(citiesList[i].stations[citiesList[i].amountOfStations].Lines[k].busLine,tempLine)==0)
                    return true;
                if(strcmp(citiesList[i].stations[citiesList[i].amountOfStations].Lines[k].busLine,"")==0){
                    strcpy( citiesList[i].stations[(citiesList[i].amountOfStations)++].Lines[k].busLine ,tempLine);
                        return true;
              }
            }
        }
  }
  return false;
}

void showCities(){
    
    fp = fopen(FILEPATH, "r");
    if (!fp)
        printf("Can't open file\n");
    else {
        // Here we have taken size of
        // array 1024 you can modify it
        char buffer[1024];
        char tempStation[MAXNAME];
        char tempCity[MAXNAME];
        char tempLine[10];
        int row = 0;
        int column = 0;
        int currentCity=0;
        //int currentStation=0;
        while (fgets(buffer, 1024, fp)) {
            column = 0;
            row++;
            char* value = strtok(buffer, ",");
            if (row == 1)
                continue;
            while (value) {
                if(column == 3) {
                strcpy(tempLine,value);
                }
                if(column == 9) {
                strcpy(tempStation,value);
                }
                if(column==17){
                    strcpy(tempCity,value);
                    if(isCityExist(tempCity,tempStation,tempLine)){
                        break;
                    }
                    else {
                        strcpy
                        (citiesList[currentCity].cityName,value);
                        strcpy
                        (citiesList[currentCity].stations[(citiesList[currentCity].amountOfStations)].stationName,tempStation);
                        for(int k=0;k<SIZE;k++){
                            if(strcmp(citiesList[currentCity].stations[citiesList[currentCity].amountOfStations].Lines[k].busLine,"")==0){
                                strcpy( citiesList[currentCity].stations[(citiesList[currentCity].amountOfStations)++].Lines[k].busLine ,tempLine);
                                    break;
                          }
                        }
                        currentCity++;
                    }
                }
            value = strtok(NULL, ",");
            column++;
            }
        }
        fclose(fp);
    }
}

void busLineList(){
    printf("Bus line list:\n");
    for(int i=0;i<AMOUNTOFCITIES;i++){
        printf("\n%d %s:",i+1,citiesList[i].cityName);
        for(int j=0;j<citiesList[i].amountOfStations;j++){
             printf("\n\tstation %s lines: \n",citiesList[i].stations[j].stationName);
            for(int k=0;k<SIZE;k++){
                if (strcmp(citiesList[i].stations[j].Lines[k].busLine,"")!=0)
                    printf("\t\tbus lines %d:  %s\n",k+1,citiesList[i].stations[j].Lines[k].busLine);
            }
        }
    }
}


void printCity(){
 printf("city list:\n");
  for(int i=0;i<AMOUNTOFCITIES;i++){
   printf("%d %s\n",i+1,citiesList[i].cityName);
  }
}

void busStaionList(){
    printf("stations list:\n");
     for(int i=0;i<AMOUNTOFCITIES;i++){
         printf("\n%s stations: \n",citiesList[i].cityName);
         for(int j=0;j<citiesList[i].amountOfStations;j++)
             printf("station %d:  %s\n",j+1,citiesList[i].stations[j].stationName);
     }
}

//void disCity(){}
//void disStaion()//BFS{}
int main(){
    initAmountOfStations();
    showCities();
    for(;;){
        //printf("\033[1;34m");
        printf("\n\nPlease choose option:\n");
        printf("Press 1 to see the cities list\n");
        printf("Press 2 to see the staions list\n");
        printf("Press 3 to see which bus is passing at a particular station\n");
        printf("Press 4 to see the distance from one city to another with reference to bus stops\n");
        printf("Press 5 to see the distance from one station to another\n");
        printf("Press 9 to exit\n");

        int option;
        scanf("%d",&option);
        //initAmountOfStations();
        //showCities();
        switch (option)
        {
            case 1:
                printCity();
                break;
            case 2:
                busStaionList();
                break;
            case 3:
                busLineList();
                break;
            case 4:
                //disCity();//show the dis between one city and other
                break;
            case 5:
                //disStaion();
                break;
            case 9:
                return 0;
      }
    }
  return 0;
}
