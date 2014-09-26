#include "Display.h"

#ifdef _WIN32
#	include <Windows.h>
#	include <VersionHelpers.h>
#else // linux?
#	include <fstream>
#	include <sys/utsname.h>
#endif

using namespace std;

Display::Display()
{
}


Display::~Display()
{
}

#ifdef _WIN32
LONG GetStringRegKey(HKEY hKey, const wstring &strValueName, wstring &strValue, const wstring &strDefaultValue)
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

void Display::getCPUDescription(string &str) {
#ifdef _WIN32
	HKEY hKey;
	LONG lRes = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);
	bool bExistsAndSuccess (lRes == ERROR_SUCCESS);

	wstring strValueOfProcessorName;
	GetStringRegKey(hKey, L"ProcessorNameString", strValueOfProcessorName, L"Not Found");
	string strVal(strValueOfProcessorName.begin(), strValueOfProcessorName.end());
	str = strVal;
#elif __linux
	ifstream file("/proc/cpuinfo");
	string line;
	str = "Not found in /proc/cpuinfo";
	while( getline( file, line)) {
		if( line.find( "model name") != string::npos) {
			size_t semiColonPos = line.find( ":");
			str = line.substr( semiColonPos + 2, line.length() - semiColonPos - 2);
			break;
		}
	}
#else
	str = "Information not available for this OS";
#endif
}

void Display::getOSDescription( string &str) {
#ifdef _WIN32
	HKEY hKey;
	LONG lRes = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hKey);
	bool bExistsAndSuccess(lRes == ERROR_SUCCESS);

	wstring strCurrentVersion;
	GetStringRegKey(hKey, L"CurrentVersion", strCurrentVersion, L"Not Found");
	string currentVersion(strCurrentVersion.begin(), strCurrentVersion.end());

	wstring strProductName;
	GetStringRegKey(hKey, L"ProductName", strCurrentVersion, L"Not Found");
	string productName(strCurrentVersion.begin(), strCurrentVersion.end());

	str = "Windows (" + currentVersion + ") " + productName;
#elif __linux
	struct utsname sysinfo;
	if( uname( &sysinfo) < 0) {
		str = "Cannot Determine Linux Version";
	} else {
		string sysname( sysinfo.sysname);
		string sysrelease( sysinfo.release);
		str = sysname + ' ' + sysrelease;
	}
#else
	str = "Other Operating System";
#endif
}
