#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "Formatter.h"

CString IntToStr(int i)
{
	CString str;
	str.Format(L"%d", i);
	return str;
}

CString DoubleToStr(double i)
{
	CString str;
	str.Format(L"%.2lf", i);
	return str;
}

std::string WtoA(CString str)
{
	std::string result = "";
	for (int i = 0; i < str.GetLength(); i++)
	{
		char ch = 0;
		switch (str.GetAt(i))
		{
		case L'�':ch = 128; break;
		case L'�':ch = 129; break;
		case L'�':ch = 130; break;
		case L'�':ch = 131; break;
		case L'�':ch = 132; break;
		case L'�':ch = 133; break;
		case L'�':ch = 134; break;
		case L'�':ch = 135; break;
		case L'�':ch = 136; break;
		case L'�':ch = 137; break;
		case L'�':ch = 138; break;
		case L'�':ch = 139; break;
		case L'�':ch = 140; break;
		case L'�':ch = 141; break;
		case L'�':ch = 142; break;
		case L'�':ch = 143; break;
		case L'�':ch = 144; break;
		case L'�':ch = 145; break;
		case L'�':ch = 146; break;
		case L'�':ch = 147; break;
		case L'�':ch = 148; break;
		case L'�':ch = 149; break;
		case L'�':ch = 150; break;
		case L'�':ch = 151; break;
		case L'�':ch = 152; break;
		case L'�':ch = 153; break;
		case L'�':ch = 154; break;
		case L'�':ch = 155; break;
		case L'�':ch = 156; break;
		case L'�':ch = 157; break;
		case L'�':ch = 158; break;
		case L'�':ch = 159; break;
		case L'�':ch = 160; break;
		case L'�':ch = 161; break;
		case L'�':ch = 162; break;
		case L'�':ch = 163; break;
		case L'�':ch = 164; break;
		case L'�':ch = 165; break;
		case L'�':ch = 166; break;
		case L'�':ch = 167; break;
		case L'�':ch = 168; break;
		case L'�':ch = 169; break;
		case L'�':ch = 170; break;
		case L'�':ch = 171; break;
		case L'�':ch = 172; break;
		case L'�':ch = 173; break;
		case L'�':ch = 174; break;
		case L'�':ch = 175; break;
		case L'�':ch = 176; break;
		case L'�':ch = 177; break;
		case L'�':ch = 178; break;
		case L'�':ch = 179; break;
		case L'�':ch = 180; break;
		case L'�':ch = 181; break;
		case L'�':ch = 182; break;
		case L'�':ch = 183; break;
		case L'�':ch = 184; break;
		case L'�':ch = 185; break;
		case L'�':ch = 186; break;
		case L'�':ch = 187; break;
		case L'�':ch = 188; break;
		case L'�':ch = 189; break;
		case L'�':ch = 190; break;
		case L'�':ch = 191; break;
		default:
		{
			result += (char)str.GetAt(i);
		}
		}
		if (ch)result += ch;
	}
	return result;
}

CString AtoW(std::string str)
{
	CString result = L"";
	for (int i = 0; i < str.length(); i++)
	{
		wchar_t ch = 0;
		switch (str[i])
		{
		case -128:ch = L'�'; break;
		case -127:ch = L'�'; break;
		case -126:ch = L'�'; break;
		case -125:ch = L'�'; break;
		case -124:ch = L'�'; break;
		case -123:ch = L'�'; break;
		case -122:ch = L'�'; break;
		case -121:ch = L'�'; break;
		case -120:ch = L'�'; break;
		case -119:ch = L'�'; break;
		case -118:ch = L'�'; break;
		case -117:ch = L'�'; break;
		case -116:ch = L'�'; break;
		case -115:ch = L'�'; break;
		case -114:ch = L'�'; break;
		case -113:ch = L'�'; break;
		case -112:ch = L'�'; break;
		case -111:ch = L'�'; break;
		case -110:ch = L'�'; break;
		case -109:ch = L'�'; break;
		case -108:ch = L'�'; break;
		case -107:ch = L'�'; break;
		case -106:ch = L'�'; break;
		case -105:ch = L'�'; break;
		case -104:ch = L'�'; break;
		case -103:ch = L'�'; break;
		case -102:ch = L'�'; break;
		case -101:ch = L'�'; break;
		case -100:ch = L'�'; break;
		case -99:ch = L'�'; break;
		case -98:ch = L'�'; break;
		case -97:ch = L'�'; break;
		case -96:ch = L'�'; break;
		case -95:ch = L'�'; break;
		case -94:ch = L'�'; break;
		case -93:ch = L'�'; break;
		case -92:ch = L'�'; break;
		case -91:ch = L'�'; break;
		case -90:ch = L'�'; break;
		case -89:ch = L'�'; break;
		case -88:ch = L'�'; break;
		case -87:ch = L'�'; break;
		case -86:ch = L'�'; break;
		case -85:ch = L'�'; break;
		case -84:ch = L'�'; break;
		case -83:ch = L'�'; break;
		case -82:ch = L'�'; break;
		case -81:ch = L'�'; break;
		case -80:ch = L'�'; break;
		case -79:ch = L'�'; break;
		case -78:ch = L'�'; break;
		case -77:ch = L'�'; break;
		case -76:ch = L'�'; break;
		case -75:ch = L'�'; break;
		case -74:ch = L'�'; break;
		case -73:ch = L'�'; break;
		case -72:ch = L'�'; break;
		case -71:ch = L'�'; break;
		case -70:ch = L'�'; break;
		case -69:ch = L'�'; break;
		case -68:ch = L'�'; break;
		case -67:ch = L'�'; break;
		case -66:ch = L'�'; break;
		case -65:ch = L'�'; break;
		default:
		{
			result += (wchar_t)str[i];
		}
		}
		if (ch)result += ch;
	}
	return result;
}
