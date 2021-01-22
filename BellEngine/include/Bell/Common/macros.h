#ifndef _MACROS_H
#define _MACROS_H

namespace Bell
{
#define NON_COPYABLE(Class)\
    Class& operator=(const Class& obj) = delete;\
    Class(const Class& obj) = delete;

#define NON_MOVABLE(Class)\
    Class& operator=(Class&& obj) = delete;\
    Class(Class&& obj) = delete;

}

#endif // !_MACROS_H
