#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int t, n;


struct point{
	int x, y;
	point(int x, int y){
		this->x = x;
		this->y = y;
	}
};

void myswap(vector< vector<int> >& res, point p1, point p2, int N){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			swap(res[i+p1.x][j+p1.y], res[i+p2.x][j+p2.y]);
}

vector< vector<int> >& rotate_mat(vector< vector<int> >& res, int N){
	// vector< vector<int> > ret(N, vector<int>(N, 0));
	myswap(res, point(0, 0), point(0, N), N);
	myswap(res, point(0, 0), point(N, 0), N);
	myswap(res, point(N, 0), point(N, N), N);
	return res;
}

vector< vector<int> > rotate(vector< vector<int> >& res, int N){
	vector< vector<int> > ret(N, vector<int>(N, 0));
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			ret[j][N-i-1] = res[i][j];
		}
	}
	return ret;
}

bool comp(vector< vector<int> >& f, vector< vector<int> >& t, int N){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(f[i][j]<t[i][j])
				return true;
			else if(f[i][j]>t[i][j])
				return false;
		}
	}
	return false;
}


void dfs(vector< vector<int> >& res, int N, int i, int j){
	if(N%2==0){
		dfs(res, N/2, 0, 0);
		dfs(res, N/2, 0, N/2);
		dfs(res, N/2, N/2, 0);
		dfs(res, N/2, N/2, N/2);
	}
	vector< vector<int> > min(N, vector<int>(N, 0));
	vector< vector<int> > tp(N, vector<int>(N, 0));
	for(int row=i;row<i+N;row++)
		for(int col=j;col<j+N;col++){
			min[row-i][col-j] = res[row][col];
			tp[row-i][col-j] = res[row][col];
		}
	for(int k=0;k<3;k++){
		if(N%2==0)
			tp = rotate_mat(tp, N/2);
		else
			tp = rotate(tp, N);
		if(comp(tp, min, N))
			min = tp;
	}
	for(int row=i;row<i+N;row++)
		for(int col=j;col<j+N;col++)
			res[row][col] = min[row-i][col-j];
}




int main(){
	while(cin>>t){
		while(t--){
			cin>>n;
			vector< vector<int> > A(n, vector<int>(n, 0)), B(n, vector<int>(n, 0));
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					cin>>A[i][j];
				}
			}
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					cin>>B[i][j];
				}
			}
			// cout<<"->>>>>>>>1"<<endl;
			dfs(A, n, 0, 0);
			dfs(B, n, 0, 0);
			// cout<<"->>>>>>>>2"<<endl;
			int i, j;
			for(i=0;i<n;i++){
				for(j=0;j<n;j++){
					if(A[i][j]!=B[i][j]){
						cout<<"No"<<endl;
						break;
					}
				}
				if(j!=n)
					break;
			}
			if(i==n)
				cout<<"Yes"<<endl;
		}
	}
}