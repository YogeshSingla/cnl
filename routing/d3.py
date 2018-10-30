graph = { 'A' : ['B','C','E'],
          'B' : ['D','A','E'],
          'C' : ['A','F','G'],
          'D' : ['B','E'],
          'E' : ['A','B','D'],
          'F' : ['C'],
          'G' : ['C']}

def dfs(graph, start):
    stack = [start]
    visited = []
    
    while stack:
        #push neighbours of current node in stack
        current_node = stack.pop() #use pop() for stack-dfs
        if current_node not in visited:
            visited.append(current_node)
            for n in graph[current_node]:
                stack.append(n)
            print current_node,
        
print("\ndfs")
dfs(graph,'A')