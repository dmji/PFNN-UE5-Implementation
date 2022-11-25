// Fill out your copyright notice in the Description page of Project Settings.


#include "FileHandlersUtil.h"

FFloat32 UBinaryFloatFileReader::readItem()
{
	FFloat32 item;
	uint8* ByteBuffer = reinterpret_cast<uint8*>(&item);

	if(!m_FileHandle->Read(ByteBuffer, sizeof(FFloat32)))
		m_Errors++;
	return item;
}

bool UBinaryFloatFileReader::isOpen()
{
	return nullptr != m_FileHandle;
}

int32 UBinaryFloatFileReader::nErrorsOnRead()
{
	return m_Errors;
}

UBinaryFloatFileReader::UBinaryFloatFileReader(const FString arg_FileName, ...) 
	: m_Errors(0)
{
	FString RelativePath = FPaths::ProjectDir();
	const FString FullPath = RelativePath += arg_FileName;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	m_FileHandle = PlatformFile.OpenRead(*FullPath);
}

UBinaryFloatFileReader::~UBinaryFloatFileReader()
{
	delete m_FileHandle;
}