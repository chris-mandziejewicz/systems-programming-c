#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

int main (int argc, char *argv[]) {
    int i = 1, weight;
    int numOfVertices = 0;
    char *first = "test", *second = "test";

    vertex_t *vlist_head = NULL;
    //Since argv[0] is the name of the file, use 1
    while ( argv[i] != NULL && argv[i + 1] != NULL && argv[i + 2] != NULL ) {
	//First vertex, second vertex, weight
	first = argv[i];
	second = argv[i+1];
	weight = atoi(argv[i+2]);
	add_edge(&vlist_head, first, second, weight);
	i = i + 3;
    }

    /* print out our adjacency list */
    vertex_t *vp;
    adj_vertex_t *adj_v;
    printf("Adjacency list:\n");
    for (vp = vlist_head; vp != NULL; vp = vp->next) {
	printf("  %s: ", vp->name);
	for (adj_v = vp->adj_list; adj_v != NULL; adj_v = adj_v->next) {
	    printf("%s(%d) ", adj_v->vertex->name, adj_v->edge_weight);
	}
	printf("\n");
    }

    //Find the number of vertices
    if ( vlist_head != NULL ) {
	numOfVertices = numVertices(&vlist_head);


	//If three vertices or more have just one path, no tour exists.
	if ( threeVerticesOnePath(&vlist_head) ) {
	    printf("No tour exists.\n");
	}else{
	    //Start a start and will find a tour if it exists
	    vertex_t *start = find_start(&vlist_head);
	    //Set up dynamic array of strings using malloc.
	    //Will be used to store and check tour path.
	    //Works like an array list.
	    char **arr = (char **)malloc(sizeof(char) * numOfVertices * 100);//that 100 is to make sure it does not seg fault

	    //Set the first element to the start
	    arr[0] = (start->name);
	    int distance = 0;

	    int addToListCheck = 0;
	    tour_path(&start, numOfVertices - 1, arr, addToListCheck, numOfVertices, distance, distance);
	    //If the last element is not added that means no tour was found
	    if ( arr[numOfVertices - 1] == NULL ) {
		printf("No tour exists\n");
	    }
	    //Free the arr I made
	    free(arr);
	}
    }else{
	printf("No tour exists\n");
    }
    printf("\n");
    //Free all structures
    free_vertices(&vlist_head);
    return 0;
}
