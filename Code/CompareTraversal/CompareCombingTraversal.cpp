#include<bits/stdc++.h>
using namespace std;

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
class Graph{ 
    public:
        int V;
        vector<Vertex> vertices;
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
        	cout<<"here\n"<<V<<endl;
			for(int i = 1; i < V; ++i){
				cout<<i<<" -> ";
				for(int j = 0; j < vertices[i].edges.size(); ++j)
					cout<<vertices[i].edges[j]<<" ";
				cout<<endl;
			}
		}
        void BFS(int k){
			list<int> queue;
			vertices[k].isVisited = true;
			queue.push_back(k);
			list<int>::iterator i;

			while(!queue.empty()){
				k = queue.front();
				cout <<k<<" ";
				queue.pop_front();
				for(int i = 0; i < vertices[k].edges.size(); ++i)
					if(!vertices[vertices[k].edges[i]].isVisited){
						vertices[vertices[k].edges[i]].isVisited = true;
						queue.push_back(vertices[k].edges[i]);
					}
			}
        }
		void DFS(int k){
			vertices[k].isVisited = true;
			cout<<k<<" ";
			for(int i = 0; i < vertices[k].edges.size(); ++i)
				if(!vertices[vertices[k].edges[i]].isVisited)
					DFS(vertices[k].edges[i]);

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
	ifstream inp;
	inp.open("input.txt");
	if(!inp) { 
		cerr << "Error: file could not be opened" << endl;
		exit(1);
	}
    int vertices, edges, k;
	inp>>vertices;
	inp>>edges;
	cout<<vertices<<" "<<edges<<endl;
    Graph g1(vertices+1), g2(vertices+1), g3(vertices+1);
    for(int i = 0; i < edges; ++i){
		int src, dest;
		inp>>src;
		inp>>dest;
		g1.createEdge(src, dest);
		g2.createEdge(src, dest);
		g3.createEdge(src, dest);
	}
    inp>>k;
	vector<int> initNodes(k);
	for(int i = 0; i < k; ++i)
		inp>>initNodes[i];
   	g1.displayEdges();
	g2.displayEdges();
	g3.displayEdges();
	
	cout<<"\nBFS : ";
   	g2.BFS(initNodes[0]);
   	cout<<"\nDFS : ";
    g1.DFS(initNodes[0]);
	cout<<"\nCombing Traversal : ";
    g3.combingTraversal(k, initNodes);
 
    return 0;
}