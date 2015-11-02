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

    void launch( TaskDescripter* task );

    void run();

    void stop( const TaskDescripter* task );
    void stop( std::string task_id );

private:

    friend Singleton<TaskManager>; 
    std::vector<TaskDescripter*> taskdescripters_;

    void launch_single( TaskDescripter* task );

};

#endif //!TASK_MANAGER_H_ 