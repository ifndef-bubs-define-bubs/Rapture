#pragma once
#include "Math/Math.h"
#include "Macros/Transfer.h"

namespace Rapture
{
	class RAPT_API Application
	{
	public:
		virtual void onRender() = 0;
		virtual void onUpdate() = 0;

		void run();
		bool running() const;

	private:
		void render();
		void update(); 
		void shutDown(); 
		void processInput();
		
		bool m_running = true;
	};
	
	Application* createApplication();
}

