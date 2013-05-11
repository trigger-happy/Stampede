#ifndef MAY_PROTO_ORX_H
#define MAY_PROTO_ORX_H
#include <orx.h>

class may_proto_orx
{
public:
	static orxSTATUS orxFASTCALL init();
	static orxSTATUS orxFASTCALL run();
	static void orxFASTCALL exit();
	
	static may_proto_orx* instance();
	
private:
	may_proto_orx();
	
	orxSTATUS orxFASTCALL update();
};

#endif // MAY_PROTO_ORX_H
