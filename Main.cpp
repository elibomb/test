﻿#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <shobjidl_core.h>
#include <ctime>
#include <thread>
#include "resource.h"
#include <chrono>
#include <iphlpapi.h>
#include <stdio.h>
#include <vector>
#include "RecoilTables.h"
#include "Features.h"
#include <sstream>
#include <tchar.h>
#include <string>
#include <string.h>
#include "md5.h"
#include "Console.h"
#include <filesystem>
#include <iostream>
#include <memory>
#include <array>
#include <fstream>
#pragma comment(lib, "urlmon.lib")
#include <urlmon.h>
#define _WIN32_DCOM
#define FG_RED "\033[31m"
#define FG_PURPLE "\033[35m"
#define FG_GREEN "\033[32m"
#define FG_YELLOW "\033[33m"
#define FG_WHITE "\033[0m"
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
# pragma comment(lib, "wbemuuid.lib")
#define CRED_MAX_USERNAME_LENGTH            513
#define CRED_MAX_CREDENTIAL_BLOB_SIZE       512
#define CREDUI_MAX_USERNAME_LENGTH CRED_MAX_USERNAME_LENGTH
#define CREDUI_MAX_PASSWORD_LENGTH (CRED_MAX_CREDENTIAL_BLOB_SIZE / 2)
#pragma argsused
#pragma warning(disable : 4996)
#pragma comment(lib,"Winmm.lib")
#include "strptime.h"


#pragma region Materials
std::string Weapon = "NONE", Scope = "NONE", Barrel = "NONE", Sounds = "ON";
std::string hwid; std::string resultHash; std::string Time; std::string finalKey;
using namespace std;
int SelectedScope = 1;  int SelectedBarrel = 1;
bool bAK47 = false; bool bLR300 = false; bool bMP5 = false; bool bCSMG = false; bool bTHOMPSON = false; bool bSemi = false; bool bM249 = false; bool bSound = true; bool b8x = false; bool bHolo = false; bool bSimple = false; bool bSuppressor = false; bool bMuzzleBoost = false;
bool b16x; bool enabled = false; bool silence = false; bool gui = false; std::string checkedHwid; string myText;
std::string check1; std::string check2; std::string check3; std::string check4; std::string check5; 

float UserSens;
HW_PROFILE_INFO hwProfileInfo;

#pragma endregion

//VARIANT GetCpu()
//{
//	VARIANT CPU;
//	wchar_t pszName[CREDUI_MAX_USERNAME_LENGTH + 1] = L"user";
//	wchar_t pszPwd[CREDUI_MAX_PASSWORD_LENGTH + 1] = L"password";
//	BSTR strNetworkResource;
//	bool localconn = true;
//	//strNetworkResource = localconn ? (bstr_t)L"\\\\.\\root\\CIMV2" : (bstr_t)L"\\\\remote--machine\\root\\CIMV2";
//	COAUTHIDENTITY* userAcct = NULL;
//	COAUTHIDENTITY authIdent;
//	HRESULT hres;
//	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
//
//	if (localconn)
//		hres = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
//	else
//		hres = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IDENTIFY, NULL, EOAC_NONE, NULL);
//	IWbemLocator* pLoc = NULL;
//	hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
//	IWbemServices* pSvc = NULL;
//
//	if (localconn)
//		hres = pLoc->ConnectServer(_bstr_t(strNetworkResource), NULL, NULL, 0, NULL, 0, 0, &pSvc);
//	else
//		hres = pLoc->ConnectServer(_bstr_t(strNetworkResource), _bstr_t(pszName), _bstr_t(pszPwd), NULL, NULL, NULL, NULL, &pSvc);
//
//	if (localconn)
//		hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
//	else
//	{
//		memset(&authIdent, 0, sizeof(COAUTHIDENTITY));
//		authIdent.PasswordLength = wcslen(pszPwd);
//		authIdent.Password = (USHORT*)pszPwd;
//		authIdent.User = (USHORT*)pszName;
//		authIdent.UserLength = wcslen(pszName);
//		authIdent.Domain = 0;
//		authIdent.DomainLength = 0;
//		authIdent.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;
//		userAcct = &authIdent;
//		hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_DEFAULT, RPC_C_AUTHZ_DEFAULT, COLE_DEFAULT_PRINCIPAL, RPC_C_AUTHN_LEVEL_PKT_PRIVACY, RPC_C_IMP_LEVEL_IMPERSONATE, userAcct, EOAC_NONE);
//	}
//
//	IEnumWbemClassObject* pEnumerator = NULL;
//	hres = pSvc->ExecQuery((bstr_t)L"WQL", (bstr_t)L"SELECT * FROM Win32_Processor",
//		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
//
//	if (!localconn)
//	{
//		hres = CoSetProxyBlanket(pEnumerator, RPC_C_AUTHN_DEFAULT, RPC_C_AUTHZ_DEFAULT, COLE_DEFAULT_PRINCIPAL, RPC_C_AUTHN_LEVEL_PKT_PRIVACY, RPC_C_IMP_LEVEL_IMPERSONATE, userAcct, EOAC_NONE);
//	}
//	IWbemClassObject* pclsObj = NULL;
//	ULONG uReturn = 0;
//	while (pEnumerator)
//	{
//		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
//		if (0 == uReturn || FAILED(hr))
//			break;
//		VARIANT vtProp;
//		hr = pclsObj->Get(L"ProcessorId", 0, &CPU, 0, 0);
//		return CPU;
//		pclsObj->Release();
//		pclsObj = NULL;
//	}
//	pSvc->Release();
//	pLoc->Release();
//	pEnumerator->Release();
//	if (pclsObj != NULL)
//		pclsObj->Release();
//	CoUninitialize();
//	cin.get();
//
//}

string getHWID() {
	HW_PROFILE_INFO hwProfileInfo;
	GetCurrentHwProfile(&hwProfileInfo);
	wstring hwidWString = hwProfileInfo.szHwProfileGuid;
	string hwid(hwidWString.begin(), hwidWString.end());
	check1 = hwid.substr(1, 8); check2 = hwid.substr(10, 4); check3 = hwid.substr(15, 4); check4 = hwid.substr(20, 4); check5 = hwid.substr(25, 12);
	return hwid;
}

//string bstr_to_str(BSTR source) {
//	_bstr_t wrapped_bstr = _bstr_t(source);
//	int length = wrapped_bstr.length();
//	char* char_array = new char[length];
//	strcpy_s(char_array, length + 1, wrapped_bstr);
//	return char_array;
//}

long int unix_timestamp() {
	static std::time_t time_now = std::time(nullptr);;
	time_t t = std::time(0);
	long int now = static_cast<long int> (t);
	Time = std::to_string(now);
	Time = Time.substr(0, 7);
	return 0;
}

template< typename ... Args >
std::string stringer(Args const& ... args)
{
	std::ostringstream stream;
	using List = int[];
	(void)List {
		0, ((void)(stream << args), 0) ...
	};
	return stream.str();
}

//long int MD5Encryption() {
//	VARIANT MyData = GetCpu();
//	hwid = bstr_to_str(MyData.bstrVal);
//	if (true)
//	{
//		checkedHwid = check1 + hwid + check4 + check2 + check3;
//		resultHash = md5(md5(md5(md5(md5(checkedHwid)))));
//		finalKey = stringer(resultHash, Time);
//	}
//	return 0;
//}

namespace CurrentWeapon {
	double x(int Bullet) {
		if (bAK47 == true)
			return (((Recoil_Ak47[Bullet].x * Scopes()) * Barrels()) / 4) / UserSens;
		else if (bLR300 == true)
			return (((Recoil_Lr300[Bullet].x * Scopes()) * Barrels()) / 2) / UserSens;
		else if (bMP5 == true)
			return (((Recoil_Mp5a4[Bullet].x * Scopes()) * Barrels()) / 2) / UserSens;
		else if (bTHOMPSON == true)
			return (((Recoil_Thompson_g[Bullet].x * Scopes()) * Barrels()) / 2) / UserSens;
		else if (bCSMG == true)
			return (((Recoil_Custom_g[Bullet].x * Scopes()) * Barrels()) / 2) / UserSens;
		else if (bM249 == true)
			return (((Recoil_M249[Bullet].x * Scopes()) * Barrels()) / 2) / UserSens;
		else if (bSemi == true)
			return (((Recoil_Semi_r[Bullet].x * Scopes()) * Barrels()) / 4) / UserSens;
		else
			return 0;
	}
	double y(int Bullet) {
		if (bAK47 == true)
			return (((Recoil_Ak47[Bullet].y * Scopes()) * Barrels()) / 4) / UserSens;
		else if (bLR300 == true)
			return (((Recoil_Lr300[Bullet].y * Scopes()) * Barrels()) / 2) / UserSens;
		else if (bMP5 == true)
			return (((Recoil_Mp5a4[Bullet].y * Scopes()) * Barrels()) / 2) / UserSens;
		else if (bTHOMPSON == true)
			return (((Recoil_Thompson_g[Bullet].y * Scopes()) * Barrels()) / 2) / UserSens;
		else if (bCSMG == true)
			return (((Recoil_Custom_g[Bullet].y * Scopes()) * Barrels()) / 2) / UserSens;
		else if (bM249 == true)
			return (((Recoil_M249[Bullet].y * Scopes()) * Barrels()) / 2) / UserSens;
		else if (bSemi == true)
			return (((Recoil_Semi_r[Bullet].y * Scopes()) * Barrels()) / 2) / UserSens;
		else
			return 0;
	}
	double Delay() {
		if (bAK47 == true)
			return WeaponData::AK47.Delay;
		else if (bLR300 == true)
			return WeaponData::LR300.Delay;
		else if (bMP5 == true)
			return WeaponData::MP5.Delay;
		else if (bTHOMPSON == true)
			return WeaponData::THOMPSON.Delay;
		else if (bCSMG == true)
			return WeaponData::CUSTOM_SMG.Delay;
		else if (bM249 == true)
			return WeaponData::M249.Delay;
		else if (bSemi == true)
			return WeaponData::SEMI.Delay;
		else
			return 0;
	}
	double Control(int bullet) { //"CONTROL TIME" ONLY AK
		if (bAK47 == true)
			return ControlTime_Ak47[bullet];
		else if (bLR300 == true)
			return WeaponData::LR300.Delay;
		else if (bMP5 == true)
			return WeaponData::MP5.Delay;
		else if (bTHOMPSON == true)
			return WeaponData::THOMPSON.Delay;
		else if (bCSMG == true)
			return WeaponData::CUSTOM_SMG.Delay;
		else if (bM249 == true)
			return WeaponData::M249.Delay;
		else if (bSemi == true)
			return WeaponData::SEMI.Delay;
		else
			return 0;
	}
	int Bullet() { // How many Bullets the weapon has. Checks the amout of values stored in the vector
		if (bAK47 == true)
			return Recoil_Ak47.size() - 1;
		else if (bLR300 == true)
			return Recoil_Lr300.size() - 1;
		else if (bMP5 == true)
			return Recoil_Mp5a4.size() - 1;
		else if (bTHOMPSON == true)
			return Recoil_Thompson_g.size() - 1;
		else if (bCSMG == true)
			return Recoil_Custom_g.size() - 1;
		else if (bM249 == true)
			return Recoil_M249.size() - 1;
		else if (bSemi == true)
			return Recoil_Semi_r.size() - 1;
		else
			return 0;
	}

	bool WeaponActive() {
		if (bAK47 == true || bLR300 == true || bMP5 == true || bTHOMPSON == true || bCSMG == true || bSemi == true || bM249 == true)
			return true;
		else
			return false;
	}
	void RecoilBreak(int count) {
		if (bSemi == true) {
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		else if (bM249 == true) {
		}
		else if (bSemi != true || bM249 != true) {
			if (count == CurrentWeapon::Bullet()) {
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
		}
	}
};

int Request() {
	std::string url = "https://macrorust.com/license.php?hwid=" + checkedHwid;
	std::wstring url2(url.begin(), url.end());
	IStream* stream;
	HRESULT result = URLOpenBlockingStream(0, (LPCWSTR)url2.c_str(), &stream, 0, 0);

	char buffer[100];
	unsigned long bytesRead;
	stringstream ss;
	stream->Read(buffer, 100, &bytesRead);
	while (bytesRead > 0U)
	{
		ss.write(buffer, (long long)bytesRead);
		stream->Read(buffer, 100, &bytesRead);
	}
	string resultString = ss.str();

	if (resultString == finalKey) {
	/*std::cout << blue << "\n";
	std::cout << yellow << "\n";
	Type("   >> Input Sensitivity: ", 10);
	std::cin >> UserSens;
	TransparentWindow();
	Recoils();*/
	}
	else {
		std::cout << red << "\n";
		Type("-> License Not Found :(\n", 10);
		std::cout << blue << "\n";
		Type("-> !! Send the code to the seller.\n\n", 10);
		std::cout << "       " << checkedHwid << "\n\n";
		system("pause");
	}
	return 0;
}

//void CheckLicense() {
//	unix_timestamp();
//	getHWID();
//	MD5Encryption();
//	Request();
//}


void DrawGui()
{
	system("cls");
	system("color 5");
	//_setmode(_fileno(stdout), _O_TEXT);
	std::cout << FG_WHITE << " -------------------------------------------------------------- " << std::endl;

	std::cout << FG_WHITE << "   " "[" << FG_YELLOW << "WEAPONS" << FG_WHITE << "]" << "             |"  FG_WHITE << "        " "[" << FG_YELLOW << "ATTACHMENTS" << FG_WHITE << "]" << std::endl;

	std::cout << "                         |" << std::endl;

	std::cout << FG_WHITE << "   " "[" << FG_PURPLE << "F2" << FG_WHITE << "]" << "AK-47" << "             |" << FG_WHITE << "        " "[" << FG_PURPLE << "<<<<" << FG_WHITE << "]" << "X8" << std::endl;
	std::cout << FG_WHITE << "   " "[" << FG_PURPLE << "F3" << FG_WHITE << "]" << "LR-300" << "            |" << FG_WHITE << "        " "[" << FG_PURPLE << ">>>>" << FG_WHITE << "]" << "X16" << std::endl;
	std::cout << FG_WHITE << "   " "[" << FG_PURPLE << "F4" << FG_WHITE << "]" << "MP5A4" << "             |" << FG_WHITE << "        " "[" << FG_PURPLE << " UP " << FG_WHITE << "]" << "Holo" << std::endl;
	std::cout << FG_WHITE << "   " "[" << FG_PURPLE << "F5" << FG_WHITE << "]" << "S.A.R." << "            |" << FG_WHITE << "        " "[" << FG_PURPLE << "DOWN" << FG_WHITE << "]" << "Simple Handmade" << std::endl;
	std::cout << FG_WHITE << "   " "[" << FG_PURPLE << "F6" << FG_WHITE << "]" << "Thompson" << "          |" << FG_WHITE << "        " "[" << FG_PURPLE << "PGUP" << FG_WHITE << "]" << "Muzzle Boost" << std::endl;
	std::cout << FG_WHITE << "   " "[" << FG_PURPLE << "F7" << FG_WHITE << "]" << "Custom SMG" << "        |" << FG_WHITE << "        " "[" << FG_PURPLE << "PGDW" << FG_WHITE << "]" << "Silencer" << std::endl;
	std::cout << FG_WHITE << "   " "[" << FG_PURPLE << "F8" << FG_WHITE << "]" << "M249" << "              |" << FG_WHITE << "        " "[" << FG_PURPLE << "xxxx" << FG_WHITE << "]" << "xxxx" << std::endl;
	std::cout << FG_WHITE << "   " "[Python = M2 + Holo" << FG_PURPLE << "" << FG_WHITE << "]" << "" << "  |" << FG_WHITE << "        " "[" << "M92 = LR + Holo" << FG_WHITE << "]" << std::endl << std::endl;

	std::cout << FG_WHITE << "   " "[" << FG_RED << "INS." << FG_WHITE << "]" << "Turn OFF recoil" << " |" << FG_WHITE << "        " "[" << FG_RED << "DEL." << FG_WHITE << "]" << "Turn OFF sounds" << std::endl;

	std::cout << " -------------------------------------------------------------- " << std::endl;
	std::cout << FG_WHITE << "                 " << FG_RED"[" << "!" << "]" << FG_GREEN << "UserSens : " << FG_RED << UserSens << std::endl;
	std::cout << FG_WHITE << "                 " "[" << FG_GREEN << "i" << FG_WHITE << "]" "Weapon : " << Weapon << std::endl;
	std::cout << FG_WHITE << "                 " "[" << FG_GREEN << "i" << FG_WHITE << "]" << "Scope :  " << Scope << std::endl;
	std::cout << FG_WHITE << "                 " "[" << FG_GREEN << "i" << FG_WHITE << "]" << "Barrel : " << Barrel << std::endl;
	std::cout << FG_WHITE << "                  " "[" << (enabled ? FG_GREEN "ON" : FG_RED "OFF") << FG_WHITE << "]" << "Enabled" << std::endl;
	//std::cout << FG_WHITE << "                  " "[" << (silence ? FG_GREEN "DEL" : FG_RED "DEL") << FG_WHITE << "]" << "Silence Mode" << std::endl;
}
void CloseWeapons() {
	bAK47 = false; bLR300 = false; bMP5 = false; bCSMG = false; bTHOMPSON = false; bSemi = false; bM249 = false;
}
void AllClose() {
	bAK47 = false; bLR300 = false; bMP5 = false; bCSMG = false; bTHOMPSON = false; bSemi = false; bM249 = false;
	bSimple = false; bHolo = false; b8x = false; b16x = false;
	enabled = false;
}
//int WINAPI WinMain(
//	HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine,
//	int nShowCmd)
//{
//
//	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), SND_RESOURCE | SND_ASYNC);
//	return 0;
//}
bool Recoils() {
	for (;;)
	{
		if (GetAsyncKeyState(VK_F2) & 1)
		{
			CloseWeapons();
			if (bLR300 == false && bMP5 == false && bCSMG == false && bTHOMPSON == false && bSemi == false && bM249 == false) {
				bAK47 = !bAK47;
				Weapon = "AK47";
				enabled = true;
				DrawGui();
				if (silence == false)
				{
					//PlaySound(TEXT("AK.wav"), NULL, SND_SYNC);
					PlaySound(MAKEINTRESOURCE(IDR_WAVE2), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

				}
			}
		}
		if (GetAsyncKeyState(VK_F3) & 1)
		{
			CloseWeapons();
			if (bAK47 == false && bMP5 == false && bCSMG == false && bTHOMPSON == false && bSemi == false && bM249 == false) {
				bLR300 = !bLR300;
				Weapon = "LR300";
				enabled = true;
				DrawGui();
				if (silence == false)
				{
					PlaySound(MAKEINTRESOURCE(IDR_WAVE5), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
					//PlaySound(TEXT("LR.wav"), NULL, SND_SYNC);
				}
			}
		}
		if (GetAsyncKeyState(VK_F4) & 1)
		{
			CloseWeapons();
			if (bLR300 == false && bAK47 == false && bCSMG == false && bTHOMPSON == false && bSemi == false && bM249 == false) {
				bMP5 = !bMP5;
				Weapon = "MP5";
				enabled = true;
				DrawGui();
				if (silence == false)
				{
					//PlaySound(TEXT("MP5.wav"), NULL, SND_SYNC);
					PlaySound(MAKEINTRESOURCE(IDR_WAVE7), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

				}
			}
		}
		if (GetAsyncKeyState(VK_F5) & 1)
		{
			CloseWeapons();
			if (bLR300 == false && bMP5 == false && bCSMG == false && bTHOMPSON == false && bAK47 == false && bM249 == false) {
				bSemi = !bSemi;
				Weapon = "SEMI";
				enabled = true;
				DrawGui();
				if (silence == false)
				{
					PlaySound(MAKEINTRESOURCE(IDR_WAVE10), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
					//PlaySound(TEXT("SAR.wav"), NULL, SND_SYNC);
				}
			}
		}
		if (GetAsyncKeyState(VK_F6) & 1)
		{
			CloseWeapons();
			if (bLR300 == false && bMP5 == false && bCSMG == false && bAK47 == false && bSemi == false && bM249 == false) {
				bTHOMPSON = !bTHOMPSON;
				Weapon = "THOMPSON";
				enabled = true;
				DrawGui();
				if (silence == false)
				{
					PlaySound(MAKEINTRESOURCE(IDR_WAVE14), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

					//PlaySound(TEXT("Thompson.wav"), NULL, SND_SYNC);
				}
			}
		}
		if (GetAsyncKeyState(VK_F7) & 1)
		{
			CloseWeapons();
			if (bLR300 == false && bMP5 == false && bAK47 == false && bTHOMPSON == false && bSemi == false && bM249 == false) {
				bCSMG = !bCSMG;
				Weapon = "CUSTOM_SMG";
				enabled = true;
				DrawGui();
				if (silence == false)
				{
					PlaySound(MAKEINTRESOURCE(IDR_WAVE3), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

					//PlaySound(TEXT("Custom.wav"), NULL, SND_SYNC);
				}
			}
		}
		if (GetAsyncKeyState(VK_F8) & 1)
		{
			CloseWeapons();
			if (bLR300 == false && bMP5 == false && bCSMG == false && bTHOMPSON == false && bSemi == false && bAK47 == false) {
				bM249 = !bM249;
				Weapon = "M249";
				enabled = true;
				DrawGui();
				if (silence == false)
				{
					PlaySound(MAKEINTRESOURCE(IDR_WAVE6), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

					//PlaySound(TEXT("M2.wav"), NULL, SND_SYNC);
				}
			}
		}

		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			AllClose();
			DrawGui();
			if (silence == false)
			{
				PlaySound(MAKEINTRESOURCE(IDR_WAVE8), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
				//PlaySound(TEXT("OFF.wav"), NULL, SND_SYNC);
			}
		}
		if (GetAsyncKeyState(VK_DELETE) == -32767)
		{
			silence = !silence;
			DrawGui();
			if (silence == false)
			{
				PlaySound(MAKEINTRESOURCE(IDR_WAVE11), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
			}
			if (silence == true)
			{
				std::cout << '\a';
			}
		}

		if (GetAsyncKeyState(VK_LEFT) & 1)
		{
			b8x = !b8x;
			switch (b8x)
			{
			case(true):
				Scope = "8x"; bHolo = false; bSimple = false; b16x = false;
				if (silence == false)
				{
					PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
					//PlaySound(TEXT("8X.wav"), NULL, SND_SYNC);
				}
				break;
			case(false):
				Scope = "NONE";
				break;
			}
			DrawGui();
		}

		if (GetAsyncKeyState(VK_RIGHT) & 1)
		{
			b16x = !b16x;
			switch (b16x)
			{
			case(true):
				//PlaySound(MAKEINTRESOURCE(IDR_WAVE15), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
				Scope = "16x"; bHolo = false; bSimple = false; b8x = false;
				if (silence == false)
				{
					PlaySound(MAKEINTRESOURCE(IDR_WAVE15), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
					//PlaySound(TEXT("8X.wav"), NULL, SND_SYNC);
				}
				break;
			case(false):
				Scope = "NONE";
				break;
			}
			DrawGui();
		}

		if (GetAsyncKeyState(VK_DOWN) & 1) {
			bSimple = !bSimple;
			if (bSimple == true) {
				Scope = "SIMPLE"; b8x = false; bHolo = false; b16x = false;
				if (silence == false)
				{
					PlaySound(MAKEINTRESOURCE(IDR_WAVE13), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

					//sndPlaySound(TEXT("Simple Sight.wav"), SND_FILENAME | SND_ASYNC);
					//PlaySound(TEXT("Simple Sight.wav"), NULL, SND_SYNC);
				}
			}
			else if (bSimple == false)
			{
				Scope = "NONE";
			}
			DrawGui();
		}

		if (GetAsyncKeyState(VK_UP) & 1) {
			bHolo = !bHolo;
			if (bHolo == true) {
				Scope = "HOLO"; b8x = false; bSimple = false; b16x = false;
				if (silence == false)
				{
					PlaySound(MAKEINTRESOURCE(IDR_WAVE4), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

					//sndPlaySound(TEXT("Holo.wav"), SND_FILENAME | SND_ASYNC);
				}
			}
			else if (bHolo == false)
			{
				Scope = "NONE";
			}
			DrawGui();
		}

		if (GetAsyncKeyState(VK_NEXT) & 1) {
			bSuppressor = !bSuppressor;
			if (bSuppressor == true) {
				Barrel = "Silencer"; bMuzzleBoost = false;
				if (silence == false)
				{
					PlaySound(MAKEINTRESOURCE(IDR_WAVE12), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
					//PlaySound(TEXT("8X.wav"), NULL, SND_SYNC);
				}
			}
			else if (bSuppressor == false)
			{
				Barrel = "NONE";
			}
			DrawGui();
		}

		//if (GetAsyncKeyState(VK_PRIOR) & 1) {
		//	bMuzzleBoost = !bMuzzleBoost;
		//	if (bMuzzleBoost == true) {
		//		Barrel = "Muzzle Boost"; bSuppressor = false;
		//	}
		//	else if (bMuzzleBoost == false)
		//	{
		//		Scope = "NONE";
		//	}
		//	DrawGui();
		//}

		if (CurrentWeapon::WeaponActive() == true)
		{
			for (int i = 0; i <= CurrentWeapon::Bullet() && GetAsyncKeyState(VK_LBUTTON) & 0x8000 && GetAsyncKeyState(VK_RBUTTON) & 0x8000; i++)
			{
				Smoothing((int)IsMuzzleBoost((float)CurrentWeapon::Delay()), (int)IsMuzzleBoost(CurrentWeapon::Control(i)), (int)CurrentWeapon::x(i), (int)CurrentWeapon::y(i));
				CurrentWeapon::RecoilBreak(i);
			}
			Sleep(1);
		}
	}
	return false;
}
void Smoothing(double delay, double control_time, int x, int y) {
	int x_ = 0, y_ = 0, t_ = 0;
	for (int i = 1; i <= (int)control_time; ++i) {
		int xI = i * x / (int)control_time;
		int yI = i * y / (int)control_time;
		int tI = i * (int)control_time / (int)control_time;
		mouse_event(1, (int)xI - (int)x_, (int)yI - (int)y_, 0, 0);
		QSleep((int)tI - (int)t_);
		x_ = xI; y_ = yI; t_ = tI;
	}
	QSleep((int)delay - (int)control_time);
}
int IsMuzzleBoost(float Delay) { // Is muzzle boost attached?
	if (bMuzzleBoost == true) {
		float difference = Delay * 0.1f;
		Delay = Delay - difference;
		return (int)Delay + 2;
	}
	else
		return (int)Delay;
}
double Barrels() { // What barrel Attachment is on
	if (bSuppressor == true) {
		if (bM249 == true)
			Multiplyer::Barrel.Suppressor = 0.75;
		if (bCSMG == true)
			Multiplyer::Barrel.Suppressor = 0.85;
		if (bSimple == true || bHolo == true)
			return 0.8;
		if (b8x == true && bSuppressor == true)
			return 1;
		else
			return Multiplyer::Barrel.Suppressor;
	}
	else if (bMuzzleBoost == true) {
		return Multiplyer::Barrel.None;
	}
	else
		return Multiplyer::Barrel.None;
}
double Scopes() { // What Scope Attachment is on
	if (b8x == true) {
		if (bCSMG == true || bTHOMPSON == true) {
			if (b8x == true)
				return Multiplyer::Scope.x8 + 0.75;
		}
		return Multiplyer::Scope.x8;
	}
	else if (b8x == true) {
		if (bAK47 == true) {
			if (b8x == true)
				return Multiplyer::Scope.x8 + 0.00279;
		}
		return Multiplyer::Scope.x8;
	}
	else if (bSimple == true) {
		if (bCSMG == true || bTHOMPSON == true) {
			if (bSimple == true)
				return Multiplyer::Scope.Simple + 0.05;
		}
		return Multiplyer::Scope.Simple;
	}
	else if (bHolo == true) {
		if (bCSMG == true || bTHOMPSON == true) {
			if (bHolo == true)
				return Multiplyer::Scope.Holo + 0.25;
		}
		return Multiplyer::Scope.Holo;
	}
	else if (bHolo == true) {
		if (bAK47 == true) {
			if (bHolo == true)
				return Multiplyer::Scope.Holo + 0.01395;
		}
		return Multiplyer::Scope.Holo;
	}
	else if (b16x == true) {
		return Multiplyer::Scope.x16;
	}
	else
		return Multiplyer::Scope.None;
}
void QSleep(int ms) // Sleep / Delay
{
	LONGLONG timerResolution;
	LONGLONG wantedTime;
	LONGLONG currentTime;

	QueryPerformanceFrequency((LARGE_INTEGER*)&timerResolution);
	timerResolution /= 1000;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	wantedTime = currentTime / timerResolution + ms;
	currentTime = 0;
	while (currentTime < wantedTime)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
		currentTime /= timerResolution;
	}
}
void PreLaunch()
{
	//SetConsole(true);
	HWND hwnd = GetConsoleWindow();
	SetConsoleTitle(L"Beamer Dreamer !");
	if (hwnd != NULL) { MoveWindow(hwnd, 800, 200, 550, 340, TRUE); }
	TransparentWindow();
	SetConsoleTitle(L"Beamer Dreamer !");

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);


	if (hwnd != NULL) { MoveWindow(hwnd, 800, 200, 550, 340, TRUE); }
	SetLayeredWindowAttributes(hwnd, 1000, 1000, LWA_ALPHA);

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
	//std::cout << blue << "\n";
	std::cout << yellow << "\n";
	
	/// //////////////////////////////

	//unix_timestamp();
	
	
	//Request();

	/// //////////////////////////////
	Type("   >> Connecting to https://time.is/ : \n", 1);
	Type("   >> ............................... \n\n", 50);
	Type("   >> Todays date : ", 1);

	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
	std::string str(buffer);
	std::cout << str << endl;
	std::time_t now = std::time(0);
	std::tm* now_tm = gmtime(&now);
	std::tm tomorrow_tm(*now_tm);
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tomorrow_tm.tm_mday = 15;
	tomorrow_tm.tm_mon = 12 - 1;
	tomorrow_tm.tm_year = 2021 - 1900;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//std::time_t t = std::time(0);   // get time now
	//std::tm* now = std::localtime(&t);
	//std::cout << (now->tm_year + 1900) << '-'<< (now->tm_mon + 1) << '-'<< now->tm_mday<< "\n\n";
	
	Type("   >> Your subscription expires : ", 1); std::cout << green;
	std::cout << (tomorrow_tm.tm_year + 1900) << '-' << (tomorrow_tm.tm_mon + 1) << '-' << tomorrow_tm.tm_mday << "\n\n";
	std::time_t tomorrow = std::mktime(&tomorrow_tm);
	double delta = std::difftime(tomorrow, now);
	////int todaysDate = now->tm_mday + now->tm_mon + 1+ now->tm_year + 1900;
	//std::cout << todaysDate;
	std::cout << yellow;
	Type("   >> Time left : ", 1);
	std::cout << green;
	std::cout << delta / 86400 << " days.\n\n\n";

	std::cout << yellow;
	if (delta / 86400 < 0)
	{
		std::cout << red << "\n";
		Type("   >> Your Subscription has expired, please contact developer\n", 2);
		Type("   >> ......................................................", 200);
		exit(3);
	}

	Type("   >> Input Sensitivity: ", 2);
	std::cin >> UserSens;
}
void PreLaunchTest()
{
	//SetConsole(true);
	HWND hwnd = GetConsoleWindow();
	SetConsoleTitle(L"Beamer Dreamer !");
	if (hwnd != NULL) { MoveWindow(hwnd, 800, 200, 550, 340, TRUE); }
	TransparentWindow();
	SetConsoleTitle(L"Beamer Dreamer !");

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);


	if (hwnd != NULL) { MoveWindow(hwnd, 800, 200, 550, 340, TRUE); }
	SetLayeredWindowAttributes(hwnd, 1000, 1000, LWA_ALPHA);

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
	//std::cout << blue << "\n";
	std::cout << yellow << "\n";

	Type("   >> Input Sensitivity: ", 2);
	std::cin >> UserSens;
}
void preLaunchHWIDCheck()
{
	getHWID();
	checkedHwid = check1 + hwid + check4 + check2 + check3;

	//std::cout << "   >> Your HWID : " << checkedHwid << endl;
	ofstream myfile;
	myfile.open("Do Not Delete.txt");

	int i;
	for (i = 0; (i < 100 && checkedHwid[i] != '\0'); i++)
		checkedHwid[i] = checkedHwid[i] + 26;

	myfile << checkedHwid;
	myfile.close();
	checkedHwid = check1 + hwid + check4 + check2 + check3;

	
	ifstream MyReadFile("Do Not Delete.txt");
	getline(MyReadFile, myText);

	for (i = 0; (i < 100 && myText[i] != '\0'); i++)
		myText[i] = myText[i] - 26;

	MyReadFile.close();
	//std::cout << myText;
}
void prepreLaunchMessage()
{
	HWND hwnd = GetConsoleWindow();
	SetConsoleTitle(L"Beamer Dreamer !");
	if (hwnd != NULL) { MoveWindow(hwnd, 800, 200, 550, 340, TRUE); }
	std::cout << blue << "\n";
	Type("  -> Beamer Dreamer Script\n", 10);
	Type("  -> Checking license...\n", 10);
}

int main(int argc, char* argv[])
{
	//////////////////////////////////
	//Testing

	PreLaunchTest();
	DrawGui();
	Recoils();

	//////////////////////////////////

	//SetConsole(true);

	/////////////////////////////////
	//Main

	/*prepreLaunchMessage();
	Sleep(1000);
	preLaunchHWIDCheck();

	if (checkedHwid == myText)
	{
		std::cout << "  -> HWID matching \n";
		Sleep(2000);
		PreLaunch();
		DrawGui();
		Recoils();
	}
	else
	{
		std::cout << "  -> Bad HWID. Contact developer.";
		Sleep(120000);
		exit(3);
	}*/
	
	//SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}
