
********************
Nonane
********************

Aliases
================================================================================
``nonane``

Bibliographic Information
=========================
**Equation of State**: E.W. Lemmon and R. Span, 2006, Short Fundamental Equations of State for 20 Industrial Fluids, *J. Chem. Eng. Data*, 51:785-850

**Surface Tension**: A. Mulero and I. Cachadi\~na and M. I. Parra, 2012, Recommended Correlations for the Surface Tension of Common Fluids, *J. Phys. Chem. Ref. Data*, 41:043105-1:13

**Viscosity**: Marcia L. Huber and Arno Laesecke and Hong Wei Xiang, 2004, Viscosity correlations for minor constituent fluids in natural gas: n-octane, n-nonane and n-decane, *Fluid Phase Equilibria*, 224:263-270

**Conductivity**: M.L. Huber and R.A. Perkins, 2005, Thermal conductivity correlations for minor constituent fluids in natural gas: n-octane, n-nonane and n-decane, *Fluid Phase Equilibria*, 227:47-55

**Lennard-Jones Parameters for ECS**: Marcia L. Huber and Arno Laesecke and Hong Wei Xiang, 2004, Viscosity correlations for minor constituent fluids in natural gas: n-octane, n-nonane and n-decane, *Fluid Phase Equilibria*, 224:263-270



Fluid Data
==========

Fluid Parameters

=========================  ==============================
Mole Mass [kg/kmol]        128.25510
Triple Point Temp. [K]     219.700
Triple Point Press. [kPa]  0.0004445435924
Minimum temperature [K]    219.700
=========================  ==============================

Critical Parameters

==============================  ==============================
Temperature [K]                 594.550
Density [kg/m\ :sup:`3`\ ]      232.141731
Pressure [kPa]                  2281.00000
==============================  ==============================


Saturated Vapor Deviations
==========================

.. plot::

    Fluid = "Nonane"
    RPFluid = "REFPROP-nonane"

    #Saturated Vapor
    from CoolProp.CoolProp import Props
    from numpy import linspace,array,abs
    import matplotlib.pyplot as plt

    Tt = Props(Fluid,'Tmin')
    Tc = Props(Fluid,'Tcrit')
    Tv = linspace(Tt+0.01,0.95*Tc,20)

    #All the CoolProp calculations
    p = array([Props('P','T',T,'Q',1,Fluid) for T in Tv])
    rho = array([Props('D','T',T,'Q',1,Fluid) for T in Tv])
    cp = array([Props('C','T',T,'Q',1,Fluid) for T in Tv])
    cv = array([Props('O','T',T,'Q',1,Fluid) for T in Tv])
    h0 = Props('H','T',(Tt+Tc)/2.0,'Q',1,Fluid)
    h = array([Props('H','T',T,'Q',1,Fluid)-h0 for T in Tv])
    s0 = Props('S','T',(Tt+Tc)/2.0,'Q',1,Fluid)
    s = array([Props('S','T',T,'Q',1,Fluid)-s0 for T in Tv])   
    sigma = array([Props('I','T',T,'Q',1,Fluid) for T in Tv])
    visc = array([Props('V','T',T,'Q',1,Fluid) for T in Tv])
    cond = array([Props('L','T',T,'Q',1,Fluid) for T in Tv])

    Rp = array([Props('P','T',T,'Q',1,RPFluid) for T in Tv])
    Rrho = array([Props('D','T',T,'Q',1,RPFluid) for T in Tv])
    Rcp = array([Props('C','T',T,'Q',1,RPFluid) for T in Tv])
    Rcv = array([Props('O','T',T,'Q',1,RPFluid) for T in Tv])
    Rh0 = Props('H','T',(Tt+Tc)/2.0,'Q',1,RPFluid)
    Rh = array([Props('H','T',T,'Q',1,RPFluid)-Rh0 for T in Tv])
    Rs0 = Props('S','T',(Tt+Tc)/2.0,'Q',1,RPFluid)
    Rs = array([Props('S','T',T,'Q',1,RPFluid)-Rs0 for T in Tv])
    Rsigma = array([Props('I','T',T,'Q',1,RPFluid) for T in Tv])
    Rvisc = array([Props('V','T',T,'Q',1,RPFluid) for T in Tv])
    Rcond = array([Props('L','T',T,'Q',1,RPFluid) for T in Tv])

    fig = plt.figure()

    ax = fig.add_axes((0.15,0.15,0.8,0.8))
    ax.semilogy(Tv/Tc,abs(p/Rp-1)*100,'o',label='Pressure')
    ax.semilogy(Tv/Tc,abs(rho/Rrho-1)*100,'o',label='Density')
    ax.semilogy(Tv/Tc,abs(cp/Rcp-1)*100,'o',label='Specific heat (cp)')
    ax.semilogy(Tv/Tc,abs(cv/Rcv-1)*100,'o',label='Specific heat (cv)')
    ax.semilogy(Tv/Tc,abs(h/Rh-1)*100,'o',label='Enthalpy')
    ax.semilogy(Tv/Tc,abs(s/Rs-1)*100,'o',label='Entropy')
    ax.semilogy(Tv/Tc,abs(visc/Rvisc-1)*100,'^',label='Viscosity')
    ax.semilogy(Tv/Tc,abs(cond/Rcond-1)*100,'s',label='Conductivity')
    ax.semilogy(Tv/Tc,abs(sigma/Rsigma-1)*100,'p',label='Surface tension')
    ax.set_ylim(1e-16,100)
    ax.set_title('Saturated Vapor Deviations from REFPROP 9.1')
    ax.set_xlabel('Reduced temperature T/Tc')
    ax.set_ylabel('Absolute deviation [%]')
    ax.legend(numpoints=1,loc='best')
    plt.show()

Saturated Liquid Deviations
===========================

.. plot::

    Fluid = "Nonane"
    RPFluid = "REFPROP-nonane"

    #Saturated Liquid
    from CoolProp.CoolProp import Props
    from numpy import linspace,array,abs
    import matplotlib.pyplot as plt

    Tt = Props(Fluid,'Tmin')
    Tc = Props(Fluid,'Tcrit')
    Tv = linspace(Tt+0.01,0.95*Tc,20)

    #All the CoolProp calculations
    p = array([Props('P','T',T,'Q',0,Fluid) for T in Tv])
    rho = array([Props('D','T',T,'Q',0,Fluid) for T in Tv])
    cp = array([Props('C','T',T,'Q',0,Fluid) for T in Tv])
    cv = array([Props('O','T',T,'Q',0,Fluid) for T in Tv])
    h0 = Props('H','T',(Tt+Tc)/2.0,'Q',0,Fluid)
    h = array([Props('H','T',T,'Q',0,Fluid)-h0 for T in Tv])
    s0 = Props('S','T',(Tt+Tc)/2.0,'Q',0,Fluid)
    s = array([Props('S','T',T,'Q',0,Fluid)-s0 for T in Tv])    
    visc = array([Props('V','T',T,'Q',0,Fluid) for T in Tv])
    cond = array([Props('L','T',T,'Q',0,Fluid) for T in Tv])
    sigma = array([Props('I','T',T,'Q',0,Fluid) for T in Tv])

    Rp = array([Props('P','T',T,'Q',0,RPFluid) for T in Tv])
    Rrho = array([Props('D','T',T,'Q',0,RPFluid) for T in Tv])
    Rcp = array([Props('C','T',T,'Q',0,RPFluid) for T in Tv])
    Rcv = array([Props('O','T',T,'Q',0,RPFluid) for T in Tv])
    Rh0 = Props('H','T',(Tt+Tc)/2.0,'Q',0,RPFluid)
    Rh = array([Props('H','T',T,'Q',0,RPFluid)-Rh0 for T in Tv])
    Rs0 = Props('S','T',(Tt+Tc)/2.0,'Q',0,RPFluid)
    Rs = array([Props('S','T',T,'Q',0,RPFluid)-Rs0 for T in Tv])
    Rvisc = array([Props('V','T',T,'Q',0,RPFluid) for T in Tv])
    Rcond = array([Props('L','T',T,'Q',0,RPFluid) for T in Tv])
    Rsigma = array([Props('I','T',T,'Q',0,RPFluid) for T in Tv])

    fig = plt.figure()

    ax = fig.add_axes((0.15,0.15,0.8,0.8))
    ax.semilogy(Tv/Tc,abs(p/Rp-1)*100,'o',label='Pressure')
    ax.semilogy(Tv/Tc,abs(rho/Rrho-1)*100,'o',label='Density')
    ax.semilogy(Tv/Tc,abs(cp/Rcp-1)*100,'o',label='Specific heat (cp)')
    ax.semilogy(Tv/Tc,abs(cv/Rcv-1)*100,'o',label='Specific heat (cv)')
    ax.semilogy(Tv/Tc,abs(h/Rh-1)*100,'o',label='Enthalpy')
    ax.semilogy(Tv/Tc,abs(s/Rs-1)*100,'o',label='Entropy')
    ax.semilogy(Tv/Tc,abs(visc/Rvisc-1)*100,'^',label='Viscosity')
    ax.semilogy(Tv/Tc,abs(cond/Rcond-1)*100,'s',label='Conductivity')
    ax.semilogy(Tv/Tc,abs(sigma/Rsigma-1)*100,'p',label='Surface tension')
    ax.set_ylim(1e-16,100)
    ax.set_title('Saturated Liquid Deviations from REFPROP 9.1')
    ax.set_xlabel('Reduced temperature T/Tc')
    ax.set_ylabel('Absolute deviation [%]')
    ax.legend(numpoints=1,loc='best')
    plt.show()

Along the critical isotherm where T=T\ :sub:`c`
================================================
.. plot::

    Fluid = "Nonane"
    RPFluid = "REFPROP-nonane"

    #Critical isotherm
    from CoolProp.CoolProp import Props
    from numpy import linspace,array,abs
    import matplotlib.pyplot as plt

    Tc = Props(Fluid,'Tcrit')
    rhoc = Props(Fluid,'rhocrit')
    rhov = linspace(1e-12,2*rhoc)

    #All the CoolProp calculations
    p = array([Props('P','T',Tc,'D',D,Fluid) for D in rhov])
    rho = array([Props('D','T',Tc,'D',D,Fluid) for D in rhov])
    cp = array([Props('C','T',Tc,'D',D,Fluid) for D in rhov])
    cv = array([Props('O','T',Tc,'D',D,Fluid) for D in rhov])
    h0 = Props('H','T',0.95*Tc,'Q',1,Fluid)
    h = array([Props('H','T',Tc,'D',D,Fluid)-h0 for D in rhov])
    s0 = Props('S','T',0.95*Tc,'Q',1,Fluid)
    s = array([Props('S','T',Tc,'D',D,Fluid)-s0 for D in rhov])
    visc = array([Props('V','T',Tc,'D',D,Fluid) for D in rhov])
    cond = array([Props('L','T',Tc,'D',D,Fluid) for D in rhov])

    Rp = array([Props('P','T',Tc,'D',D,RPFluid) for D in rhov])
    Rrho = array([Props('D','T',Tc,'D',D,RPFluid) for D in rhov])
    Rcp = array([Props('C','T',Tc,'D',D,RPFluid) for D in rhov])
    Rcv = array([Props('O','T',Tc,'D',D,RPFluid) for D in rhov])
    Rh0 = Props('H','T',0.95*Tc,'Q',1,RPFluid)
    Rh = array([Props('H','T',Tc,'D',D,RPFluid)-Rh0 for D in rhov])
    Rs0 = Props('S','T',0.95*Tc,'Q',1,RPFluid)
    Rs = array([Props('S','T',Tc,'D',D,RPFluid)-Rs0 for D in rhov])
    Rvisc = array([Props('V','T',Tc,'D',D,RPFluid) for D in rhov])
    Rcond = array([Props('L','T',Tc,'D',D,RPFluid) for D in rhov])

    fig = plt.figure()

    ax = fig.add_axes((0.15,0.15,0.8,0.8))
    ax.semilogy(rhov/rhoc,abs(p/Rp-1)*100,'o',label='Pressure')
    ax.semilogy(rhov/rhoc,abs(cp/Rcp-1)*100,'o',label='Specific heat (cp)')
    ax.semilogy(rhov/rhoc,abs(cv/Rcv-1)*100,'o',label='Specific heat (cv)')
    ax.semilogy(rhov/rhoc,abs(h/Rh-1)*100,'o',label='Enthalpy')
    ax.semilogy(rhov/rhoc,abs(s/Rs-1)*100,'o',label='Entropy') 
    ax.semilogy(rhov/rhoc,abs(visc/Rvisc-1)*100,'^',label='Viscosity')
    ax.semilogy(rhov/rhoc,abs(cond/Rcond-1)*100,'s',label='Conductivity')
    ax.set_ylim(1e-16,100)
    ax.set_title('Critical isotherm Deviations from REFPROP 9.1')
    ax.set_xlabel(r'Reduced density $\rho/\rho_c$')
    ax.set_ylabel('Absolute deviation [%]')
    ax.legend(numpoints=1,loc='best')
    plt.show()

Check of p,h and p,s as inputs (X: Failure .: Success)
=================================================================
.. plot::

    from CoolProp.Plots.Plots import Ph,Ps
    from CoolProp.CoolProp import Props
    from matplotlib import pyplot as plt
    import numpy as np

    Ref = "Nonane"
    fig = plt.figure(figsize=(10,5))
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)

    Tmin = Props(Ref,'Tmin')+3
    pmin = Props('P','T',Tmin,'Q',0,Ref)
    pmax = Props(Ref,'pcrit')*2
    hmin = Props('H','T',Tmin,'Q',0,Ref)
    hmax = 2*Props('H','T',Props(Ref,'Tcrit')-1,'Q',1,Ref)-hmin
    smin = Props('S','T',Tmin,'Q',0,Ref)
    smax = 2*Props('S','T',Props(Ref,'Tcrit')-1,'Q',1,Ref)-smin

    Ph(Ref, axis = ax1, Tmin = Tmin, Tmax = 594.540000)
    Ps(Ref, axis = ax2, Tmin = Tmin, Tmax = 594.540000)

    for p in np.linspace(pmin,pmax,10):
        for h in np.linspace(hmin,hmax):
            _bad = False
            try:
                T = Props('T','H',h,'P',p,Ref)
                rho = Props('D','H',h,'P',p,Ref)
                hEOS = Props('H','T',T,'D',rho,Ref)
            except ValueError:
                _bad = True
            if _bad or abs(hEOS/h-1)>1e-6:
                ax1.plot(h,p,'x',ms = 10)
            else:
                ax1.plot(h,p,'k.', ms = 1)

    for p in np.linspace(pmin,pmax,10):
        for s in np.linspace(smin,smax):
            _bad = False
            try:
                T = Props('T','S',s,'P',p,Ref)
                rho = Props('D','S',s,'P',p,Ref)
                sEOS = Props('S','T',T,'D',rho,Ref)
            except ValueError:
                _bad = True
            if _bad or abs(sEOS/s-1)>1e-6:
                ax2.plot(s,p,'x',ms = 10)
            else:
                ax2.plot(s,p,'k.', ms = 1)

    plt.tight_layout()
