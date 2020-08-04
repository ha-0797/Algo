#include <iostream> 
#include <string.h> 
#include <fstream>

using namespace std; 
  
bool memoize(char* S1, char* S2, char* C, bool** IL) 
{ 
    int M = strlen(S1), N = strlen(S2); 
  
   	for (int i = 0; i <= M; ++i){
   		for (int j = 0; j <= N; ++j)
   			IL[i][j] = false;
   	}

    for (int i=0; i<=M; ++i) 
    { 
        for (int j=0; j<=N; ++j) 
        { 
            if (i==0 && j==0) 
                IL[i][j] = true; 
  
            else if (i==0 && S2[j-1]==C[j-1]) 
                IL[i][j] = IL[i][j-1]; 
  
            else if (j==0 && S1[i-1]==C[i-1]) 
                IL[i][j] = IL[i-1][j]; 
  
            else if(S1[i-1]==C[i+j-1] && S2[j-1]!=C[i+j-1]) 
                IL[i][j] = IL[i-1][j]; 
  
            else if (S1[i-1]!=C[i+j-1] && S2[j-1]==C[i+j-1]) 
                IL[i][j] = IL[i][j-1]; 
  
            else if (S1[i-1]==C[i+j-1] && S2[j-1]==C[i+j-1]) 
                IL[i][j]=(IL[i-1][j] || IL[i][j-1]) ; 
        } 
    } 
  
    return IL[M][N]; 
} 

int main(int argc, char const *argv[])
{
	ifstream file;
	char buff[256] = "stuff.txt";
	char S1[256], S2[256], C[256];
    bool** mem;
    file.open(buff);
	file >> S1 >> S2 >> C;
	int M = strlen(S1), N = strlen(S2);
    mem = new bool*[M+1];
    for (int i = 0; i < M; ++i)
    {
    	mem[i] = new bool[N];
    }
    cout << S1 << endl<< S2 << endl<< C << endl;
	if(memoize(S1,S2,C, mem)){
		cout << "Yes";
	}
	return 0;
}