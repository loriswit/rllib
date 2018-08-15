#include <rllib/game/Scene.hpp>
#include <rllib/stream/FileReader.hpp>
#include <rllib/stream/FileWriter.hpp>

#define RL_ASSERT_HAS_ENTITY(entity, name) RL_ASSERT(entity, "scene has no entity with name '" + (name) + "'");

namespace rl
{

Scene::Scene(const FilePath & path)
{
    load(path);
}

void Scene::load(const FilePath & path)
{
    FileReader(path).readAll() >> *this;
}

void Scene::save(const FilePath & path) const
{
    FileWriter(path, true).write(*this);
}

bool Scene::hasEntity(const std::string & name) const
{
    return findEntity(name).has_value();
}

std::size_t Scene::entityCount() const noexcept
{
    return m_entities.size();
}

const Entity & Scene::operator[](const std::string & name) const
{
    const auto entity = findEntity(name);
    RL_ASSERT_HAS_ENTITY(entity, name);
    return *entity;
}

Entity & Scene::operator[](const std::string & name)
{
    auto entity = findEntity(name);
    RL_ASSERT_HAS_ENTITY(entity, name);
    return *entity;
}

const Entity & Scene::operator[](std::size_t index) const
{
    return m_entities[index];
}

Entity & Scene::operator[](std::size_t index)
{
    return m_entities[index];
}

std::vector<Entity>::iterator Scene::begin() noexcept
{
    return m_entities.begin();
}

std::vector<Entity>::const_iterator Scene::cbegin() const noexcept
{
    return m_entities.cbegin();
}

std::vector<Entity>::iterator Scene::end() noexcept
{
    return m_entities.end();
}

std::vector<Entity>::const_iterator Scene::cend() const noexcept
{
    return m_entities.cend();
}

void Scene::deserialize(ByteStream & data)
{
    auto entityList = locator(data);
    
    header.resize(entityList.empty() ? data.size() : entityList.front().offset);
    std::copy_n(data.cbegin(), header.size(), header.begin());
    
    for(auto & entityInfo : entityList)
    {
        ByteStream entityData(entityInfo.size);
        std::copy_n(data.cbegin() + entityInfo.offset, entityInfo.size, entityData.begin());
        
        m_entities.push_back(entityData.get<Entity>());
    }
}

ByteStream Scene::serialize() const
{
    ByteStream data;
    data << header;
    
    for(const auto & entity : m_entities)
        data << entity;
    
    return data;
}

std::optional<std::reference_wrapper<Entity>> Scene::findEntity(const std::string & name)
{
    auto entity = std::find_if(m_entities.begin(), m_entities.end(), [&name](const auto & ent)
    {
        return ent.name == name;
    });
    
    if(entity == m_entities.end())
        return {};
    else
        return *entity;
}

std::optional<std::reference_wrapper<const Entity>> Scene::findEntity(const std::string & name) const
{
    const auto entity = std::find_if(m_entities.cbegin(), m_entities.cend(), [&name](const auto & ent)
    {
        return ent.name == name;
    });
    
    if(entity == m_entities.cend())
        return {};
    else
        return *entity;
}

std::function<std::vector<EntityLocation>(ByteStream &)> Scene::locator = locator::names;

} // namespace rl
