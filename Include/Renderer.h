#pragma once
#include "Game.h"
#include "Component.h"
class CRenderer : public CComponent
{
public:
	virtual void Render();
public:
	CRenderer();
	virtual ~CRenderer();
};

