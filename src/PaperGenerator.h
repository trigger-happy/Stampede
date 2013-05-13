#ifndef PAPERGENERATOR_H
#define PAPERGENERATOR_H
#include <vector>
#include <functional>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/pool/object_pool.hpp>
#include <orx.h>
#include "Paper.h"

class PaperGenerator : public boost::noncopyable
{
public:
	typedef Paper::PAPER_TYPE STAMP;
	typedef std::function<void ()> GameOverFunc;
	
	PaperGenerator();
	
	void start();
	void reset();
	void stop();
	
	void orxFASTCALL clockUpdate( const orxCLOCK_INFO* clockInfo );
	
	int32_t stampPaper( STAMP stamp );
	
	void atGameOver( GameOverFunc f )
	{
		m_onGameOver = f;
	}
	
private:
	void spawnPaper();
	void addPaperToStack( Paper* paper );
	void setCurrentPaper( Paper* paper );
	
	
	boost::object_pool<Paper>	m_paperPool;
	std::vector<Paper*>			m_paperStack;
	std::vector<Paper*>			m_exitingPapers;
	bool						m_running = false;
	double						m_elapsed = 0;
	orxCLOCK*					m_clock = nullptr;
	Paper*						m_currentPaper = nullptr;
	int32_t						m_maxStackSize = 0;
	int32_t						m_scorePenalty = 0;
	int32_t						m_paperStackYOffset = 0;
	
	GameOverFunc				m_onGameOver;
};

typedef boost::shared_ptr<PaperGenerator> PaperGeneratorPtr;

#endif // PAPERGENERATOR_H
