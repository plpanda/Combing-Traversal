#include<iostream>
#include<vector>
#include<queue>
#include <stdio.h>

using namespace std;
/*	Vertex class represents a particular vertex */
class Vertex{
	public:
		int id, level, degree;
		bool isRoot, isVisited;
		Vertex(int id){
			this->id = id;
			isVisited = false;
			level = -1;
			degree = 0;
		}
		void print(){
			cout<<"("<<id<<" d="<<degree<<" l="<<level<<")";
			if(isVisited)
				cout<<"*";
		}
};
/* Graph class represents a Graph, having edges and set of vertices */
class Graph{
	int V, rootId;
	vector<Vertex> vertices;
	int **edges;
	public:
		Graph(int v){
			V = v;
			edges = new int*[V];
			for(int i = 0; i < V; ++i){
				vertices.push_back(Vertex(i));
				edges[i] = new int[V];
				for(int j = 0; j < V; ++j){
					edges[i][j] = 0;
				}
			}
		}
		void setRootNode(int id){
			rootId = id-1;
		}
		void createEdge(int src, int dest){
			edges[src-1][dest-1] = 1;
			edges[dest-1][src-1] = 1;
			vertices[src-1].degree++;
			vertices[dest-1].degree++;
		}
		void displayVertices(){
			for(int i = 0; i < V; ++i){
				if(i==rootId)
					cout<<"=>";
				vertices[i].print();
				cout<<"\t";
			}
			cout<<endl;
		}
		void displayEdges(){
			for(int i = 0; i < V; ++i){
				for(int j = 0; j < V; ++j){
					cout<<edges[i][j]<<" ";
				}
				cout<<endl;
			}
		}
		/* Assign level to each vertex based on its position
		   from root node in the graph */
		void assignLevel(){
			vertices[rootId].level = 0;
			vector<int> que;
			for(int i = 0; i < V; ++i)
				if(edges[rootId][i]){
					que.push_back(i);
					vertices[i].level = 1;
				}
			while(que.size() != 0){
				for(int i = 0; i < V; ++i)
					if(edges[que[0]][i] && vertices[i].level == -1){
						que.push_back(i);
						vertices[i].level = vertices[que[0]].level + 1;
					}/*else if(edges[que[0]][i] && vertices[i].level != -1){
						vertices[i].level = min(vertices[que[0]].level + 1, vertices[i].level);
					}*/
				que.erase(que.begin());
			}
		}
		/* Select k outer nodes to begin combing traversal with, 
		   Greedily selects the highest level nodes first, then
		   nodes with highest degree */
		vector<int> findOuterNodes(int k){
			vector<int> nodes;
			nodes.push_back(0);
			int j;
			for(int i = 1; i < V; ++i){
				j = i-1;
				while(j >= 0 && (vertices[i].level > vertices[nodes[j]].level || 
					(vertices[i].level == vertices[nodes[j]].level && vertices[nodes[j]].degree < vertices[i].degree))){
					nodes[j+1] = nodes[j];
					j--;
				}
				nodes[j+1] = i;
			}
			nodes.erase(next(nodes.begin(),k),nodes.end());
			return nodes;
		}
		/* Acc to BFS, if a node is visited, in the next phase all its 
			neighbouring unvisited nodes are visited. This method finds
			out the possible neighbouring unvisited nodes sorted by highest 
			level then highest degree greedily */
		vector<int> findPossiblePaths(int node){
			vector<int> posNodes;
			for(int i = 0; i < V; ++i)
				if(edges[node][i] && !vertices[i].isVisited)
					posNodes.push_back(i);
			int j, temp;
			for(int i = 1; i < posNodes.size(); ++i){
				j = i-1;
				temp = posNodes[i];
				while(j >= 0 &&(vertices[temp].level > vertices[posNodes[j]].level ||
					(vertices[temp].level == vertices[posNodes[j]].level && vertices[posNodes[j]].degree < vertices[temp].degree))){
					posNodes[j+1] = posNodes[j];
					j--;
				}
				posNodes[j+1] = temp;
			}
			return posNodes;
		}
		/* Implementation of combing traversal */
		void startCombingBFS(int k){
			vector<int> initNodes = findOuterNodes(k);
			vector<queue<int>> bfsQ(k);
			for(int i = 0; i < k; ++i)
				bfsQ[i].push(initNodes[i]);
			int pass = 1;
			while(true){
				bool condition = false;
				for(int i = 0; i < k; ++i)
					if(bfsQ[i].size() > 0){
						condition = true;
						break;
					}
				if(!condition)
					break;
				cout<<"\nPass : "<<pass<<"; Visited Nodes : ";
				for(int i = 0; i < k; ++i){
					while(bfsQ[i].size() && vertices[bfsQ[i].front()].isVisited)
						bfsQ[i].pop();
					if(!bfsQ[i].size())
						continue;
					int node = bfsQ[i].front();
					bfsQ[i].pop();
					cout<<"*"<<node<<"\t";
					vertices[node].isVisited = true;
					vector<int> nextVisit = findPossiblePaths(node);
					for(int j = 0; j < nextVisit.size(); ++j)					
						bfsQ[i].push(nextVisit[j]);
				}
				pass++;
			}
		}
};
int main(){
	freopen("TestCase//input.txt", "r", stdin);
	/*Graph g(13);
	g.setRootNode(1);
	
	g.createEdge(1,2);
	g.createEdge(1,3);
	g.createEdge(1,4);
	g.createEdge(1,5);
	g.createEdge(1,6);
	g.createEdge(2,7);
	g.createEdge(4,8);
	g.createEdge(4,9);
	g.createEdge(6,10);
	g.createEdge(6,11);
	g.createEdge(6,12);
	g.createEdge(7,13);
		
	g.assignLevel();	
	g.displayVertices();
	g.startCombingBFS(4);*/
	
	int vertices, root, edges, k;
	cin>>vertices>>root>>edges;
	Graph g(vertices);
	g.setRootNode(root);
	for(int i = 0; i < edges; ++i){
		int src, dest;
		cin>>src>>dest;
		g.createEdge(src, dest);
	}
	cin>>k;
	g.assignLevel();	
	g.displayVertices();
	g.startCombingBFS(k);
	return 0;
}
