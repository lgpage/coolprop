
#ifndef CPSTATE_H
#define CPSTATE_H

#include <iostream>
#include "FluidClass.h"
#include "CoolProp.h"
#include "TTSE.h"

bool match_pair(long iI1, long iI2, long I1, long I2);
void sort_pair(long *iInput1, double *Value1, long *iInput2, double *Value2, long I1, long I2);

/*!
A class that contains the magic to cache a value.

Includes an "=" assignment operator and casting to boolean
so you can do something like::

double CoolPropStateClassSI::d3phir_dTau3(double tau, double delta){
	if (cache.d3phir_dTau3) 
	{
		return cache.d3phir_dTau3;
	}
	else 
	{
		cache.d3phir_dTau3 = pFluid->d3phir_dTau3(tau,delta);
		return cache.d3phir_dTau3;
	}
};

*/
class CachedElement
{
private:
	bool is_cached;
	double value;
public:
	/// Default constructor
	CachedElement(){this->clear();};
	/// Assignment operator - sets the value and sets the flag
	void operator=( const double& value){this->value = value; this->is_cached = true;};
	/// Cast to boolean, for checking if cached
	operator bool() const {return is_cached;};
	/// Cast to double, for returning value
	operator double() const {return value;};
	/// Clear the flag and the value
	void clear(){is_cached = false; this->value = _HUGE;};
};

class StateCache
{
public:
	StateCache(){};
	CachedElement phi0, dphi0_dTau, dphi0_dDelta, d2phi0_dTau2, d2phi0_dDelta_dTau, 
		d2phi0_dDelta2, d3phi0_dTau3, d3phi0_dDelta_dTau2, d3phi0_dDelta2_dTau, 
		d3phi0_dDelta3, phir, dphir_dTau, dphir_dDelta, d2phir_dTau2, d2phir_dDelta_dTau, 
		d2phir_dDelta2, d3phir_dTau3, d3phir_dDelta_dTau2, d3phir_dDelta2_dTau, 
		d3phir_dDelta3;
	void clear(){phi0.clear();
				dphi0_dTau.clear(); 
				dphi0_dDelta.clear(); 
				d2phi0_dTau2.clear(); 
				d2phi0_dDelta_dTau.clear(); 
				d2phi0_dDelta2.clear(); 
				d3phi0_dTau3.clear(); 
				d3phi0_dDelta_dTau2.clear(); 
				d3phi0_dDelta2_dTau.clear(); 
				d3phi0_dDelta3.clear(); 
				phir.clear(); 
				dphir_dTau.clear(); 
				dphir_dDelta.clear(); 
				d2phir_dTau2.clear(); 
				d2phir_dDelta_dTau.clear(); 
				d2phir_dDelta2.clear(); 
				d3phir_dTau3.clear(); 
				d3phir_dDelta_dTau2.clear(); 
				d3phir_dDelta2_dTau.clear(); 
				d3phir_dDelta3.clear();
			};
};

class CoolPropStateClassSI
{
protected:

	StateCache cache;	

	std::string _Fluid;
	
	bool SaturatedL,SaturatedV,_noSatLSatV;

	// Saturation values
	double rhosatL, rhosatV, psatL, psatV, TsatL, TsatV;

	// Pointers to the Liquid and Vapor classes
	CoolPropStateClassSI *SatL, *SatV;

	void add_saturation_states(void);
	void remove_saturation_states(void);

	// To be used to update internal variables if you know that your parameters are T,Q or P,Q
	void update_twophase(long iInput1, double Value1, long iInput2, double Value2);

	// To be used to update internal variables if you know that your parameters are T,D
	void update_Trho(long iInput1, double Value1, long iInput2, double Value2);

	// To be used to update internal variables if you know that your parameters are T,P
	void update_Tp(long iInput1, double Value1, long iInput2, double Value2);

	/// To be used to update internal variables if you know that your parameters are P,H
	/// If T0 and rho0 are included, start at this value for the solution
	void update_ph(long iInput1, double Value1, long iInput2, double Value2, double T0 = -1, double rho0 = -1);

	// To be used to update internal variables if you know that your parameters are P,S
	void update_ps(long iInput1, double Value1, long iInput2, double Value2);

	// To be used to update internal variables if you know that your parameters are P,D
	void update_prho(long iInput1, double Value1, long iInput2, double Value2);

	// To be used to update internal variables if you know that your parameters are H,S
	void update_hs(long iInput1, double Value1, long iInput2, double Value2);

	// Update using the TTSE lookup tables
	void update_TTSE_LUT(long iInput1, double Value1, long iInput2, double Value2);

	// Check whether the quality corresponds to saturated liquid or vapor
	void check_saturated_quality(double Q);

	/// Check whether within the TTSE range
	bool within_TTSE_range(long iInput1, double Value1, long iInput2, double Value2);

public:
	Fluid * pFluid;

	/// Temporarily set a flag to tell that the next call to update should be special 
	/// cased as though it is single-phase even if it isn't
	bool flag_SinglePhase;

	/// Temporarily set a flag to tell that the next call to update should be special 
	/// cased as though it is two-phase even if it isn't
	bool flag_TwoPhase;

	// Bulk values
	double _rho,_T,_p,_Q,_h,_s,_logp, _logrho, tau, delta;

	// Phase flags
	bool TwoPhase, SinglePhase, s_cached, h_cached;
	
	// Default Constructor
	CoolPropStateClassSI(){SatL = NULL; SatV = NULL;};

	// Constructor with fluid name
	CoolPropStateClassSI(std::string FluidName);

	// Constructor with fluid pointer
	CoolPropStateClassSI(Fluid *pFluid);

	// Destructor to clear SatL and SatV
	~CoolPropStateClassSI();

	/// Saturation temperature
	double Tsat(double Q);

	double superheat(void);

	/// Get the name of the fluid
	std::string get_name(void){return pFluid->get_name();};

	/// Stop it from adding the SatL and SatV class pointers
	void no_SatLSatV(void){_noSatLSatV = true;};

	// Property updater
	// Uses the indices in CoolProp for the input parameters
	void update(long iInput1, double Value1, long iInput2, double Value2);

	// Returns an output based on the key provided
	// where iInput is one of iT,iP,iH,iS,....
	double keyed_output(long iInput);

	// Property accessors for saturation parameters directly
	// These all are calculated every time if the state is saturated or two-phase
	double rhoL(void){return rhosatL;};
	double rhoV(void){return rhosatV;};
	double pL(void){return psatL;};
	double pV(void){return psatV;};
	double TL(void){return TsatL;};
	double TV(void){return TsatV;};
	// Derived parameters for the saturation states
	double hL(void);
	double hV(void);
	double sL(void);
	double sV(void);
	double cpL(void);
	double cpV(void);
	double viscL(void);
	double viscV(void);
	double condL(void);
	double condV(void);

	// The phase as an integer flag
	long phase(void);

	// Bulk properties accessors - temperature and density are directly calculated every time
	// All other parameters are calculated on an as-needed basis
	// If single-phase, just plug into the EOS, otherwise need to do two-phase analysis
	double T(void){return _T;};
	double rho(void){return _rho;};
	double p(void){return _p;};
	double Q(void){return _Q;};
	double h(void);
	double s(void);
	double cp(void);
	double cv(void);
	double speed_sound(void);
	double isothermal_compressibility(void);
	double isobaric_expansion_coefficient(void);
	double drhodh_constp(void);
	double drhodp_consth(void);
	/// A smoothed version of the derivative using a spline curve in the region of x=0 to x=xend
	double drhodh_constp_smoothed(double xend);
	/// A smoothed version of the derivative using a spline curve in the region of x=0 to x=xend
	double drhodp_consth_smoothed(double xend);
	/// Density corresponding to the smoothed derivatives in the region of x=0 to x=xend
	void rho_smoothed(double xend, double *rho_spline, double *dsplinedh, double *dsplinedp);

	double viscosity(void);
	double conductivity(void);

	double surface_tension(void);

	// ----------------------------------------	
	// TTSE LUT things
	// ----------------------------------------

	/// Enable the TTSE
	void enable_TTSE_LUT(void);
	/// Check if TTSE is enabled
	bool isenabled_TTSE_LUT(void);
	/// Disable the TTSE
	void disable_TTSE_LUT(void);
	/// Enable the writing of TTSE tables to file
	void enable_TTSE_LUT_writing(void);
	/// Check if the writing of TTSE tables to file is enabled
	bool isenabled_TTSE_LUT_writing(void);
	/// Disable the writing of TTSE tables to file
	void disable_TTSE_LUT_writing(void);
	/// Over-ride the default size of both of the saturation LUT
	void set_TTSESat_LUT_size(int N);
	/// Over-ride the default size of the single-phase LUT
	void set_TTSESinglePhase_LUT_size(int Np, int Nh);
	/// Over-ride the default range of the single-phase LUT
	void set_TTSESinglePhase_LUT_range(double hmin, double hmax, double pmin, double pmax);
	/// Get the current range of the single-phase LUT
	void get_TTSESinglePhase_LUT_range(double *hmin, double *hmax, double *pmin, double *pmax);

	/// Evaluate the B term from TTSE method
	double B_TTSE(double _p, double _h);
	/// Evaluate the D term from TTSE method
	double D_TTSE(double _p, double _h);
	/// Get the ratio directly which is just a bit faster
	double B_over_D_TTSE(double _p, double _h);

	/// Interpolate within the TTSE LUT
	double interpolate_in_TTSE_LUT(long iParam, long iInput1, double Input1, long iInput2, double Input2);

	// ----------------------------------------	
	// Derivatives of properties
	// ----------------------------------------

	double dvdp_constT(void);
	double dvdT_constp(void);

	double drhodT_constp(void);
	double drhodp_constT(void);
	double d2rhodp2_constT(void);
	double d2rhodTdp(void);
	double d2rhodT2_constp(void);
	double d2rhodhdQ(void);
	double d2rhodpdQ(void);
	double d2rhodhdp(void);
	double d2rhodh2_constp(void);
	
	double dpdrho_constT(void);
	double dpdrho_consth(void);
	double dpdT_constrho(void);
	double dpdT_consth(void);
	double d2pdrho2_constT(void);
	double d2pdrhodT(void);
	double d2pdT2_constrho(void);

	double dhdrho_constT(void);
	double dhdrho_constp(void);
	double dhdT_constrho(void);
	double dhdT_constp(void);
	double dhdp_constT(void);
	double d2hdrho2_constT(void);
	double d2hdrhodT(void);
	double d2hdT2_constrho(void);
	double d2hdT2_constp(void);
	double d2hdp2_constT(void);
	double d2hdTdp(void);

	double dsdrho_constT(void);
	double dsdT_constrho(void);
	double dsdrho_constp(void);
	double dsdT_constp(void);
	double dsdp_constT(void);
	double d2sdrho2_constT(void);
	double d2sdrhodT(void);
	double d2sdT2_constrho(void);
	double d2sdT2_constp(void);
	double d2sdp2_constT(void);
	double d2sdTdp(void);

	// ----------------------------------------	
	// Derivatives along the saturation curve
	// ----------------------------------------
	
	/// Derivative of temperature w.r.t. pressure along saturation curve
	double dTdp_along_sat(void);
	/// Second derivative of temperature w.r.t. pressure along saturation curve
	double d2Tdp2_along_sat(void);
	/// Partial derivative w.r.t. pressure of dTdp along saturation curve
	double ddp_dTdp_along_sat(void);
	/// Partial derivative w.r.t. temperature of dTdp along saturation curve
	double ddT_dTdp_along_sat(void);

	double dhdp_along_sat_vapor(void);
	double dhdp_along_sat_liquid(void);
	double d2hdp2_along_sat_vapor(void);
	double d2hdp2_along_sat_liquid(void);

	double dsdp_along_sat_vapor(void);
	double dsdp_along_sat_liquid(void);
	double d2sdp2_along_sat_vapor(void);
	double d2sdp2_along_sat_liquid(void);

	double drhodp_along_sat_vapor(void);
	double drhodp_along_sat_liquid(void);
	double d2rhodp2_along_sat_vapor(void);
	double d2rhodp2_along_sat_liquid(void);

	double drhodT_along_sat_vapor(void);
	double drhodT_along_sat_liquid(void);

	// ----------------------------------------	
	// Helmholtz Energy Derivatives
	// ----------------------------------------

	double phi0(double tau, double delta);
	double dphi0_dDelta(double tau, double delta);
	double dphi0_dTau(double tau, double delta);
	double d2phi0_dDelta2(double tau, double delta);
	double d2phi0_dDelta_dTau(double tau, double delta);
	double d2phi0_dTau2(double tau, double delta);
	double d3phi0_dDelta3(double tau, double delta);
	double d3phi0_dDelta2_dTau(double tau, double delta);
	double d3phi0_dDelta_dTau2(double tau, double delta);
	double d3phi0_dTau3(double tau, double delta);

	double phir(double tau, double delta);
	double dphir_dDelta(double tau, double delta);
	double dphir_dTau(double tau, double delta);
	double d2phir_dDelta2(double tau, double delta);
	double d2phir_dDelta_dTau(double tau, double delta);
	double d2phir_dTau2(double tau, double delta);
	double d3phir_dDelta3(double tau, double delta);
	double d3phir_dDelta2_dTau(double tau, double delta);
	double d3phir_dDelta_dTau2(double tau, double delta);
	double d3phir_dTau3(double tau, double delta);
};



























class CoolPropStateClass : public CoolPropStateClassSI
{

public:

	//// Default Constructor
	CoolPropStateClass(); 

	//// Constructor with fluid name
	CoolPropStateClass(std::string FluidName); 

	//// Constructor with fluid pointer
	CoolPropStateClass(Fluid *pFluid); 

	//// Property updater
	//// Uses the indices in CoolProp for the input parameters
	void update(long iInput1, double Value1, long iInput2, double Value2);

	/// Returns an output based on the key provided where iInput is one of iT,iP,iH,iS,....
	double keyed_output(long iInput){return convert_from_SI_to_unit_system(iInput,CoolPropStateClassSI::keyed_output(iInput),get_standard_unit_system());};

	//// Property accessors for saturation parameters directly
	//// These all are calculated every time if the state is saturated or two-phase
	double pL(void){return convert_from_SI_to_unit_system(iP,psatL,get_standard_unit_system());};
	double pV(void){return convert_from_SI_to_unit_system(iP,psatV,get_standard_unit_system());};
	double TL(void){return convert_from_SI_to_unit_system(iT,TsatL,get_standard_unit_system());};
	double TV(void){return convert_from_SI_to_unit_system(iT,TsatV,get_standard_unit_system());};
	//// Derived parameters for the saturation states
	double hL(void){return convert_from_SI_to_unit_system(iH,CoolPropStateClassSI::hL(),get_standard_unit_system());};
	double hV(void){return convert_from_SI_to_unit_system(iH,CoolPropStateClassSI::hV(),get_standard_unit_system());};
	double sL(void){return convert_from_SI_to_unit_system(iS,CoolPropStateClassSI::sL(),get_standard_unit_system());};
	double sV(void){return convert_from_SI_to_unit_system(iS,CoolPropStateClassSI::sV(),get_standard_unit_system());};
	double cpL(void){return convert_from_SI_to_unit_system(iC,CoolPropStateClassSI::cpL(),get_standard_unit_system());};
	double cpV(void){return convert_from_SI_to_unit_system(iC,CoolPropStateClassSI::cpV(),get_standard_unit_system());};
	double viscL(void){return convert_from_SI_to_unit_system(iV,CoolPropStateClassSI::viscL(),get_standard_unit_system());};
	double viscV(void){return convert_from_SI_to_unit_system(iV,CoolPropStateClassSI::viscV(),get_standard_unit_system());};
	double condL(void){return convert_from_SI_to_unit_system(iL,CoolPropStateClassSI::condL(),get_standard_unit_system());};
	double condV(void){return convert_from_SI_to_unit_system(iL,CoolPropStateClassSI::condV(),get_standard_unit_system());};

	/// Pressure in kPa
	double p(void){return convert_from_SI_to_unit_system(iP,CoolPropStateClassSI::p(),get_standard_unit_system());};
	/// Enthalpy in kJ/kg
	double h(void){return convert_from_SI_to_unit_system(iH,CoolPropStateClassSI::h(),get_standard_unit_system());};
	/// Entropy in kJ/kg/K
	double s(void){return convert_from_SI_to_unit_system(iS,CoolPropStateClassSI::s(),get_standard_unit_system());};
	/// Constant pressure specific heat in kJ/kg/K
	double cp(void){return convert_from_SI_to_unit_system(iC,CoolPropStateClassSI::cp(),get_standard_unit_system());};
	/// Constant volume specific heat in kJ/kg/K
	double cv(void){return convert_from_SI_to_unit_system(iO,CoolPropStateClassSI::cv(),get_standard_unit_system());};
	/// Thermal conductivity in kJ/kg/K
	double conductivity(void){return convert_from_SI_to_unit_system(iL,CoolPropStateClassSI::conductivity(),get_standard_unit_system());};

	double isothermal_compressibility(void){return CoolPropStateClassSI::isothermal_compressibility()*conversion_factor("1/P");};
	double isobaric_expansion_coefficient(void){return CoolPropStateClassSI::isobaric_expansion_coefficient()*conversion_factor("D/T");};
	double drhodh_constp(void){return CoolPropStateClassSI::drhodh_constp()*conversion_factor("D/H");};
	double drhodp_consth(void){return CoolPropStateClassSI::drhodp_consth()*conversion_factor("D/P");};

	///// A smoothed version of the derivative using a spline curve in the region of x=0 to x=xend
	double drhodh_constp_smoothed(double xend){return CoolPropStateClassSI::drhodh_constp_smoothed(xend)*conversion_factor("D/H");};
	/// A smoothed version of the derivative using a spline curve in the region of x=0 to x=xend
	double drhodp_consth_smoothed(double xend){return CoolPropStateClassSI::drhodp_consth_smoothed(xend)*conversion_factor("D/P");};

	//// ----------------------------------------	
	//// TTSE LUT things
	//// ----------------------------------------

	/// Over-ride the default range of the single-phase LUT
	/// Inlet parameters in kJ/kg and kPa
	void set_TTSESinglePhase_LUT_range(double hmin, double hmax, double pmin, double pmax)
	{
		double _hmin = hmin / conversion_factor("H"); // [J/kg]
		double _hmax = hmax / conversion_factor("H"); // [J/kg]
		double _pmin = pmin / conversion_factor("P"); // [kPa]
		double _pmax = pmax / conversion_factor("P"); // [kPa]
		CoolPropStateClassSI::set_TTSESinglePhase_LUT_range(_hmin,_hmax,_pmin,_pmax);
	};
	/// Get the current range of the single-phase LUT
	void get_TTSESinglePhase_LUT_range(double *hmin, double *hmax, double *pmin, double *pmax)
	{
		// Call the base class function
		CoolPropStateClassSI::get_TTSESinglePhase_LUT_range(hmin,hmax,pmin,pmax);
		
		// Unit conversions
		*hmin *= conversion_factor("H"); // [kJ/kg]
		*hmax *= conversion_factor("H"); // [kJ/kg]
		*pmin *= conversion_factor("P"); // [kPa]
		*pmax *= conversion_factor("P"); // [kPa]
	};

	///// Interpolate within the TTSE LUT
	//double interpolate_in_TTSE_LUT(long iParam, long iInput1, double Input1, long iInput2, double Input2);

	//// ----------------------------------------	
	//// Derivatives of properties
	//// ----------------------------------------

	double dvdp_constT(void){return CoolPropStateClassSI::dvdp_constT()*conversion_factor("1/D/P");};
	double dvdT_constp(void){return CoolPropStateClassSI::dvdT_constp()*conversion_factor("1/D/T");};

	double drhodT_constp(void){return CoolPropStateClassSI::drhodT_constp()*conversion_factor("D/T");};
	double drhodp_constT(void){return CoolPropStateClassSI::drhodp_constT()*conversion_factor("D/P");};
	double d2rhodp2_constT(void){return CoolPropStateClassSI::d2rhodp2_constT()*conversion_factor("D*D/P/P");};
	double d2rhodTdp(void){return CoolPropStateClassSI::d2rhodTdp()*conversion_factor("D*D/T/P");};
	double d2rhodT2_constp(void){return CoolPropStateClassSI::d2rhodT2_constp()*conversion_factor("D*D/T/T");};
	double d2rhodhdQ(void){return CoolPropStateClassSI::d2rhodhdQ()*conversion_factor("D*D/H/Q");};
	double d2rhodpdQ(void){return CoolPropStateClassSI::d2rhodpdQ()*conversion_factor("D*D/P/Q");};
	double d2rhodhdp(void){return CoolPropStateClassSI::d2rhodhdp()*conversion_factor("D*D/H/P");};
	double d2rhodh2_constp(void){return CoolPropStateClassSI::d2rhodh2_constp()*conversion_factor("D*D/H/H");};
	
	double dpdrho_constT(void){return CoolPropStateClassSI::dpdrho_constT()*conversion_factor("P/D");};
	double dpdrho_consth(void){return CoolPropStateClassSI::dpdrho_consth()*conversion_factor("P/D");};
	double dpdT_constrho(void){return CoolPropStateClassSI::dpdT_constrho()*conversion_factor("P/T");};
	double dpdT_consth(void){return CoolPropStateClassSI::dpdT_consth()*conversion_factor("P/T");};
	double d2pdrho2_constT(void){return CoolPropStateClassSI::d2pdrho2_constT()*conversion_factor("P/D");};
	double d2pdrhodT(void){return CoolPropStateClassSI::d2pdrhodT()*conversion_factor("P*P/D/T");};
	double d2pdT2_constrho(void){return CoolPropStateClassSI::d2pdT2_constrho()*conversion_factor("P*P/T/T");};

	double dhdrho_constT(void){return CoolPropStateClassSI::dhdrho_constT()*conversion_factor("H/D");};
	double dhdrho_constp(void){return CoolPropStateClassSI::dhdrho_constp()*conversion_factor("H/D");};
	double dhdT_constrho(void){return CoolPropStateClassSI::dhdT_constrho()*conversion_factor("H/T");};
	double dhdT_constp(void){return CoolPropStateClassSI::dhdT_constp()*conversion_factor("H/T");};
	double dhdp_constT(void){return CoolPropStateClassSI::dhdp_constT()*conversion_factor("H/P");};
	double d2hdrho2_constT(void){return CoolPropStateClassSI::d2hdrho2_constT()*conversion_factor("H*H/D/D");};
	double d2hdrhodT(void){return CoolPropStateClassSI::d2hdrhodT()*conversion_factor("H*H/D/T");};
	double d2hdT2_constrho(void){return CoolPropStateClassSI::d2hdT2_constrho()*conversion_factor("H*H/T/T");};
	double d2hdT2_constp(void){return CoolPropStateClassSI::d2hdT2_constp()*conversion_factor("H*H/T/T");};
	double d2hdp2_constT(void){return CoolPropStateClassSI::d2hdp2_constT()*conversion_factor("H*H/P/P");};
	double d2hdTdp(void){return CoolPropStateClassSI::d2hdTdp()*conversion_factor("H*H/T/P");};

	double dsdrho_constT(void){return CoolPropStateClassSI::dTdp_along_sat()*conversion_factor("S/D");};
	double dsdT_constrho(void){return CoolPropStateClassSI::dTdp_along_sat()*conversion_factor("S/T");};
	double dsdrho_constp(void){return CoolPropStateClassSI::dTdp_along_sat()*conversion_factor("S/D");};
	double dsdT_constp(void){return CoolPropStateClassSI::dTdp_along_sat()*conversion_factor("S/T");};
	double dsdp_constT(void){return CoolPropStateClassSI::dTdp_along_sat()*conversion_factor("S/P");};
	double d2sdrho2_constT(void){return CoolPropStateClassSI::dTdp_along_sat()*conversion_factor("S*S/D/D");};
	double d2sdrhodT(void){return CoolPropStateClassSI::dTdp_along_sat()*conversion_factor("S*S/D/T");};
	double d2sdT2_constrho(void){return CoolPropStateClassSI::dTdp_along_sat()*conversion_factor("S*S/T/T");};
	double d2sdT2_constp(void){return CoolPropStateClassSI::dTdp_along_sat()*conversion_factor("S*S/T/T");};
	double d2sdp2_constT(void){return CoolPropStateClassSI::dTdp_along_sat()*conversion_factor("S*S/P/P");};
	double d2sdTdp(void){return CoolPropStateClassSI::dTdp_along_sat()*conversion_factor("S*S/T/P");};

	//// ----------------------------------------	
	//// Derivatives along the saturation curve
	//// ----------------------------------------
	//
	/// Derivative of temperature w.r.t. pressure along saturation curve
	double dTdp_along_sat(void){return CoolPropStateClassSI::dTdp_along_sat()*conversion_factor("T/P");};
	///// Second derivative of temperature w.r.t. pressure along saturation curve
	double d2Tdp2_along_sat(void){return CoolPropStateClassSI::d2Tdp2_along_sat()*conversion_factor("T*T/P/P");};

	double dhdp_along_sat_vapor(void){return CoolPropStateClassSI::dhdp_along_sat_vapor()*conversion_factor("H/P");};
	double dhdp_along_sat_liquid(void){return CoolPropStateClassSI::dhdp_along_sat_liquid()*conversion_factor("H/P");};
	double d2hdp2_along_sat_vapor(void){return CoolPropStateClassSI::d2hdp2_along_sat_vapor()*conversion_factor("H*H/P/P");};
	double d2hdp2_along_sat_liquid(void){return CoolPropStateClassSI::d2hdp2_along_sat_liquid()*conversion_factor("H*H/P/P");};

	double dsdp_along_sat_vapor(void){return CoolPropStateClassSI::dsdp_along_sat_vapor()*conversion_factor("S/P");};
	double dsdp_along_sat_liquid(void){return CoolPropStateClassSI::dsdp_along_sat_liquid()*conversion_factor("S/P");};
	double d2sdp2_along_sat_vapor(void){return CoolPropStateClassSI::d2sdp2_along_sat_vapor()*conversion_factor("S*S/P/P");};
	double d2sdp2_along_sat_liquid(void){return CoolPropStateClassSI::d2sdp2_along_sat_liquid()*conversion_factor("S*S/P/P");};

	double drhodp_along_sat_vapor(void){return CoolPropStateClassSI::drhodp_along_sat_vapor()*conversion_factor("D/P");};
	double drhodp_along_sat_liquid(void){return CoolPropStateClassSI::drhodp_along_sat_liquid()*conversion_factor("D/P");};
	double d2rhodp2_along_sat_vapor(void){return CoolPropStateClassSI::d2rhodp2_along_sat_vapor()*conversion_factor("D*D/P/P");};
	double d2rhodp2_along_sat_liquid(void){return CoolPropStateClassSI::d2rhodp2_along_sat_liquid()*conversion_factor("D*D/P/P");};

	double drhodT_along_sat_vapor(void){return CoolPropStateClassSI::drhodT_along_sat_vapor()*conversion_factor("D/T");};
	double drhodT_along_sat_liquid(void){return CoolPropStateClassSI::drhodT_along_sat_liquid()*conversion_factor("D/T");};
};

#endif
