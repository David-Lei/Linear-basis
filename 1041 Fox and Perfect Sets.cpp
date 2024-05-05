#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstdlib>
#define MAXN 0x7fffffff
typedef long long LL;
const int mod=1e9+7;
using namespace std;
inline int Getint(){register int x=0,f=1;register char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}return x*f;}
int ans,f[35][35][2];
void Add(int &x,int y){x=((x+y>=mod)?(x+y-mod):(x+y));}
int main(){
//	freopen("ans.txt","w",stdout);
	int n=Getint();
	f[30][0][1]=1;
	for(int i=30;i>0;i--)
		for(int j=0;j<=30;j++){
			Add(f[i-1][j][0],(1LL<<j)*f[i][j][0]%mod);
			Add(f[i-1][j+1][0],f[i][j][0]);
			int x=j?(1<<(j-1)):1,y=j?(1<<(j-1)):0;
			if(n>>(i-1)&1){
				Add(f[i-1][j][0],(LL)x*f[i][j][1]%mod);
				Add(f[i-1][j][1],(LL)y*f[i][j][1]%mod);
				Add(f[i-1][j+1][1],f[i][j][1]);
			}else Add(f[i-1][j][1],(LL)x*f[i][j][1]%mod);
		}
	for(int i=0;i<=30;i++)
		Add(ans,f[0][i][0]),Add(ans,f[0][i][1]);
	/*
	for(int i=0;i<=30;i++){
		for(int j=0;j<=30;j++){
			cout<<"I= "<<i<<" J= "<<j<<" f[i][j][k]= ";
			for(int k=0;k<=1;k++)cout<<f[i][j][k]<<' ';
			cout<<'\n';
		}
	}
	*/
	cout<<ans;
	return 0;
}

