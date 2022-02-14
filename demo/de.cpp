//头部文件文件
#include <Windows.h>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

namespace De{
	SECURITY_ATTRIBUTES saa,sab;
	PROCESS_INFORMATION pi;
	STARTUPINFO sui;
	HANDLE mReadPipe,mWritePipe,mReadFile,mWriteFile;
	HANDLE mThread;
	DWORD dwRead;
	void closehandle()
	{
	    CloseHandle(mReadPipe);
	    CloseHandle(mWritePipe);
	    CloseHandle(mReadFile);
	    CloseHandle(mWriteFile);
	    mReadPipe=NULL;
	    mWritePipe=NULL;
	    mReadFile=NULL;
	    mWriteFile=NULL;
	    mThread=NULL;
	}
	 
	DWORD WINAPI PipeProc(LPVOID lpParameter)  // thread data
	{
	    HANDLE hRead = (HANDLE)lpParameter;
	    char buf[1024];
	    memset(buf,0,1024);
	    DWORD dwRead;
	    while(1)
	    {
	        PeekNamedPipe(hRead,buf,1024,&dwRead,NULL,NULL);
	        if(dwRead != 0)
	        {
	            ReadFile(hRead,buf,1024,&dwRead,NULL);
	            cout<<buf<<endl;
	            memset(buf,0,sizeof(buf));
	        }
	         
	    }
	    return 0;
	};
	
	void send(string str){
		char buf[256];
		memset(buf,0,256);
		strcpy(buf,str.c_str());
		buf[strlen(buf)]='\n';
		WriteFile(mWriteFile,buf,strlen(buf),&dwRead,NULL);
		//cout<<str<<endl<<buf<<endl;
	} 
	
	void connect(){
		//初始化SECURITY_ATTRIBUTES结构
		saa.bInheritHandle = TRUE;
		saa.lpSecurityDescriptor=NULL;
		saa.nLength = sizeof(SECURITY_ATTRIBUTES);
		     
		sab.bInheritHandle = TRUE;
		sab.lpSecurityDescriptor=NULL;
		sab.nLength = sizeof(SECURITY_ATTRIBUTES);
		     
		//创建匿名管道
		if(!CreatePipe(&mReadPipe,&mWriteFile,&saa,0))
		{
		    cout<<"创建匿名管道失败"<<endl;
		    return;
		}
		if(!CreatePipe(&mReadFile,&mWritePipe,&sab,0))
		{
		    cout<<"创建匿名管道失败"<<endl;
		    return;
		}
		     
		ZeroMemory(&sui,sizeof(STARTUPINFO)); //结构初始化为0
		GetStartupInfo(&sui); //获取调用进程信息
		     
		sui.dwFlags =  STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
		sui.wShowWindow = SW_HIDE;
		sui.hStdInput = mReadPipe;
		sui.hStdOutput = mWritePipe;
		sui.hStdError = mWritePipe;
		stringstream a;
		if(!CreateProcess(NULL,"ws.exe 15567",NULL,NULL,TRUE,0,NULL,NULL,&sui,&pi))
		{
		    cout<<"创建子进程失败"<<endl;
		    closehandle();
		    return;
		}
		 
		mThread = CreateThread(NULL,0,PipeProc,(LPVOID)mReadFile,0,NULL);
		if(NULL==mThread)
		{
		    cout<<"创建线程失败!"<<endl;
		    closehandle();
		    return;
		}
		 
		CloseHandle(mThread);
	}
	void setVec(bool x){
		if(x){
			send("{'arg':'mode','vec':true}");
		}else{
			send("{'arg':'mode','vec':false}");
		}
	}
	void build(){
		//cout<<"touch"<<endl;
		send("{'arg':'build'}");
	}
	void add(int id){
		stringstream ss;
		ss<<"{'arg':'add','id':'"<<id<<"'}";
		send(ss.str());
	}
	void link(int from,int to,int id){
		stringstream ss;
		ss<<"{'arg':'link','from':'"<<from<<"','to':'"<<to<<"','id':'"<<id<<"'}";
		send(ss.str());
	}
	void init(string type){
		stringstream ss;
		ss<<"{'arg':'init','type':'"<<type<<"'}";
		send(ss.str());
	}
	void light(int id,bool point){
		string a=point? "true":"false";
		stringstream ss;
		ss<<"{'arg':'light','point':"<<a<<",'id':'"<<id<<"'}";
		send(ss.str());
	}
	void remove(int id,bool point){
		string a=point? "true":"false";
		stringstream ss;
		ss<<"{'arg':'remove','point':"<<a<<",'id':'"<<id<<"'}";
		send(ss.str());
	}
	void offlight(int id,bool point){
		string a=point? "true":"false";
		stringstream ss;
		ss<<"{'arg':'offlight','point':"<<a<<",'id':'"<<id<<"'}";
		send(ss.str());
	}
}
