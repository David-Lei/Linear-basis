#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstdlib>
#define MAXN 0x7fffffff
typedef long long LL;
const int N=20005;
using namespace std;
inline LL Getint(){register LL x=0,f=1;register char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}return x*f;}
LL a[N];
int n,Q,h[N],cntEdge;
struct node{int to,next;}g[N<<1];
void AddEdge(int x,int y){g[++cntEdge].to=y,g[cntEdge].next=h[x],h[x]=cntEdge;}

struct L_B{
	LL p[65];
	L_B(){memset(p,0,sizeof(p));}
}b[N][15];
inline void Insert(L_B &a,LL x){
	for(int i=62;i>=0;i--){
		if(!(x>>i))continue;
		if(!a.p[i]){a.p[i]=x;break;}
		x^=a.p[i];
	}
}
inline LL Query_Max(L_B a){
	LL ret=0;
	for(int i=62;i>=0;i--)
		if((ret^a.p[i])>ret)ret^=a.p[i];
	return ret;
}
inline void Merge(L_B &a,L_B b){
	for(int i=62;i>=0;i--)
		if(b.p[i])Insert(a,b.p[i]);
}

int fa[N][20],dep[N];
void Dfs(int x){
	Insert(b[x][0],a[x]);
	for(int i=1;(1<<i)<=dep[x];i++){
		fa[x][i]=fa[fa[x][i-1]][i-1];
		b[x][i]=b[x][i-1];
		Merge(b[x][i],b[fa[x][i-1]][i-1]);
	}
	for(int i=h[x];i;i=g[i].next){
		int to=g[i].to;
		if(dep[to])continue;
		dep[to]=dep[x]+1;
		fa[to][0]=x;
		Dfs(to);
	}
}

L_B LCA(int u,int v){
	L_B ret;
	if(dep[u]<dep[v])swap(u,v);
	for(int i=log2(dep[u]);i>=0;i--)
		if(dep[u]-(1<<i)>=dep[v])Merge(ret,b[u][i]),u=fa[u][i];
	if(u==v)return Merge(ret,b[u][0]),ret;
	for(int i=log2(dep[u]);i>=0;i--)
		if(fa[u][i]!=fa[v][i])
			Merge(ret,b[u][i]),Merge(ret,b[v][i]),u=fa[u][i],v=fa[v][i];
	Merge(ret,b[u][1]),Merge(ret,b[v][0]);
	return ret;
}

int main(){
	int size=40<<20;//40M
	__asm__ ("movq %0,%%rsp\n"::"r"((char*)malloc(size)+size));
	n=Getint(),Q=Getint();
	for(int i=1;i<=n;i++)a[i]=Getint();
	for(int i=1;i<n;i++){
		int x=Getint(),y=Getint();
		AddEdge(x,y),AddEdge(y,x);
	}
	
	dep[1]=1;Dfs(1);
	
	for(int i=1;i<=Q;i++){
		int x=Getint(),y=Getint();
		cout<<Query_Max(LCA(x,y))<<'\n';
	}
	exit(0);
}

