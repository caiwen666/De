#include<iostream>
#include "de.cpp" 
#define MAXN_POINT 500001 
#define MAXN_QUERY 500001
using namespace std;
//namespace De{void connect(){}void setVec(bool x){}void build(){}void add(int id){}void link(int from,int to,int id){}void init(string type){}void light(int id,bool point){}void remove(int id,bool point){}void offlight(int id,bool point){}}

//part1.���鼯
int fa[MAXN_POINT];
int find(int x){
	while(x!=fa[x]){
		///de
		De::remove(x*10+fa[x],false);
		///
		fa[x]=fa[fa[x]];
		///de
		De::link(x,fa[fa[x]],x*10+fa[fa[x]]);
		De::init("breadthfirst");
		De::light(x*10+fa[fa[x]],false);
		getchar();
		De::offlight(x*10+fa[fa[x]],false);
		///
		x=fa[x];
	}
	return x;
}
void add_uns(int a,int b){
	a=find(a);
	b=find(b);
	fa[b]=a;
	
	///de
	De::link(b,a,b*10+a);
	De::init("breadthfirst");
	De::light(b*10+a,false);
	getchar();
	De::offlight(b*10+a,false);
	///
	
	//!!!!!!!!!!!!!ע�������ǰ�b���ӵ�a����
	//add_uns��ʱ����add_uns(a=��ǰ�ڵ㣬b=�ӽڵ�) 
}


//part2.ͼ�Ľṹ
struct Edge{
	int to,next;
} edge[MAXN_QUERY*2];
int head[MAXN_POINT];
int size=0;
void add_edge(int u,int v){
	size++;
	edge[size].to=v;
	edge[size].next=head[u];
	head[u]=size;
}

//part3.tarjan��lca
//���ǲ�����������ѯ����Ϣ
struct Query{
	int to,next,id,same;//idΪѯ��id��Ҳ���ǵڼ���ѯ�ʣ�������ã�sameΪ�����ѯ�����Ӧ��ѯ�ʣ�ѯ��id��ͬ�� 
	bool flag;//�Ƿ��Ѿ������ 
} query[MAXN_QUERY*2];//ÿ��ѯ��ʵ���϶�Ϊһ��ѯ��
int head_q[MAXN_POINT];
int size_q=0;
int ans[MAXN_POINT];
void add_q(int x,int y,int id){
	size_q++;
	query[size_q].to=y;
	query[size_q].next=head_q[x];
	query[size_q].same=size_q+1;
	query[size_q].id=id;
	head_q[x]=size_q;
	size_q++;
	query[size_q].to=x;
	query[size_q].next=head_q[y];
	query[size_q].same=size_q-1;
	query[size_q].id=id;
	head_q[y]=size_q;
}
//x�ǵ�ǰҪ�����Ľڵ㣬fΪ����ڵ�ĸ��ڵ� 
bool vis[MAXN_POINT]; 
void lca(int x,int f){
	for(int i=head[x];i!=0;i=edge[i].next){
		int to=edge[i].to; 
		if(to!=f&&!vis[to]){//ȷ���ӽڵ㲻�Ǹ��ڵ㣬����û�б�������
			lca(to,x); 
			add_uns(x,to);
			vis[to]=true;
		}
	}
	//�����͵�ǰ�ڵ��йصĽ��� 
	for(int i=head_q[x];i!=0;i=query[i].next){
		if(!query[i].flag&&vis[query[i].to]){//�����һ���ڵ�������ˣ�����û�н��ѯ�� 
			//���Խ����
			ans[query[i].id]=find(query[i].to);
			query[i].flag=true;
			query[query[i].same].flag=true;
		}
	}
}

int main(){
	De::connect();
	De::build();
	ios::sync_with_stdio(false);
	int n,m,s;
	cin>>n>>m>>s;
	for(int i=1;i<=n-1;i++){
		int x,y;
		cin>>x>>y;
		fa[i]=i;
		De::add(i);
		add_edge(x,y);
		add_edge(y,x);
	}
	fa[n]=n;
	De::add(n);
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		add_q(a,b,i);
	}
	
	lca(s,0);
	
	for(int i=1;i<=m;i++){
		cout<<ans[i]<<endl;
	}
	return 0;
}
