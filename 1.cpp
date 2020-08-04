#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream file;
	string s_temp, s_temp2;
	bool* match;
	int **planes, **airports, size, *pos, *visit;
	char buff[256];

	cout << "Enter file name: ";
	cin >> buff;
	file.open(buff);

	file >> s_temp >> size;
	planes = new int*[size];
	airports = new int*[size];
	visit = new int[size];
	pos = new int[size];
	match = new bool[size];
	for(int i = 0; i < size; i++){
		planes[i] = new int[size];
		airports[i] = new int[size];
		pos[i] = 0;	
		visit[i] = -1;
		match[i] = false;
	}
	getline(file, s_temp);
	for(int i = 0; i < size; i++){
		getline(file, s_temp);
		int pos = 0;
		for(int j = 0; j < size; j++){
			pos = s_temp.find("A", pos+1);
			s_temp2 = s_temp.substr(pos+1, 1);
			planes[i][stoi(s_temp2)-1] = j;		
		}
	}

	for(int i = 0; i < size; i++){
		getline(file, s_temp);
		int pos = 0;
		for(int j = 0; j < size; j++){
			pos = s_temp.find("P", pos+1);
			s_temp2 = s_temp.substr(pos+1, 1);
			airports[i][stoi(s_temp2)-1] = j;
		}
	}

	for (int i = 0; i < size; ++i)
	{
		cout << "P"<<i+1<<": ";
		for (int j = 0; j < size; ++j)
		{
			cout << planes[i][j] +1<< " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < size; ++i)
	{
		cout << "A"<<i+1<<": ";
		for (int j = 0; j < size; ++j)
		{
			cout << airports[i][j] +1<< " ";
		}
		cout << endl;
	}
	cout << endl;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(!match[j]){
				int airport = airports[j][pos[j]];  
				if(visit[airport] == -1){
					match[j] = true;
					visit[airport] = j;
				}
				else{
					for(int k = 0; k < size; k++){
						if(planes[airport][k] == visit[airport]){
							pos[j]++;
							break;
						}
						if(planes[airport][k] == j){
							pos[visit[airport]]++;
							match[visit[airport]] = false;
							visit[airport] = j;
							match[j] = true;
							break;
						}
					}
				}
			}
		}
	}

	for(int i = 0; i < size; i++){
		cout << "P" << i+1 << " A" << visit[i]+1 << endl;
	}
	return 0;
}