#ifdef RAPT_DLL
	#define RAPT_API __declspec(dllexport)
#else 
	#define RAPT_API __declspec(dllimport)
#endif
