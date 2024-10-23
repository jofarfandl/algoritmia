#include <cstdlib> 
#include <bits/stdc++.h>
#include <iostream> 
#include <conio.h>
using namespace std;
#define V 5
#define V2 5
int parent[V2];
int tamanio;
int graph[5][5];
int graph2[5][5];

struct nodo{ 
    char nombre;
    struct nodo *siguiente; 
    struct arista *adyacencia;
}; 
struct arista{ 
    int peso;
    struct nodo *destino;
    struct arista *siguiente; 
}; 
typedef struct nodo *Tnodo;
typedef struct arista *Tarista;

Tnodo p;

void menu(); 
void insertar_nodo(); 
void agrega_arista(Tnodo &, Tnodo &, Tarista &); 
void insertar_arista(); 
void vaciar_aristas(Tnodo &); 
void eliminar_nodo();
void eliminar_arista();
void mostrar_grafo(); 
void mostrar_aristas();
int minKey(int key[], bool mstSet[]);
void printMST(int parent[], int graph[V][V]);
void primMST(int graph[V][V]);
void printSolution(int dist[][V]);
void floydWarshall(int graph2[][V]);
int find(int i);
void union1(int i, int j);
void kruskalMST(int cost[V2][V2]);
void dijkstra(int graph[V][V],int src);
int minDistance(int dist[], bool sptSet[]);
void printSolution2(int dist[]);

int main(){  
    p=NULL; 
    int op;
    do{ 
        menu(); 
        cin>>op;
        switch(op){ 
            case 1:{ 
                insertar_nodo();
                tamanio++;
                break;}
            case 2: insertar_arista(); 
                break;
            case 3: eliminar_nodo(); 
                break;
            case 4: eliminar_arista(); 
                break;
            case 5: mostrar_grafo();
                break;
            case 6: mostrar_aristas();
                break;
            case 7: primMST(graph); 
                break;
            case 8: floydWarshall(graph2);
                break;
            case 9: kruskalMST(graph);
                break;
            case 10: dijkstra(graph,0);
                break;
            case 11: system("PAUSE"); cout<<"Hasta la proxima...\n"<<endl; return EXIT_SUCCESS; 
                break;
            default: cout<<"OPCION NO VALIDA"; 
                break;  
        } 
    cout<<endl<<endl; 
    system("pause"); system("cls"); 
    }while(op!=11); 
    getch();
    return 0;
}

void menu(){ 
    cout<<"\n\t GRAFOS DIRIGIDO \n\n"; 
    cout<<" 1. INSERTAR UN NODO "<<endl;  
    cout<<" 2. INSERTAR UNA ARISTA "<<endl;  
    cout<<" 3. ELIMINAR UN NODO "<<endl;  
    cout<<" 4. ELIMINAR UNA ARISTA "<<endl; 
    cout<<" 5. MOSTRAR GRAFO "<<endl;  
    cout<<" 6. MOSTRAR ARISTAS DE UN NODO "<<endl; 
    cout<<" 7. ALGORITMO DE PRIM "<<endl;
    cout<<" 8. ALGORITMO DE FLOYD "<<endl; 
    cout<<" 9. ALGORITMO DE KRUSKAL "<<endl; 
    cout<<" 10. ALGORITMO DE DIJKSTRA "<<endl; 
    cout<<" 11. SALIR "<<endl; 
    cout<<"\n INGRESE OPCION: "; 
}

void insertar_nodo(){
    Tnodo t,nuevo=new struct nodo; 
    cout<<"INGRESE VARIABLE:"; 
    cin>>nuevo->nombre; 
    nuevo->siguiente = NULL; 
    nuevo->adyacencia=NULL; 

    if(p==NULL){ 
        p = nuevo; 
        cout<<"PRIMER NODO"; 
    } 
    else { 
        t = p; 
        while(t->siguiente!=NULL) 
        { 
            t = t->siguiente; 
        } 
        t->siguiente = nuevo; 
        cout<<"NODO INGRESADO"; 
    } 
} 

void agrega_arista(Tnodo &aux, Tnodo &aux2,float peso, Tarista &nuevo){ 
    Tarista q; 
    if(aux->adyacencia==NULL){ 
        aux->adyacencia=nuevo; 
        nuevo->destino=aux2;
        nuevo->peso=peso;
        cout<<"PRIMERA ARISTA";
    } 
    else{ 
        q=aux->adyacencia; 
        while(q->siguiente!=NULL) 
        q=q->siguiente; 
        nuevo->destino=aux2; 
        nuevo->peso=peso;
        q->siguiente=nuevo; 
        cout<<"ARISTA AGREGADA"; 
    } 
}

void insertar_arista(){ 
    char ini, fin;
    int peso,cont=0,cont2=0;
    Tarista nuevo=new struct arista; 
    Tnodo aux, aux2;  

    if(p==NULL){ 
        cout<<"GRAFO VACIO"; 
        return;
    }
    nuevo->siguiente=NULL; 
    cout<<"INGRESE NODO DE INICIO:";  
    cin>>ini; 
    cout<<"INGRESE NODO FINAL:"; 
    cin>>fin; 
    cout<<"INGRESE PESO:"; 
    cin>>peso; 
    aux=p; 
    aux2=p; 
    while(aux2!=NULL){ 
        if(aux2->nombre==fin){ 
            break;
        }  
        aux2=aux2->siguiente; 
        cont++;
    } 
    while(aux!=NULL){ 
        if(aux->nombre==ini){ 
            agrega_arista(aux,aux2,peso,nuevo);
            graph[cont2][cont]=peso;
            graph2[cont2][cont]=peso;
            return; 
        } 
        aux = aux->siguiente;
        cont2++;
    }
} 

void vaciar_aristas(Tnodo &aux){ 
    Tarista q,r; 
    q=aux->adyacencia; 
    while(q->siguiente!=NULL){ 
        r=q; 
        q=q->siguiente; 
        delete(r); 
    } 
} 

void eliminar_nodo(){   
    char var;
    Tnodo aux,ant;
    aux=p;
    cout<<"ELIMINAR UN NODO\n";
    if(p==NULL){
        cout<<"GRAFO VACIO...!!!!";
        return;
    }
    cout<<"INGRESE NOMBRE DE VARIABLE:";
    cin>>var;
    while(aux!=NULL){
        if(aux->nombre==var){
            if(aux->adyacencia!=NULL)
                vaciar_aristas(aux);
            if(aux==p){
                p=p->siguiente;
                delete(aux);
                cout<<"NODO ELIMINADO...!!!!";
                return;
            }
            else{
                ant->siguiente = aux->siguiente;
                delete(aux);
                cout<<"NODO ELIMINADO...!!!!";
                return;
            }
        }
        else{
            ant=aux;
            aux=aux->siguiente;
        }
    }
}

void eliminar_arista(){
    char ini, fin;
    Tnodo aux, aux2;
    Tarista q,r;
    cout<<"\n ELIMINAR ARISTA\n";
    cout<<"INGRESE NODO DE INICIO:";
    cin>>ini;
    cout<<"INGRESE NODO FINAL:";
    cin>>fin;
    aux=p;
    aux2=p;
    while(aux2!=NULL){
        if(aux2->nombre==fin){
            break;
        }
        else
        aux2=aux2->siguiente;
    }
    while(aux!=NULL){
        if(aux->nombre==ini){
            q=aux->adyacencia;
            while(q!=NULL){
                if(q->destino==aux2){
                    if(q==aux->adyacencia)
                        aux->adyacencia=aux->adyacencia->siguiente;
                    else
                        r->siguiente=q->siguiente;
                    delete(q);
                    cout<<"ARISTA  "<<aux->nombre<<"----->"<<aux2->nombre<<" ELIMINADA.....!!!!";
                    return;
                }
            }
            r=q;
            q=q->siguiente;
        }
        aux = aux->siguiente;
    }
}

void mostrar_grafo(){   
    Tnodo ptr; 
    Tarista arista; 
    ptr=p; 
    cout<<"NODO|LISTA DE ADYACENCIA\n"; 
    while(ptr!=NULL){ 
        cout<<" "<<ptr->nombre<<"|";  
        if(ptr->adyacencia!=NULL){
            arista=ptr->adyacencia; 
        while(arista!=NULL){ 
            cout<<" "<<arista->destino->nombre; 
            cout<<" "<<arista->peso; 
            arista=arista->siguiente; 
        }
    } 
    ptr=ptr->siguiente; 
    cout<<endl; 
    } 
} 

void mostrar_aristas(){ 
    Tnodo aux; 
    Tarista arista; 
    char var; 
    cout<<"MOSTRAR ARISTAS DE NODO\n"; 
    cout<<"INGRESE NODO:"; 
    cin>>var; 
    aux=p; 
    while(aux!=NULL){ 
        if(aux->nombre==var){ 
            if(aux->adyacencia==NULL){ 
                cout<<"EL NODO NO TIENE ARISTAS...!!!!"; 
                return; 
            } 
            else{ 
                cout<<"NODO|LISTA DE ADYACENCIA\n"; 
                cout<<" "<<aux->nombre<<"|"; 
                arista=aux->adyacencia; 

                while(arista!=NULL) { 
                    cout<<arista->destino->nombre<<" ";
                    cout<<arista->peso<<" ";
                    arista=arista->siguiente; 
                } 
                cout<<endl; 
                return; 
            }
    } 
    else 
    aux=aux->siguiente; 
    } 
} 

int minKey(int key[], bool mstSet[]){
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;
	return min_index;
}

void printMST(int parent[], int graph[V][V]){
	cout<<"Edge \tWeight\n";
	for (int i = 1; i < tamanio; i++){
		cout<<parent[i]<<" - "<<i<<" \t"<<graph[i][parent[i]]<<" \n";
    }
}

void primMST(int graph[V][V]){
	int parent[V];
	int key[V];
	bool mstSet[V];

	for (int i = 0; i < V; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	key[0] = 0;
	parent[0] = -1;

	for (int count = 0; count < V - 1; count++){
		int u = minKey(key, mstSet);
		mstSet[u] = true;
		for (int v = 0; v < V; v++)
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}
	printMST(parent, graph);
}

void floydWarshall(int graph2[V][V]){
    for(int i=0;i<tamanio;i++){
            for(int j=0;j<tamanio;j++){
                if(i!=j && graph2[i][j]==0){
                    graph2[i][j]=INT_MAX;
                }
            }
        }
    int dist[V][V], i, j, k;
    for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			dist[i][j] = graph2[i][j];
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j])
					&& (dist[k][j] != INT_MAX
						&& dist[i][k] != INT_MAX))
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
    printSolution(dist);
}
void printSolution(int dist[V][V]){
	cout << "The following matrix shows the shortest "
			"distances"
			" between every pair of vertices \n";
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INT_MAX)
				cout << "INT_MAX"
					<< "	 ";
			else
				cout << dist[i][j] << "	 ";
		}
		cout << endl;
	}
}

int find(int i){
	while (parent[i] != i)
		i = parent[i];
	return i;
}

void union1(int i, int j){
	int a = find(i);
	int b = find(j);
	parent[a] = b;
}


void kruskalMST(int cost[V2][V2]){
    for (int i = 0; i < V2; i++){
        for(int j = 0; j < V2; j++){
            if (cost [i][j] == 0){
                cost[i][j] = INT_MAX;
            }

        }
    }
        
	int mincost = 0; 

	for (int i = 0; i < V2; i++)
		parent[i] = i;

	int edge_count = 0;
	while (edge_count < V2 - 1) {
		int min = INT_MAX, a = -1, b = -1;
		for (int i = 0; i < V2; i++) {
			for (int j = 0; j < V2; j++) {
				if (find(i) != find(j) && cost[i][j] < min) {
                    
                        min = cost[i][j];
                        a = i;
                        b = j;
				}
			}
		}
		union1(a, b);
        edge_count++;
        if(min != INT_MAX){
            printf("Edge %d:(%d, %d) cost:%d \n",
			edge_count, a+1, b+1, min);
		mincost += min;   
        }
	}
	printf("\n Minimum cost= %d \n", mincost);
}

int minDistance(int dist[], bool sptSet[]){
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void printSolution2(int dist[]){
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < tamanio; i++)
        if(dist[i]!=INT_MAX){
            printf("%d \t\t %d\n", i, dist[i]);
        }else{
            printf("%d \t\t 0\n", i);
        }
}

void dijkstra(int graph[V][V],int src){
    int dist[V]; 
    bool sptSet[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    dist[src] = 0;
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    printSolution2(dist);
}