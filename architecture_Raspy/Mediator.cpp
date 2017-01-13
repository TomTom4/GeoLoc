#include "Mediator.h"

using namespace std;

	// setting s_instance which is a static attribut that needs to be setted
	Mediator *Mediator::s_instance = 0;
	// implementing Mediator constructor
	Mediator::Mediator(): m_model(){}

	Mediator* Mediator::instance(){
		if(Mediator::s_instance)
			Mediator::s_instance = new Mediator;
		mutex_mediator = PTHREAD_MUTEX_INITIALIZER;
		return Mediator::s_instance;
	}
	//******** GET ********//

	//** PWM
	unsigned char Mediator::getPwmMotorBack()
	{
		unsigned char buff;
		Mediator::lockMutex();
		buff = m_model.getPwmMotorBack();
		Mediator::unlockMutex();
		return buff;
	 }

	//** Steering Wheel
	unsigned char Mediator::getStateSteeringWheel()
	{
		unsigned char buff;
		Mediator::lockMutex();
		return m_model.getStateSteeringWheel();
		Mediator::unlockMutex();
		return buff;
	}

	//** Encoder
	float Mediator::getEncoderWheelBackLeft()
	{
		float buff;
		Mediator::lockMutex();
		return m_model.getEncoderWheelBackLeft();
		Mediator::unlockMutex();
		return buff;
	}

	float Mediator::getEncoderWheelBackRight()
	{
		float buff;
		Mediator::lockMutex();
		return m_model.getEncoderWheelBackRight();
		Mediator::unlockMutex();
		return buff;
	}

	//** US Validity
	unsigned char Mediator::getValidityFrontLeft()
	{
		unsigned char buff;
		Mediator::lockMutex();
		return m_model.getValidityFrontLeft();
		Mediator::unlockMutex();
		return buff;
	}

	unsigned char Mediator::getValidityFrontCenter()
	{
		unsigned char buff;
		Mediator::lockMutex();
		return m_model.getValidityFrontCenter();
		Mediator::unlockMutex();
		return buff;
	}

	unsigned char Mediator::getValidityFrontRight()
	{
		unsigned char buff;
		Mediator::lockMutex();
		return m_model.getValidityFrontRight();
		Mediator::unlockMutex();
		return buff;
	}

	unsigned char Mediator::getValidityBackLeft()
	{
		unsigned char buff;
		Mediator::lockMutex();
		return m_model.getValidityBackLeft();
		Mediator::unlockMutex();
		return buff;
	}

	unsigned char Mediator::getValidityBackCenter()
	{
		unsigned char buff;
		Mediator::lockMutex();
		return m_model.getValidityBackCenter();
		Mediator::unlockMutex();
		return buff;
	}

	unsigned char Mediator::getValidityBackRight()
	{
		unsigned char buff;
		Mediator::lockMutex();
		return m_model.getValidityBackRight();
		Mediator::unlockMutex();
		return buff;
	}

	//** Distance
	unsigned char Mediator::getDistanceFrontLeft()
	{
		unsigned char buff;
		Mediator::lockMutex();
  	return m_model.getDistanceFrontLeft();
		Mediator::unlockMutex();
		return buff;
	}

	unsigned char Mediator::getDistanceFrontCenter()
	{
		unsigned char buff;
		Mediator::lockMutex();
		return m_model.getDistanceFrontCenter();
		Mediator::unlockMutex();
		return buff;
	}

	unsigned char Mediator::getDistanceFrontRight()
	{
		unsigned char buff;
		Mediator::lockMutex();
		return m_model.getDistanceFrontRight();
		Mediator::unlockMutex();
		return buff;
	}

	unsigned char Mediator::getDistanceBackLeft()
	{
		unsigned char buff;
		Mediator::lockMutex();
		return m_model.getDistanceBackLeft();
		Mediator::unlockMutex();
		return buff;
	}

	unsigned char Mediator::getDistanceBackCenter()
	{
		unsigned char buff;
		Mediator::lockMutex();
		return m_model.getDistanceBackCenter();
		Mediator::unlockMutex();
		return buff;
	}

	unsigned char Mediator::getDistanceBackRight()
	{
		unsigned char buff;
		Mediator::lockMutex();
		return m_model.getDistanceBackRight();
		Mediator::unlockMutex();
		return buff;
	}

	//******** ADD ********//

	void Mediator::addPwmMotorBack(unsigned char val)
	{
		Mediator::lockMutex();
		m_model.addPwmMotorBack(val);
		Mediator::unlockMutex();
	}

	//** Steering Wheel
	void Mediator::addStateSteeringWheel(unsigned char val)
	{
		Mediator::lockMutex();
		m_model.addStateSteeringWheel(val);
		Mediator::unlockMutex();
	}

	//** Encoder
	void Mediator::addEncoderWheelBackLeft(float val)
	{
		Mediator::lockMutex();
		m_model.addEncoderWheelBackLeft(val);
		Mediator::unlockMutex();
	}

	void Mediator::addEncoderWheelBackRight(float val)
	{
		Mediator::lockMutex();
  	m_model.addEncoderWheelBackRight(val);
		Mediator::unlockMutex();
	}

	//** US Validity
	void Mediator::addValidityFrontLeft(unsigned char val)
	{
		Mediator::lockMutex();
  	m_model.addValidityFrontLeft(val);
		Mediator::unlockMutex();
	}

	void Mediator::addValidityFrontCenter(unsigned char val)
	{
		Mediator::lockMutex();
  	m_model.addValidityFrontCenter(val);
		Mediator::unlockMutex();
	}

	void Mediator::addValidityFrontRight(unsigned char val)
	{
		Mediator::lockMutex();
		m_model.addValidityFrontRight(val);
		Mediator::unlockMutex();
	}

	void Mediator::addValidityBackLeft(unsigned char val)
	{
		Mediator::lockMutex();
		m_model.addValidityBackLeft(val);
		Mediator::unlockMutex();
	}

	void Mediator::addValidityBackCenter(unsigned char val)
	{
		Mediator::lockMutex();
		m_model.addValidityBackCenter(val);
		Mediator::unlockMutex();
	}

	void Mediator::addValidityBackRight(unsigned char val)
	{
		Mediator::lockMutex();
		m_model.addValidityBackRight(val);
		Mediator::unlockMutex();
	}

	void Mediator::addDistanceFrontLeft(unsigned char val)
	{
		Mediator::lockMutex();
  	m_model.addDistanceFrontLeft(val);
		Mediator::unlockMutex();
	}

	void Mediator::addDistanceFrontCenter(unsigned char val)
	{
		Mediator::lockMutex();
		m_model.addDistanceFrontCenter(val);
		Mediator::unlockMutex();
	}

	void Mediator::addDistanceFrontRight(unsigned char val)
	{
		Mediator::lockMutex();
		m_model.addDistanceFrontRight(val);
		Mediator::unlockMutex();
	}

	void Mediator::addDistanceBackLeft(unsigned char val)
	{
		Mediator::lockMutex();
		m_model.addDistanceBackLeft(val);
		Mediator::unlockMutex();
	}

	void Mediator::addDistanceBackCenter(unsigned char val)
	{
		Mediator::lockMutex();
		m_model.addDistanceBackCenter(val);
		Mediator::unlockMutex();
	}

	void Mediator::addDistanceBackRight(unsigned char val)
	{
		Mediator::lockMutex();
		m_model.addDistanceBackRight(val);
		Mediator::unlockMutex();
	}

	void Mediator::printEncoder()
	{
		Mediator::lockMutex();
		m_model.printEncoder();
		Mediator::unlockMutex();
	}

	void Mediator::printModel()
	{
		Mediator::lockMutex();
		m_model.printModel();
		Mediator::unlockMutex();
	}

	//*** Thread
	void Mediator::lockMutex(void)
	{
		pthread_mutex_lock(&mutex_mediator);
	}

	void Mediator::unlockMutex(void)
	{
		pthread_mutex_unlock(&mutex_mediator);
	}
