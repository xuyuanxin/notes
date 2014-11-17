/*
bfs:breadth first search 广度优先搜索 
1 搜索最短路径
 for any vertex v reachable from s,BFS computes a shortest path from s to v



color[u] 顶点颜色 有三种 white gray black 
white 白色表示尚未搜索
gray vertices, which are discovered vertices that have not yet had their adjacency 
lists fully examined. 
black 黑色表示

从顶点S开始在图G中搜索
BFS(G, s) 
{
	for each vertex uin G
	{
	    color[u] = WHITE 
	    d[u] = ∞
	    p[u] = NIL
	}
	
	color[s] = GRAY 
	d[s] = 0 
	p[s] = NIL 
	    
	Q = NULL (空)
	ENQUEUE(Q, s)

	while Q ≠ NULL
	{
	    u = DEQUEUE(Q)
	    
	    for each vin Adj[u] 
	    {
	        if color[v] == WHITE
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



*/



