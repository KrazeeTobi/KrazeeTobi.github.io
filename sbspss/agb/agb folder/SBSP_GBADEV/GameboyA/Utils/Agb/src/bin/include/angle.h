//======================================================
//    angle.h
//    Class for AGB angle 
//
//    Copyright (C) 1999-2000,NINTENDO Co.,Ltd.
//======================================================

#ifndef	_AGB_ANGLE_
#define	_AGB_ANGLE_

#define	_AGB_ANGLE_PIE	(3.14159265359f)

#include <agbtypes.h>

__MAGBX__START

class Angle
{
protected :

	double	m_angle;

//	static const double m_pie;
	static const double m_rad2agb;
	static const double m_agb2rad;

	u8	Radian2AGB(double _angle);
	double	AGB2Radian(u8 _angle);

public :
	Angle();
	Angle(u8 _angle);
	Angle(double _angle);
	Angle(const Angle& _X);
	Angle(double _y,double _x);

	~Angle();

	double	sin(void);
	double	cos(void);
	double	tan(void);

	u8	GetAGB(void);
	double	Get(void);

	void Set(u8 _angle);
	void Set(double _angle);
	void Set(double _y,double _x);

	Angle& operator=(const Angle& _X);
	Angle& operator=(u8 _angle);
	Angle& operator=(double _angle);

	bool IsInAngle(const Angle& _Prev,const Angle& _Next);
};

__MAGBX__END

#endif	//  _AGB_ANGLE_

//
//