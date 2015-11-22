/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-11-06
* Description:
* * * * * * * * * * * * * * * */

#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_ 

#include <string>
#include <vector>

#include "maraton.h"
#include "TaskDescripter.h"
#include "Task.h"

class TaskManager :
    public MRT::Singleton<TaskManager> 
{
public:

    void                            run();
    void                            stop( std::string task_id );
    void                            task_finish( std::string task_id , Executor* executor );

    Error                           launch( TaskDescripter* task );
    std::string                     error() { return error_; };
    Task*                           find( std::string task_id );

private:

    std::vector<TaskDescripter*>    taskdescripters_;
    std::vector<Task*>              task_list_;
    std::string                     error_ = ""; 

    friend Singleton<TaskManager>; 
};

#endif // !TASK_MANAGER_H_ 