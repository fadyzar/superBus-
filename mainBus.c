
//  Created by fady zarka on 23/04/2022.
//
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define MAXNAME 150
#define SIZE 300
#define MAX_NEIGHBORS 10
#define AMOUNTOFCITIES 193
#define  FILEPATH "/Users/fadyzarka/Desktop/busStaion/stations.csv"
#define FILE2PATH "Schedules.csv"
 

struct line
{
    char busLine[5];
};


struct station
 {
    int visited;
    int stationArrange;
    char stationName[MAXNAME];
    struct line Lines[SIZE];
    struct station* neighbors[MAX_NEIGHBORS];
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
void initVisited(){
for(int i=0;i<AMOUNTOFCITIES;i++){
    for(int j=0;j<citiesList[i].amountOfStations;j++){
        citiesList[i].stations[j].visited=0;
        }
    }
}

bool isCityExist(char cityName[],char tempStation[],char tempLine[],int tempArrange,struct station** ptr){
 
  for(int i=0; i<AMOUNTOFCITIES;i++){
    if(strcmp(citiesList[i].cityName,cityName)==0){
        for(int j=0;j<citiesList[i].amountOfStations;j++){
            if(strcmp(citiesList[i].stations[j].stationName,tempStation)==0){
                *ptr=&(citiesList[i].stations[j]);
               citiesList[i].stations[j].stationArrange=tempArrange;
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
        citiesList[i].stations[citiesList[i].amountOfStations].stationArrange=tempArrange;
        *ptr=&(citiesList[i].stations[citiesList[i].amountOfStations]);
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
        int tempArrange=0;
        int row = 0;
        int column = 0;
        int currentCity=0;
        struct station* prev = NULL;
        struct station* curr=NULL;
        while (fgets(buffer, 1024, fp)) {
            column = 0;
            row++;
            char* value= strtok(buffer, ",");
            if (row == 1)
                continue;
            while (value) {
                if(column == 3) {//bus line column
                strcpy(tempLine,value);
                }
                if(column == 7){
                    tempArrange=atoi(value);
                }
                if(column == 9) {//station column
                    strcpy(tempStation,value);
                }
                if(column==17){//city column
                    strcpy(tempCity,value);
                    if(isCityExist(tempCity,tempStation,tempLine,tempArrange,&curr)){
                        if(!(prev==NULL || strcmp(prev->stationName,curr->stationName)==0))
                            if(prev->stationArrange==(curr->stationArrange)-1)
                                for(int i=0;i<MAX_NEIGHBORS;i++){
                                    if(prev->neighbors[i]!=NULL)
                                        if(strcmp(prev->neighbors[i]->stationName,curr->stationName)==0)
                                                break;
                                    if(prev->neighbors[i]==NULL){
                                        prev->neighbors[i]=curr;
                                        break;
                                    }
                                }
                        break;
                    }
                    else {
                        strcpy
                        (citiesList[currentCity].cityName,value);
                        strcpy
                        (citiesList[currentCity].stations[(citiesList[currentCity].amountOfStations)].stationName,tempStation);
                        citiesList[currentCity].stations[(citiesList[currentCity].amountOfStations)].stationArrange=tempArrange;
                        curr=&citiesList[currentCity].stations[(citiesList[currentCity].amountOfStations)];
                        if(!(prev==NULL || strcmp(prev->stationName,curr->stationName)==0))
                            if(prev->stationArrange==(curr->stationArrange)-1)
                                for(int i=0;i<MAX_NEIGHBORS;i++){
                                    if(prev->neighbors[i]!=NULL)
                                        if(strcmp(prev->neighbors[i]->stationName,curr->stationName)==0)
                                                break;
                                    if(prev->neighbors[i]==NULL){
                                        prev->neighbors[i]=curr;
                                        break;
                                    }
                                }
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
            prev=curr;
            column++;
            }
        }
        fclose(fp);
    }
}

void findMaxNeghbors(){
    int counter=0,max=0;
    char station[60];
    char city[60];
    for(int i=0;i<AMOUNTOFCITIES;i++){
        for(int j=0;j<citiesList[i].amountOfStations;j++){
            for(int k=0;k<MAX_NEIGHBORS;k++){
                if(citiesList[i].stations[j].neighbors[k]!=NULL)
                    counter++;
                }
            if(counter>max){
                max=counter;
                strcpy(station,citiesList[i].stations[j].stationName);
                strcpy(city,citiesList[i].cityName);
                }
            counter=0;
            }
    }
    printf("max neghbors: %d station: %s city: %s\n",max,station,city);
}

void busLineList(){
    printf("Bus line list:\n");
    for(int i=0;i<AMOUNTOFCITIES;i++){
        printf("\n%d %s:",i+1,citiesList[i].cityName);
        for(int j=0;j<citiesList[i].amountOfStations;j++){
             printf("\n\tstation %s lines: \n",citiesList[i].stations[j].stationName);
            for(int k=0;k<SIZE;k++){
                if (strcmp(citiesList[i].stations[j].Lines[k].busLine,"")!=0)
                    printf("\t\tbus line %d:  %s\n",k+1,citiesList[i].stations[j].Lines[k].busLine);
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

void printNeighbors(struct station* arr[]){
    for(int i=0;i<MAX_NEIGHBORS;i++){
        if(arr[i]!=NULL)
            printf("\tNEIGHBOR %d:  %s\n",i+1,arr[i]->stationName);
    }
}

void busStaionList(){
    printf("stations list:\n");
     for(int i=0;i<AMOUNTOFCITIES;i++){
         printf("\n%s stations: \n",citiesList[i].cityName);
         for(int j=0;j<citiesList[i].amountOfStations;j++){
             printf("\tstation %d:  %s\n",j+1,citiesList[i].stations[j].stationName);
             //printNeighbors(citiesList[i].stations[j].neighbors);
             //printf("is visited: %d\n",citiesList[i].stations[j].visited);
             printf("\n");
         }
         //printf("\n");
     }
}
void printStationByCity(char city[]){
for(int i=0;i<AMOUNTOFCITIES;i++){
    if(strcmp(citiesList[i].cityName,city)==0){
    printf("\n%s stations: \n",citiesList[i].cityName);
         for(int j=0;j<citiesList[i].amountOfStations;j++){
         printf("\tstation %d:  %s\n",j+1,citiesList[i].stations[j].stationName);
         }
   }        
}
}
void printBusLinesByStation(char station[]){
    for(int i=0;i<AMOUNTOFCITIES;i++){
         for(int j=0;j<citiesList[i].amountOfStations;j++){
             if(strcmp(citiesList[i].stations[j].stationName,station)==0)
             for(int k=0;k<SIZE;k++){
               if (strcmp(citiesList[i].stations[j].Lines[k].busLine,"")!=0)
                    printf("\t\tbus lines %d:  %s\n",k+1,citiesList[i].stations[j].Lines[k].busLine);
            }     
        }
    }
}




void printStationNeighbors(char input[]){
     for(int i=0;i<AMOUNTOFCITIES;i++){
         for(int j=0;j<citiesList[i].amountOfStations;j++){
             if(strcmp(citiesList[i].stations[j].stationName,input)==0)
                printNeighbors(citiesList[i].stations[j].neighbors);
         }
    }
}


int totalStations(){
    int result=0;
    for(int i=0;i<AMOUNTOFCITIES;i++)
        result+=citiesList[i].amountOfStations;
    return result;
}

int recDis(struct station* neighbor, char endStation[], int counter){
    if(neighbor==NULL)
        return 0;
    if(neighbor->visited==1)
        return 0;
    neighbor->visited=1;
    if(strcmp(neighbor->stationName,endStation)==0)
        return counter+1;
    //(*counter)++;
    int result=0;
    //int max=0;
    for(int i=0;i<MAX_NEIGHBORS;i++){
        if(neighbor->neighbors[counter]==NULL)
            return 0;
        //if(strcmp(neighbor->stationName,endStation)==0)
            //return (*counter)++;
        //counter++;
        result+=recDis(neighbor->neighbors[i], endStation,counter+1);
        if(result==1)
            return result+1;
    }
    return result;
}
void twoStationsDis(char beginningStation[],char endStation[]){
    if(strcmp(beginningStation,"")==0||strcmp(endStation,"")==0){
        printf("Invalid input.\n");
        return; 
        }
    for(int i=0;i<AMOUNTOFCITIES;i++)
        for(int j=0;j<citiesList[i].amountOfStations;j++){
            if(strcmp(citiesList[i].stations[j].stationName,beginningStation)==0){
                if(strcmp(beginningStation,endStation)==0){
                    printf("Same station.\n");
                    return; 
                    }
                if(citiesList[i].stations[j].neighbors[0]==NULL){
                    printf("Path not found.\n");
                    return; 
                    }
                int curr=0;
                int result=0,path=0;
                int counter=0;
                struct station* current=citiesList[i].stations[j].neighbors[curr];
                while (current!=NULL) {
                    path=recDis(current,endStation,counter);
                    if(path!=0){
                        if(result==0)
                            result=path;
                        else
                            result=result>path? path:result;
                    }
                    initVisited();
                    current=citiesList[i].stations[j].neighbors[curr++];
                    }
                if(result==0){
                    printf("Path not found.\n");
                    return; }
                else
                    printf("\"%s\" is %d stations away from \"%s\".\n",endStation,result,beginningStation);
                    return;
                }
            }
            printf("Boarding station not found.\n");//לא נמצאה תחנת העלייה
            return;
        }




int main(){
    initAmountOfStations();
    initVisited();
    showCities();
    char beg[60],end[60],city[20],station[60];
    for(;;){
        printf("\033[1;36m");
      
        printf("\n~~~~~SuperBus company~~~~~\n");
         printf("\033[1;37m");
        printf("\nPlease choose option:\n");
        printf("1: Show all the cities list\n");
        printf("2: Show all stations for each city\n");
        printf("3: Show all the  bus lines that passing at a particular station\n");
        printf("4: Show stations for specific city\n");
        printf("5: Show bus lines for specific station\n");
        printf("6: Show the distance from one city to another with reference to bus stops\n");
        printf("7: Show the distance from one station to another\n");
        printf("8: Show a specific station's neighbors\n ");
        printf("Press 9 to exit\n");

        int option;
        scanf("%d",&option);
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
             printf("Enter city name\n");
                getchar();
                fgets(city, 60, stdin);
                city[strlen(city) - 1] = 0;
                 printStationByCity(city);
                break;
            case 5:
                 printf("Enter station name\n");
                getchar();
                fgets(station, 60, stdin);
                station[strlen(station) - 1] = 0;
                printBusLinesByStation(station);
                break;
            case 6:
                //disCity();//show the dis between one city and other
                break;
            case 7:
                printf("Enter boarding station\n");
                getchar();
                fgets(beg, 60, stdin);
                beg[strlen(beg) - 1] = 0;
                printf("\nenter drop-off station\n");
                fgets(end, 60, stdin);
                end[strlen(end) - 1] = 0;
                getchar();
                twoStationsDis(beg,end);
                break;
            case 8:
                printf("enter station\n");
                getchar();
                fgets(beg, 60, stdin);
                beg[strlen(beg) - 1] = 0;
                printStationNeighbors(beg);
                break;
            case 9:
                return 0;
      }
    }
  return 0;
}
