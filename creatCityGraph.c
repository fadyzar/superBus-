#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INFINITY 9999
#define MAXVNUM 30
char ans;
typedef struct
{
 int Vnum;
 int arcs[MAXVNUM][MAXVNUM];            //The storage structure of the graph is the adjacency matrix
}Graph;
int createGraph(Graph *g,int *start,int *end)
{
 int n,m,i,j,k,s,count;
 int t[MAXVNUM];
 printf("n u   Please enter the number of bus stops and buses :n");
 scanf("%d %d",&n,&m);
 if(n<=1 || m<1)
  return -1;
 g->Vnum = n;
 for(i=0;i<n;i++)
  for(j=0;j<n;j++)
   g->arcs[i][j] = INFINITY;    //The adjacency matrix is initialized
 for(s=0;s<m;s++)
 {
  printf("n ▲ please enter no %d Serial Numbers of the stations the bus passes through [ 0<= Serial number <=%d,-1 Ending  】  :n",s+1,n-1);
  scanf("%d",&k);
  count = 0;
  while(k!=-1)
  {
   t[count++]=k;
   scanf("%d",&k);
  }
  for(i=0;i<count-1;i++)
  {
   for(j=i+1;j<count;j++)        //In the current line, there is a direct bus from t [I] to t [j]
    g->arcs[t[i]][t[j]]=1;
  }
 }
 printf("n u   Please enter the upper station number and the lower station number [ 0<= Serial number <=%d 】 :n",n-1);
 scanf("%d%d",start,end);
 if( *start<0 || *start>n-1 || *end<0 || *end>n-1)
  return -1;
 return 0;
}
int findMinmum(Graph g,int start,int end)   //The dijkstra algorithm finds the minimum number of rides
{
 int s[MAXVNUM];
 int i,j,u,*dist,min;
 if(start==end)
  return 0;
 dist=(int *)malloc(sizeof(int));
 if(dist==NULL)
  return -1;
 for(i=0;i<g.Vnum;i++)
 {
  dist[i]=g.arcs[start][i];    //From start can be direct to the station on the train times set 1
  s[i]=0;       //Boarding times at all stations have not been found
 }
 s[start]=1;   //The minimum number of trips to start has been found
 dist[start]=0;   //The minimum number of rides from site start to start is initialized to 0
 for(i=0;i<g.Vnum;++i)
 {
  min=INFINITY;
  u=start;
  for(j=0;j<g.Vnum;++j)  //U is the least frequent bus ride of any station that can be reached from start
  {
   if(s[j]==0 && dist[j]<min)
   {
    min=dist[j];
    u=j;
   }
  }
  s[u]=1;    //The minimum hop times from site start to u have been found. Add u to set s
  for(j=0;j<g.Vnum;++j)   //Updates the minimum number of rides for other sites in the current situation
  {
   if(s[j]==0 && min+g.arcs[u][j]<dist[j])
    dist[j]=min+g.arcs[u][j];
  }
 }
 return dist[end];
}
int main(void)
{
 int start,end,m;
 printf("\n Description: \n");
 printf("\n\t Hello! Welcome to use this system! \n");
 printf("\t[ one ]   The system is created according to the digraph, please enter how many stations you want to travel to the destination and the number of buses at the location. The number of stations corresponds to the number of vertices in a directed graph. \n");
 printf("\t[ two ]   Please enter the site of each bus path, which corresponds to the vertex of each edge in the directed graph. Press after typing -1 Enter the path of the next bus. \n ");
 printf("\t[ three ]   Please enter the station number of the boarding point and the number of the next station, which is equivalent to any two vertices in the directed graph. After input, the system will output the minimum number of car changes according to the input information. \n ");
 do
 {
  Graph G;
  if(createGraph(&G,&start,&end)==-1)
  {
   printf("n      I'm sorry to hear that !n     Failed to create directed graph !   n     Please reenter the data  !n");
   return 0;
  }
  m=findMinmum(G,start,end);
  if(m<INFINITY)
   printf("  congratulations !n   The destination can be reached by car n   From the station %d The next station %d The minimum number of car changes is:   %dn",start,end,m-1);
  else
   printf("n I'm sorry !n There is no bus available to reach the station  !n");
  printf("n Shall we continue (y/n)?");
  fflush(stdin);
  ans=getchar();
  system("cls");
 }while(ans=='y' || ans=='Y');
 printf("n----------------------- Thank you for using the system! ----------------------------");
 system("pause");
 return 0;
} 