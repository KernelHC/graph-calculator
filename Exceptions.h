#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>

using std::exception;
using std::string;

class SyntaxError : public exception {
public:
    const char* what() const noexcept override {
        return "Error: syntax error";
    }
};

class InvalidVertexName : public exception {
public:
    const char* what() const noexcept override {
        return "Error: invalid vertex name";
    }
};

class VertexNotExist : public exception {
    string error_message;
public:
    VertexNotExist (const string &e):error_message() {
        error_message += string("Error: ") + e + string(" connects a non existent vertex");
    }
    const char* what() const noexcept override {
        return error_message.c_str();
    }
};

class VertexDuplication : public exception {
public:
    const char* what() const noexcept override {
        return "Error: multiple vertices with the same name are not allowed";
    }
};

class EdgeDuplication : public exception {
public:
    const char* what() const noexcept override {
        return "Error: multiple edges with the same vertices are not allowed";
    }
};

class GraphNotDefined : public exception {
    string error_message;
public:
    GraphNotDefined(const string &str): error_message() {
        error_message += string("Error: ") + str + string(" is not defined");
    }
    const char* what() const noexcept override {
        return error_message.c_str();
    }
};

class FileError : public exception {
    string error_message;
public:
    FileError(const string &str): error_message() {
        error_message += string("Error: cannot open file: ") + str;
    }
    const char* what() const noexcept override {
        return error_message.c_str();
    }
};

class NullArgument : public exception {
public:
    const char* what() const noexcept override {
        return "Error: received null argument";
    }
};




#endif