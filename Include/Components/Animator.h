#pragma once
#include "../Component.h"

//�� ������Ʈ�� ��ӹ޴� ������Ʈ�� SpriteRenderer���� �̺�Ʈ �Լ��� ȣ��ȴ�.
//������Ʈ�� ��ӹ�����, �������̽��� �ֱ� ������, �ھ�� ��
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

