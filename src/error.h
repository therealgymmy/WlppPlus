/******************************************************************************
 * Copyright (C) 2012 Jimmy Lu
 *
 * This namespace is used to handle errors.
 * Include this header in every other class/namespace that might error out,
 *  preferablly the last one to avoid any kind of dependency issues.
 ******************************************************************************/

#ifndef ERROR_H
#define ERROR_H

#include <iostream>

#include "common.h"

namespace error {

// ErrorCode enumerator,
//  contains error codes for known error conditions.
// Do NOT initialize an instance of this enumerator,
//  since it has no use outside of ErrorObject.
enum ErrorCode {
    // Default retCode == 1

    // File specific error codes.
    FILE_CANNOT_OPEN,       // retCode == 4
    FILE_CANNOT_CLOSE,      // retCode == 5

    // Scanning specific error codes.
    LEX_ERROR,

    // Production rule related error codes.
    NO_MATCHING_PROD_RULE,  // retCode == 11

    // Parse Tree error codes.
    TREE_IS_NULL,           // retCode == 16
};

// Interface for ErrorObject.
// Always use ErrorObjectPtr to wrap around it.
// If any additional features not provided here are needed,
//  inherit this class as parent class of ErrorObject in
//  the corresponding namespace where the
//  additional features are intended to be used.
class ErrorObjectInterface {
    friend class ErrorObjectPtr;
    public:
        virtual std::string toString() const;
        int retCode() const;
    protected:
        ErrorCode errCode_;
        std::string errLocation_;    // Where did this error occur?
        std::string errMsg_;

        ErrorObjectInterface(ErrorCode errCode,
                             std::string errLocation,
                             std::string errMsg);
        virtual ~ErrorObjectInterface();
};

// Basic ErrorObject with no additional features added.
// If no need for additional error handling, use this instead.
// Do NOT inherit this class!
class ErrorObject: public ErrorObjectInterface {
    public:
        ErrorObject(ErrorCode errCode,
                    std::string errLocation,
                    std::string errMsg);
};

// Smart pointer container for ErrorObjectInterface*.
class ErrorObjectPtr {
    public:
        ErrorObjectPtr(ErrorObjectInterface *err);
        ~ErrorObjectPtr();
        ErrorObjectInterface* operator->();
    private:
        ErrorObjectInterface *err_;
};

}

#endif//ERROR_H
