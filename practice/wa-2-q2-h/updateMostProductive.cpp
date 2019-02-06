#include <iostream>
#include <vector>

using namespace std;

void updateMostProductive(const vector<int> & A, vector< vector <int> > & V, int j) {
    //assume A[0..n] contains correct cumulative sums
    //assume V[1..j-1][1..j-1] is correct.
    vector<int> temp;
    temp.resize(j+1);
    temp[0] = 0;
    for (int k=1; k<=j-1; k++){
        int bestSum = V[j-1][k];
        int firstGameNum = j-k+1;
        int newSum = A[j] - A[firstGameNum - 1];
        if(newSum >= bestSum)
            temp[k] = j;
        else
            temp[k] = V[j-1][k];
    }
    temp[j] = j;
    V.push_back(temp);
    //end condition: V[1..j][1..j] is correct.
    return;
}

int main(){
  vector<int> A;
  A.push_back(0); A.push_back(1); A.push_back(3); A.push_back(6); A.push_back(10);
  vector< vector <int> > V;
  vector<int> v0; v0.push_back(0);
  vector<int> v1; v1.push_back(0); v1.push_back(1);
  vector<int> v2; v2.push_back(0); v2.push_back(2); v2.push_back(2);
  V.push_back(v0); V.push_back(v1); V.push_back(v2);  
  
  updateMostProductive(A, V, 3);
  
  cout << V[3][0] << " " << V[3][1] << " " << V[3][2] << " " << V[3][3] << endl;
  
  return 0;
}
