#include "types/decl.h"
#include "scene.h"

namespace testing {
    interfaces::IScene* create_scene() {
        return new types::Scene();
    }
}
