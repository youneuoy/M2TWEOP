#include "fsystem.h"

vector<string> fsystem::getAllSubFolders(string s)
{
	vector<string> names;
	string search_path = s + "/*.*";
	WIN32_FIND_DATAA fd;
	HANDLE hFind = ::FindFirstFileA(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				if (checkDots(fd.cFileName))
					names.push_back(fd.cFileName);
			}
		} while (::FindNextFileA(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

int fsystem::checkDots(string s)
{
	for (char c : s)
	{
		if (c != '.')
			return 1;
	}
	return 0;
}

vector<string> fsystem::getAllFiles(string s)
{
	vector<string> names;
	string search_path = s + "/*.*";
	WIN32_FIND_DATAA fd;
	HANDLE hFind = ::FindFirstFileA(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					names.push_back(fd.cFileName);
			}
		} while (::FindNextFileA(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}
string fsystem::get_ext(const string& st)
{
	size_t pos = st.rfind('.');
	if (pos <= 0) return "";
	return st.substr(pos + 1, string::npos);
}

void fsystem::loadTexture(string* path, LPDIRECT3DTEXTURE9* image, LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	HRESULT res = D3DXCreateTextureFromFile(g_pd3dDevice, path->c_str(), image);
	string t = std::system_category().message(res);
	if (res != D3D_OK)
	{
		t = t +" "+ *path;
		MessageBoxA(NULL, t.c_str(), "Loading texture err!", MB_OK | MB_ICONASTERISK);
	}

}
