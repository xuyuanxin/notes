/*
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



