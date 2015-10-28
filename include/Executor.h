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

using namespace std;


class Executor
{
public:

    Executor( ExecutorSession* session);
    ~Executor();
    
    //func
    void run();

    //getter & setter
    ExecutorSession* session();
    bool connected() { return this->connected_; };
    void refresh() { this->last_update_time_ = Timer::tick(); };
    
    void memory_size( long value ) { memory_size_ = value; };
    size_t memory_size() { return memory_size_; };

    void disk_size( long value ) { disk_size_ = value; };
    size_t disk_size() { return disk_size_; };

    void id( string value ) { id_ = value; };
    string id() { return id_; };

    void ability( long value ) { ability_ = value; };
    size_t ability() { return ability_; };

    void status( EXECUTORSTATUS value ) { status_ = value; };
    EXECUTORSTATUS status() { return status_; };

private:

    ExecutorSession* session_;
    
    //variable
    int last_update_time_ = 0;
    bool connected_ = true;

    //property
    size_t memory_size_ = 0;
    size_t disk_size_ = 0;
    string id_ = "";
    size_t ability_ = 0;
    EXECUTORSTATUS status_ = EXECUTORSTATUS::UNKNOWN;

    //func
    bool check_timeout();
};

#endif //!EXECUTOR_H_ 