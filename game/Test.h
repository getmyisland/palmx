#ifndef _PE_TEST_H__
#define _PE_TEST_H__

#include <PalmEngineEntry.h>

class Test : public PalmEngine::PalmEngineEntry
{
public:
	Test() {}
	~Test() {}

	void Entry() override;
};

#endif