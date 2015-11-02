#include "TaskManager.h"
#include "Executor.h"

#include "ExecutorManager.h"

void TaskManager::launch( TaskDescripter* task )
{
    taskdescripters_.push_back( task );
}

void TaskManager::run()
{
    if ( taskdescripters_.size() > 0 )
    {
        for ( auto t : this->taskdescripters_ )
        {
            launch_single( *t );
        }
    }
}

void TaskManager::stop( std::string task_id )
{

}

void TaskManager::launch_single( TaskDescripter* task )
{
    std::vector<Executor*> executors;
    for ( auto executor_id : task->executor() )
    {
        auto executor = ExecutorManager::instance()->find( executor_id );
        if ( executor == nullptr ) continue;
        executors.push_back( executor );
    }

    //TODO
}
