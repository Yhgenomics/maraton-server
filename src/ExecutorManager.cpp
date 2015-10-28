#include "ExecutorManager.h"
#include "ExecutorSession.h"
#include "Executor.h"

Executor * ExecutorManager::find( Session * session )
{
    return this->find( session->id() );
}

Executor * ExecutorManager::find( int session_id )
{
    for ( auto result : this->instances() )
    {
        if ( result->session()->id() == session_id )
        {
            return result;
        }
    }
    return nullptr;
}

void ExecutorManager::run()
{
    for ( auto result : this->instances() )
    {
        result->run();
    }
}
