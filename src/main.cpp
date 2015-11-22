#include "MRT.h"
#include "ExecutorListener.h"
#include "ExecutorManager.h"
#include "TaskManager.h"
#include "RESTAPIListener.h"
#include "WebSubscriber.h"

int main(int argc,char** argv)
{     
    while(true)
    {
        //WebSubscriber::instance( )->task_result( "taskId" , 100 );
        MRT::SyncWorker::create( 1 , [ ] ( MRT::SyncWorker* worker )
        { 
            ExecutorManager::instance( )->run( );
            TaskManager::instance( )->run( );

            return false;
        } , nullptr, nullptr );

        MRT::Maraton::instance( )->regist(
            make_uptr( ExecutorListener , "localhost" ) );
        MRT::Maraton::instance( )->regist(
            make_uptr( RestAPIListener , "localhost" ) );
        MRT::Maraton::instance( )->loop( );
    }
    return 0;
}
