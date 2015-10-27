/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-10-27
* Description:
* * * * * * * * * * * * * * * */

#ifndef EXECUTOR_MANAGER_H_
#define EXECUTOR_MANAGER_H_ 

#include "maraton.h"
#include "Executor.h"
#include "Session.h"

class ExecutorManager :
    public Manager<Executor>,
    public Singleton<ExecutorManager>
{
public:

    Executor* find( Session* session );
    Executor* find( int session_id );
    void run();

private:

    friend Singleton<ExecutorManager>;

};

#endif //!EXECUTOR_MANAGER_H_ 