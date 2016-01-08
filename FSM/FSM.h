//create by zhuling 2016.1.8
#ifndef __FSM_H__
#define __FSM_H__

#include "cocos2d.h"
class FSMState;

class FSM
{
public:
	FSM();

	~FSM();

	// add FSM states
	FSMState& addState(FSMState state);
	FSMState& addState(int stateName);
	FSMState& addState(
		int stateName,
		const std::function<void()>& enterFunc,
		const std::function<void(float)>& updateFunc = nullptr,
		const std::function<void()>& exitFunc = nullptr);

	// translate functions
	void translateToState(int stateName);
	void translateToStateNoRepeat(int stateName);
	void translateToStateNextUpdate(int stateName);
	void translateToStateNextUpdateNoRepeat(int stateName);

	/// getters
	// @return last seconds of current state
	float getStateLastTime();

	// Get the name of current state
	int	  getCurrentStateName();

	// Get the name of previous state
	int   getPreviousStateName();

	void setNextState(int state);

	// update FSM
	void update(float dt);

protected:
	FSMState* _currentState;
	FSMState* _previousState;
	float _stateLastTime;
	int _delayedStateName;
	std::map<int, FSMState> _states;

};



#endif // !__FSM_H__
