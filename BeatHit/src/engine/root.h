#pragma once
#include "../engine/component.h"

class Root : public Component {
public:
    Root() {
        name = "root";
    }

    void Load() override;
    void Process() override;
    void Drop() override;
    void Draw() override;
};