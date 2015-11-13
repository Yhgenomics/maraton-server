/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-11-09
* Description:
* * * * * * * * * * * * * * * */

#ifndef ERROR_H_
#define ERROR_H_ 

#include <string>

class Error
{
public:

    Error()
    {

    }
    Error( size_t code , std::string message )
    {
        this->code_     = code;
        this->message_  = message_;
    }
    Error( Error & error )
    {
        this->code_     = error.code_;
        this->message_  = error.message_;
    }
    Error( Error && error )
    {
        this->code_     = error.code_;
        this->message_  = error.message_;

        error.message_ = "";
        error.code_ = 0;
    }

    size_t      code() { return this->code_; };
    void        code( size_t value ) { this->code_ = value; };

    std::string message() { return this->message_; };
    void        message( std::string value ) { this->message_ = value; if ( this->code_ != 0 ) printf( "Error:%s\r\n", this->message_.c_str() ); };

private:

    size_t code_ = 0;
    std::string message_ = "";
};

#endif // !ERROR_H_ 
