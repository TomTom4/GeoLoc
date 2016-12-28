#ifndef DEF_MODEL
#define DEF_MODEL

class Model{

	public:
	//methodes
		Model();
	private:
	//attributs
		unsigned char m_pwm_motor_ar_d;
		unsigned char m_pwm_motor_ar_g;
		unsigned char m_cpt_dir;
		unsigned char m_encodeur_wheel_ar_d;
		unsigned char m_encodeur_wheel_ar_g;

		unsigned char m_us_id_av_d;
		unsigned char m_us_validity_av_d;
		unsigned char m_us_distance_av_d;

		unsigned char m_us_id_av_c;
		unsigned char m_us_validity_av_c;
		unsigned char m_us_distance_av_c;

		unsigned char m_us_id_av_g;
		unsigned char m_us_validity_av_g;
		unsigned char m_us_distance_av_g;

		unsigned char m_us_id_ar_d;
		unsigned char m_us_validity_ar_d;
		unsigned char m_us_distance_ar_d;

		unsigned char m_us_id_ar_c;
		unsigned char m_us_validity_ar_c;
		unsigned char m_us_distance_ar_c;

		unsigned char m_us_id_ar_g;
		unsigned char m_us_validity_ar_g;
		unsigned char m_us_distance_ar_g;


};

#endif
