#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int N = 1000010;


int order(int num){
    if(num==1)
        return 2;
    int x=1, y=2;
    int count = 3;
    while(y<=num){
        if(y==num)
            return count;
        int tmp = y;
        y = x+y;
        x = tmp;
        count++;
    }
    return 0;
}

int main(){
	int data[N];
    while(cin>>n){
        memset(data, 0, N*sizeof(int));
        data[0] = 1;
        int x;
        int mj = 0;
        for(int i=0;i<n;i++){
            cin>>x;
            int j = order(x);
            if(j==0)
                continue;
            data[j] = (data[j-1]+data[j])%1000000007;
            if(x==1)
            	data[1]++;
            mj = max(j, mj);
        }
        int res = 0;
        for(int i=1;i<=mj;i++){
        	cout<<data[i]<<endl;
            res = (res+data[i])%1000000007;
        }
        cout<<res<<endl;
    }
}
