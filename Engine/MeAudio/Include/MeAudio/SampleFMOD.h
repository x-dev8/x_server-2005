#include <fmod/fmod.h>

class HRAUIDO_API HRSampleFMOD
{
public:
	HRSampleFMOD();
	~HRSampleFMOD();
	// implement the pgISample interface
	//
	virtual const char* GetSampleName() const  {  return Name;  }
	
	virtual void Destroy();

	virtual void Play(bool nLoop=false);

	virtual void Stop();

	virtual void StopLooping();

	virtual bool IsPlaying();

protected:
	HRSampleFMOD(const char* nName, FMOD::Sound* Sample);
	virtual ~HRSampleFMOD();
	virtual void Update();

	FMOD::Sound*	Sample;
	int				Channel;
	bool			Loop;
	bool			Playing;
	float			Length;
	bool			WantDestroy;
	float			TimeLeft;
	std::string		Name;
protected:

private:

};