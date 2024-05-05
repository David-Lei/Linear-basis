#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstdlib>
#define MAXN 0x7fffffff
typedef long long LL;
const int N=400005,mod=1e9+7;
using namespace std;
inline LL Getint(){register LL x=0,f=1;register char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}return x*f;}
int n,m,h[N],cntEdge;
LL pw[105],ans;
struct node{int to,next;LL val;}g[N<<2];
void AddEdge(int x,int y,LL z){
	g[++cntEdge].to=y,g[cntEdge].next=h[x],h[x]=cntEdge,g[cntEdge].val=z;
}

LL p[65];
void Insert(LL x){
	for(int i=62;i>=0;i--){
		if(!(x>>i))continue;
		if(!p[i]){p[i]=x;break;}
		x^=p[i];
	}
}

LL Cir[N<<2],dx[N];
int dfn[N],id,cnt;
bool vis[N];
void Dfs(int x,int fa){
	dfn[++id]=x,vis[x]=1;
	for(int i=h[x];i;i=g[i].next){
		int to=g[i].to;
		if(to==fa)continue;
		if(vis[to])Cir[++cnt]=dx[to]^dx[x]^g[i].val;
		else dx[to]=dx[x]^g[i].val,Dfs(to,x);
	}
}

int r=0;
LL dig[2];
void Cal(){
	r=0,memset(p,0,sizeof(p));
	for(int i=1;i<=cnt;i++)Insert(Cir[i]);
	for(int i=0;i<=62;i++)r+=(p[i]>0);
	for(int i=0;i<=62;i++){
		bool flag=0;
		dig[0]=dig[1]=0;
		for(int j=1;j<=id;j++)dig[(dx[dfn[j]]>>i)&1]++;
		for(int j=0;j<=62;j++)if((p[j]>>i)&1){flag=1;break;}
		LL now=(dig[0]*(dig[0]-1)/2+dig[1]*(dig[1]-1)/2)%mod;
		if(flag){
			if(r)now=now*pw[r-1]%mod;
			now=now*pw[i]%mod;
			ans=(ans+now)%mod;
		}
		now=dig[0]*dig[1]%mod;
		if(flag){if(now)now=now*pw[r-1]%mod;}
		else now=now*pw[r]%mod;
		now=now*pw[i]%mod;
		ans=(ans+now)%mod;
	}
}

int main(){
	pw[0]=1;for(int i=1;i<=100;i++)pw[i]=(pw[i-1]<<1)%mod;
	int n=Getint(),m=Getint();
	for(int i=1;i<=m;i++){
		int x=Getint(),y=Getint();LL z=Getint();
		AddEdge(x,y,z),AddEdge(y,x,z);
	}
	
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		id=cnt=0,Dfs(i,0);
		Cal();
	}
	cout<<ans;
	return 0;
}

