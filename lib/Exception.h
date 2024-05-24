//
// Created by antilopa on 16.05.24.
//

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class Exception: public std::exception
{
public:
    Exception(const std::string& message): message{message}
    {}
    const char* what() const noexcept override
    {
        return message.c_str();     // получаем из std::string строку const char*
    }
private:
    std::string message;    // сообщение об ошибке
};




class IndexOutOfBoundsException: public Exception{
public:
    IndexOutOfBoundsException(const std::string& message): Exception(message){};
};

class IllegalException: public Exception{
public:
    IllegalException(const std::string& message): Exception(message){};
};

class IllegalIndex: public Exception{
public:
    IllegalIndex(const std::string& message): Exception(message){};
};

#endif //EXCEPTION_H
