#include "../engine/component.h"

class Root : public Component {
public:
    Root() {}

    void Load() override;
    void Process() override;
    void Drop() override;
};