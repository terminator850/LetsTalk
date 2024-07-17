#include <string>
#include<vector>
using namespace std;
struct PointInfo{
    string m_address;
    int m_port;
    string m_nickname;
    string m_pwd;
    uint64_t m_last_heartbeat_time;
};

class ConnectionManager{
public:
    ConnectionManager(string nickname, int prot);
    //接收链接请求，维护 m_friend_point_infos
    int JoinChat();
private:
    // 定时向m_friend_point_infos发送心跳，更新心跳超时列表 
    void heartbeat();
    void onHeartbeat();

    PointInfo m_mine_point_info;
    vector<PointInfo> m_friend_point_infos;
};