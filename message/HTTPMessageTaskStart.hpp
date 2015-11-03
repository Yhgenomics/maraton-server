#ifndef HTTPMESSAGE_TASK_START_HPP_
#define HTTPMESSAGE_TASK_START_HPP_

#include "Message.h"
#include "json.hpp"
#include <string>
using namespace std;

namespace Protocol
{
    class HTTPMessageTaskStart : public Message
    {
    public:
    
        // Getter of id_
        string id()
        {
            return id_;
        }
        
        // Setter of id_
        void id( string value )
        {
            id_ = value;
            raw_data_[ "data" ][ "id" ] = value;
        }
        
        // Getter of name_
        string name()
        {
            return name_;
        }
        
        // Setter of name_
        void name( string value )
        {
            name_ = value;
            raw_data_[ "data" ][ "name" ] = value;
        }
        
        // Getter of fastq_
        vector<string> fastq()
        {
            return fastq_;
        }
        
        // Setter of fastq_
        void fastq( vector<string> value )
        {
            fastq_ = value;
            raw_data_[ "data" ][ "fastq" ] = value;
        }
        
        // Getter of executor_
        vector<string> executor()
        {
            return executor_;
        }
        
        // Setter of executor_
        void executor( vector<string> value )
        {
            executor_ = value;
            raw_data_[ "data" ][ "executor" ] = value;
        }
        
        // Getter of aligner_
        string aligner()
        {
            return aligner_;
        }
        
        // Setter of aligner_
        void aligner( string value )
        {
            aligner_ = value;
            raw_data_[ "data" ][ "aligner" ] = value;
        }
        
        // Getter of args_
        vector<string> args()
        {
            return args_;
        }
        
        // Setter of args_
        void args( vector<string> value )
        {
            args_ = value;
            raw_data_[ "data" ][ "args" ] = value;
        }
        
        // Serilize Constructor
        HTTPMessageTaskStart()
            : Message( PROTOCOL_VERSION , 10000 , 0 )
        {
            id( "" );
            name( "" );
            fastq(  );
            executor(  );
            aligner( "" );
            args(  );
        }
        
        // Deserilize Constructor
        HTTPMessageTaskStart( Message* message )
            : Message( *message )
        {
            this->id_ = raw_data_[ "data" ][ "id" ].get<string>();
            this->name_ = raw_data_[ "data" ][ "name" ].get<string>();
            this->fastq_ = raw_data_[ "data" ][ "fastq" ].get<vector<string>>();
            this->executor_ = raw_data_[ "data" ][ "executor" ].get<vector<string>>();
            this->aligner_ = raw_data_[ "data" ][ "aligner" ].get<string>();
            this->args_ = raw_data_[ "data" ][ "args" ].get<vector<string>>();
        }
    
    private:
    
        string id_;
        string name_;
        vector<string> fastq_;
        vector<string> executor_;
        string aligner_;
        vector<string> args_;
    
    }; // End of class define of HTTPMessageTaskStart

} // End of namespace Protocol
#endif // !HTTPMessage_Task_Start_HPP_
