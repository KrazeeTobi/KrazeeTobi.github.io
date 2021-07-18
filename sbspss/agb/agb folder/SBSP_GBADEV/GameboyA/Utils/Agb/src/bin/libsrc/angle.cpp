//======================================================
//    angle.cpp
//    Class for AGB angle
//
//    Copyright (C) 1999-2000 NINTENDO Co.,Ltd.
//======================================================

#include <math.h>
#include <agbtypes.h>
#include <angle.h>

__MAGBX__START

const double Angle::m_rad2agb = 128.0f / _AGB_ANGLE_PIE;
const double Angle::m_agb2rad = _AGB_ANGLE_PIE / 128.0f;

u8 Angle::Radian2AGB(double _angle)
{
	double	tmp = _angle;
	tmp *= m_rad2agb;
	int	iRet = (int)tmp;
	while( iRet < 0 ) iRet += 256;
	while( iRet >= 256 ) iRet -= 256;
	return (u8)iRet;
}

double Angle::AGB2Radian(u8 _angle)
{
	int angle = (int)_angle;
	if( angle >= 128 ) angle -= 256;
	double	tmp = (double)angle;
	tmp *= m_agb2rad;
	return tmp;
}

Angle::Angle() : m_angle(0.0f)
{
}

Angle::Angle(u8 _angle)
{
	Set(_angle);
}

Angle::Angle(double _angle) : m_angle(0.0f)
{
}

Angle::Angle(const Angle& _X) : m_angle(((Angle&)_X).Get())
{
}

Angle::Angle(double _y,double _x)
{
	m_angle = atan2(_y,_x);
}

Angle::~Angle()
{
}

double Angle::sin(void)
{
	return ::sin(m_angle);
}

double Angle::cos(void)
{
	return ::cos(m_angle);
}

u8 Angle::GetAGB(void)
{
	return Radian2AGB(m_angle);
}

double Angle::Get(void)
{
	return m_angle;
}

void Angle::Set(double _angle)
{
	m_angle = _angle;
}

void Angle::Set(u8 _angle)
{
	m_angle = AGB2Radian(_angle);
}

void Angle::Set(double _y,double _x)
{
	m_angle = atan2(_y,_x);
}

Angle& Angle::operator=(const Angle& _X)
{
	if( &_X != this )
	{
		m_angle = ((Angle&)_X).Get();
	}
	return *this;
}

Angle& Angle::operator=(u8 _angle)
{
	Set(_angle);
	return *this;
}

Angle& Angle::operator=(double _angle)
{
	Set(_angle);
	return *this;
}

__MAGBX__END

//
//