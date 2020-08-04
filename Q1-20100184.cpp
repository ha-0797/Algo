#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


class node;

class edge{
public:
	node* Origin;
	node* Dest;
};

class node{
public:
	string chem;
	vector<node*> edges;
	//for BFS
	node* parent;
	bool visit; 		
	int level;			
};


class listNode{
public:
	node* val;
	listNode* next;
};

class queue{
public:
	int count;
	listNode* head;
	listNode* tail;

	queue(node* temp){
		listNode* val = new listNode;
		val -> val = temp;
		val -> next = NULL;
		head = val;
		tail = val;
		count = 1;
		temp -> visit = true;
	}

	void push(node* val){
		listNode* temp = new listNode;
		temp -> val = val;
		temp -> next = NULL;
		tail -> next = temp;
		tail = temp;
		count++;
	}

	node* pop(){
		node* temp = head -> val;
		listNode* temp2;
		for(int i = 0; i < temp ->edges.size();i++){
			if(!temp-> edges[i]->visit){
				temp -> edges[i] -> visit = true;
				temp -> edges[i] -> parent = temp;
				temp -> edges[i] -> level = temp -> level + 1;
				push(temp -> edges[i]);
			}
		}
		temp2 = head;
		head = head -> next;
		temp = temp2 -> val;
		delete temp2;
		count--;
		return temp;
	}
};


class graph{
public:
	vector<node*> chems;
	vector<edge> reacts;
	vector<node*> g_BFS;
	

	graph(char* file){		//O(n|E| + |V|)
		string buff, s_temp;
		ifstream f;
		node* n_temp;
		edge* e_temp;
		int size;
		f.open(file);
		f >> buff >> size;
		getline(f, buff);

		//make all nodes
		for(int i = 0; i < size; i++){				//O(|V|)
			f >> buff;
			buff = buff.substr(0,buff.length()-1);
			n_temp = new node;
			n_temp -> parent = NULL;
			n_temp -> chem = buff;
			n_temp -> visit = false;
			chems.push_back(n_temp);
			getline(f, buff);
		}


		f.close();
		f.open(file);
		getline(f, buff);

		//make all edges
		for(int i = 0; i < size; i++){							//O(n|E|)
			getline(f, buff);
			int pos = buff.find(":");
			buff = buff.substr(pos+2);
			while(pos != -1){									//O(degree(v))
				pos = buff.find(",");
				if(pos == -1){
					s_temp = buff;
				} else{
					s_temp = buff.substr(0,pos);
				}
				for(int j = 0; j < size; j++){
					if(chems[j] -> chem == s_temp){
						e_temp = new edge;
						e_temp -> Origin = chems[i];
						e_temp -> Dest = chems[j];
						chems[i] -> edges.push_back(chems[j]);
						reacts.push_back(*e_temp);
						break;
					}
				}
				buff = buff.substr(pos + 2);
			}
		}

	}

	BFS(){
		queue q(chems[0]);
		chems[0] -> level = 0;
		while(q.count){			//O(|V|)
			q.pop();
		}	
	}
};


int main(int argc, char const *argv[])
{
	char buff[256];
	int size;
	bool check = true;
	node* fail1, *fail2;
	vector<node*> box1, box2;
	graph* g;
	cout << "Enter file name: ";
	cin >> buff;
	g = new graph(buff);			//O(n|E|+|V|)
	g->BFS();						//O(|V|)
	for(int i = 0; i < g -> reacts.size(); i++){			//O(|E|)
		if(g -> reacts[i].Origin -> level == g -> reacts[i].Dest -> level){
			check = false;
			fail1 = g -> reacts[i].Origin;
			fail2 = g -> reacts[i].Dest;
			break;
		}
	}
	if(check){
		cout << "Yes" << endl;
		for(int i = 0; i < g -> chems.size(); i++){			//O(|V|)
			if((g->chems[i] -> level)%2){
				box2.push_back(g -> chems[i]);
			} else{
				box1.push_back(g -> chems[i]);
			}
		}
		for(int i = 0; i < box1.size(); i++){				//O(|V|)
			cout << box1[i] -> chem;
			if(i < box1.size()-1)
				cout << ", "; 
			else
				cout << endl;
		}
		for(int i = 0; i < box2.size(); i++){				//O(|V|)
			cout << box2[i] -> chem;
			if(i < box1.size()-1)
				cout << ", ";
		}
	} else{
		cout << "No" << endl;
		while(fail1){
			box1.push_back(fail1);
			fail1 = fail1 -> parent;
		}
		reverse(box1.begin(), box1.end());					//O(|V|)
		while(fail2){										//O(|V|)
			box2.push_back(fail2);
			fail2 = fail2 -> parent;
		}
		box1.insert(box1.end(), box2.begin(), box2.end());	//O(|V|)
		for( int i = 0; i < box1.size(); i++){				//O(|V|)
			cout << box1[i] -> chem ;
			if(i < box1.size()-1){
				cout << " -> ";
			}
		}
	}
	return 0;
}