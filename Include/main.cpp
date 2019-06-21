#include "Core.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	if (!GET_SINGLE(CCore)->Init(hInstance))
	{
		CCore::DestroyInstance();
		return 0;
	}

	int	iRev = GET_SINGLE(CCore)->Run();

	CCore::DestroyInstance();

	return iRev;
}
