#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstdlib>
#include<set>
#define MAXN 0x7fffffff
typedef long long LL;
const int N=5005,M=20005;
using namespace std;
inline LL Getint(){register LL x=0,f=1;register char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}return x*f;}
int n,m,Q;
int h[N],cnt;
struct node{int to,next;LL val;}g[M<<1];
void AddEdge(int x,int y,LL z){g[++cnt].to=y,g[cnt].next=h[x],h[x]=cnt,g[cnt].val=z;}

set<LL>v;
set<LL>::iterator it;

LL p[65],num;
void Insert(LL x){
	for(int i=62;i>=0;i--){
		if(!(x>>i))continue;
		if(!p[i]){p[i]=x;break;}
		x^=p[i];
	}
}
LL Low(LL x){for(int i=62;i>=0;i--)if((x^p[i])<x)x^=p[i];return x;}

void Update(LL x){
	if(!x)return;LL tmp;
	for(it=v.begin();it!=v.end();it=v.upper_bound(tmp)){
		tmp=*it;
		if((tmp^x)<tmp)tmp^=x;
		v.erase(it),v.insert(tmp);
	}
	Insert(x),num++;
}
LL dis[N];
bool vis[N];
void Dfs(int x,int fa){
	vis[x]=1;
	v.insert(Low(dis[x]));
	for(int i=h[x];i;i=g[i].next){
		int to=g[i].to;
		if(to==fa)continue;
		if(vis[to])Update(Low(dis[to]^dis[x]^g[i].val));
		else dis[to]=dis[x]^g[i].val,Dfs(to,x);
	}
}

void Add(int a,int b,LL c){
	AddEdge(a,b,c),AddEdge(b,a,c);
	if(vis[a]&&vis[b])return Update(Low(dis[a]^dis[b]^c)),void();
	if(!vis[a]&&!vis[b])return;
	if(vis[b])swap(a,b);
	dis[b]=dis[a]^c,Dfs(b,a);
}

struct Edge{int l,r;LL val;}s[M];
int del[M];bool is_del[M];

LL ans[M];
int main(){
	vis[1]=1;
	n=Getint(),m=Getint(),Q=Getint();
	for(int i=1;i<=m;i++)s[i].l=Getint(),s[i].r=Getint(),s[i].val=Getint();
	for(int i=1;i<=Q;i++)del[i]=Getint(),is_del[del[i]]=1;
	for(int i=1;i<=m;i++)if(!is_del[i])Add(s[i].l,s[i].r,s[i].val);
	v.insert(0);
	ans[Q+1]=(v.size()*(1ll<<num))-1;
	for(int i=Q;i>=1;i--){
		Add(s[del[i]].l,s[del[i]].r,s[del[i]].val);
		ans[i]=(v.size()*(1ll<<num))-1;
	}
	for(int i=1;i<=Q+1;i++)cout<<ans[i]<<'\n';
	return 0;
}
/*
5 7 7
1 2 1
1 3 1
2 4 2
2 5 2
4 5 4
5 3 9
4 3 1
7
6
5
4
3
2
1
*/
