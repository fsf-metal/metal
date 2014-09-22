#include "CPU.h"

#ifdef _WIN32
#	include <Windows.h>
#else
// do something for linux
#endif

CPU::CPU()
{
}


CPU::~CPU()
{
}

#ifdef _WIN32
LONG GetStringRegKey(HKEY hKey, const std::wstring &strValueName, std::wstring &strValue, const std::wstring &strDefaultValue)
{
	strValue = strDefaultValue;
	WCHAR szBuffer[512];
	DWORD dwBufferSize = sizeof(szBuffer);
	ULONG nError;
	nError = RegQueryValueExW(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
	if (ERROR_SUCCESS == nError)
	{
		strValue = szBuffer;
	}
	return nError;
}
#endif

void CPU::getDetails(std::string &str) {
#ifdef _WIN32
	HKEY hKey;
	LONG lRes = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);
	bool bExistsAndSuccess (lRes == ERROR_SUCCESS);

	std::wstring strValueOfProcessorName;
	GetStringRegKey(hKey, L"ProcessorNameString", strValueOfProcessorName, L"Not Found");
	std::string strVal(strValueOfProcessorName.begin(), strValueOfProcessorName.end());
	str = strVal;
#elif __linux
	str = "For Linux This needs to be read from /proc/cpuinfo";
#else
	str = "Information not available for this OS";
#endif
}
