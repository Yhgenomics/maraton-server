/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-11-10
* Description:
* * * * * * * * * * * * * * * */

#ifndef EXECUTOR_TASK_DESCRIPTER_H_
#define EXECUTOR_TASK_DESCRIPTER_H_

#include <vector>
#include <string>

#include "maraton-server.h"
#include "TaskDescripter.h"

class ExecutorTaskDescripter
{
public:

    ExecutorTaskDescripter();
    ExecutorTaskDescripter( TaskDescripter * descripter , std::vector<std::string> fastq );

    PP_DEF( std::string , aligner )
    PP_DEF( std::vector<std::string> , args )
    PP_DEF( std::vector<std::string> , fastq )
    PP_DEF( std::string, id)
private:

    std::string                 id_;
    std::string                 aligner_;
    std::vector<std::string>    args_;
    std::vector<std::string>    fastq_;
};

#endif // !EXECUTOR_TASK_DESCRIPTER_H_ 