#pragma once

#include "interface.h"

class PluginA final : public PluginBase
{
    FACTORY_MAP_REGISTER(PluginA)

public:
    PluginA();
    ~PluginA() override;

public:
    [[nodiscard]] std::string name() const override;
    void echo() override;
};

class PluginB final : public PluginBase
{
    FACTORY_MAP_REGISTER(PluginB)

public:
    PluginB();
    ~PluginB() override;

public:
    [[nodiscard]] std::string name() const override;
    void echo() override;
};

class PluginC final : public PluginBase
{
    FACTORY_MAP_REGISTER(PluginC)

public:
    PluginC();
    ~PluginC() override;

public:
    [[nodiscard]] std::string name() const override;
    void echo() override;
};