#include "Model.h"

using namespace std;
	//Add your methodes over here 
	Model::Model(){
		m_pwm_motor_ar_d = 0;
		m_pwm_motor_ar_g = 0;
		m_cpt_dir = 0;
		m_encodeur_wheel_ar_d = 0;
		m_encodeur_wheel_ar_g = 0;

		m_us_id_av_d = 0;
		m_us_validity_av_d = 0;
		m_us_distance_av_d = 0;

		m_us_id_av_c = 0;
		m_us_validity_av_c = 0;
		m_us_distance_av_c = 0;

		m_us_id_av_g = 0;
		m_us_validity_av_g = 0;
		m_us_distance_av_g = 0;

		m_us_id_ar_d = 0;
		m_us_validity_ar_d = 0;
		m_us_distance_ar_d = 0;

		m_us_id_ar_c = 0;
		m_us_validity_ar_c = 0;
		m_us_distance_ar_c = 0;

		m_us_id_ar_g = 0;
		m_us_validity_ar_g = 0;
		m_us_distance_ar_g = 0;

}
