#pragma once

#include <cassert>
#include <string>
#include <unordered_map>
#include <memory>

#define FACTORY_MAP_DEFINE_(class_name, key_scope) \
protected: \
    [[nodiscard]] static inline auto& _factory_internal_derived_class_creator_map() \
    { \
        static std::unordered_map<key_scope, std::shared_ptr<class_name>(*)()> map{}; \
        return map; \
    } \
    template<typename T> \
    [[nodiscard]] static inline std::shared_ptr<class_name> _factory_internal_derived_class_creator() \
    { \
        return std::make_shared<T>(); \
    }

#define FACTORY_MAP_REGISTER_(class_name, key_scope) \
private: \
    static inline bool _factory_internal_is_derived_class_registered = []() -> bool \
    { \
        auto& map = class_name::_factory_internal_derived_class_creator_map(); \
        /* Sanity check to ensure we don't register the same class more than once. */ \
        assert(map.find(key_scope::class_name) == map.end()); \
        if (map.find(key_scope::class_name) != map.end()) { \
            std::abort(); \
        } \
        map[key_scope::class_name] = class_name::_factory_internal_derived_class_creator<class_name>; \
        return true; \
    }();

#define FACTORY_MAP_CREATE_(class_name, key_scope) \
private: \
    static inline std::unordered_map<key_scope, std::shared_ptr<class_name>> _factory_internal_derived_class_map{}; \
public: \
    [[nodiscard]] static inline std::shared_ptr<class_name> Create(const key_scope key) \
    { \
        const auto& map = class_name::_factory_internal_derived_class_creator_map(); \
        assert(map.find(key) != map.end()); \
        if (map.find(key) == map.end()) \
        { \
            std::abort(); \
        } \
        return map.at(key)(); \
    } \
    [[nodiscard]] static inline const std::shared_ptr<class_name>& Get(const key_scope key) \
    { \
        auto it = _factory_internal_derived_class_map.find(key); \
        if (it == _factory_internal_derived_class_map.end()) \
        { \
            it = _factory_internal_derived_class_map.insert(std::make_pair(key, Create(key))).first; \
        } \
        return it->second; \
    }

#define FACTORY_MAP_DEFINE(class_name) FACTORY_MAP_DEFINE_(class_name, KEY_SCOPE)
#define FACTORY_MAP_REGISTER(class_name) FACTORY_MAP_REGISTER_(class_name, KEY_SCOPE)
#define FACTORY_MAP_CREATE(class_name) FACTORY_MAP_CREATE_(class_name, KEY_SCOPE)

#define FACTORY_DECLARE_BASE(class_name) \
    FACTORY_MAP_DEFINE(class_name) \
    FACTORY_MAP_CREATE(class_name)

#define KEY_SCOPE Backend

enum struct Backend : std::uint8_t
{
    PluginA,
    PluginB,
    PluginC
};

class PluginBase
{
    FACTORY_DECLARE_BASE(PluginBase)

public:
    PluginBase() = default;
    virtual ~PluginBase() = default;

public:
    [[nodiscard]] virtual std::string name() const = 0;
    virtual void echo() = 0;
};
