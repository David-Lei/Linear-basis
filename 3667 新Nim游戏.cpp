#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstdlib>
#define MAXN 0x7fffffff
typedef long long LL;
const int N=105;
using namespace std;
inline int Getint(){register int x=0,f=1;register char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline bool cmp(const int &a,const int &b){return a>b;}
LL a[N],p[65],ans;
bool Insert(LL x){
	for(int i=62;i>=0;i--){
		if(!(x>>i))continue;
		if(!p[i]){p[i]=x;break;}
		x^=p[i];
	}
	return x>0;
}
int main(){
	int n=Getint();
	for(int i=1;i<=n;i++)a[i]=Getint();
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)if(!Insert(a[i]))ans+=a[i];
	cout<<ans<<'\n';
	return 0;
}

