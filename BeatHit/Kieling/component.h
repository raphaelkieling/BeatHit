#pragma once
class Component {
public:
	virtual void Load() = 0;
	virtual void Process() = 0;
	virtual void Drop() = 0;
	virtual ~Component() {}
};