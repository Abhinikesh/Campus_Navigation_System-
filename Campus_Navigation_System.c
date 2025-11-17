#include <stdio.h>
#include <string.h>
#define INF 9999
#define MAX 10

int minDistance(int dist[], int visited[], int n)
{
    int min = INF, min_index = -1;
    for (int v = 0; v < n; v++)
        if (!visited[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

void printPath(int parent[], int j, char locations[MAX][30])
{
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j], locations);
    printf(" -> %s", locations[j]);
}

void dijkstra(int graph[MAX][MAX], int n, int src, int dest, char locations[MAX][30])
{
    int dist[MAX], visited[MAX], parent[MAX];
    for (int i = 0; i < n; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++)
    {
        int u = minDistance(dist, visited, n);
        if (u == -1)
            break;
        visited[u] = 1;

        for (int v = 0; v < n; v++)
        {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\nShortest distance from %s to %s = %d\n", locations[src], locations[dest], dist[dest]);
    printf("Path: %s", locations[src]);
    printPath(parent, dest, locations);
    printf("\n");
}

int main()
{
    int n = 6;

    char locations[MAX][30] = {
        "Hostel",
        "Library",
        "Canteen",
        "Classroom",
        "Admin_Block",
        "Sports_Ground"};

    int graph[MAX][MAX] = {
        {0, 2, 4, 0, 0, 0},
        {2, 0, 0, 3, 0, 0},
        {4, 0, 0, 2, 0, 0},
        {0, 3, 2, 0, 4, 0},
        {0, 0, 0, 4, 0, 3},
        {0, 0, 0, 0, 3, 0}};

    printf("\n------------------------------\n");
    printf("     CAMPUS NAVIGATION SYSTEM   \n");
    printf("------------------------------\n\n");

    printf("Available Locations:\n");
    for (int i = 0; i < n; i++)
        printf("%d. %s\n", i, locations[i]);

    int src, dest;
    printf("\nEnter Source Location ID (0-%d): ", n - 1);
    scanf("%d", &src);
    printf("Enter Destination Location ID (0-%d): ", n - 1);
    scanf("%d", &dest);

    if (src < 0 || src >= n || dest < 0 || dest >= n)
    {
        printf("\nInvalid input! Please enter valid location IDs.\n");
        return 0;
    }

    dijkstra(graph, n, src, dest, locations);

    printf("\n-------------------------------------------\n");
    printf("Thank you for using Campus Navigation System!\n");
    printf("-------------------------------------------\n");

    return 0;
}
