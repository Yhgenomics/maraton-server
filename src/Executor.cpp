#include "maraton-server.h"
#include "Executor.h"
#include "ExecutorTaskDescripter.h"

#include "MessagesHandler.hpp"
#include "MessageTaskDeliver.hpp"
#include "MessageTaskCancel.hpp"

using namespace Protocol;

Executor::Executor( ExecutorSession * session )
{
    this->session_ = session;

    //say hello to client
    uptr<Protocol::MessageGreeting> msg = make_uptr( Protocol::MessageGreeting );
    session->send_message( move_ptr( msg ) );

    this->refresh( );
}

Executor::~Executor( )
{
    SAFE_DELETE( this->current_task_ );
}

void Executor::run( )
{
    if ( !this->connected( ) ) return;

    if ( this->check_timeout( ) ) return;
}

void Executor::stop_task( )
{
    if ( this->current_task_ == nullptr ) return;

    uptr<Protocol::MessageTaskCancel> msg = make_uptr( Protocol::MessageTaskCancel );
    msg->task_id( this->current_task_->id( ) );

    this->session( )->send_message( move_ptr( msg ) );
}

ExecutorSession * Executor::session( )
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
        err.message( this->id( ) + ": task running" );
        return err;
    }

    this->current_task( task );

    if ( task->aligner( ).empty( ) )
    {
        err.code( 1 );
        err.message( this->id( ) + ": no aligner assigned" );
        return err;

    }

    if ( task->fastq( ).empty( ) )
    {
        err.code( 1 );
        err.message( this->id( ) + ": no fastq files assigned" );
        return err;
    }

    uptr<MessageTaskDeliver> msg = make_uptr( MessageTaskDeliver );
    msg->aligner ( task->aligner( ) );
    msg->task_id ( task->id( ) );
    msg->uri_list( task->fastq( ) );
    msg->reference ( task->reference( ) );

    this->session( )->send_message( move_ptr( msg ) );

    return err;
}

bool Executor::check_timeout( )
{
    size_t delta = Timer::tick( ) - this->last_update_time_;

    if ( delta >= EXECUTOR_TIMEOUT )
    {
        this->last_update_time_ = Timer::tick( );
        this->connected_        = false;
        this->session_->close( );
        LOG_SYS( "Kick %ld\r\n" , this->session( )->id( ) );
        return true;
    }

    return false;
}
