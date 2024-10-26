#pragma once
#include "Application/Application.h"


int main(void)
{

	Rapture::Application* app = Rapture::createApplication();
	app->run(); 
	delete[] app;

	return 0;
}