#include<bits/stdc++.h>
using namespace std;

/*	Vertex class represents a particular vertex */
class Vertex{
	public:
		int id;
		bool isVisited;
		vector<int> edges;
		Vertex(int id){
			this->id = id;
			isVisited = false;
		}
};
/* Graph class represents a Graph, having edges and set of vertices */
class Graph{
	int V;
	vector<Vertex> vertices;
	public:
		Graph(int v){
			V = v;
			for(int i = 1; i < V; ++i)
				vertices.push_back(Vertex(i));
		}
		void createEdge(int src, int dest){
			vertices[src].edges.push_back(dest);
			vertices[dest].edges.push_back(src);
		}
		void displayEdges(){
			for(int i = 1; i < V; ++i){
				cout<<i<<" -> ";
				for(int j = 0; j < vertices[i].edges.size(); ++j)
					cout<<vertices[i].edges[j]<<" ";
				cout<<endl;
			}
		}
		vector<int> getPossiblePaths(int n){
			vector<int> arr;
			for(int i = 0; i < vertices[n].edges.size(); ++i)
				if(!vertices[vertices[n].edges[i]].isVisited)
					arr.push_back(vertices[n].edges[i]);
			return arr;
		}
		void combingTraversal(int k, vector<int> combingNodes){
			vector<unordered_set<int>> posPaths(k);
			int pass = 1;
            cout<<"\nPass : "<<pass++<<" ->\t";
            for(int i = 0; i < k; ++i){
                cout<<combingNodes[i]<<"\t";
                vertices[combingNodes[i]].isVisited = true;
            }
			while(1){
				int breakT = 0;
				cout<<"\nPass : "<<pass++<<" ->\t";
				for(int i = 0; i < k; ++i){
					if(combingNodes[i] != -1){
						vector<int> arr = getPossiblePaths(combingNodes[i]);
						if(arr.size() > 0){	//There are not-traversed nodes to be traversed
							int index = rand() % arr.size();
							combingNodes[i] = arr[index];
							arr.erase(arr.begin()+index);
							posPaths[i].insert(arr.begin(), arr.end());
							
						}else{	//We have to pick from set
							while(posPaths[i].size() > 0 && vertices[*posPaths[i].begin()].isVisited)
								posPaths[i].erase(*posPaths[i].begin());
							if(posPaths[i].size() > 0){
								combingNodes[i] = *posPaths[i].begin();
								posPaths[i].erase(*posPaths[i].begin());
							}else
								combingNodes[i] = -1;
						}
                        if(combingNodes[i] != -1){
                            cout<<combingNodes[i]<<"\t";
						    vertices[combingNodes[i]].isVisited = true;
                        }
					}
					breakT = breakT || (combingNodes[i] != -1);
				}
				if(!breakT)
					break;
			}
		}
};
int main(){
	srand(time(NULL));
	freopen("TestCase//input2.txt", "r", stdin);
	int vertices, edges, k;
	cin>>vertices>>edges;
	Graph g(vertices+1);
	for(int i = 0; i < edges; ++i){
		int src, dest;
		cin>>src>>dest;
		g.createEdge(src, dest);
	}	
	cin>>k;
	vector<int> initNodes(k);
	for(int i = 0; i < k; ++i)
		cin>>initNodes[i];
	cout<<"Graph and it's Edges : \n";
	g.displayEdges();
	g.combingTraversal(k, initNodes);
	return 0;
}
