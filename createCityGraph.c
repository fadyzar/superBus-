#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAXNAME 150
#define SIZE 300
#define AMOUNTOFCITIES 193
#define  FILEPATH "/Users/fadyzarka/Desktop/busStaion/stations.csv"
#define FILE2PATH "Schedules.csv"
#define INFINITY 9999
#define MAXVNUM 30
struct node {
    int vertex;
    struct node* next;
};
struct node* createNode(char[]);

struct Graph {
    int numVertices;
    struct node** adjLists;//** pointer to matrix dinami 
};

struct line
{
    char busLine[SIZE];
    char stationArrangements[5];
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

// Create a node
struct node* createNode(char v[]) {
    //bug - creates a node even when the node exists
    struct node* newNode = (node*)malloc(sizeof(struct node));
    //v=citiesList->stations->stationName;
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Create a graph
struct Graph* createAGraph(int vertices) {
    struct Graph* graph = (Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = (struct node**)malloc(vertices * sizeof(struct node*));
    int i;
    for (i = 0; i < vertices; i++){
     for(int j=0;j<vertices;j++){
        graph->adjLists[i][j].vertex =0 ;
     }
    }
    return graph;
}

// Add edge
void addEdge(struct Graph* graph, int firstNode, int secondNode) {
    // Add edge from firstNode to secondNode
    struct node* newNode = createNode(secondNode);
    newNode->next = graph->adjLists[firstNode];
    graph->adjLists[firstNode] = newNode;

    // Add edge from d to s
    newNode = createNode(firstNode);
    newNode->next = graph->adjLists[secondNode];
    graph->adjLists[secondNode] = newNode;
}

// Print the graph
/*void printGraph(struct Graph* graph) {
    int v;
    for (v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjLists[v];
        printf("\n Vertex %d\n: ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}
*/
int main() {
    struct Graph* graph = createAGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 2);

    printGraph(graph);

    return 0;
}
