#ifndef HTTPMESSAGE_COMMAND_HPP_
#define HTTPMESSAGE_COMMAND_HPP_

#include "Message.h"
#include "json.hpp"
#include <string>

using namespace std;

namespace Protocol
{
    class HTTPMessageCommand : public Message
    {
    public:
    
        // Getter of cmd_
        string cmd()
        {
            return cmd_;
        }
        
        // Setter of cmd_
        void cmd( string value )
        {
            cmd_ = value;
            raw_data_[ "data" ][ "cmd" ] = value;
        }
        
        // Getter of uris_
        vector<string> uris()
        {
            return uris_;
        }
        
        // Setter of uris_
        void uris( vector<string> value )
        {
            uris_ = value;
            raw_data_[ "data" ][ "uris" ] = value;
        }
        
        // Getter of runasuser_
        string runAsUser()
        {
            return runasuser_;
        }
        
        // Setter of runasuser_
        void runAsUser( string value )
        {
            runasuser_ = value;
            raw_data_[ "data" ][ "runAsUser" ] = value;
        }
        
        // Getter of executors_
        vector<string> executors()
        {
            return executors_;
        }
        
        // Setter of executors_
        void executors( vector<string> value )
        {
            executors_ = value;
            raw_data_[ "data" ][ "executors" ] = value;
        }
        
        // Serilize Constructor
        HTTPMessageCommand()
            : Message( PROTOCOL_VERSION , 10100 , 0 )
        {
            cmd( "" );
            uris(  );
            runAsUser( "root" );
            executors(  );
        }
        
        // Deserilize Constructor
        HTTPMessageCommand( Message* message )
            : Message( *message )
        {
            this->cmd_ = raw_data_[ "data" ][ "cmd" ].get<string>();
            this->uris_ = raw_data_[ "data" ][ "uris" ].get<vector<string>>();
            this->runasuser_ = raw_data_[ "data" ][ "runAsUser" ].get<string>();
            this->executors_ = raw_data_[ "data" ][ "executors" ].get<vector<string>>();
        }
    
    private:
    
        string cmd_;
        vector<string> uris_;
        string runasuser_;
        vector<string> executors_;
    
    }; // End of class define of HTTPMessageCommand

} // End of namespace Protocol
#endif // !HTTPMessage_Command_HPP_
