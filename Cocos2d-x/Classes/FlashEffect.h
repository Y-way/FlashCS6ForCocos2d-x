#ifndef __FLASH_EFFECT_H__
#define __FLASH_EFFECT_H__

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
#include "DisplayParameter.h"
#include "FlashEffectDefine.h"

USING_NS_CC;

//��Ч��ʱ��������
class EffectCreateAction : public ActionInterval
{
protected:
	bool init(float delay_start, float duration);
	virtual EffectCreateAction* clone() const override;
	virtual EffectCreateAction* reverse() const override;
	virtual void update(float time) override;
	virtual void startWithTarget(Node *target) override;
	virtual bool doCreate() = 0;
	virtual bool doDestory() = 0;

protected:
	EffectCreateAction():
		m_bCreated(false),
		m_fDelayStart(0),
		m_fDuration(0)
	{};
	virtual ~EffectCreateAction()
	{};

private:
	float								m_fDelayStart;				// ��ʼ��ʱ
	float								m_fDuration;				// ����ʱ��
	bool								m_bCreated;					// �Ƿ��Ѵ���
};

//������Ч��ʱ����
class SoundCreateAction : public EffectCreateAction
{
public:
	static SoundCreateAction * create(const char * sound, float duration,
		float delay_start, bool loop, float pitch, float pan, float gain);

	//override
	virtual bool doCreate() override;
	virtual bool doDestory() override;

protected:
	SoundCreateAction():
		m_szSound(nullptr),
		m_fPitch(false),
		m_fPan(false),
		m_fGain(false),
		m_bLoop(false),
		m_nSoundID(0)
	{};
	virtual ~SoundCreateAction()
	{
		doDestory();
		m_szSound = nullptr;
		m_nSoundID = 0;
	};

private:
	const char *						m_szSound;					//�����ļ���
	float								m_fPitch;					//
	float								m_fPan;
	float								m_fGain;
	bool								m_bLoop;					//�Ƿ�ѭ������
	unsigned int						m_nSoundID;					// ��Ӧ�Ķ�������
};

class ImageCreateAction : public EffectCreateAction
{
public:
	static ImageCreateAction * create(const char * image, DisplayParameter param,
		float duration, float delay_start);

	//override
	virtual bool doCreate() override;
	virtual bool doDestory() override;

protected:
	ImageCreateAction() :
		m_pSprite(nullptr),
		m_szImageName(nullptr)
	{};
	virtual ~ImageCreateAction()
	{
		doDestory();
		m_szImageName = nullptr;
	};

private:
	const char *						m_szImageName;				// ͼƬ��
	DisplayParameter					m_DisplayParameter;			// ��ʾ����
	Sprite *							m_pSprite;					// ͼƬ��ʾ����
};

class NodeCreateAction : public EffectCreateAction
{
public:
	//����
	static NodeCreateAction * create(const char * effect_id, DisplayParameter param,
		ActionInterval * action, float duration, float delay_start);

	//override
	virtual bool doCreate() override;
	virtual bool doDestory() override;

protected:
	NodeCreateAction():
		m_szEffectID(nullptr),
		m_pAction(nullptr)
	{};
	~NodeCreateAction()
	{
		doDestory();

		m_szEffectID = nullptr;
	};

private:
	const char *						m_szEffectID;				//��ЧID
	DisplayParameter					m_DisplayParameter;			//��ʼ��ʾ����
	Action *							m_pAction;					//�˶�
	Node *								m_pNode;					//����������
};

class FlashEffect : public Node
{
public:
	static FlashEffect * create(const char * effect_id);
	// �Ӷ��������ص�
	void onSubEffectFinish();

protected:
	bool init(const char * effect_id);
	// ��XML��ȡAction
	ActionInterval * parseXmlToAction(tinyxml2::XMLElement * action);
	// ����������Ч����
	ActionInterval * createShakeAction(float duration, Point range=Point(2,2), float rate=10);

private:
	FlashEffect() :
		m_nSubEffectRuningCount(0)
	{};

private:
	int									m_nSubEffectRuningCount;	//�����е�����Ч����
};

class FlashEffectManager
{
public:
	static FlashEffectManager * getInstance()
	{
		if (nullptr == s_Instance)
		{
			s_Instance = new FlashEffectManager;
		}
		return s_Instance;
	};
	//���ļ�������ЧXML�ĵ�
	bool loadConfig(const char * xml_file);
	//ͨ��ID������Ч
	FlashEffect * createEffect(const char * effect_id);

protected:
	//ͨ����ЧID��ȡ��ЧXML�ڵ�
	tinyxml2::XMLElement * getEffectXmlNode(const char * effect_id);

private:
	FlashEffectManager():
		m_pXmlDocument(nullptr)
	{};
	~FlashEffectManager()
	{
		if (m_pXmlDocument != nullptr)
		{
			delete m_pXmlDocument;
		}
	};

private:
	static FlashEffectManager *				s_Instance;				//����ʵ��
	tinyxml2::XMLDocument *					m_pXmlDocument;			//��ЧXML�ĵ�

	friend class FlashEffect;
};

#endif // __FLASH_EFFECT_H__
