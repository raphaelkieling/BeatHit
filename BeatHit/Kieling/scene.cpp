#include "component.cpp"
#include <vector>
#include <string>

using namespace std;

namespace Kieling {
	class Scene {
	public:
		vector<Component*> components;
		string name;

		Scene(string name) {
			this->name = name;
		}

		void Load() {
			printf(string("Loading scene: " + name).c_str());
		}
	};
}
