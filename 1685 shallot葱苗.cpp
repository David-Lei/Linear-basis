#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstdlib>
#include<vector>
#include<map>
#define ls v<<1
#define rs v<<1|1
#define MAXN 0x7fffffff
typedef long long LL;
const int N=500005;
using namespace std;
inline int Getint(){register int x=0,f=1;register char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}return x*f;}
struct Seg{
	int l,r;
	vector<int>val;
}Tree[N<<2];
struct L_B{
	int p[32];
	void Insert(int x){
		for(int i=31;i>=0;i--){
			if(!(x>>i))continue;
			if(!p[i]){p[i]=x;break;}
			x^=p[i];
		}
}
	int Query_Max(){
		int ret=0;
		for(int i=31;i>=0;i--)
			if((ret^p[i])>ret)ret^=p[i];
		return ret;
	}
}tmp;
void Build(int v,int l,int r){
	Tree[v].l=l,Tree[v].r=r;
	if(l==r)return;
	int mid=l+r>>1;
	Build(ls,l,mid),Build(rs,mid+1,r);
}
void Modify(int v,int l,int r,int val){
	if(Tree[v].r<l||Tree[v].l>r)return;
	if(l<=Tree[v].l&&Tree[v].r<=r)return Tree[v].val.push_back(val),void();
	Modify(ls,l,r,val),Modify(rs,l,r,val);
}
void Query(int v,L_B tmp){
	for(int i=0;i<Tree[v].val.size();i++)tmp.Insert(Tree[v].val[i]);
	if(Tree[v].l==Tree[v].r)return cout<<tmp.Query_Max()<<'\n',void();
	Query(ls,tmp),Query(rs,tmp);
}

map<int,int>sav;
map<int,int>::iterator it;
int main(){
	int n=Getint();
	Build(1,1,n);
	for(int i=1;i<=n;i++){
		int x=Getint();
		if(x>0)sav[x]=i;
		else{
			x=-x;
			Modify(1,sav[x],i-1,x);
			sav.erase(x);
		}
	}
	for(it=sav.begin();it!=sav.end();it++)Modify(1,it->second,n,it->first);
	Query(1,tmp);
	return 0;
}

