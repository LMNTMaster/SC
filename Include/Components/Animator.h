#pragma once
#include "../Component.h"

//이 컴포넌트를 상속받는 컴포넌트는 SpriteRenderer에서 이벤트 함수가 호출된다.
//컴포넌트를 상속받으나, 인터페이스만 있기 때문에, 코어로 들어감
class CAnimator :
	public CComponent
{
public:
	virtual void OnAnimationStart();
	virtual void OnAnimationUpdate();
	virtual void OnAnimationEnd();

public:
	CAnimator();
	virtual ~CAnimator();
};

