#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstdlib>
#define MAXN 0x7fffffff
typedef long long LL;
const int N=100005,M=500005;
using namespace std;
inline int Getint(){register int x=0,f=1;register char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}return x*f;}
int h[N],cnt=1;
struct node{int to,next;}g[M<<1];
void AddEdge(int x,int y){g[++cnt].to=y,g[cnt].next=h[x],h[x]=cnt;}
struct Edge{int x,y,val;}e[M];
int fa[N],val[M];
bool vis[N],use[M];
void Dfs1(int x){
	vis[x]=1;
	for(int i=h[x];i;i=g[i].next){
		int to=g[i].to;
		if(vis[to])continue;
		use[i>>1]=1,fa[to]=x;
		Dfs1(to);
	}
}
void Dfs2(int x){
	for(int i=h[x];i;i=g[i].next){
		int to=g[i].to;
		if(fa[to]^x)continue;
		Dfs2(to);
		e[i>>1].val^=val[to];
		val[x]^=val[to];
	}
}
int p[35];
bool Insert(int x){
	for(int i=31;i>=0;i--){
		if(!((x>>i)&1))continue;
		if(!p[i]){p[i]=x;break;}
		x^=p[i];
	}
	return x>0;
}
int main(){
	srand(20020130);
	int n=Getint(),m=Getint();
	for(int i=1;i<=m;i++){
		int x=e[i].x=Getint(),y=e[i].y=Getint();
		AddEdge(x,y),AddEdge(y,x);
	}
	Dfs1(1);
	for(int i=1;i<=m;i++){
		if(use[i])continue;
		int x=rand()%1000000000+1;
		e[i].val=x;
		val[e[i].x]^=x,val[e[i].y]^=x;
	}
	Dfs2(1);
	int Q=Getint(),ans=0;
	while(Q--){
		int k=Getint();
		memset(p,0,sizeof(p));
		bool ok=0;
		for(int i=1;i<=k;i++){
			int x=Getint()^ans;
			if(!Insert(e[x].val))ok=1;
		}
		if(!ok)puts("Connected"),ans++;
		else puts("Disconnected");
	}
	return 0;
}

