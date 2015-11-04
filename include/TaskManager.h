/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_ 

#include <string>
#include <vector>

#include "maraton.h"
#include "TaskDescripter.hpp"

class TaskManager :
    public Singleton<TaskManager> 
{
public:

    bool launch( TaskDescripter* task );

    std::string error() { return error_; };

    void run();

    void stop( std::string task_id );

private:

    friend Singleton<TaskManager>; 
    std::vector<TaskDescripter*> taskdescripters_;

    std::string error_ = "";
    bool launch_single( TaskDescripter* task );

};

#endif //!TASK_MANAGER_H_ 