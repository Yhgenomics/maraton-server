#include "ExecutorListener.h"
#include "ExecutorManager.h"

ExecutorListener::ExecutorListener( std::string ip )
    : Listener( ip , LISTEN_PORT )
{
}

ExecutorListener::~ExecutorListener( )
{
}

MRT::Session * ExecutorListener::create_session( )
{
    return new ExecutorSession( );
}

void ExecutorListener::on_session_open( MRT::Session * session )
{
    Executor* executor = new Executor( scast<ExecutorSession*>( session ) );
    ExecutorManager::instance( )->push( executor );
}

void ExecutorListener::on_session_close( MRT::Session * session )
{
    auto s   = scast<ExecutorSession*>( session );
    auto exe = ExecutorManager::instance( )->find( s->id( ) );

    if( exe != nullptr )
    {
        ExecutorManager::instance( )->pop( exe );
    }
}
