#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

bool memoize(vector<int> set1, vector<int> set2, int k, map<string, bool>& m){
	int sum1 = 0, sum2 = 0;
	string map;
	for (int i = 0; i < set1.size(); ++i){
		sum1 += set1[i];
		map = map + to_string(set1[i]) + " ";
	}
	if(m[map])
		return true;
	for (int i = 0; i < set2.size(); ++i){
		sum2 += set2[i];
	}
	
	if(sum1-sum2 == k){
		m[map] = true;
		//return true;
	}
	else
		m[map] = false;
	for (int i = 0; i < set1.size(); ++i)
	{
		int temp = set1[i];
		set2.push_back(temp);
		set1.erase(set1.begin()+i);
		memoize(set1, set2, k, m);
		set1.emplace(set1.begin()+i, temp);
		set2.pop_back();
	}
	return false;
}

void print(string sum, vector<int> v){
	int pos = 0, size = sum.length();
	int sum1 = 0, sum2 = 0, iter = 0;
	string s2;
	while(pos <= size && iter < v.size()){
		int pos2 = sum.find(" ", pos+1);
		if(sum.substr(pos,pos2-pos) == to_string(v[iter])){
			sum1 += v[iter];
			pos=pos2+1;
		} else {
			sum2 += v[iter];
			s2 = s2 + to_string(v[iter]) + " ";
		}
		iter++;
	}
	cout << "POSSIBLE\n";
	cout << "S1 " << sum << "sum = " << sum1 << endl;
	cout << "S2 " << s2 << "sum = " << sum2 << endl;
	cout << "Difference: " << sum1 << " - " << sum2 << " = " << sum1-sum2 <<endl;
}

int main(int argc, char const *argv[])
{
	ifstream file;
	char buff[256];
	string s_temp;
	int k, i_temp;
	vector<int> v1, v2;
	map<string, bool> m;

	cout << "Enter file name: ";
	cin >> buff;

	file.open(buff);
	file >> s_temp >> k;
	file >> s_temp;
	while(file >> i_temp)
		v1.push_back(i_temp);
	// for (int i = 0; i < v1.size(); ++i)
	// 	cout << v1[i] << " ";
	memoize(v1, v2, k ,m);
	for (std::map<string,bool>::iterator it=m.begin(); it!=m.end(); ++it){
	    if(it->second){
	       	print(it->first, v1);
	    	break;
	    }
	}
	return 0;
}