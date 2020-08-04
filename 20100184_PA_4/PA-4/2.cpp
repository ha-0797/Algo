#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void mem(vector<int> v, int start, int stop){
	
}

int main(int argc, char const *argv[])
{
	ifstream file;
	string s_temp;
	vector<int> cuts;
	int size, cut1, cut2, cut3, i_temp;
	char buff[256];
	cout << "Enter file name: ";
	cin >> buff;

	file.open(buff);
	file >> s_temp >> size;
	file >> s_temp;
	while(file >> i_temp)
		cuts.push_back(i_temp);
	for (int i = 0; i < cuts.size(); ++i)
		cout << cuts[i] << " ";
	return 0;
}