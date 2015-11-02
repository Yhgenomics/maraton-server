/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-10-27
* Description:
* * * * * * * * * * * * * * * */

#ifndef EXECUTOR_MANAGER_H_
#define EXECUTOR_MANAGER_H_ 

#include "maraton.h"
#include "Session.h"
#include "Executor.h"

class ExecutorManager :
    public Manager<Executor>,
    public Singleton<ExecutorManager>
{
public:

    Executor* find( Session* session );
    Executor* find( int session_id );
    Executor* find( std::string executor_id );

    void run();
    bool pop( Executor* instance ) override;
    std::vector<Executor*> list();

private:

    friend Singleton<ExecutorManager>;

};

#endif //!EXECUTOR_MANAGER_H_ 