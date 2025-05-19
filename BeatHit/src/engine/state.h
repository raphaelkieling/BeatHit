#pragma once

class State {
public:
    virtual ~State() = default;

    virtual void OnEnter() {}
    virtual void OnUpdate() {}
    virtual void OnExit() {}
    virtual void OnDraw() {}
};