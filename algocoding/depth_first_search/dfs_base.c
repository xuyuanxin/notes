/*-----------------------------------------------------------------------------------
----> Depth-first search
The strategy followed by depth-first search is, as its name implies, to search "deep-
er" in the graph whenever possible. In depth-first search, edges are explored out  of 
the most recently discovered vertex v that still has unexplored edges leaving it. Wh-
en all of v's edges have been explored, the search "backtracks" to explore edges lea-
ving the vertex from which v was discovered. This process continues until we have di-
scovered all the vertices that are reachable from the original source vertex. If  any 
undiscovered vertices remain, then one of them is selected as a new source and the s-
earch is repeated from that source. This entire process is repeated until all vertic-
es are discovered


DFS(G) 
{
    for each vertex uin G
    {
        color[u] = WHITE 
        p[u] = NIL 
    }
    
	time = 0
    
    for each vertex uin G
    {
        if color[u] = WHITE
        {
            DFS-VISIT(u) 
        }
    }
}


DFS-VISIT(u)
{
    color[u] = GRAY 
    time = time+1 
    d[u] = time
    
    for each vin Adj[u]
    {
        if color[v] == WHITE
        {
            p[v] = u
            DFS-VISIT(v) 
        }
    }
    color[u] = BLACK
    f[u] = time+1 
}


adj[]
0--> 2,1,5
1--> 0,2
2--> 0,1,3,4
3--> 5,4,2
4--> 3,2
5--> 3,0

  0----------2               
  | \       /| \                
  |  \     / |  \                
  |   \   /  |   \             
  |     1    |    \             
  |          |     \            
  5----------3-------4     


The search begins when the constructor calls the recursive dfs() to mark and visit v-
ertex 0 and proceeds as follows:

Since 2 is first on 0's adjacency list and is unmarked, dfs() recursively calls itse-
lf to mark and visit 2.

Now, 0 is first on 2's adjacency list and is marked, so dfs() skips it. Then, since -
1 is next on 2's adjacency list and is unmarked, dfs() recursively calls itself to m-
ark and visit 1.

Visiting 1 is different: since both vertices on its list(0 and 2) are already marked,
no recursive calls are needed, and dfs() returns from the recursive call dfs(1) . The
next edge examined is 2-3(since 3 is the vertex after 1 on 2's adjacency list), so  -
dfs() recursive calls itself to mark and visit 3.

Vertex 5 is first on 3's adjacency list and is unmarked, so dfs() recursively calls -
itself to mark and visit 5.

Both vertices on 5's list(3 and 0) are already marked, so no recursive calls are nee-
ded.

Vertex 4 is next on 3's adjacency list and is unmarked, so dfs() recursively calls -
itself to mark and visit 4, the last vertex to be marked.

After 4 is marked, dfs() needs to check the vertices on its list , then the remaining
vertices on 3's list, then 2's list, then 0's list, but no more recursive call happen
because all vertices are marked.
-----------------------------------------------------------------------------------*/
