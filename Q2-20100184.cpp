#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class ListNode{
public:
	string leader;
	ListNode* next;
	ListNode* parent;
};


int main(int argc, char const *argv[])
{
	map<string,int> stuff;
	ifstream f;
	ListNode** graph, *temp, *prev;
	string line,leader, *stuff2;
	bool DAG = false;
	char buff[256];
	int size,count = 0,*check,*set;
	vector<ListNode*> top_sort;


	cout << "Enter file name: ";
	cin >> buff;
	f.open(buff);
	f >> buff >> size;
	check = new int[size];
	graph = new ListNode*[size];
	set = new int[size];
	stuff2 = new string[size];

	//create adjacency list
	getline(f,line);
	while(getline(f,line)){
		int pos = line.find(":");
		leader = line.substr(0,pos);
		prev = new ListNode;
		prev -> leader = leader;
		prev -> next = NULL;
		graph[count] = prev;
		stuff[leader] = count;
		stuff2[count] = leader;
		count++;
		if(line.length() > pos+2)
			line = line.substr(pos +2);
		else
			line = line.substr(pos);
		while(line.length() > 1){
			temp = new ListNode;
			temp -> next = NULL;
			pos = line.find(",");
			if(pos == -1){
				temp -> leader = line.substr(0,line.length());
				prev -> next = temp;
				break;
			} else{
				leader = line.substr(0, pos);
				temp -> leader = leader;
				prev -> next = temp;
				prev = temp;
				line = line.substr(pos + 2);
			}
		}
	}


	for(int i = 0; i < size; i++){
		check[i] = 0;
	}

	//create array which stores cardinality
	for(int i = 0; i < size; i++){
		temp = graph[i];
		temp = temp -> next;
		while(temp){
			check[stuff[temp->leader]]++;
			temp = temp -> next;
		}
	}

	//check and create topological sort
	count = 0;
	int top = 0;
	while(top < size){
		DAG = false;		
		for(int i = 0; i < size; i++){
			if(check[i] == 0){
				DAG = true;
				set[count] = i;
				count++;
				top_sort.push_back(graph[i]);
				check[i] = -1;
			}
		}
		if(!DAG){
			cout << "No"<<endl;
			break;
		}
		prev = graph[set[top]];
		prev = prev -> next;
		while(prev){
			check[stuff[prev -> leader]]--;
			prev = prev -> next;
		}
		top++;
	}

	//output
	if(DAG){
		cout << "Yes"<<endl;
		for(int i = 0; i < size; i++){
			cout << top_sort[i] -> leader;
			if(i < size -1)
				cout << ", ";
		}
	} 
	return 0;
}