

#include "Manager.h"

#include <string>
#include <iostream>

using namespace std;


int main(int argc, char** argv)
{
    if(argc!=2)
    {
        cout<<"Usage: merge.exe configFile\n";
        return 1;
    }
    string configFile(argv[1]);

    Manager manager;
    bool status = manager.initialize(configFile);
    if(status)
    {
        status = manager.merge();
    }

    return (int)(!status);

}
