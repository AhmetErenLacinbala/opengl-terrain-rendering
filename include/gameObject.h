#pragma once

class GameObject {
public:
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
};
