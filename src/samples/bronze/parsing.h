#ifndef __PARSING_H
#define __PARSING_H

void parseNOS( const std::string& cmd, Metal::NewOrderSingle &);

class ParsingException: public std::exception {
private:
    std::string message_;
public:
    ParsingException(const std::string& message) : message_(message) { };
    virtual const char* what() const throw() {
        return message_.c_str();
    }
};

#endif // __PARSING_H
