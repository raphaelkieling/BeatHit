#include <vector>
#include <string>
#include "component.h"
#include "scene.h"
#include <raymath.h>

void Scene::OnStart() {
	root->Load();
}

void Scene::Process()  {}

void Scene::Draw() {}

void Scene::InternalProcess() {
	root->InternalProcess(root);
	Process();
}

void Scene::CameraControl() {
	float scroll = GetMouseWheelMove();
	if (scroll != 0.0f) {
		Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), *activeCamera);
		float zoomBefore = activeCamera->zoom;

		activeCamera->zoom += scroll * 0.1f;
		activeCamera->zoom = Clamp(activeCamera->zoom, 0.1f, 5.0f);

		Vector2 mouseWorldPosAfter = GetScreenToWorld2D(GetMousePosition(), *activeCamera);
		Vector2 delta = Vector2Subtract(mouseWorldPos, mouseWorldPosAfter);
		activeCamera->target = Vector2Add(activeCamera->target, delta);
	}

	Vector2 mouse = GetMousePosition();

	if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON)) {
		Vector2 delta = Vector2Subtract(mouse, lastCameraMousePos);
		delta = Vector2Scale(delta, -1.0f / activeCamera->zoom);
		activeCamera->target = Vector2Add(activeCamera->target, delta);
	}

	lastCameraMousePos = mouse;
}

void Scene::InternalDraw() {
	if (activeCamera) {
		CameraControl();
		BeginMode2D(*activeCamera);
	}
	
	root->InternalDraw(root);
	Draw();

	if (activeCamera) {
		EndMode2D();
	}
	
}

void Scene::OnExit()  {
	root->Drop();
	root->ClearAllChildren();
}

void Scene::AddComponent(Component* component) {
	root->AddComponent(component);
}

void Scene::ClearRemoveQueue() {
	while (!toRemoveIds.empty()) {
		uint64_t id = toRemoveIds.front();
		toRemoveIds.pop();

		root->RemoveComponentById(id);
	}
}

void Scene::DropComponentId(uint64_t id) {
	toRemoveIds.push(id);
}