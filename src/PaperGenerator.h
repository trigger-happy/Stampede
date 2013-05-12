#ifndef PAPERGENERATOR_H
#define PAPERGENERATOR_H
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <orx.h>

class PaperGenerator : public boost::noncopyable
{
public:
	PaperGenerator();
	
	void orxFASTCALL clockUpdate( const orxCLOCK_INFO* clockInfo );
private:
	orxCLOCK*	m_clock;
};

typedef boost::shared_ptr<PaperGenerator> PaperGeneratorPtr;

#endif // PAPERGENERATOR_H
