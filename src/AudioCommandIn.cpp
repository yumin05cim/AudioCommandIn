// -*- C++ -*-
/*!
 * @file  AudioCommandIn.cpp
 * @brief Audio Command In Component
 * @date $Date$
 *
 * $Id$
 */

#include "AudioCommandIn.h"

// Module specification
// <rtc-template block="module_spec">
static const char* audiocommandin_spec[] =
  {
    "implementation_id", "AudioCommandIn",
    "type_name",         "AudioCommandIn",
    "description",       "Audio Command In Component",
    "version",           "1.0",
    "vendor",            "yumin05cim",
    "category",          "Tes",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
AudioCommandIn::AudioCommandIn(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_commandInIn("commandIn", m_commandIn),
    m_targetVelocityOut("targetVelocity", m_targetVelocity)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
AudioCommandIn::~AudioCommandIn()
{
}



RTC::ReturnCode_t AudioCommandIn::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("commandIn", m_commandInIn);
  
  // Set OutPort buffer
  addOutPort("targetVelocity", m_targetVelocityOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t AudioCommandIn::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AudioCommandIn::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AudioCommandIn::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t AudioCommandIn::onActivated(RTC::UniqueId ec_id)
{
	m_Mode = STOP_MODE;

  return RTC::RTC_OK;
}


RTC::ReturnCode_t AudioCommandIn::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AudioCommandIn::onExecute(RTC::UniqueId ec_id)
{
	if(this->m_commandInIn.isNew()) {
		m_commandInIn.read();

		std::string command = m_commandIn.data;
		std::cout << command << std::endl;

		const char* go    = "go"; 
		const char* stop  = "stop";
		const char* back  = "back"; 

		if(m_Mode == STOP_MODE){
			std::cout << "now: stop mode (" << m_Mode << ")" << std::endl;

			if(command.compare(go) == 0){
				m_Mode = FORWARD_MODE;
				std::cout << "current mode is " << m_Mode << std::endl;
			}else if(command.compare(back) == 0){
				m_Mode = BACKWARD_MODE;
				std::cout << "current mode is " << m_Mode << std::endl;
			}
		}
		if(m_Mode == FORWARD_MODE){
			std::cout << "now: forward mode (" << m_Mode << ")" << std::endl;

			if(command.compare(stop) == 0){
				m_targetVelocity.data.vx = 0;
				m_Mode = STOP_MODE;
			}else if(command.compare(back) == 0){
				m_Mode = BACKWARD_MODE;
				std::cout << "current mode is " << m_Mode << std::endl;
			}
		}
		if(m_Mode == BACKWARD_MODE){
			std::cout << "now: backward mode (" << m_Mode << ")" << std::endl;

			if(command.compare(stop) == 0){
				m_targetVelocity.data.vx = 0;
				m_Mode = STOP_MODE;
			}else if(command.compare(go) == 0){
				m_Mode = FORWARD_MODE;
				std::cout << "current mode is " << m_Mode << std::endl;
			}
		}
	}

	switch(m_Mode){
		case STOP_MODE:
			m_targetVelocity.data.vx = 0;
			m_targetVelocity.data.vy = 0;
			m_targetVelocity.data.va = 0;
			break;
		case FORWARD_MODE:
			m_targetVelocity.data.vx = 0.1;
			m_targetVelocity.data.vy = 0;
			m_targetVelocity.data.va = 0;
			break;
		case BACKWARD_MODE:
			m_targetVelocity.data.vx = -0.1;
			m_targetVelocity.data.vy = 0;
			m_targetVelocity.data.va = 0;
			break;
		default:
			std::cout << "Error";
			return RTC::RTC_ERROR;
	}

	std::cout << "current mode is " << m_Mode << std::endl;

	std::cout <<  "vx = " << m_targetVelocity.data.vx << ", ";
	std::cout <<  "vy = " << m_targetVelocity.data.vy << ", ";
	std::cout <<  "va = " << m_targetVelocity.data.va << std::endl;

	m_targetVelocityOut.write();

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t AudioCommandIn::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AudioCommandIn::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AudioCommandIn::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AudioCommandIn::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AudioCommandIn::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void AudioCommandInInit(RTC::Manager* manager)
  {
    coil::Properties profile(audiocommandin_spec);
    manager->registerFactory(profile,
                             RTC::Create<AudioCommandIn>,
                             RTC::Delete<AudioCommandIn>);
  }
  
};


