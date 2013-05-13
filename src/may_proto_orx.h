#ifndef MAY_PROTO_ORX_H
#define MAY_PROTO_ORX_H
#include <orx.h>
#include "SceneManager.h"
#include "PaperGenerator.h"

class may_proto_orx
{
public:
	static orxSTATUS orxFASTCALL init();
	static orxSTATUS orxFASTCALL run();
	static void orxFASTCALL exit();
	
	static may_proto_orx* instance();
	
	// meant for callback, don't touch
	void orxFASTCALL clockUpdate( const orxCLOCK_INFO* clockInfo );
	
private:
	may_proto_orx();
	
	orxSTATUS orxFASTCALL update();
	void updateScoreDisplay();
	void setupScenes();
	
	void onGameOver();
	
private:
	orxCLOCK*			m_clock;
	orxOBJECT*			m_scoreDisplay;
	PaperGeneratorPtr	m_generator;
	SceneManagerPtr		m_sceneManager;
	
	int32_t				m_score = 0;
};

#endif // MAY_PROTO_ORX_H
