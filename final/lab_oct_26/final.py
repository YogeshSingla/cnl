# Computer Networks Lab Assignment
# Routing
# author: yogesh (kirito)

import random as r
import math

MAX_X = 100
MAX_Y = 100
MIN_X = 0
MIN_Y = 0
NUM_NODES = 10
INF = 999999

def create_node():
	x = int(r.random()*(MAX_X-MIN_X) + MIN_X)
	y = int(r.random()*(MAX_Y-MIN_Y) + MIN_Y)

	return [x,y]

def weights(n1,n2):
	square_sum = 0
	for p1,p2 in zip(n1,n2):
		square_sum = square_sum + ( p1 - p2 )**2
		#print(square_sum)
	distance = math.sqrt(square_sum)
	weight = int(2*distance)

	#assigning random weight
	weight = int(100*r.random())

	return weight

def print_network():
	for row in weight_matrix:
		print(row)


network = []

#creates nodes
for i in range(0,NUM_NODES):
	n = create_node()
	network.append(n)

#find weights between the nodes
weight_matrix = []
for i in range(0,NUM_NODES):
	row = []
	for j in range(0,NUM_NODES):
		row.append([0])
	weight_matrix.append(row)

for i in range(0,NUM_NODES):
	for j in range(0,NUM_NODES):
			weight_matrix[i][j] = weights(network[i],network[j])


source_dist = []
source_last_node = []
not_visited = []
visited = []

def dijkestra(source,destination):
	"""
	currently it works as bellman-ford
	replace the looping condition from change_in_iter to destination!=current_node to find single 
	source single destination dijkestra algorithm
	"""
	source_dist = []
	source_last_node = []
	not_visited = []
	visited = []
	for i in range(0,NUM_NODES):
		source_dist.append(INF)
		source_last_node.append(INF)
		not_visited.append(i)
	source_dist[source] = 0
	source_last_node[source] = 0
	current_node = source	#current_node stores the index of node from network list
	change_in_iter = 1
	while(change_in_iter):
		change_in_iter = 0

		#find neighbours
		for to_node in range(0,NUM_NODES):


			dist_neighbour = weight_matrix[current_node][to_node] + source_dist[current_node] 
			if(dist_neighbour<source_dist[to_node]):
				source_dist[to_node] = dist_neighbour
				source_last_node[to_node] = current_node
				change_in_iter = 1
			

		#print("Current node:",current_node)
		#print("Visited nodes:",visited)
		#print(" Unvisited nodes:",not_visited)
		#print("Distance from source:",source_dist)
		#print("Path", source_last_node)
		#print("\n")

		visited.append(current_node)
		not_visited.remove(current_node)
		min = INF
		
		for node in not_visited:
			if( min >= source_dist[node]):
				current_node = node
				min = source_dist[node]
				change_in_iter = 1

	print("source:",source)	
	print("Visited nodes:",visited)
	print(" Unvisited nodes:",not_visited)
	print("Distance from source :",source_dist)
	print("Path list is: ", source_last_node)

	p = destination
	path = []
	while(p!=source):
		path.append(p)
		p = source_last_node[p]
	path.append(source)
	path.reverse()
	print("path from {} to {} is {}".format(source,destination,path))
	print("\n")

print("Nodes in the network are: ",network)
print("\n")
print("Weights between nodes are : ")
print(print_network())
print("\n")





#dijkestra(0)


#question 1
for i in range(0,5):
	dijkestra(int(r.random()*NUM_NODES),int(r.random()*NUM_NODES))

#question 2
start_node = int(r.random()*NUM_NODES)
for i in range(0,NUM_NODES):
	dijkestra(start_node,i)
