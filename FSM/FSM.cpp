//create by zhuling
#include "FSM/FSM.h"

#include "FSM/FSMState.h"

FSM::~FSM(void)
{
	_states.clear();
}

FSM::FSM()
{
	_states.clear();
	_currentState = NULL;
	_previousState = NULL;
	_stateLastTime = 0.0;
	_delayedStateName = -1;
}

FSMState& FSM::addState(FSMState state)
{
	if (_currentState != NULL
		&& _currentState->getName() == state.getName()
		&& _currentState->exitCallback)
	{
		_currentState->exitCallback();
	}
	_states.insert(std::make_pair(state.getName(), state));
	return state;
}

void FSM::setNextState(int state)
{
	_delayedStateName = state;
}

FSMState& FSM::addState(int stateName)
{
	return this->addState(FSMState(stateName, nullptr, nullptr, nullptr));
}

FSMState& FSM::addState(
	int stateName,
	const std::function<void()>& enterFunc,
	const std::function<void(float)>& updateFunc,
	const std::function<void()>& exitFunc)
{
	return this->addState(FSMState(stateName, enterFunc, updateFunc, exitFunc));
}

void FSM::translateToState(int stateName)
{
	if (_currentState && _currentState->exitCallback)
	{
		_currentState->exitCallback();
	}

	// find state with 'stateName' as name
	FSMState* stateFound = nullptr;
	if (_states.find(stateName) != _states.end())
	{
		stateFound = &_states.at(stateName);
	}

	// change state
	_previousState = _currentState;
	_stateLastTime = 0.0;
	if (stateFound == nullptr)
	{
		_currentState = nullptr;
	}
	else
	{
		_currentState = stateFound;
	}

	// enter new state
	if (_currentState && _currentState->enterCallback)
	{
		_currentState->enterCallback();
	}
}

void FSM::translateToStateNoRepeat(int stateName)
{
	if (!_currentState || getCurrentStateName() != stateName) {
		translateToState(stateName);
	}
}

void FSM::translateToStateNextUpdate(int stateName)
{
	_delayedStateName = stateName;
}

void FSM::translateToStateNextUpdateNoRepeat(int stateName)
{
	if (getCurrentStateName() != stateName)
	{
		this->translateToStateNextUpdate(stateName);
	}
}

int FSM::getCurrentStateName()
{
	if (_currentState)
	{
		return _currentState->getName();
	}
	return -1;
}

int FSM::getPreviousStateName()
{
	if (_previousState)
	{
		return _previousState->getName();
	}
	return -1;
}

float FSM::getStateLastTime()
{
	return _stateLastTime;
}

void FSM::update(float dt)
{
	if (_delayedStateName != -1)
	{
		int tempName = _delayedStateName;
		_delayedStateName = -1;
		translateToState(tempName);
	}

	_stateLastTime += dt;

	if (_currentState && _currentState->updateCallback)
	{
		_currentState->updateCallback(dt);
	}
}
