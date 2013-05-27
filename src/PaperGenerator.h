#ifndef PAPERGENERATOR_H
#define PAPERGENERATOR_H
#include <vector>
#include <functional>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/pool/object_pool.hpp>
#include <orx.h>
#include "Paper.h"
#include "ClientHand.h"

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
	
	bool isRunning() const
	{
		return m_running;
	}
	
private:
	void spawnPaper();
	void addPaperToStack( Paper* paper );
	void setCurrentPaper( Paper* paper );
	void setNextSpawnTime();
	
	
	boost::object_pool<Paper>	m_paperPool;
	std::vector<Paper*>			m_paperStack;
	std::vector<Paper*>			m_exitingPapers;
	orxCLOCK*					m_clock = nullptr;
	orxSOUND*					m_paperSpawnSound = nullptr;
	orxSOUND*					m_stampSound = nullptr;
	orxSOUND*					m_honkSound = nullptr;
	Paper*						m_currentPaper = nullptr;
	bool						m_running = false;
	double						m_elapsed = 0;
	double						m_nextPaperSpawn = 0;
	ClientHandPtr				m_clientHand;
	
	// config vars
	int32_t						m_maxStackSize = 0;
	int32_t						m_scorePenalty = 0;
	int32_t						m_paperStackYOffset = 0;
	float						m_timePerLevel = 0;
	float						m_levelIncrement = 0;
	float						m_baseGeneratorTime = 0;
	float						m_gameStartDelay = 0;
	
	// callback
	GameOverFunc				m_onGameOver;
};

typedef std::shared_ptr<PaperGenerator> PaperGeneratorPtr;

#endif // PAPERGENERATOR_H
