#ifndef __FSM_STATE_H__
#define __FSM_STATE_H__

#include "cocos2d.h"

class FSMState
{
public:
	FSMState();

	~FSMState();

	FSMState(
		int stateName,
		const std::function<void()>& enterFunc,
		const std::function<void(float)>& updateFunc,
		const std::function<void()>& exitFunc);

	std::function<void()>		enterCallback;
	std::function<void(float)>	updateCallback;
	std::function<void()>		exitCallback;

	int getName();

	void setName(int name);

protected:
	int _stateName;

};




#endif // !__FSM_STATE_H__
