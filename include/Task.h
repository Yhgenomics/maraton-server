/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */

#ifndef TASK_H_
#define TASK_H_ 

#include <string>
#include <vector>
#include "TaskDescripter.hpp"
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
        kFinished,
        kStopped,
        kError
    };

    Task( TaskDescripter* descripter );
    ~Task();

    void                   add_executor( Executor* executor );
    void                   finish( Executor* executor );
    void                   stop();

    TaskDescripter*        descripter() { return this->descripter_; };
    Error                  launch();

    size_t                 create_time() { return this->create_time_; };
    TaskStatus             status() { return this->status_; };
    void                   status( TaskStatus value ) { this->status_ = value; };
private:

    TaskDescripter*        descripter_;
    std::vector<Executor*> executor_list_;
    std::vector<Executor*> executor_running_list_;
    bool                   is_finished_ = false;
    TaskStatus             status_ = TaskStatus::kUnknow;
    size_t                 create_time_;
    size_t                 start_time_ = 0;
    size_t                 cast_time_ = 0;
};

#endif //!TASK_H_ 