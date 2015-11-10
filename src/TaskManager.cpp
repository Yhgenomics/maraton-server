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
    this->task_list_.insert( task_list_ .begin() , t );
    auto error = t->launch();

    if ( error.code() > 0 )
    {
        this->stop( t->descripter()->id() );
    }

    return error;
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
    
}

void TaskManager::stop( std::string task_id )
{

    for ( auto itr = this->task_list_.begin(); itr != this->task_list_.end(); itr++ )
    {

        if ( Task::TaskStatus::kFinished != ( *itr )->status() && 
            task_id == (*itr)->descripter()->id() )
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

