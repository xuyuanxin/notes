/*-----------------------------------------------------------------------------------
----> Breadth-first search 
Given a graph G=(V,E) and a distinguished source vertex s, breadth-first search syst-
ematically explores the edges of G to  "discover" every vertex that is reachable from 
s. It computes the distance (smallest number of edges) from s to each reachable vert-
ex. It also produces a "breadth-first tree" with root s that contains all reachable -
vertices. For any vertex v reachable from s, the simple path in the breadth-first tr-
ee from s to v corresponds to a "shortest path" from s to v in G, that is, a path co-
ntaining the smallest number of edges. The algorithm works on both directed and undi-
rected graphs.

Breadth-first search is so named because it expands the frontier between discovered -
and undiscovered vertices uniformly across the breadth of the frontier. That is , the 
algorithm discovers all vertices at distance k from s before discovering any vertices 
at distance k + 1.


----> breadth-first tree
Breadth-first search constructs a breadth-first tree, initially containing only its -
root, which is the source vertex s. Whenever the search discovers a white vertex v in 
the course of scanning the adjacency list of an already discovered vertex u, the ver-
tex v and the edge (u,v) are added to the tree. We say that u is the predecessor or -
parent of v in the breadth-first tree. Since a vertex is discovered at most once , it
has at most one parent. Ancestor and descendant relationships in the breadth-first t-
ree are defined relative to the root s as usual: if u is on the simple path in the t-
ree from the root s to vertex v , then u is an ancestor of v and v is a descendant of 
u.


----> procedure BFS

u.color   white gray black 
All vertices start out white and may later become gray and then black. A vertex is d-
iscovered the first time it is encountered during the search, at which time it becom-
es nonwhite(gray black). all vertices adjacent to black vertices have been discovere-
d. Gray vertices may have some adjacent white vertices; they represent the frontier -
between discovered and undiscovered vertices. 

The breadth-first-search procedure BFS below assumes that the input graph G=(V, E) is 
represented using adjacency lists.

u.color   the color of each vertex u
u.p       the predecessor of u 
u.d       the distance from the source s to vertex u
Q         first-in, first-out queue Q

BFS(G, s) 
{
	for each vertex uin G
	{
	    color[u] = WHITE 
	    d[u] = max
	    p[u] = NIL
	}
	
	color[s] = GRAY 
	d[s] = 0 
	p[s] = NIL 
	    
	Q = NULL 
	ENQUEUE(Q, s)

	while Q != NULL
	{
	    u = DEQUEUE(Q)
	    
	    for each vin Adj[u] 
	    {
	        if (color[v] == WHITE)
	        {
	            color[v] = GRAY 
	            d[v] = d[u] + 1 
	            p[v] = u
	            ENQUEUE(Q, v) 
	         }       
	    }
	    color[u] = BLACK 
	}
}

--------------------
adj[]
0--> 2,1,5
1--> 0,2
2--> 0,1,3,4
3--> 5,4,2
4--> 3,2
5--> 3,0




*/

