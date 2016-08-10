#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

/* implement the functions you declare in graph.h here */

vertex_t *add_vertex (vertex_t **vtxhead, char *v_name) {
    //If the head is NULL make a graph and set head to the first vertex.
    if ( *vtxhead == NULL ) {
	*vtxhead = malloc(sizeof(vertex_t));
	(*vtxhead)->name = v_name;
	return *vtxhead;
    }else{
	vertex_t *temp = *vtxhead;
	//Find the `next` which is NULL
	while ( (temp)->next != NULL ) {
	    temp = (temp)->next;
	}
	//Add to the `next` which was NULL
	(temp)->next = malloc(sizeof(vertex_t));
	temp = (temp)->next;
	(temp)->name = v_name;
	return temp;
    }
}

vertex_t *find_vertex(vertex_t **vtxhead, char *name) {
    vertex_t *temp = *vtxhead;
    //If equal return the temp;
    if ( (strcmp (temp->name, name)) == 0 ) {
	return temp;
	//If the next one is NULL there is no match
    }else if ( ( temp->next ) == NULL ) {
	return 0;
    }else{
	//Use recursion to test all vertices.
	temp = (temp->next);
	return find_vertex(&temp, name);
    }
}

void add_adj_vertex(vertex_t **vtxhead, char *v_name, char *a_name, int weight) {
    vertex_t *vtemp = *vtxhead;//The vertex to use to go to adj_list
    vertex_t *atemp = *vtxhead;//The vertex to link to for adj_vertex->vertex
    adj_vertex_t *adj_temp;//If the adj_list is not empty use a temp pointer
    vtemp = find_vertex(vtxhead, v_name);
    atemp = find_vertex(vtxhead, a_name);

    //Set check to 1 make a new adj_list struct.
    int check = 1;
    if ( ( vtemp->adj_list ) == NULL ) {
	( vtemp->adj_list ) = malloc(sizeof(adj_vertex_t));
	( vtemp->adj_list->vertex ) = atemp;
	( vtemp->adj_list->edge_weight ) = weight;
	check = 0;
    }

    //If the list was not null enter this block
    if ( check ){
	adj_temp = vtemp->adj_list;

	//Find the null part of the adj vertex
	while( ( adj_temp->next ) != NULL ) {
	    adj_temp = ( adj_temp->next );
	}
	//Add to the null part
	adj_temp->next = malloc(sizeof(adj_vertex_t));
	adj_temp = ( adj_temp->next );
	adj_temp->edge_weight = weight;
	adj_temp->vertex = atemp;
    }
}


void add_edge (vertex_t **vtxhead, char *v1_name, char *v2_name, int weight) {
    if ( *vtxhead == NULL ) {
	add_vertex(vtxhead, v1_name);    
	add_vertex(vtxhead, v2_name);
    }
    //If the vertex is not found; add it
    if ( find_vertex(vtxhead, v1_name) == 0 ) {
	add_vertex(vtxhead, v1_name);
    }

    if ( find_vertex(vtxhead, v2_name) == 0 ) {
	add_vertex(vtxhead, v2_name);
    }
    add_adj_vertex(vtxhead, v1_name, v2_name, weight);
    add_adj_vertex(vtxhead, v2_name, v1_name, weight);
}

//Finds the number of vertices
int numVertices( vertex_t **vtxhead ) {
    vertex_t *temp = *vtxhead;
    int numOfVertices = 0;
    if ( temp == NULL ) {
	return numOfVertices;
    }

    numOfVertices++;

    while ( ( temp->next ) != NULL ) {
	numOfVertices++;
	temp = ( temp->next );
    }
    return numOfVertices;
}

//Checks if three vertices have one path.
//This means no tour exists.
int threeVerticesOnePath( vertex_t **vtxhead ) {
    vertex_t *temp = *vtxhead;
    int foundVertices = 0;
    while ( ( temp ) != NULL ) {
	if ( ( temp->adj_list->next ) == NULL ) {
	    foundVertices++;
	}
	temp = ( temp->next );
    }

    //If greater than 3. No tour exists.
    if ( foundVertices >= 3 ) {
	return 1;
    }else{
	return 0;
    }

}

//Find a starting point
vertex_t *find_start( vertex_t **vtxhead ) {
    vertex_t *temp = *vtxhead;
    //If there is a vertex with only one path that must be the starting point.
    //If there are two with one path it chooses the first one it finds.
    while ( ( temp ) != NULL ) {
	if ( ( temp->adj_list->next ) == NULL ) {
	    return temp;
	}
	temp = ( temp->next );
    }
    //Otherwise the first vertex will work
    return *vtxhead;
}

void tour_path(vertex_t **vtxhead, int VerticesToCheck, char **arr, int addToListCheck, int initialVertices, int distance, int tempdistance) {
    vertex_t *temp = *vtxhead;
    adj_vertex_t *adj_temp;
    int check= 0;

    if ( temp != NULL ) {
	//For the initial arr[0] already made in main.c
	if ( addToListCheck != 0 ) {

	    int i;
	    for ( i = 0; i < initialVertices - VerticesToCheck; i++) {
		if ( strcmp( (temp->name) , arr[i] ) == 0 )  {
		    break;
		}else{
		    check = 1;
		}
	    }
	    if ( check == 1 ) {
		distance = distance + tempdistance;

		arr[ initialVertices - VerticesToCheck ] = temp->name;
		VerticesToCheck--;
	    }
	}


	//If VerticesToCheck == 0 that means a tour was already found
	if ( VerticesToCheck != 0 ) {
	    //To add found path vertices
	    addToListCheck = addToListCheck + 1;
	    adj_temp = (temp->adj_list);	//Set the adj list to the adj list of the vertex being checked.


	    //While the adj vertices is not null continue going through the vertices to find paths
	    while ( adj_temp !=  NULL ) {
		int stringsInArr = initialVertices - VerticesToCheck;	//The number of elements in the arr
		int i;
		//FORLOOP: label used to continue going into the for loop with the adj_vertex advanced to the next one
		//Continues until the vertex is not already in the arr or when all paths were taken
FORLOOP:
		if ( adj_temp != NULL ) {

		    for ( i = 0; i < stringsInArr; i++) {
			//Checks to see if the vertex is not in the arr
			if ( strcmp( (adj_temp->vertex->name) , arr[i] ) == 0 )  {
			    adj_temp = (adj_temp->next);
			    goto FORLOOP;
			}
		    }
		}

		//Found the vertex. Use recursion with updated arguments
		if ( adj_temp != NULL ) {
		    tour_path( &(adj_temp->vertex), VerticesToCheck, arr, addToListCheck, initialVertices, distance, adj_temp->edge_weight);
		}else{
		    break;
		}
		//To continue the while loop
		adj_temp = (adj_temp->next);
	    }
	    //The arr[initialVertices + 1] == NULL is to make sure it prints only one tour path
	}else if ( ( VerticesToCheck == 0 ) && ( arr[initialVertices + 1] == NULL ) ) {
	    arr[initialVertices + 1] = "TEST";	//Once a tour is found this is used not print other tours
	    printf("\nTour path:\n   ");
	    int i;
	    for ( i = 0; i < initialVertices; i++ ) {
		printf("%s ", arr[i]);
	    }
	    printf("\nTour length: %d\n", distance);
	}
    }
}

void free_vertices(vertex_t **vtxhead) {
    vertex_t *vtemp = *vtxhead;
    //Frees all vertices. Sets next to the next vertex so the current one can be freed
    while ( vtemp != NULL ) {
	adj_vertex_t *atemp = ( vtemp->adj_list );
	//Same idea but with the adjacent vertices
	while ( atemp != NULL ) {
	    adj_vertex_t *anext = atemp->next;
	    free(atemp);
	    atemp = anext;
	}
	vertex_t *vnext = vtemp->next;
	free(vtemp);
	vtemp = vnext;
    }
}
