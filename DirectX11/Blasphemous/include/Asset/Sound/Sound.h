#pragma once

#include "../Asset.h"

#include "fmod.hpp"

class CSound : public CAsset
{
	friend class CSoundManager;

protected:
	CSound();
	virtual ~CSound();

	//사운드 관리 
	FMOD::System* mSystem = nullptr;
	//어떤 사운드가 저장되었는지 체크하는 것
	FMOD::ChannelGroup* mGroup = nullptr;
	//사운드가 포함된 채널 
	FMOD::Channel* mChannel = nullptr;
	//실제 사운드 데이터
	FMOD::Sound* mSound = nullptr;


	bool mLoop = false;
	//사운드가 동시에 몇개개가 플레이 되는가?
	int mPlayCount = 0;

public:
	//파일명 
	bool LoadSound(FMOD::System* System, FMOD::ChannelGroup* Group, bool Loop, const char* FileName);
	bool LoadSoundFullPath(FMOD::System* System, FMOD::ChannelGroup* Group, bool Loop, const char* FullPath);

	//실행
	void Play();
	void Stop();
	// 일시정지
	void Pause();
	// 재시작
	void Resume();
	static FMOD_RESULT SoundEnd(FMOD_CHANNELCONTROL* channelcontrol, FMOD_CHANNELCONTROL_TYPE controltype, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype, void* commanddata1, void* commanddata2);

};


