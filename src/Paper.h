#ifndef PAPER_H
#define PAPER_H
#include <cstdint>
#include <orx.h>

class Paper
{
public:
	enum class PAPER_TYPE : uint8_t
	{
		RED,
		GREEN,
		BLUE,
		JUNK
	};
	
	Paper( PAPER_TYPE type );
	
	inline PAPER_TYPE paperType() const
	{
		return m_type;
	}
	
	orxVECTOR position() const;
	void setPosition( const orxVECTOR& pos );
	
private:
	PAPER_TYPE	m_type;
	orxOBJECT*	m_object;
};

#endif // PAPER_H
