#pragma once

#include "Rapture.h"

class Sandbox : public Rapture::Application
{

public:
	 
	virtual void onRender() override;
	virtual void onUpdate() override;

};

