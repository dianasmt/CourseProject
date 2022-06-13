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
		case L'À':ch = 128; break;
		case L'à':ch = 129; break;
		case L'Á':ch = 130; break;
		case L'á':ch = 131; break;
		case L'Â':ch = 132; break;
		case L'â':ch = 133; break;
		case L'Ã':ch = 134; break;
		case L'ã':ch = 135; break;
		case L'Ä':ch = 136; break;
		case L'ä':ch = 137; break;
		case L'Å':ch = 138; break;
		case L'å':ch = 139; break;
		case L'¨':ch = 140; break;
		case L'¸':ch = 141; break;
		case L'Æ':ch = 142; break;
		case L'æ':ch = 143; break;
		case L'Ç':ch = 144; break;
		case L'ç':ch = 145; break;
		case L'È':ch = 146; break;
		case L'è':ch = 147; break;
		case L'É':ch = 148; break;
		case L'é':ch = 149; break;
		case L'Ê':ch = 150; break;
		case L'ê':ch = 151; break;
		case L'Ë':ch = 152; break;
		case L'ë':ch = 153; break;
		case L'Ì':ch = 154; break;
		case L'ì':ch = 155; break;
		case L'Í':ch = 156; break;
		case L'í':ch = 157; break;
		case L'Î':ch = 158; break;
		case L'î':ch = 159; break;
		case L'Ï':ch = 160; break;
		case L'ï':ch = 161; break;
		case L'Ð':ch = 162; break;
		case L'ð':ch = 163; break;
		case L'Ñ':ch = 164; break;
		case L'ñ':ch = 165; break;
		case L'Ò':ch = 166; break;
		case L'ò':ch = 167; break;
		case L'Ó':ch = 168; break;
		case L'ó':ch = 169; break;
		case L'Ô':ch = 170; break;
		case L'ô':ch = 171; break;
		case L'Õ':ch = 172; break;
		case L'õ':ch = 173; break;
		case L'Ö':ch = 174; break;
		case L'ö':ch = 175; break;
		case L'×':ch = 176; break;
		case L'÷':ch = 177; break;
		case L'Ø':ch = 178; break;
		case L'ø':ch = 179; break;
		case L'Ù':ch = 180; break;
		case L'ù':ch = 181; break;
		case L'ú':ch = 182; break;
		case L'û':ch = 183; break;
		case L'Û':ch = 184; break;
		case L'ü':ch = 185; break;
		case L'Ý':ch = 186; break;
		case L'ý':ch = 187; break;
		case L'Þ':ch = 188; break;
		case L'þ':ch = 189; break;
		case L'ß':ch = 190; break;
		case L'ÿ':ch = 191; break;
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
		case -128:ch = L'À'; break;
		case -127:ch = L'à'; break;
		case -126:ch = L'Á'; break;
		case -125:ch = L'á'; break;
		case -124:ch = L'Â'; break;
		case -123:ch = L'â'; break;
		case -122:ch = L'Ã'; break;
		case -121:ch = L'ã'; break;
		case -120:ch = L'Ä'; break;
		case -119:ch = L'ä'; break;
		case -118:ch = L'Å'; break;
		case -117:ch = L'å'; break;
		case -116:ch = L'¨'; break;
		case -115:ch = L'¸'; break;
		case -114:ch = L'Æ'; break;
		case -113:ch = L'æ'; break;
		case -112:ch = L'Ç'; break;
		case -111:ch = L'ç'; break;
		case -110:ch = L'È'; break;
		case -109:ch = L'è'; break;
		case -108:ch = L'É'; break;
		case -107:ch = L'é'; break;
		case -106:ch = L'Ê'; break;
		case -105:ch = L'ê'; break;
		case -104:ch = L'Ë'; break;
		case -103:ch = L'ë'; break;
		case -102:ch = L'Ì'; break;
		case -101:ch = L'ì'; break;
		case -100:ch = L'Í'; break;
		case -99:ch = L'í'; break;
		case -98:ch = L'Î'; break;
		case -97:ch = L'î'; break;
		case -96:ch = L'Ï'; break;
		case -95:ch = L'ï'; break;
		case -94:ch = L'Ð'; break;
		case -93:ch = L'ð'; break;
		case -92:ch = L'Ñ'; break;
		case -91:ch = L'ñ'; break;
		case -90:ch = L'Ò'; break;
		case -89:ch = L'ò'; break;
		case -88:ch = L'Ó'; break;
		case -87:ch = L'ó'; break;
		case -86:ch = L'Ô'; break;
		case -85:ch = L'ô'; break;
		case -84:ch = L'Õ'; break;
		case -83:ch = L'õ'; break;
		case -82:ch = L'Ö'; break;
		case -81:ch = L'ö'; break;
		case -80:ch = L'×'; break;
		case -79:ch = L'÷'; break;
		case -78:ch = L'Ø'; break;
		case -77:ch = L'ø'; break;
		case -76:ch = L'Ù'; break;
		case -75:ch = L'ù'; break;
		case -74:ch = L'ú'; break;
		case -73:ch = L'û'; break;
		case -72:ch = L'Û'; break;
		case -71:ch = L'ü'; break;
		case -70:ch = L'Ý'; break;
		case -69:ch = L'ý'; break;
		case -68:ch = L'Þ'; break;
		case -67:ch = L'þ'; break;
		case -66:ch = L'ß'; break;
		case -65:ch = L'ÿ'; break;
		default:
		{
			result += (wchar_t)str[i];
		}
		}
		if (ch)result += ch;
	}
	return result;
}
