#include "TaskManager.h"
#include "Executor.h"

#include "ExecutorManager.h"
#include "MaratonMath.hpp"

#include <memory>

bool TaskManager::launch( TaskDescripter* task )
{
    return launch_single( task );
    //taskdescripters_.push_back( task );
}

void TaskManager::run()
{
    
}

void TaskManager::stop( std::string task_id )
{
    auto executors = ExecutorManager::instance()->list();

    for ( auto exe : executors )
    {
        if ( exe->current_task() != nullptr &&
             exe->current_task()->id() == task_id )
        {
            exe->stop_task();
        }
    }
}

bool TaskManager::launch_single( TaskDescripter* task )
{
    this->error_ = "";
    
    if ( task == nullptr )
    {
        this->error_ += "[TaskManager] task is null\r\n";
        return false;
    }

    std::vector<Executor*> executors;
    size_t sum_score = 0;

    for ( auto executor_id : task->executor() )
    {
        auto executor = ExecutorManager::instance()->find( executor_id );

        if ( executor == nullptr ) continue;

        executors.push_back( executor );
        sum_score += executor->ability();
    }

    size_t exe_count = executors.size();
    size_t fastq_count = task->fastq().size();
    
    std::vector<std::string> fastqs( task->fastq() );

    std::vector<std::string> exe_fastq_list;

    for ( auto executor : executors )
    {
        exe_fastq_list.clear();

        if ( executor->status() != Executor::ExecutorStatus::kIdle )
        {
            this->error_ += "[" + executor->id() + "] not idle\r\n";
            break;
        }

        int fastq_size = static_cast< int > ( maraton_round( ( ( double )executor->ability() / ( double )sum_score )  * fastq_count ) );

        for ( size_t i = 0; i < fastq_size; i++ )
        {
            exe_fastq_list.push_back( fastqs.front() );
            fastqs.erase( fastqs.begin() );
        }

        TaskDescripter* executor_task = new TaskDescripter();
        executor_task->id( task->id() );
        executor_task->args( task->args() );
        executor_task->aligner( task->aligner() );
        executor_task->fastq( exe_fastq_list );
        executor_task->name( task->name() );
        executor_task->status( task->status() );

        if ( !executor->launch_task( executor_task ) )
        {
            this->error_ += "[" + executor->id() +"] launch task errors\r\n" ;
            SAFE_DELETE( executor_task );
            break;
        }
    }
     
    return this->error_.empty() == false;
}
