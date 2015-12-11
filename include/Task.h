/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-11-10
* Description:
* * * * * * * * * * * * * * * */

#ifndef TASK_H_
#define TASK_H_ 

#include <string>
#include <vector>
#include <map>

#include "TaskDescripter.h"
#include "Executor.h"
#include "Error.h"
#include "maraton.h"

class Task
{
public:

    enum TaskStatus
    {
        kUnknow = 0 ,
        kPending,
        kRunning,
        kMerging,
        kFinished,
        kStopped,
        kError
    };

    Task( TaskDescripter* descripter );
    ~Task();

    void                   add_executor( Executor* executor );
    void                   alignment_finish( Executor* executor );
    void                   merge_finish( const size_t status );
    void                   fail( size_t error_code );
    void                   stop();

    TaskDescripter*        descripter() { return this->descripter_; };
    Error                  launch();

    size_t                 create_time() { return this->create_time_; };
    TaskStatus             status() { return this->status_; };
    void                   status( TaskStatus value ) { this->status_ = value; };
    
    size_t                 progress() { return this->progress_; }
    
    void                   update_progress( );
    void                   update_executor_status( Executor* executor , 
                                                   TaskStatus status );
private:

    TaskDescripter*        descripter_;
    std::vector<Executor*> executor_list_;

    std::map<std::string , 
        TaskStatus>        executor_map_;

    bool                   is_finished_             = false;
    TaskStatus             status_                  = TaskStatus::kUnknow;
    size_t                 create_time_;
    size_t                 start_time_              = 0;
    size_t                 cast_time_               = 0;
    size_t                 progress_                = 0; 
    Executor*              merger_                  = nullptr;
};

#endif // !TASK_H_ 