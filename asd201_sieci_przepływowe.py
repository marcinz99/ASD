##############################
### from, to, weight #########
graph = [(0, 1, 4),
         (0, 3, 3),
         (0, 5, 3),
         (1, 2, 4),
         (1, 4, 2),
         (2, 4, 2),
         (2, 6, 5),
         (3, 2, 2),
         (3, 5, 1),
         (4, 6, 3),
         (5, 4, 2)]
V = 7
E = 11
###############################
class Colors:
	white = 0
	gray = 1
	black = 2
###############################
	
def createGraphRepresentation():
	gr = list()
	for i in range(V):
		gr.append(list())
	for i in graph:
		gr[i[0]].append((i[1], i[2]))
	return gr


def findExtendingPath(gr, cf, s, t):
	extp = list()
	parent = list()
	color = list()
	for i in range(V):
		color.append(Colors.white)
		parent.append(-1)
	
	queue = list()
	queue.append(s)
	color[s] = Colors.gray
	
	while len(queue) != 0:
		u = queue.pop(0)
		for i in range(V):
			if cf[u][i] > 0 and color[i] == Colors.white:
				color[i] = Colors.gray
				parent[i] = u
				queue.append(i)
		color[u] = Colors.black
	
	i = t
	while i != -1:
		extp.insert(0, i)
		i = parent[i]
	return extp

def fordFulkerson(gr, s=-1, t=-1):
	if s == -1: s = 0
	if t == -1: t = V-1
	cf = list()
	for i in range(V):
		cf.append(list())
		for j in range(V):
			cf[i].append(-1)
	
	max_flow = 0
	for i in range(V):
		for j in gr[i]:
			cf[i][j[0]] = j[1]
			cf[j[0]][i] = 0

	while True:
		path = findExtendingPath(gr, cf, s, t)
		print(path)
		if len(path) <= 1: break
		edges = list()
		for i in range(len(path)-1):
			edges.append((path[i], path[i+1]))
		print(edges)
		
		current_flow = cf[edges[0][0]][edges[0][1]]
		for i in edges:
			if cf[i[0]][i[1]] < current_flow: current_flow = cf[i[0]][i[1]]
		
		print("Aktualny przepływ: {}".format(current_flow))
		max_flow += current_flow
		for i in edges:
			cf[i[0]][i[1]] -= current_flow
			cf[i[1]][i[0]] += current_flow
	
	print("\nMaksymalny przepływ: {}".format(max_flow))

def main():
	gr = createGraphRepresentation()
	fordFulkerson(gr)
main()
