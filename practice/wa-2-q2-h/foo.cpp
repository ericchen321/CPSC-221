void foo(int n, vector<int> &vec){
  for(int i=0; i<n-1; i++){
    if(vec[i]<0)
      bar(i); // assume bar(i) takes O(1)
  }
  bar(n+1);
}


