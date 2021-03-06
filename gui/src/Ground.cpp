
#include <Ground.hpp>

Ground::Ground(const glm::vec2 &pos, const Gem &gem, const Food &food) : _gem(gem), _food(food, pos), _position(pos)
{
    _sphereCenter.x = pos.x;
    _sphereCenter.y = 0.5f;
    _sphereCenter.z = pos.y;
    _sphereRadius = 0.5f;
    
    _selected = false;
    _summoning = false;
    
    for (int i = 0; i < 6; ++i) {
        _gemList.push_back(new Gem(_gem, static_cast<GemType>(i), _position));
    }
}

Ground::~Ground()
{
    
}

void    Ground::draw(Shader *shader) const
{
    std::list<int>::const_iterator rec = _recourse.begin();
    
    if (*rec) {
        _food.draw(shader);
    }
    ++rec;
    for (GemList::const_iterator it = _gemList.begin(), end = _gemList.end(); it != end; ++it) {
        if (*rec)
            (*it)->draw(shader);
        ++rec;
    }
}

void	Ground::update(const sf::Clock &clock, float serverSpeed)
{
    std::list<int>::const_iterator rec = _recourse.begin();
    
    if (*rec) {
        _food.update(clock, serverSpeed);
    }
    ++rec;
    for (GemList::const_iterator it = _gemList.begin(), end = _gemList.end(); it != end; ++it) {
        if (*rec)
            (*it)->update(clock, serverSpeed);
        ++rec;
    }

}

void Ground::setRecourse(const std::list<int> &recourse)
{
    _recourse = recourse;
}

const std::list<int> &Ground::getRecourse() const
{
    return _recourse;
}

const glm::vec2 &Ground::getPosition() const {
    return _position;
}

void Ground::setPosition(const glm::vec2 &pos) {
    _position = pos;
}

const GemList &Ground::getGemList() const
{
    return (_gemList);
}

const glm::vec3	&Ground::getSphereCenter() const
{
    return (_sphereCenter);
}

float		Ground::getSphereRadius() const
{
    return (_sphereRadius);
}

void	Ground::setSelected(bool selected)
{
    _selected = selected;
}

bool	Ground::isSummoning() const
{
    return (_summoning);
}

void	Ground::setSummoning(bool summoning)
{
    _summoning = summoning;
}