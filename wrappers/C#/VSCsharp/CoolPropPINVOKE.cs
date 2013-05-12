/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

class CoolPropPINVOKE {

  protected class SWIGExceptionHelper {

    public delegate void ExceptionDelegate(string message);
    public delegate void ExceptionArgumentDelegate(string message, string paramName);

    static ExceptionDelegate applicationDelegate = new ExceptionDelegate(SetPendingApplicationException);
    static ExceptionDelegate arithmeticDelegate = new ExceptionDelegate(SetPendingArithmeticException);
    static ExceptionDelegate divideByZeroDelegate = new ExceptionDelegate(SetPendingDivideByZeroException);
    static ExceptionDelegate indexOutOfRangeDelegate = new ExceptionDelegate(SetPendingIndexOutOfRangeException);
    static ExceptionDelegate invalidCastDelegate = new ExceptionDelegate(SetPendingInvalidCastException);
    static ExceptionDelegate invalidOperationDelegate = new ExceptionDelegate(SetPendingInvalidOperationException);
    static ExceptionDelegate ioDelegate = new ExceptionDelegate(SetPendingIOException);
    static ExceptionDelegate nullReferenceDelegate = new ExceptionDelegate(SetPendingNullReferenceException);
    static ExceptionDelegate outOfMemoryDelegate = new ExceptionDelegate(SetPendingOutOfMemoryException);
    static ExceptionDelegate overflowDelegate = new ExceptionDelegate(SetPendingOverflowException);
    static ExceptionDelegate systemDelegate = new ExceptionDelegate(SetPendingSystemException);

    static ExceptionArgumentDelegate argumentDelegate = new ExceptionArgumentDelegate(SetPendingArgumentException);
    static ExceptionArgumentDelegate argumentNullDelegate = new ExceptionArgumentDelegate(SetPendingArgumentNullException);
    static ExceptionArgumentDelegate argumentOutOfRangeDelegate = new ExceptionArgumentDelegate(SetPendingArgumentOutOfRangeException);

    [DllImport("CoolProp", EntryPoint="SWIGRegisterExceptionCallbacks_CoolProp")]
    public static extern void SWIGRegisterExceptionCallbacks_CoolProp(
                                ExceptionDelegate applicationDelegate,
                                ExceptionDelegate arithmeticDelegate,
                                ExceptionDelegate divideByZeroDelegate, 
                                ExceptionDelegate indexOutOfRangeDelegate, 
                                ExceptionDelegate invalidCastDelegate,
                                ExceptionDelegate invalidOperationDelegate,
                                ExceptionDelegate ioDelegate,
                                ExceptionDelegate nullReferenceDelegate,
                                ExceptionDelegate outOfMemoryDelegate, 
                                ExceptionDelegate overflowDelegate, 
                                ExceptionDelegate systemExceptionDelegate);

    [DllImport("CoolProp", EntryPoint="SWIGRegisterExceptionArgumentCallbacks_CoolProp")]
    public static extern void SWIGRegisterExceptionCallbacksArgument_CoolProp(
                                ExceptionArgumentDelegate argumentDelegate,
                                ExceptionArgumentDelegate argumentNullDelegate,
                                ExceptionArgumentDelegate argumentOutOfRangeDelegate);

    static void SetPendingApplicationException(string message) {
      SWIGPendingException.Set(new System.ApplicationException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingArithmeticException(string message) {
      SWIGPendingException.Set(new System.ArithmeticException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingDivideByZeroException(string message) {
      SWIGPendingException.Set(new System.DivideByZeroException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingIndexOutOfRangeException(string message) {
      SWIGPendingException.Set(new System.IndexOutOfRangeException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingInvalidCastException(string message) {
      SWIGPendingException.Set(new System.InvalidCastException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingInvalidOperationException(string message) {
      SWIGPendingException.Set(new System.InvalidOperationException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingIOException(string message) {
      SWIGPendingException.Set(new System.IO.IOException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingNullReferenceException(string message) {
      SWIGPendingException.Set(new System.NullReferenceException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingOutOfMemoryException(string message) {
      SWIGPendingException.Set(new System.OutOfMemoryException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingOverflowException(string message) {
      SWIGPendingException.Set(new System.OverflowException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingSystemException(string message) {
      SWIGPendingException.Set(new System.SystemException(message, SWIGPendingException.Retrieve()));
    }

    static void SetPendingArgumentException(string message, string paramName) {
      SWIGPendingException.Set(new System.ArgumentException(message, paramName, SWIGPendingException.Retrieve()));
    }
    static void SetPendingArgumentNullException(string message, string paramName) {
      Exception e = SWIGPendingException.Retrieve();
      if (e != null) message = message + " Inner Exception: " + e.Message;
      SWIGPendingException.Set(new System.ArgumentNullException(paramName, message));
    }
    static void SetPendingArgumentOutOfRangeException(string message, string paramName) {
      Exception e = SWIGPendingException.Retrieve();
      if (e != null) message = message + " Inner Exception: " + e.Message;
      SWIGPendingException.Set(new System.ArgumentOutOfRangeException(paramName, message));
    }

    static SWIGExceptionHelper() {
      SWIGRegisterExceptionCallbacks_CoolProp(
                                applicationDelegate,
                                arithmeticDelegate,
                                divideByZeroDelegate,
                                indexOutOfRangeDelegate,
                                invalidCastDelegate,
                                invalidOperationDelegate,
                                ioDelegate,
                                nullReferenceDelegate,
                                outOfMemoryDelegate,
                                overflowDelegate,
                                systemDelegate);

      SWIGRegisterExceptionCallbacksArgument_CoolProp(
                                argumentDelegate,
                                argumentNullDelegate,
                                argumentOutOfRangeDelegate);
    }
  }

  protected static SWIGExceptionHelper swigExceptionHelper = new SWIGExceptionHelper();

  public class SWIGPendingException {
    [ThreadStatic]
    private static Exception pendingException = null;
    private static int numExceptionsPending = 0;

    public static bool Pending {
      get {
        bool pending = false;
        if (numExceptionsPending > 0)
          if (pendingException != null)
            pending = true;
        return pending;
      } 
    }

    public static void Set(Exception e) {
      if (pendingException != null)
        throw new ApplicationException("FATAL: An earlier pending exception from unmanaged code was missed and thus not thrown (" + pendingException.ToString() + ")", e);
      pendingException = e;
      lock(typeof(CoolPropPINVOKE)) {
        numExceptionsPending++;
      }
    }

    public static Exception Retrieve() {
      Exception e = null;
      if (numExceptionsPending > 0) {
        if (pendingException != null) {
          e = pendingException;
          pendingException = null;
          lock(typeof(CoolPropPINVOKE)) {
            numExceptionsPending--;
          }
        }
      }
      return e;
    }
  }


  protected class SWIGStringHelper {

    public delegate string SWIGStringDelegate(string message);
    static SWIGStringDelegate stringDelegate = new SWIGStringDelegate(CreateString);

    [DllImport("CoolProp", EntryPoint="SWIGRegisterStringCallback_CoolProp")]
    public static extern void SWIGRegisterStringCallback_CoolProp(SWIGStringDelegate stringDelegate);

    static string CreateString(string cString) {
      return cString;
    }

    static SWIGStringHelper() {
      SWIGRegisterStringCallback_CoolProp(stringDelegate);
    }
  }

  static protected SWIGStringHelper swigStringHelper = new SWIGStringHelper();


  static CoolPropPINVOKE() {
  }


  [DllImport("CoolProp", EntryPoint="CSharp_IProps")]
  public static extern double IProps(int jarg1, int jarg2, double jarg3, int jarg4, double jarg5, int jarg6);

  [DllImport("CoolProp", EntryPoint="CSharp_IsFluidType")]
  public static extern int IsFluidType(string jarg1, string jarg2);

  [DllImport("CoolProp", EntryPoint="CSharp_DerivTerms__SWIG_0")]
  public static extern double DerivTerms__SWIG_0(string jarg1, double jarg2, double jarg3, string jarg4);

  [DllImport("CoolProp", EntryPoint="CSharp_Phase__SWIG_0")]
  public static extern void Phase__SWIG_0(string jarg1, double jarg2, double jarg3, string jarg4);

  [DllImport("CoolProp", EntryPoint="CSharp_Phase_Trho__SWIG_0")]
  public static extern int Phase_Trho__SWIG_0(string jarg1, double jarg2, double jarg3, string jarg4);

  [DllImport("CoolProp", EntryPoint="CSharp_Phase_Tp__SWIG_0")]
  public static extern int Phase_Tp__SWIG_0(string jarg1, double jarg2, double jarg3, string jarg4);

  [DllImport("CoolProp", EntryPoint="CSharp_F2K")]
  public static extern double F2K(double jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_K2F")]
  public static extern double K2F(double jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_PrintSaturationTable")]
  public static extern void PrintSaturationTable(string jarg1, string jarg2, double jarg3, double jarg4);

  [DllImport("CoolProp", EntryPoint="CSharp_FluidsList__SWIG_0")]
  public static extern void FluidsList__SWIG_0(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_get_aliases__SWIG_0")]
  public static extern void get_aliases__SWIG_0(string jarg1, string jarg2);

  [DllImport("CoolProp", EntryPoint="CSharp_get_REFPROPname__SWIG_0")]
  public static extern void get_REFPROPname__SWIG_0(string jarg1, string jarg2);

  [DllImport("CoolProp", EntryPoint="CSharp_get_errstring__SWIG_0")]
  public static extern void get_errstring__SWIG_0(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_get_errstringc")]
  public static extern string get_errstringc();

  [DllImport("CoolProp", EntryPoint="CSharp_get_errstring_copy")]
  public static extern int get_errstring_copy(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_get_svnrevision")]
  public static extern int get_svnrevision();

  [DllImport("CoolProp", EntryPoint="CSharp_get_version__SWIG_0")]
  public static extern int get_version__SWIG_0(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_get_index_units__SWIG_0")]
  public static extern void get_index_units__SWIG_0(int jarg1, string jarg2);

  [DllImport("CoolProp", EntryPoint="CSharp_get_debug")]
  public static extern int get_debug();

  [DllImport("CoolProp", EntryPoint="CSharp_debug__SWIG_0")]
  public static extern void debug__SWIG_0(int jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_rhosatL_anc")]
  public static extern double rhosatL_anc(string jarg1, double jarg2);

  [DllImport("CoolProp", EntryPoint="CSharp_rhosatV_anc")]
  public static extern double rhosatV_anc(string jarg1, double jarg2);

  [DllImport("CoolProp", EntryPoint="CSharp_psatL_anc")]
  public static extern double psatL_anc(string jarg1, double jarg2);

  [DllImport("CoolProp", EntryPoint="CSharp_psatV_anc")]
  public static extern double psatV_anc(string jarg1, double jarg2);

  [DllImport("CoolProp", EntryPoint="CSharp_enable_TTSE_LUT")]
  public static extern bool enable_TTSE_LUT(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_isenabled_TTSE_LUT")]
  public static extern bool isenabled_TTSE_LUT(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_disable_TTSE_LUT")]
  public static extern bool disable_TTSE_LUT(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_enable_TTSE_LUT_writing")]
  public static extern bool enable_TTSE_LUT_writing(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_isenabled_TTSE_LUT_writing")]
  public static extern bool isenabled_TTSE_LUT_writing(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_disable_TTSE_LUT_writing")]
  public static extern bool disable_TTSE_LUT_writing(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_set_TTSESat_LUT_size")]
  public static extern bool set_TTSESat_LUT_size(string jarg1, int jarg2);

  [DllImport("CoolProp", EntryPoint="CSharp_set_TTSESinglePhase_LUT_size")]
  public static extern bool set_TTSESinglePhase_LUT_size(string jarg1, int jarg2, int jarg3);

  [DllImport("CoolProp", EntryPoint="CSharp_set_TTSESinglePhase_LUT_range")]
  public static extern bool set_TTSESinglePhase_LUT_range(string jarg1, double jarg2, double jarg3, double jarg4, double jarg5);

  [DllImport("CoolProp", EntryPoint="CSharp_get_TTSESinglePhase_LUT_range")]
  public static extern bool get_TTSESinglePhase_LUT_range(string jarg1, HandleRef jarg2, HandleRef jarg3, HandleRef jarg4, HandleRef jarg5);

  [DllImport("CoolProp", EntryPoint="CSharp_viscosity_dilute")]
  public static extern double viscosity_dilute(string jarg1, double jarg2, double jarg3, double jarg4, double jarg5);

  [DllImport("CoolProp", EntryPoint="CSharp_conformal_Trho")]
  public static extern double conformal_Trho(string jarg1, string jarg2, double jarg3, double jarg4, HandleRef jarg5, HandleRef jarg6);

  [DllImport("CoolProp", EntryPoint="CSharp_Props__SWIG_0")]
  public static extern double Props__SWIG_0(string jarg1, string jarg2);

  [DllImport("CoolProp", EntryPoint="CSharp_Props1")]
  public static extern double Props1(string jarg1, string jarg2);

  [DllImport("CoolProp", EntryPoint="CSharp_Props__SWIG_1")]
  public static extern double Props__SWIG_1(char jarg1, char jarg2, double jarg3, char jarg4, double jarg5, string jarg6);

  [DllImport("CoolProp", EntryPoint="CSharp_Props__SWIG_2")]
  public static extern double Props__SWIG_2(string jarg1, char jarg2, double jarg3, char jarg4, double jarg5, string jarg6);

  [DllImport("CoolProp", EntryPoint="CSharp_DerivTerms__SWIG_1")]
  public static extern double DerivTerms__SWIG_1(string jarg1, double jarg2, double jarg3, HandleRef jarg4);

  [DllImport("CoolProp", EntryPoint="CSharp_DerivTerms__SWIG_2")]
  public static extern double DerivTerms__SWIG_2(string jarg1, double jarg2, double jarg3, HandleRef jarg4, bool jarg5, bool jarg6);

  [DllImport("CoolProp", EntryPoint="CSharp_debug__SWIG_1")]
  public static extern int debug__SWIG_1();

  [DllImport("CoolProp", EntryPoint="CSharp_set_debug")]
  public static extern void set_debug(int jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_set_phase")]
  public static extern void set_phase(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_Phase__SWIG_1")]
  public static extern string Phase__SWIG_1(string jarg1, double jarg2, double jarg3);

  [DllImport("CoolProp", EntryPoint="CSharp_Phase_Trho__SWIG_1")]
  public static extern string Phase_Trho__SWIG_1(string jarg1, double jarg2, double jarg3);

  [DllImport("CoolProp", EntryPoint="CSharp_Phase_Tp__SWIG_1")]
  public static extern string Phase_Tp__SWIG_1(string jarg1, double jarg2, double jarg3);

  [DllImport("CoolProp", EntryPoint="CSharp_get_BibTeXKey")]
  public static extern string get_BibTeXKey(string jarg1, string jarg2);

  [DllImport("CoolProp", EntryPoint="CSharp_get_EOSReference")]
  public static extern string get_EOSReference(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_get_TransportReference")]
  public static extern string get_TransportReference(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_FluidsList__SWIG_1")]
  public static extern string FluidsList__SWIG_1();

  [DllImport("CoolProp", EntryPoint="CSharp_get_aliases__SWIG_1")]
  public static extern string get_aliases__SWIG_1(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_get_REFPROPname__SWIG_1")]
  public static extern string get_REFPROPname__SWIG_1(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_get_errstring__SWIG_1")]
  public static extern string get_errstring__SWIG_1();

  [DllImport("CoolProp", EntryPoint="CSharp_get_version__SWIG_1")]
  public static extern string get_version__SWIG_1();

  [DllImport("CoolProp", EntryPoint="CSharp_add_REFPROP_fluid")]
  public static extern bool add_REFPROP_fluid(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_get_param_index")]
  public static extern int get_param_index(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_get_Fluid_index")]
  public static extern int get_Fluid_index(string jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_get_index_units__SWIG_1")]
  public static extern string get_index_units__SWIG_1(int jarg1);

  [DllImport("CoolProp", EntryPoint="CSharp_get_fluid")]
  public static extern IntPtr get_fluid(int jarg1);
}
