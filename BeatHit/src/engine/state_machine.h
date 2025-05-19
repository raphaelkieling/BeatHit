#pragma once
#include "component.h"
#include "State.h"
#include <string>
#include <unordered_map>

class StateMachine : public Component {
private:
    State* currentState = nullptr;

public:
    std::string currentStateName;
    std::unordered_map<std::string, State*> states;

    StateMachine* AddState(const std::string& name, State* state) {
        states[name] = state;
        return this;
    }

    StateMachine* SetCurrent(const std::string& name) {
        auto it = states.find(name);
        if (it != states.end()) {
            if (currentState) currentState->OnExit();
            currentState = it->second;
            currentStateName = name;
            currentState->OnEnter();
        }
        return this;
    }

    void Load() override {
        if (currentState) currentState->OnEnter();
    }

    void Process() override {
        if (currentState) currentState->OnUpdate();
    }

    void Draw() override {
        if (currentState) currentState->OnDraw();
    }

    void Drop() override {}

    ~StateMachine() {
        for (auto& pair : states)
            delete pair.second;
    }
};