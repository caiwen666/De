#include "de.cpp"
#include<iostream>
#include<queue>
#include<cstring>
#define MAXN_EDGE 500001
#define MAXN_POINT 10001 
#define INF 0x3f3f3f3f
using namespace std;

int dis[10001];
bool lock[10001];

struct Edge{
    int to,w,next;
} edges[MAXN_EDGE];
int head[MAXN_POINT];
int size=0;
void push(int from,int to,int w){
	size++;
    edges[size].to=to;
    edges[size].w=w;
    edges[size].next=head[from];
    head[from]=size;
	
	///de
    De::add(from);
    De::add(to);
    De::link(from,to,size);//ֱ��ʹ��size��Ϊ�ߵ�id
    Sleep(200);
	///
}

int n,m,s;
void spfa(){
	//spfa
	///de
	De::init("grid");
	///
	memset(dis,0x3f,sizeof(dis));
	queue<int> q;
	lock[s]=true;//��ͬ��dijkstra�㷨�������lock�����ǵ�ǰ���Ƿ��ڶ����� 
	q.push(s);//�ӵ�ǰ�㿪ʼ������չ 
	dis[s]=0;
	while(!q.empty()){
	    int now=q.front();
		///de
	    De::light(now,true);
	    Sleep(2000);
		///
	    q.pop();
	    lock[now]=false;//���˳������ˣ����� 
	    Edge now_edge;
	    for(int p=head[now];p!=0;p=now_edge.next){//������ǰ�����еı� 
	    	Sleep(2000);
			///de
			De::light(p,false);
			///
			now_edge=edges[p];
			///de
			De::light(now_edge.to,true);
			///
	    	//cout<<"touch:P"<<p<<endl; 
			if(dis[now_edge.to]>dis[now]+now_edge.w){
				dis[now_edge.to]=dis[now]+now_edge.w; 
				if(!lock[now_edge.to]){//û���ڶ������� 
					lock[now_edge.to]=true;//���� 
				    q.push(now_edge.to);//ѹ����� 
				}
			}
			///de
			Sleep(2000);
			De::offlight(p,false);
			De::offlight(now_edge.to,true);
			///
		}
		///de
		De::offlight(now,true);
		Sleep(2000);
		///
	}
}

int main(){
	///de
	De::connect();
	De::build();
	///
	//De::send("aaa");
    cin>>n>>m>>s;
    for(int i=1;i<=m;i++){
        int arg1,arg2,arg3;
        cin>>arg1>>arg2>>arg3;
        push(arg1,arg2,arg3);
    }
    spfa();
    for(int i=1;i<=n;i++){
        if(dis[i]==INF){
            cout<<2147483647<<" ";
        }else{
            cout<<dis[i]<<" ";
        }
    }
    return 0;
}
