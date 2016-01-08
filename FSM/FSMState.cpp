#include "FSM/FSMState.h"

FSMState::FSMState(void) :
_stateName(-1),
enterCallback(nullptr),
updateCallback(nullptr),
exitCallback(nullptr)
{
}

FSMState::~FSMState()
{

}

FSMState::FSMState(
	int stateName,
	const std::function<void()>& enterFunc,
	const std::function<void(float)>& updateFunc,
	const std::function<void()>& exitFunc)
{
	_stateName = stateName;
	enterCallback = enterFunc;
	updateCallback = updateFunc;
	exitCallback = exitFunc;
}

int FSMState::getName()
{
	return _stateName;
}

void FSMState::setName(int name)
{
	_stateName = name;
}