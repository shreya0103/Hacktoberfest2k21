#include<stdio.h>
#include<stdlib.h>

//PRIM'S ALGORITHM

#define MAX 10
#define TEMP 0
#define PERM 1
#define infinity 9999
#define NIL - 1

struct Edge {
    int u;
    int v;
};

int n;
int adj[MAX][MAX];

int predecessor[MAX];
int status[MAX];
int length[MAX];

void create_graph() {
    int i, max_edges, origin, destin, wt;

    printf("\nEnter number of vertices : ");
    scanf("%d", & n);
    max_edges = n * (n - 1) / 2;

    for (i = 1; i <= max_edges; i++) {
        printf("\nEnter Edge %d(-1 -1 to quit) : ", i);
        scanf("%d %d", & origin, & destin);
        if ((origin == -1) && (destin == -1))
            break;
        printf("\nEnter weight for this Edge : ");
        scanf("%d", & wt);
        if (origin >= n || destin >= n || origin < 0 || destin < 0) {
            printf("\nInvalid Edge!\n");
            i--;
        } else {
            adj[origin][destin] = wt;
            adj[destin][origin] = wt;
        }
    }
}

int min_temp() {
    int i;
    int min = infinity;
    int k = -1;

    for (i = 0; i < n; i++) {
        if (status[i] == TEMP && length[i] < min) {
            min = length[i];
            k = i;
        }
    }

    return k;
}

void PrimsAlgo(int r, struct Edge tree[MAX]) {
    int current, i;
    int count = 0;

    for (i = 0; i < n; i++) {
        predecessor[i] = NIL;
        length[i] = infinity;
        status[i] = TEMP;
    }

    length[r] = 0;

    while (1) {
        current = min_temp();

        if (current == NIL) {
            if (count == n - 1)
                return;
            else {
                printf("\nGraph is not connected, No spanning tree possible\n");
                exit(1);
            }
        }

        status[current] = PERM;

        if (current != r) {
            count++;
            tree[count].u = predecessor[current];
            tree[count].v = current;
        }

        for (i = 0; i < n; i++)
            if (adj[current][i] > 0 && status[i] == TEMP)
                if (adj[current][i] < length[i]) {
                    predecessor[i] = current;
                    length[i] = adj[current][i];
                }
    }

}

void p2main() {
    int wt_tree = 0;
    int i, root;
    struct Edge tree[MAX];

    create_graph();

    printf("\nEnter root vertex : ");
    scanf("%d", & root);

    PrimsAlgo(root, tree);

    printf("\nEdges to be included in spanning tree are : \n");

    for (i = 1; i <= n - 1; i++) {
        printf("%d-> ", tree[i].u);
        printf("%d\n", tree[i].v);
        wt_tree += adj[tree[i].u][tree[i].v];
    }
    printf("\nWeight of spanning tree is : %d\n", wt_tree);

}
//-------------------------------------------------------------------

//Kruskal's algorithm

struct edge {
    long int source, destination, weight;
};

struct subProblem {
    long int parent;
    long int r;
};

void Swapping(struct edge Array[], long int a, long int b) {
    struct edge temp;

    temp = Array[a];
    Array[a] = Array[b];

    Array[b] = temp;
}

long int Search(struct subProblem child[], long int a) {

    if (child[a].parent != a)
        child[a].parent = Search(child, child[a].parent);

    return child[a].parent;
}

void adding(struct subProblem child[], long int x, long int y) {
    long int temp1 = Search(child, x);
    long int temp2 = Search(child, y);

    if (child[temp1].r < child[temp2].r)
        child[temp1].parent = temp2;
    else if (child[temp1].r > child[temp2].r)
        child[temp2].parent = temp1;

    else {
        child[temp2].parent = temp1;
        child[temp1].r++;
    }
}

void Heapify(struct edge Array[], long int n, long int a) {
    long int largest = a;
    long int l = 2 * a + 1;
    long int r = 2 * a + 2;

    if (l < n && Array[l].weight > Array[largest].weight)
        largest = l;

    if (r < n && Array[r].weight > Array[largest].weight)
        largest = r;

    if (largest != a) {
        Swapping(Array, a, largest);

        Heapify(Array, n, largest);
    }
}

void minHeap(struct edge Array[], long int n) {

    for (long int a = n / 2 - 1; a >= 0; a--)
        Heapify(Array, n, a);

    for (long int a = n - 1; a > 0; a--) {

        Swapping(Array, 0, a);

        Heapify(Array, a, 0);
    }
}

void KruskalAlgo(struct edge Graph[], long int edj, long int vert, struct edge tree[]) {
    minHeap(Graph, edj);

    struct subProblem * child =
        (struct subProblem * ) malloc(vert * sizeof(struct subProblem));

    for (long int a = 0; a < vert; ++a) {
        child[a].parent = a;
        child[a].r = 0;
    }
    long int a = 0, b = 0;
    while (a < vert - 1 && b < edj) {

        struct edge next_edge = Graph[b++];

        long int x = Search(child, next_edge.source);
        long int y = Search(child, next_edge.destination);

        if (x != y) {
            tree[a++] = next_edge;
            adding(child, x, y);
        }

    }
}

void p1main() {

    long int vert = 4, edj = 5;

    printf("ENTER THE NUMBER OF VERTICES  :  ");
    scanf("%ld", & vert);

    printf("\nENTER THE NUMBER OF EDGES   :  ");
    scanf("%ld", & edj);

    struct edge graph[edj];
    struct edge tree[vert - 1];
    //node numbering starts with 0
    printf("\n\nEnter the NODE NUMBERS where EDGE is present ...format--->(a b)\n");
    for (long int a = 0; a < edj; a++) {
        printf("EDGE %ld           ----> ", a + 1);
        scanf("%ld%ld", & graph[a].source, & graph[a].destination, & graph[a].weight);
        printf("ENTER IT'S WEIGHT  ----> ");
        scanf("%ld", & graph[a].weight);
    }

    KruskalAlgo(graph, edj, vert, tree);

    printf("\n\nEdges in the required MST -\n(source destination  Weight) \n");
    for (long int a = 0; a < vert - 1; a++) {
        printf("    %ld          %ld        %ld\n", tree[a].source, tree[a].destination, tree[a].weight);
    }

}

//---------------------------------------------------------------------------------------------------------------

void main() {
    int
    var;
    printf("Enter 1 for Kruskal's algorithm ...\n");
    printf("Enter 2 for Prims     algorithm ...\n");
    printf("PLEASE ENTER YOUR CHOICE : ");
    scanf("%d", &
        var);
    if (var == 1) {
        p1main();
    } else if (var == 2) {
        p2main();
    } else {
        printf("ENTER A VALID NO.");
    }

}
