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
char s[N];
LL p[65];
void Insert(LL x){
	for(int i=62;i>=0;i--){
		if(!(x>>i))continue;
		if(!p[i]){p[i]=x;break;}
		x^=p[i];
	}
}
int main(){
	int n=Getint(),m=Getint(),ans=0;
	for(int i=1;i<=m;i++){
		scanf("%s",s);
		LL x=0;
		for(int j=0;j<n;j++)if(s[j]=='O')x^=(1LL<<j);
		Insert(x);
	}
	for(int i=0;i<=62;i++)ans+=(bool)p[i];
	cout<<(1LL<<ans)%2008;
	return 0;
}