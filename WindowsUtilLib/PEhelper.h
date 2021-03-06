#pragma once
#include <windows.h>
#include <stdlib.h>
#include <string>
#include "BaseUtil.h"

class PEInfo {
public:
	explicit PEInfo(HMODULE _module) {
		module = _module;
		LoadModule(module);
	}
	bool LoadModule(HMODULE Module);
	static HMODULE GetModuleHandle(const char* name);
	static HMODULE GetModuleHandle(const wchar_t* name);
	//if the code is in dll, you can use this function to get exe module
	static HMODULE GetEXEModuleHandle();
	//if the code is in dll, you can use this function to get dll module.
	static HMODULE GetCurrentModuleHandle();
private:
	HMODULE module;

};


namespace zzj
{
class PEFile{
#define ThrowExceptionIfFail(error) \
	if(!IsOperationSucceed(error))\
		throw error;
#define ReturnIfFail(error) \
	if(!IsOperationSucceed(error))\
		return error;
public:
	enum ErrorCode
	{
		SUCCESS=1,
		INVALID_PEFILE,
		LOAD_PE_ERROR,
		INVALID_FILE_NAME,
		WINAPI_ERROR,
		ZZJ_LIB_ERROR,
		INVALID_PARAMETER
	};
	
	explicit PEFile(std::string fileName,Allocator* allocator);
	~PEFile();
	ErrorCode LoadPE();
	ErrorCode UnloadPE();
	static DWORD RVAToVA(char* imageBase,DWORD rva);
	static ErrorCode IsValidPE(std::string _fileName);
	static bool IsOperationSucceed(ErrorCode error);
	static ErrorCode ReadDosHeader(std::string fileName, IMAGE_DOS_HEADER* dosHeader);
	static ErrorCode ReadNTHeader(std::string fileName, const IMAGE_DOS_HEADER& dosHeader, IMAGE_NT_HEADERS* ntHeader);
	static ErrorCode ReadDataDirectoryTable(char* imageBase, IMAGE_NT_HEADERS* ntheader, IMAGE_DATA_DIRECTORY*& dataDirectoryTable);
	static ErrorCode ReadImportLibrary(char* imageBase,IMAGE_DATA_DIRECTORY* dataDirectoryTable, IMAGE_IMPORT_DESCRIPTOR*& importLibrary, DWORD& numOfImportLibrary);
	static DWORD AlignData(DWORD data, DWORD alignment);

	std::string fileName;
	DWORD fileSize;


	IMAGE_DOS_HEADER* dosHeader;
	IMAGE_NT_HEADERS* ntHeader;
	IMAGE_DATA_DIRECTORY* dataDirectoryTable;
	IMAGE_SECTION_HEADER* sectionHeader;

	IMAGE_IMPORT_DESCRIPTOR* importLibrary;
	DWORD numOfImportLibrary=0;

	DWORD extraDataSize;
	char* extraData = nullptr;

private:
	Allocator* allocator;
	char* peImage=nullptr;
	
};
}