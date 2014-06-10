#ifndef __DISPLAY_PARAMETER_H__
#define __DISPLAY_PARAMETER_H__

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"

USING_NS_CC;

class DisplayParameter
{
public:
	DisplayParameter():
		m_ptPosition(0,0),
		m_ptAnchorPoint(0.5f,0.5f),
		m_ptScale(1,1),
		m_fRotation(0),
		m_Color(1,1,1,1),
		m_nZOrder(0)
	{};

public:
	// ��XML��ȡ��ֵ
	bool readXml(const tinyxml2::XMLElement * xml);
	// Ӧ����cocos::node
	void apply(Node * node);

public:
	Point						m_ptPosition;				// ����λ��
	Point						m_ptAnchorPoint;			// ����ê��
	Point						m_ptScale;					// ���ű���
	float						m_fRotation;				// ������ת�Ƕ�
	Color4F						m_Color;					// ��ʼ��ɫ
	int							m_nZOrder;					// ��ʾ�㼶����
};


#endif // __DISPLAY_PARAMETER_H__