/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef EXECUTOR_H_
#define EXECUTOR_H_ 

#include "maraton.h"

class ExecutorSession;

class Executor
{
public:

    Executor( ExecutorSession* session);
    ~Executor();
    
    //func
    void run();

    //getter & setter
    ExecutorSession* session();
    bool connected() { return this->connected_; };
    void refresh() { this->last_update_time_ = Timer::tick(); };

private:

    ExecutorSession* session_;
    
    //variable
    int last_update_time_ = 0;
    bool connected_ = true;

    //func
    bool check_timeout();
};

#endif //!EXECUTOR_H_ 