#include "IOModule.h"
#include "OverlappedIOBaseFileResourceFactory.h"

int main()
{
	//SSB::FileResourceFactory ioFactory;
	SSB::OverlappedIOBaseFileResourceFactory ioFactory;
	SSB::FileResource* fr = nullptr;

	ioFactory.SetFilePath("Read.txt");
	while (ioFactory.Read() != SSB::IOState::SUCCESS);
	fr = ioFactory.GetFileResource();

	ioFactory.SetFilePath("Write.txt");
	ioFactory.SetFileResource(fr);
	while (ioFactory.Write() != SSB::IOState::SUCCESS);
}