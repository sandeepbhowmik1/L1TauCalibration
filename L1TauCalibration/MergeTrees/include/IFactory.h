

#ifndef IFACTORY_H
#define IFACTORY_H


#include <iostream>
#include <string>
#include <memory>

class ITrees;

class IFactory
{
    public :
        virtual ~IFactory(){};
        virtual ITrees* createTrees(const std::string& name) = 0;

};

extern std::auto_ptr<IFactory> g_factory;

#define BEGIN()\
        class Factory : public IFactory\
        {\
            public:\
            Factory(){};\
            ~Factory(){};\
            virtual ITrees* createTrees(const std::string& name)\
            {

#define DEFINE_TREES( Class )\
                if( name == #Class ) return new Class();

#define END()\
                std::cerr<<"Unknown class name '"<<name<<"'\n";\
                return NULL;\
            }\
        };\
        static void createFactory()\
        {\
            g_factory = std::auto_ptr<IFactory>(new Factory());\
        }

#endif
