#include "Mediator.h"

using namespace std;

	// setting s_instance which is a static attribut that needs to be setted
	Mediator *Mediator::s_instance = 0;
	// implementing Mediator constructor
	Mediator::Mediator(): m_model(){}
	
	Mediator* Mediator::instance(){
		if(Mediator::s_instance)
			Mediator::s_instance = new Mediator;
		return Mediator::s_instance;
	}
	//******** GET ********//

	//** PWM
	unsigned char Mediator::getPwmMotorBack()
	{
		 return m_model.getPwmMotorBack();
	}

	//** Steering Wheel
	unsigned char Mediator::getStateSteeringWheel()
	{
		return m_model.getStateSteeringWheel();
	}

	//** Encoder
	float Mediator::getEncoderWheelBackLeft()
	{
		return m_model.getEncoderWheelBackLeft();
	}

	float Mediator::getEncoderWheelBackRight()
	{
		return m_model.getEncoderWheelBackRight();
	}

	//** US Validity
	unsigned char Mediator::getValidityFrontLeft()
	{
		return m_model.getValidityFrontLeft();
	}
	
	unsigned char Mediator::getValidityFrontCenter()
	{
		return m_model.getValidityFrontCenter();
	}

	unsigned char Mediator::getValidityFrontRight()
	{
		return m_model.getValidityFrontRight();
	}

	unsigned char Mediator::getValidityBackLeft()
	{
		return m_model.getValidityBackLeft();
	}

	unsigned char Mediator::getValidityBackCenter()
	{
		return m_model.getValidityBackCenter();
	}

	unsigned char Mediator::getValidityBackRight()
	{
		return m_model.getValidityBackRight();

	}

	//** Distance
	unsigned char Mediator::getDistanceFrontLeft()
	{
  		return m_model.getDistanceFrontLeft();

	}

	unsigned char Mediator::getDistanceFrontCenter()
	{
		return m_model.getDistanceFrontCenter();
	}

	unsigned char Mediator::getDistanceFrontRight()
	{
		return m_model.getDistanceFrontRight();
	}

	unsigned char Mediator::getDistanceBackLeft()
	{
		return m_model.getDistanceBackLeft();

	}

	unsigned char Mediator::getDistanceBackCenter()
	{
		return m_model.getDistanceBackCenter();
	}

	unsigned char Mediator::getDistanceBackRight()
	{
		return m_model.getDistanceBackRight();

	}

	//******** ADD ********//

	void Mediator::addPwmMotorBack(unsigned char val)
	{
		  m_model.addPwmMotorBack(val);
	}

	//** Steering Wheel
	void Mediator::addStateSteeringWheel(unsigned char val)
	{
		m_model.addStateSteeringWheel(val);
	}

	//** Encoder
	void Mediator::addEncoderWheelBackLeft(float val)
	{
		m_model.addEncoderWheelBackLeft(val);
	}

	void Mediator::addEncoderWheelBackRight(float val)
	{
  		m_model.addEncoderWheelBackRight(val);

	}

	//** US Validity
	void Mediator::addValidityFrontLeft(unsigned char val)
	{
  		m_model.addValidityFrontLeft(val);

	}

	void Mediator::addValidityFrontCenter(unsigned char val)
	{
  		m_model.addValidityFrontCenter(val);

	}

	void Mediator::addValidityFrontRight(unsigned char val)
	{
		m_model.addValidityFrontRight(val);

	}

	void Mediator::addValidityBackLeft(unsigned char val)
	{
		m_model.addValidityBackLeft(val);

	}

	void Mediator::addValidityBackCenter(unsigned char val)
	{
		m_model.addValidityBackCenter(val);
	}

	void Mediator::addValidityBackRight(unsigned char val)
	{
		m_model.addValidityBackRight(val);

	}

	void Mediator::addDistanceFrontLeft(unsigned char val)
	{
  		m_model.addDistanceFrontLeft(val);

	}

	void Mediator::addDistanceFrontCenter(unsigned char val)
	{
		m_model.addDistanceFrontCenter(val);

	}

	void Mediator::addDistanceFrontRight(unsigned char val)
	{
		m_model.addDistanceFrontRight(val);

	}

	void Mediator::addDistanceBackLeft(unsigned char val)
	{
		m_model.addDistanceBackLeft(val);

	}

	void Mediator::addDistanceBackCenter(unsigned char val)
	{
		m_model.addDistanceBackCenter(val);

	}

	void Mediator::addDistanceBackRight(unsigned char val)
	{
		m_model.addDistanceBackRight(val);

	}

	void Mediator::printEncoder()
	{
		m_model.printEncoder();
	}

	void Mediator::printModel()
	{
		m_model.printModel();
	}
	
