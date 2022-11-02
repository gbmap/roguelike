#pragma once 


class Renderer;

class Renderable 
{
public: 
    Renderable();
    ~Renderable();

    virtual void Render(Renderer* renderer) = 0;
};

class DummyRenderable : public Renderable
{
public:
    void Render(Renderer* renderer) override;
};

class MsgOnRenderableCreated
{
public:
    Renderable* renderable;
    MsgOnRenderableCreated(Renderable* r);
};

class MsgOnRenderableDestroyed
{
public:
    Renderable* renderable;
    MsgOnRenderableDestroyed(Renderable* r); 
};

