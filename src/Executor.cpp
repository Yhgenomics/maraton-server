#include "maraton-server.h"
#include "Executor.h"
#include "ExecutorTaskDescripter.h"

#include "MessagesHandler.hpp"
#include "MessageTaskDeliver.hpp"
#include "MessageTaskCancel.hpp"

using namespace Protocol;
 
Executor::Executor( ExecutorNode * session )
{
    this->session_ = session;

    //say hello to client
    UPTR<Protocol::MessageGreeting> msg = MAKE_UPTR( Protocol::MessageGreeting );
    session->send( MOVE(msg) );

    this->refresh();
}

Executor::~Executor()
{
    SAFE_DELETE( this->current_task_ );
}

void Executor::operator()( ExecutorNode * session )
{
}

void Executor::run()
{
    if ( !this->connected() ) return;

    if ( this->check_timeout() ) return;
}

void Executor::stop_task()
{
    if ( this->current_task_ == nullptr ) return;

    UPTR<Protocol::MessageTaskCancel> msg = MAKE_UPTR( Protocol::MessageTaskCancel );
    msg->task_id( this->current_task_->id() );

    this->session()->send( MOVE(msg) );
}

ExecutorNode * Executor::session()
{
    return this->session_;
}

Error Executor::launch_task( ExecutorTaskDescripter* task )
{
    Error err;
    err.code( 0 );

    if ( this->current_task_ != nullptr )
    {
        err.code( 1 );
        err.message( this->id()+": task running" );
        return err;
    }

    this->current_task( task );

    if ( task->aligner().empty() )
    {
        err.code( 1 );
        err.message( this->id() + ": no aligner assigned" );
        return err;

    }

    if ( task->fastq().empty() )
    {
        err.code( 1 );
        err.message( this->id() + ": no fastq files assigned" );
        return err;
    }

    UPTR<MessageTaskDeliver> msg = MAKE_UPTR(MessageTaskDeliver);
    msg->aligner( task->aligner() );
    msg->task_id( task->id() );
    msg->uri_list( task->fastq() );

    this->session()->send( MOVE(msg) );

    return err;
}

bool Executor::check_timeout()
{
    size_t delta = Timer::tick() - this->last_update_time_;

    if ( delta >= EXECUTOR_TIMEOUT )
    {
        this->last_update_time_ = Timer::tick();
        this->connected_        = false;
        this->session_->close();
        LOG_SYS( "Kick %ld\r\n", this->session()->id() );
        return true;
    }

    return false;
}
