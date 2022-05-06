//
//  main.c
//  proj2debug
//
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
        //int currentStation=0;
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

int totalMaxNeighborsPerStation(struct station st){
    int result=0;
    for(int k=0;k<SIZE;k++)
        if(strcmp(st.Lines[k].busLine,"")!=0)
            result++;
    return 2*result;
}


void MaxNeighbors(){
    int max=0,temp=0;
    char station[100];
    for(int i=0;i<AMOUNTOFCITIES;i++)
        for(int j=0;j<citiesList[i].amountOfStations;j++){
            temp=totalMaxNeighborsPerStation(citiesList[i].stations[j]);
            if(max<temp){
            max=temp;
            strcpy(station,citiesList[i].cityName);
            }
        }
    printf("max possible neighbors: %d\t city: %s\n",max,station);
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
                    printf("\t\tbus lines %d:  %s\n",k+1,citiesList[i].stations[j].Lines[k].busLine);
            }
            //printf("\t\tmax neighbors: %d\n",totalMaxNeighborsPerStation(citiesList[i].stations[j]));
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
        if(arr[i]!=NULL/*&&strcmp(arr[i]->stationName,"")!=0*/)
            printf("\tNEIGHBOR %d:  %s\n",i+1,arr[i]->stationName);
    }
}

void busStaionList(){
    printf("stations list:\n");
     for(int i=0;i<AMOUNTOFCITIES;i++){
         printf("\n%s stations: \n",citiesList[i].cityName);
         for(int j=0;j<citiesList[i].amountOfStations;j++){
             printf("\tstation %d:  %s\n",j+1,citiesList[i].stations[j].stationName);
             printNeighbors(citiesList[i].stations[j].neighbors);
             printf("is visited: %d\n",citiesList[i].stations[j].visited);
             printf("\n");
         }
         //printf("\n");
     }
}

int totalStations(){
    int result=0;
    for(int i=0;i<AMOUNTOFCITIES;i++)
        result+=citiesList[i].amountOfStations;
    return result;
}

int recDis(struct station* neighbor, char endStation[], int* counter){
    if(neighbor==NULL)
        return -1;
    if(neighbor->visited==1)
        return -1;
    neighbor->visited=1;
    (*counter)++;
    for(int i=0;i<MAX_NEIGHBORS;i++){
        if(neighbor==NULL)
            return -1;
        if(strcmp(neighbor->stationName,endStation)==0)
            return *counter;
        recDis(neighbor->neighbors[i], endStation,counter);
    }
    return *counter;
}

void twoStationsDis(char beginningStation[],char endStation[]){
    if(strcmp(beginningStation,"")==0||strcmp(endStation,"")==0){
        printf("Invalid input.\n");
        return; }
    for(int i=0;i<AMOUNTOFCITIES;i++)
        for(int j=0;j<citiesList[i].amountOfStations;j++){
            if(strcmp(citiesList[i].stations[j].stationName,beginningStation)==0){
                if(strcmp(beginningStation,endStation)==0){
                    printf("Same station.\n");
                    return; }
                if(citiesList[i].stations[j].neighbors[0]==NULL){
                    printf("Path not found.\n");
                    return; }
                int curr=0;
                int result=-1,path=0;
                int counter=0;
                int* counterptr=&counter;
                struct station* current=citiesList[i].stations[j].neighbors[curr];
                while (current!=NULL) {
                    path=recDis(current,endStation,counterptr);
                    if(path!=-1){
                        if(result==-1)
                            result=path;
                        else
                            result=result>path? path:result;
                    }
                    current=citiesList[i].stations[j].neighbors[curr++];
                    }
                if(result==-1){
                    printf("Path not found.\n");
                    return; }
                else
                    printf("There is %d stations between them.\n",result);
                    return;
                }
            }
            printf("Boarding station not found.\n");//לא נמצאה תחנת העלייה
            return;
        }

void twoStations(char beginningStation[],char endStation[]){
    for(int i=0;i<AMOUNTOFCITIES;i++)
        for(int j=0;j<citiesList[i].amountOfStations;j++){
            if(strcmp(citiesList[i].stations[j].stationName,beginningStation)==0){
                if(strcmp(beginningStation,endStation)==0){
                    printf("Same station.\n");
                    return;
                    }
                int counter=-1;
                for(int k=0; k<MAX_NEIGHBORS;k++){
                    while(citiesList[i].stations[j].neighbors[k]!=NULL){
                        for(int x=0; x<MAX_NEIGHBORS;x++){
                        while(citiesList[i].stations[j].neighbors[k]->neighbors[x]!=NULL){
                            if(strcmp(citiesList[i].stations[j].neighbors[k]->neighbors[x]->stationName,endStation)){
                                //counter++;
                                break;
                                }
                            counter++;
                        }
                    }
                }
            }
}
        }
}


int main(){
    initAmountOfStations();
    initVisited();
    showCities();
    char beg[60],end[60];
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
        switch (option)
        {
            case 1:
                printCity();
                //printf("\n\n total stations: %d",totalStations());
                //MaxNeighbors();
                findMaxNeghbors();
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
                printf("enter boarding station\n");
                getchar();
                fgets(beg, 60, stdin);
                beg[strlen(beg) - 1] = 0;
                printf("enter drop-off station\n");
                fgets(end, 60, stdin);
                end[strlen(end) - 1] = 0;
                getchar();
                twoStationsDis(beg,end);
                break;
            case 9:
                return 0;
      }
    }
  return 0;
}
