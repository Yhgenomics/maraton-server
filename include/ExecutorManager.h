/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-10-27
* Description:
* * * * * * * * * * * * * * * */

#ifndef EXECUTOR_MANAGER_H_
#define EXECUTOR_MANAGER_H_ 

#include "Manager.hpp"
#include "Executor.h"

class ExecutorManager :
    public Manager<Executor>,
    public Singleton<ExecutorManager>
{
public:

    Executor*               find( ClusterNode* session );
    Executor*               find( int session_id );
    Executor*               find( std::string executor_id );
    std::vector<Executor*>  find_by_taskid( std::string task_id );

    void                    run();
    bool                    pop( Executor* instance ) override;
    std::vector<Executor*>  list();

private:

    friend Singleton<ExecutorManager>;

};

#endif // !EXECUTOR_MANAGER_H_ 