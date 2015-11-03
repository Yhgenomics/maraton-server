#ifndef MESSAGE_TASK_DELIVER_HPP_
#define MESSAGE_TASK_DELIVER_HPP_

#include "Message.h"
#include "json.hpp"
#include <string>
using namespace std;

namespace Protocol
{
    class MessageTaskDeliver : public Message
    {
    public:
    
        // Getter of task_id_
        string task_id()
        {
            return task_id_;
        }
        
        // Setter of task_id_
        void task_id( string value )
        {
            task_id_ = value;
            raw_data_[ "data" ][ "task_id" ] = value;
        }
        
        // Getter of uri_list_
        vector<std::string> uri_list()
        {
            return uri_list_;
        }
        
        // Setter of uri_list_
        void uri_list( vector<std::string> value )
        {
            uri_list_ = value;
            raw_data_[ "data" ][ "uri_list" ] = value;
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
        
        // Serilize Constructor
        MessageTaskDeliver()
            : Message( PROTOCOL_VERSION , 131 , 0 )
        {
            task_id( "" );
            uri_list(  );
            aligner( "" );
        }
        
        // Deserilize Constructor
        MessageTaskDeliver( Message* message )
            : Message( *message )
        {
            this->task_id_ = raw_data_[ "data" ][ "task_id" ].get<string>();
            this->uri_list_ = raw_data_[ "data" ][ "uri_list" ].get<vector<std::string>>();
            this->aligner_ = raw_data_[ "data" ][ "aligner" ].get<string>();
        }
    
    private:
    
        string task_id_;
        vector<std::string> uri_list_;
        string aligner_;
    
    }; // End of class define of MessageTaskDeliver

} // End of namespace Protocol
#endif // !Message_Task_Deliver_HPP_
