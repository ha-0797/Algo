#include <iostream>
#include <fstream>

using namespace std;

void max(int*mem, int**arr, int size){
	if(size < 0){return;}
	if(mem[size+2] == arr[0][size]){
		max(mem, arr, size-2);
		if(size != 0)
			cout << "week " << size-1 << " Priming" << endl;
		cout << "week " << size << " High " << arr[0][size] << endl;
	} else {
		max(mem, arr, size-1);
		cout << "week " << size<< " Low " << arr[1][size]<<endl;
	}
}

int main(int argc, char const *argv[])
{
	ifstream file;
	char buff[256];
	string s_temp;
	int size, **arr, *mem;

	cout << "Enter file name: ";
	cin >> buff;

	file.open(buff);
	file >> s_temp >> size;

	arr = new int*[2];
	arr[0] = new int[size];
	arr[1] = new int[size];
	mem = new int[size+2];
	for (int i = 0; i < size+2; ++i)
	{
		mem[i] = -1;
	}
	for (int i = 0; i < 2; ++i)
	{
		file >> s_temp;
		for (int j = 0; j < size; ++j)
		{
			file >> arr[i][j];
		}
	}
	mem[0] = 0;
	mem[1] = 0;
	for (int i = 2; i < size+2; ++i)
	{
		int a = (arr[0][i-2] + mem[i-2]);
		int b = (arr[1][i-2] + mem[i-1]);
		if(a > b)
			mem[i] = arr[0][i-2];
		else
			mem[i] = arr[1][i-2];
	}
	max(mem, arr, size-1);
	
	return 0;
}