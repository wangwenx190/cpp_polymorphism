#include "plugins.h"
#include <iostream>

PluginA::PluginA() = default;

PluginA::~PluginA() = default;

std::string PluginA::name() const
{
    return "PluginA";
}

void PluginA::echo()
{
    std::cout << "EchoA from " << name() << '!' << std::endl;
}

PluginB::PluginB() = default;

PluginB::~PluginB() = default;

std::string PluginB::name() const
{
    return "PluginB";
}

void PluginB::echo()
{
    std::cout << "EchoB from " << name() << '!' << std::endl;
}

PluginC::PluginC() = default;

PluginC::~PluginC() = default;

std::string PluginC::name() const
{
    return "PluginC";
}

void PluginC::echo()
{
    std::cout << "EchoC from " << name() << '!' << std::endl;
}