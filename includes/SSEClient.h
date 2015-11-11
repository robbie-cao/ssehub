#ifndef SSECLIENT_H
#define SSECLIENT_H

#include <string>
#include <deque>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <stdint.h>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "HTTPRequest.h"

enum SubscriptionType {
  SUBSCRIPTION_ID,
  SUBSCRIPTION_EVENT_TYPE
};

typedef struct {
  string key;
  SubscriptionType type;
} SubscriptionElement;

using namespace std;

class SSEClient {
  public:
    SSEClient(int, struct sockaddr_in* csin);
    ~SSEClient();
    int Send(const string &data);
    size_t Read(void* buf, int len);
    int Getfd();
    HTTPRequest* GetHttpReq();
    const string GetIP();
    uint32_t GetSockAddr();
    void MarkAsDead();
    bool IsDead();
    void Destroy();
    void DeleteHttpReq();
    bool isSubscribed(const string key, SubscriptionType type);
    void Subscribe(const string key, SubscriptionType type);
    bool isFiltered();

   private:
    int _fd;
    struct sockaddr_in _csin;
    bool _dead;
    unsigned int _sndBufSize;
    vector<SubscriptionElement> _subscriptions;
    boost::mutex _writelock;
    boost::shared_ptr<HTTPRequest> m_httpReq;
};

#endif
