#include "ExecutorTaskDescripter.h"

ExecutorTaskDescripter::ExecutorTaskDescripter()
{
}

ExecutorTaskDescripter::ExecutorTaskDescripter( TaskDescripter * descripter , std::vector<std::string> fastq )
{
    this->id( descripter->id() );
    this->args( descripter->args() );
    this->aligner( descripter->aligner() );
    this->fastq( fastq );
    this->reference( descripter->reference( ) );
}
