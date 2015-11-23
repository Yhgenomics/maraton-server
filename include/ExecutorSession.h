/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef EXECUTOR_SESSION_H_
#define EXECUTOR_SESSION_H_ 

#include <vector>
#include <mutex>
#include <string>

#include "ClusterSession.h"
#include "MRT.h"

class ExecutorSession :
    public ClusterSession
{
public:

    ExecutorSession();
    virtual ~ExecutorSession() override;

protected: 
     
private: 
     
    virtual void on_message( uptr<Message> message ) override;

};

#endif //EXECUTOR_SESSION_H_ 