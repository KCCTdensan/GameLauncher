#pragma once
class ComponentBase
{
public:
	ComponentBase()
		: enabled(true) {}
	~ComponentBase() {}

	virtual void Update() = 0;
	bool SetEnabled(bool _enabled) { enabled = _enabled; }

private:
	bool enabled;
};

