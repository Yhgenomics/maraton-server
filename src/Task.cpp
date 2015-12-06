#include "Task.h"
#include "ExecutorManager.h"
#include "MaratonMath.hpp"
#include "ExecutorTaskDescripter.h"
#include "WebSubscriber.h"

Task::Task( TaskDescripter * descripter )
{
    this->descripter_ = descripter;
    this->create_time_ = Timer::tick();
}

Task::~Task()
{
    SAFE_DELETE( this->descripter_ );
}

void Task::add_executor( Executor * executor )
{
    executor_list_.push_back( executor );
    executor_running_list_.push_back( executor );
}

void Task::finish( Executor * executor )
{
    for ( auto itr = executor_running_list_.begin(); itr != executor_running_list_.end(); itr++ )
    {
        if ( *itr == executor )
        {
            executor_running_list_.erase( itr );
            break;
        }
    }

    // Notify the web server
    // when all executors finish the task,
    if ( 0 == this->executor_running_list_.size() )
    {
        this->cast_time_    = Timer::tick() - this->start_time_;
        this->status_       = TaskStatus::kMerging;
        WebSubscriber::instance( )->task_done( this->descripter_->id( ) ,
                                               this->start_time_ ,
                                               this->cast_time_);
    }
}

void Task::fail( size_t error_code )
{
    for ( auto exe : executor_list_ )
    {
        exe->stop_task( );
    }

    WebSubscriber::instance( )->task_fail( this->descripter_->id( ) ,
                                           error_code);
}

Error Task::launch()
{ 
    Error error(0,"");

    if ( this->descripter_ == nullptr )
    {
        error.code( 1 );
        error.message( "descripter is null" );
        this->status_ = TaskStatus::kError;
        return error;
    }

    std::vector<Executor*> executors = executor_running_list_;
    size_t sum_score = 0;

    // Check if all executors are in standby status
    for ( auto executor : executors )
    {
        if ( executor->status() != Executor::ExecutorStatus::kStandby )
        {
            error.code( 1 );
            error.message( executor->id() + " not standby" );
            this->status_ = TaskStatus::kError;
            return error;
        }
    }

    // Calculate the total score
    for ( auto executor_id : this->descripter()->executor() )
    {
        auto executor = ExecutorManager::instance()->find( executor_id );

        if ( executor == nullptr ) continue;

        sum_score += executor->ability();
    }

    // According to the score, 
    // assign the task to the executor
    size_t exe_count    = executors.size();
    size_t fastq_count  = this->descripter()->fastq().size();

    std::vector<std::string> fastqs( this->descripter()->fastq() );

    std::vector<std::string> exe_fastq_list;

    for ( auto executor : executors )
    {
        exe_fastq_list.clear();

        int fastq_size = static_cast< int > ( 
            maraton_round( ( ( double )executor->ability() / ( double )sum_score )  * fastq_count ) 
        );

        for ( size_t i = 0; i < fastq_size; i++ )
        {
            exe_fastq_list.push_back( fastqs.front() );
            fastqs.erase( fastqs.begin() );
        }

        ExecutorTaskDescripter* executor_task_des = new ExecutorTaskDescripter( 
            this->descripter() , 
            exe_fastq_list 
        );
       
        auto executor_err = executor->launch_task( executor_task_des );

        if ( executor_err.code() > 0)
        {
            error.code( executor_err.code() );
            error.message( executor_err.message() );
            SAFE_DELETE( executor_task_des );
            break;
        }
    }

    // Check the error and update the status
    if ( 0 == error.code() )
    {
        this->start_time_ = Timer::tick();
        this->status_ = TaskStatus::kRunning;
    }
    else
    {
        this->status_ = TaskStatus::kError;
    }

    WebSubscriber::instance( )->task_start( this->descripter_->id( ) );

    return error;
}

void Task::stop()
{
    for ( auto itr = executor_list_.begin(); itr != executor_list_.end(); itr++ )
    {
        auto exe = *itr;
        exe->stop_task();
    }

    this->status_ = TaskStatus::kStopped;
}
