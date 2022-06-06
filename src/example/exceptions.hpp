/**
 * Header file for exceptions.
 * @file exceptions.hpp
 * @author Maxence
 * @version 1.0
*/

#include <exception>

namespace err {

struct NoCurrentBlock : public std::exception {
    const char* what () const noexcept override {
        return "A block has to be the current block";
    }
};

struct InvalidShape : public std::exception {
    const char* what() const noexcept override {
        return "This shape is invalid";
    }
};

}