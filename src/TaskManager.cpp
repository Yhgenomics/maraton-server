#include "TaskManager.h"
#include <memory>

#include "Executor.h"
#include "ExecutorManager.h"
#include "MaratonMath.hpp"
#include "Error.h"

Error TaskManager::launch( TaskDescripter* task )
{
    Task* t = new Task( task );
    t->status( Task::TaskStatus::kPending );

    for ( auto executor_id : task->executor() )
    {
        auto executor = ExecutorManager::instance()->find( executor_id );

        if ( executor == nullptr ) continue;

        t->add_executor( executor );
    }

    this->task_list_.insert( task_list_ .begin() , t );
     
    return Error( 0 , "" );
}

Task* TaskManager::find( std::string task_id )
{ 
    for ( auto t : this->task_list_ )
    {
        
        if ( t->descripter()->id() == task_id )
        {
            return t;
        }
    }

    return nullptr;
}

void TaskManager::run()
{
    for ( auto itr = this->task_list_.begin(); itr != this->task_list_.end(); itr++ )
    {
        Task* t = *itr;

        if ( t->status() == Task::TaskStatus::kPending )
        {
            auto result = t->launch();

            if ( result.code() != 0 )
            {
                break;
            }
        }
    }
}

void TaskManager::stop( std::string task_id )
{
    for ( auto itr = this->task_list_.begin(); itr != this->task_list_.end(); itr++ )
    {
        if ( Task::TaskStatus::kFinished != ( *itr )->status() 
             && task_id == (*itr)->descripter()->id() )
        {
            ( *itr )->stop();
            this->task_list_.erase( itr );
            SAFE_DELETE( ( *itr ) );
            break;
        }
    } 
}

void TaskManager::task_finish( std::string task_id , Executor * executor )
{
    auto task = this->find( task_id );
    task->finish( executor );
}

