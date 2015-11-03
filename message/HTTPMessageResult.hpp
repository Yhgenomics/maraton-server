#ifndef HTTPMESSAGE_RESULT_HPP_
#define HTTPMESSAGE_RESULT_HPP_

#include "Message.h"
#include "json.hpp"
#include <string>
using namespace std;

namespace Protocol
{
    class HTTPMessageResult : public Message
    {
    public:
    
        // Getter of result_
        int result()
        {
            return result_;
        }
        
        // Setter of result_
        void result( int value )
        {
            result_ = value;
            raw_data_[ "data" ][ "result" ] = value;
        }
        
        // Getter of message_
        string message()
        {
            return message_;
        }
        
        // Setter of message_
        void message( string value )
        {
            message_ = value;
            raw_data_[ "data" ][ "message" ] = value;
        }
        
        // Serilize Constructor
        HTTPMessageResult()
            : Message( PROTOCOL_VERSION , 19999 , 0 )
        {
            result(  );
            message( "" );
        }
        
        // Deserilize Constructor
        HTTPMessageResult( Message* message )
            : Message( *message )
        {
            this->result_ = raw_data_[ "data" ][ "result" ].get<int>();
            this->message_ = raw_data_[ "data" ][ "message" ].get<string>();
        }
    
    private:
    
        int result_;
        string message_;
    
    }; // End of class define of HTTPMessageResult

} // End of namespace Protocol
#endif // !HTTPMessage_Result_HPP_
