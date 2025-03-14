#pragma once

#include <windows.h>
#include <commdlg.h>
#include <atlstr.h>
#include <iostream>
#include <string>
#include <fstream>

class FileReader
{
	public:
		std::string static reader();

	private:
		static OPENFILENAME ofn;


};

