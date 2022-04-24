	if (row == 1)
				     continue;
        
          while(valueSt){
            if(column==9){
              city.stations[0]=valueSt;
              printf("test2   %s",city.stations[0]);
              int flag=0;
            for(int i=0; i<currentCity;i++){
              if(strcmp(citiesList[i].cityName,city.cityName)){
                citiesList[i].stations[currentStation++]=valueSt;
                flag=1;
                break;
              }   
            }
            if(flag==0)
              citiesList[currentCity++]=city;
            }
      value = strtok(NULL, ",");
      valueSt = strtok(NULL, ",");
			column++;
      columnSt++;
       }
    } 
    }
   
  }