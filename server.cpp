#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    #define CLOSE_SOCKET closesocket
    typedef int socklen_t;
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #define CLOSE_SOCKET close
#endif

#include "generator.hpp"
#include "index_html.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <unordered_map>
#include <thread>
#include <signal.h>

using namespace std;

int calculateGameScore(Difficulty diff, bool isOptimal, int wrongAttempts, double secondsTaken) {
    double base=1000.0;
    double mult=(diff==EASY)?1.0:(diff==MEDIUM?1.5:2.0);
    double timePenalty=min(400.0,secondsTaken*3.0);
    double mistakePenalty=wrongAttempts*75.0;
    double score=(base-timePenalty-mistakePenalty)*mult;
    if(isOptimal)score+=200;
    if(wrongAttempts==0)score+=100;
    if(secondsTaken<20.0)score+=150;
    return max(100,(int)round(score));
}

string getPlayerRank(int totalScore) {
    if(totalScore>=10000)return"DSA Legend";
    if(totalScore>=8000)return"Master";
    if(totalScore>=6000)return"Algorithmist";
    if(totalScore>=4000)return"Challenger";
    if(totalScore>=2000)return"Explorer";
    return"Beginner";
}

string jsonArray2D(const vector<vector<int>>& v) {
    string s="[";
    for(int i=0;i<(int)v.size();i++){
        s+="[";
        for(int j=0;j<(int)v[i].size();j++){
            s+=to_string(v[i][j]);
            if(j+1<(int)v[i].size())s+=",";
        }
        s+="]";
        if(i+1<(int)v.size())s+=",";
    }
    s+="]";
    return s;
}

string jsonStringArray2D(const vector<string>& v) {
    string s="[";
    for(int i=0;i<(int)v.size();i++){
        s+="\"";
        for(char c:v[i]){
            if(c=='"')s+="\\\"";
            else if(c=='\\')s+="\\\\";
            else s+=c;
        }
        s+="\"";
        if(i+1<(int)v.size())s+=",";
    }
    s+="]";
    return s;
}

Difficulty parseDifficulty(const string& s) {
    if(s=="medium"||s=="2")return MEDIUM;
    if(s=="hard"||s=="3")return HARD;
    return EASY;
}

unordered_map<string,string> parseQuery(const string& qs) {
    unordered_map<string,string> m;
    size_t start=(qs[0]=='?')?1:0;
    while(start<qs.size()){
        size_t eq=qs.find('=',start);
        if(eq==string::npos)break;
        size_t amp=qs.find('&',eq);
        if(amp==string::npos)amp=qs.size();
        m[qs.substr(start,eq-start)]=qs.substr(eq+1,amp-eq-1);
        start=amp+1;
    }
    return m;
}

string buildResponse(int status, const string& contentType, const string& body) {
    string statusText=(status==200)?"OK":(status==400)?"Bad Request":(status==404)?"Not Found":"Internal Server Error";
    ostringstream resp;
    resp<<"HTTP/1.1 "<<status<<" "<<statusText<<"\r\n"
        <<"Content-Type: "<<contentType<<"\r\n"
        <<"Content-Length: "<<body.size()<<"\r\n"
        <<"Access-Control-Allow-Origin: *\r\n"
        <<"Connection: close\r\n\r\n"
        <<body;
    return resp.str();
}

string handleGenerate(const unordered_map<string,string>& params) {
    string game="dungeon";
    Difficulty diff=EASY;
    auto it=params.find("game");
    if(it!=params.end())game=it->second;
    it=params.find("diff");
    if(it!=params.end())diff=parseDifficulty(it->second);

    ostringstream json;

    if(game=="keyhunter"){
        auto p=generator.generateKeyHunter(diff);
        json<<"{\"game\":\"keyhunter\",\"rows\":"<<p.R
            <<",\"cols\":"<<p.C<<",\"keys\":"<<p.K
            <<",\"grid\":"<<jsonStringArray2D(p.grid)
            <<",\"optimal\":"<<p.optimalSteps<<"}";
    }
    else if(game=="dungeon"){
        auto p=generator.generateDungeon(diff);
        json<<"{\"game\":\"dungeon\",\"rows\":"<<p.R
            <<",\"cols\":"<<p.C
            <<",\"grid\":"<<jsonArray2D(p.grid)
            <<",\"optimal\":"<<p.optimalMinHP<<"}";
    }
    else if(game=="dualrobot"){
        auto p=generator.generateDualRobot(diff);
        json<<"{\"game\":\"dualrobot\",\"rows\":"<<p.R
            <<",\"cols\":"<<p.C
            <<",\"grid\":"<<jsonArray2D(p.grid)
            <<",\"optimal\":"<<p.optimalLoot<<"}";
    }
    else if(game=="cherry"){
        auto p=generator.generateCherryExpedition(diff);
        json<<"{\"game\":\"cherry\",\"size\":"<<p.N
            <<",\"grid\":"<<jsonArray2D(p.grid)
            <<",\"optimal\":"<<p.optimalCherries<<"}";
    }
    else if(game=="permutation"){
        auto p=generator.generatePermutationPuzzle(diff);
        json<<"{\"game\":\"permutation\",\"size\":"<<p.N
            <<",\"grid\":"<<jsonArray2D(p.board)
            <<",\"optimal\":"<<p.optimalMoves<<"}";
    }
    else if(game=="sudoku"){
        auto p=generator.generateSudoku(diff);
        json<<"{\"game\":\"sudoku\""
            <<",\"puzzle\":"<<jsonArray2D(p.puzzle)
            <<",\"solution\":"<<jsonArray2D(p.solution)<<"}";
    }
    else{
        return"{\"error\":\"Unknown game: "+game+"\"}";
    }

    return json.str();
}

string handleScore(const unordered_map<string,string>& params) {
    Difficulty diff=EASY;
    bool optimal=false;
    int wrong=0;
    double seconds=0;

    auto it=params.find("diff");
    if(it!=params.end())diff=parseDifficulty(it->second);
    it=params.find("optimal");
    if(it!=params.end())optimal=(it->second=="1"||it->second=="true");
    it=params.find("wrong");
    if(it!=params.end())wrong=stoi(it->second);
    it=params.find("seconds");
    if(it!=params.end())seconds=stod(it->second);

    int score=calculateGameScore(diff,optimal,wrong,seconds);
    string rank=getPlayerRank(score);

    ostringstream json;
    json<<"{\"score\":"<<score<<",\"rank\":\""<<rank<<"\"}";
    return json.str();
}

void handleClient(int clientFd) {
    char buf[8192];
    memset(buf,0,sizeof(buf));
    int n=recv(clientFd,buf,sizeof(buf)-1,0);
    if(n<=0){CLOSE_SOCKET(clientFd);return;}

    string request(buf,n);
    string method,path;
    {
        istringstream iss(request);
        iss>>method>>path;
    }

    size_t qpos=path.find('?');
    string route=(qpos==string::npos)?path:path.substr(0,qpos);
    unordered_map<string,string> params=(qpos==string::npos)?unordered_map<string,string>{}:parseQuery(path.substr(qpos));

    string response;
    if(route=="/api/generate"){
        response=buildResponse(200,"application/json",handleGenerate(params));
    }
    else if(route=="/api/score"){
        response=buildResponse(200,"application/json",handleScore(params));
    }
    else if(route=="/"||route=="/index.html"){
        response=buildResponse(200,"text/html; charset=utf-8",INDEX_HTML);
    }
    else{
        response=buildResponse(404,"text/plain","Not Found");
    }

    send(clientFd,response.c_str(),response.size(),0);
    CLOSE_SOCKET(clientFd);
}

int main(int argc, char* argv[]) {
#ifndef _WIN32
    signal(SIGPIPE, SIG_IGN);
#endif

    int port=8080;
    if(argc>1)port=atoi(argv[1]);

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed.\n";
        return 1;
    }
#endif

    int serverFd=socket(AF_INET,SOCK_STREAM,0);
    if(serverFd<0){perror("socket");return 1;}

    int opt=1;
    setsockopt(serverFd,SOL_SOCKET,SO_REUSEADDR,(const char*)&opt,sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=INADDR_ANY;
    addr.sin_port=htons(port);

    if(::bind(serverFd,(sockaddr*)&addr,sizeof(addr))<0){
        perror("bind");
        CLOSE_SOCKET(serverFd);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    if(listen(serverFd,128)<0){
        perror("listen");
        CLOSE_SOCKET(serverFd);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    cout<<"\n"
        <<"  ╔══════════════════════════════════════════════╗\n"
        <<"  ║   🧠 Brain Tester Server                    ║\n"
        <<"  ║   http://localhost:"<<port<<"                    ║\n"
        <<"  ║   Press Ctrl+C to stop                      ║\n"
        <<"  ╚══════════════════════════════════════════════╝\n"
        <<"\n";

    while(true){
        sockaddr_in clientAddr{};
        socklen_t clientLen=sizeof(clientAddr);
        int clientFd=accept(serverFd,(sockaddr*)&clientAddr,&clientLen);
        if(clientFd<0){perror("accept");continue;}

        thread([clientFd]() {
            handleClient(clientFd);
        }).detach();
    }

    CLOSE_SOCKET(serverFd);
#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}