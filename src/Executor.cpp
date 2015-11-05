#include "maraton-server.h"
#include "Executor.h"
#include "ExecutorSession.h"

#include "MessagesHandler.hpp"
#include "MessageTaskDeliver.hpp"
#include "MessageTaskCancel.hpp"

using namespace Protocol;

Executor::Executor( ExecutorSession * session )
{
    this->session_ = session;

    //say hello to client
    Protocol::MessageGreeting msg;
    session->send( &msg );

    this->refresh();
}

Executor::~Executor()
{
    SAFE_DELETE( this->current_task_ );
}

void Executor::operator()( ExecutorSession * session )
{
     
}

void Executor::run()
{

    if ( !this->connected() ) return;

    if ( this->check_timeout() ) return;

}

void Executor::stop_task()
{
    
    if ( this->current_task_ == nullptr )
        return;

    MessageTaskCancel msg;
    msg.task_id( this->current_task_->id() );
    this->session()->send( &msg );
}

ExecutorSession * Executor::session()
{
    return this->session_;
}

bool Executor::launch_task( TaskDescripter* task )
{
    if ( this->current_task_ != nullptr )
    {
        return false;
    }

    this->current_task( task );

    if ( task->aligner().empty() )
        return false;

    if ( task->fastq().empty() )
        return false;

    MessageTaskDeliver msg;

    msg.aligner( task->aligner() );
    msg.task_id( task->id() );
    msg.uri_list( task->fastq() );

    this->session()->send( &msg );

    return true;
}

bool Executor::check_timeout()
{
    int delta = Timer::tick() - this->last_update_time_;

    if ( delta >= EXECUTOR_TIMEOUT )
    {
        this->last_update_time_ = Timer::tick();
        this->connected_ = false;
        this->session_->close();
        Logger::sys( "Kick %ld\r\n", this->session()->id() );
        return true;
    }

    return false;
}
