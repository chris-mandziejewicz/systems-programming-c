/* forward declarations so self-referential structures are simpler */
typedef struct vertex vertex_t;
typedef struct adj_vertex adj_vertex_t;

struct vertex {
	char *name;
	adj_vertex_t *adj_list;
	vertex_t *next;
};

struct adj_vertex {
	vertex_t *vertex;
	int edge_weight;
	adj_vertex_t *next;	
};

/* This is the one function you really should implement as part of your 
 * graph data structure's public API. 
 *
 * `add_edge` adds the specified edge to the graph passed in via the first
 * argument. If either of the edge's vertices are not already in the graph,
 * they are added before their adjacency lists are updated. If the graph
 * is currently empty (i.e., *vtxhead == NULL), a new graph is created,
 * and the caller's vtxhead pointer is modified. 
 *
 * `vtxhead`: the pointer to the graph (more specifically, the head of the
 *            list of vertex_t structures)
 * `v1_name`: the name of the first vertex of the edge to add
 * `v2_name`: the name of the second vertex of the edge to add
 * `weight` : the weight of the edge to add
 */
void add_edge (vertex_t **vtxhead, char *v1_name, char *v2_name, int weight);
vertex_t *add_vertex (vertex_t **vtxhead, char *v_name);
vertex_t *find_vertex(vertex_t **vtxhead, char *name);
void add_adj_vertex(vertex_t **vtxhead, char *v_name, char *a_name, int weight);
int numVertices(vertex_t **vtxhead);
int threeVerticesOnePath(vertex_t **vtxhead);
vertex_t *find_start(vertex_t **vtxhead);
void tour_path(vertex_t **vtxhead, int VerticesToCheck, char **arr, int addToListCheck, int initialVertices, int distance, int tempdistance);
void free_vertices(vertex_t **vtxhead);
