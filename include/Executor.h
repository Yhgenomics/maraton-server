/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-10-28
* Description:
* * * * * * * * * * * * * * * */

#ifndef EXECUTOR_H_
#define EXECUTOR_H_ 

#include <string.h>

#include "maraton.h"
#include "maraton-server.h"
#include "ExecutorSession.h"
#include "TaskDescripter.hpp"
#include "Error.h"
#include "ExecutorTaskDescripter.hpp"

using namespace std;

class Executor
{
public:

    enum ExecutorStatus
    {
        kUnknow              = 0,
        kBooting             = 1,
        kSelfTesting         = 2,
        kStandby             = 3,
        kError               = 4,
        kResourceDownloading = 10,
        kTaskDataPreparing   = 11,
        kComputing           = 12,
        kUploading           = 13,
        kTaskFinished        = 14,
        kException           = 20
    };

    Executor( ExecutorSession * session );
    ~Executor();

    //operator
    void                        operator()( ExecutorSession* session );
    
    //func
    void                        run();
    void                        stop_task();

    //void command( std::string command , std::string uris, std::string run_as_user );
    Error                       launch_task( ExecutorTaskDescripter* value );

    //getter & setter
    ExecutorSession*            session();
    bool                        connected() { return this->connected_; };
    void                        refresh() { this->last_update_time_ = Timer::tick(); };
    
    void                        memory_size( size_t value ) { memory_size_ = value; };
    size_t                      memory_size() { return memory_size_; };

    void                        disk_size( size_t value ) { disk_size_ = value; };
    size_t                      disk_size() { return disk_size_; };

    void                        id( string value ) { id_ = value; };
    string                      id() { return id_; };

    void                        ability( size_t value ) { ability_ = value; };
    size_t                      ability() { return ability_; };

    void                        status( ExecutorStatus value ) { status_ = value; };
    ExecutorStatus              status() { return status_; };

    void                        current_task( ExecutorTaskDescripter* value ) { SAFE_DELETE( this->current_task_ ); this->current_task_ = value; };
    ExecutorTaskDescripter*     current_task() { return this->current_task_; };

private:

    ExecutorSession*            session_;
    
    //variable
    size_t                      last_update_time_ = 0;
    bool                        connected_ = true;

    //property
    size_t                      memory_size_ = 0;
    size_t                      disk_size_ = 0;
    string                      id_ = "";
    size_t                      ability_ = 0;
    ExecutorStatus              status_ = ExecutorStatus::kUnknow;
    ExecutorTaskDescripter*     current_task_ = nullptr;

    //func
    bool                        check_timeout();
};

#endif //!EXECUTOR_H_ 