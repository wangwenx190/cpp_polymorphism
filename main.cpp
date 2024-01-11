#include "interface.h"

int main(int argc, char *argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);
    PluginBase::Get(Backend::PluginA)->echo();
    PluginBase::Get(Backend::PluginB)->echo();
    PluginBase::Get(Backend::PluginC)->echo();
    return 0;
}