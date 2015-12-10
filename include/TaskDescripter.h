/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-11-02
* Description:
* * * * * * * * * * * * * * * */

#ifndef TASK_HPP_
#define TASK_HPP_ 

#include <string>
#include <vector>

#include "maraton.h"
#include "maraton-server.h"
 
class TaskDescripter
{
public:

    enum TaskDescripterStatus
    {
        kUnknow = 0 ,
        kDownloading,
        kQueue,
        kRun,
        kFinish
    };

    TaskDescripter()
    {
        this->status( TaskDescripterStatus::kUnknow );
    }

    TaskDescripter( const TaskDescripter& ins )
    {
        this->id_       = ins.id_;
        this->name_     = ins.name_;
        this->aligner_  = ins.aligner_;
        this->fastq_    = ins.fastq_;
        this->executor_ = ins.executor_;
        this->args_     = ins.args_;
        this->reference_= ins.reference_;
    }

    TaskDescripter& operator=( const TaskDescripter& task )
    {
        this->id_       = task.id_;
        this->name_     = task.name_;
        this->aligner_  = task.aligner_;
        this->fastq_    = task.fastq_;
        this->executor_ = task.executor_;
        this->args_     = task.args_;
        this->reference_= task.reference_;
        return *this;
    }

    PP_DEF( std::string , id )
    PP_DEF( std::string , name )
    PP_DEF( std::string , aligner )
    PP_DEF( std::vector<std::string> , fastq )
    PP_DEF( std::vector<std::string> , executor )
    PP_DEF( std::vector<std::string> , args )
    PP_DEF( TaskDescripterStatus , status)
    PP_DEF( int , progress )
    PP_DEF( std::string , reference )

private:

    std::string                 id_ = "";
    std::string                 name_ = "";
    std::string                 aligner_ = "";
    std::vector<std::string>    fastq_;
    std::vector<std::string>    executor_;
    std::vector<std::string>    args_;
    TaskDescripterStatus        status_ = TaskDescripterStatus::kUnknow;
    int                         progress_ = 0;
    std::string                 reference_ = "";
};

#endif // !TASK_HPP_ 