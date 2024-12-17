*************************
* Include file for logwave & snid
*************************

c
c Template directory
c
      character*200 tempdir

c
c Various parameters
c

      real    EPSFRAC  ! epsilon fraction
      real    EPSRLAP  ! epsilon rlap
      real    EPSSLOPE ! epsilon slope
      real    EPSZ     ! epsilon z
      integer MAXEPOCH ! maximum number of epochs per template
      integer MAXKNOT  ! maximum number of knot points for natural cubic spline
      integer MAXLIST  ! maximum number of templates to list in one go
      integer MAXLOG   ! maximum number of logarithmic wavelength bins
      integer MAXPARAM ! maximum number of parameters in param file
      integer MAXPEAK  ! maximum number of correlation peaks to look for
      integer MAXPLOT  ! maximum number of columns in data array for plotting
      integer MAXPPT   ! maximum number of plot points (cf. MAXLOG)
      real    MAXR     ! maximum r-value to report (if arms = 0)
      integer MAXRLAP  ! maximum size of rlap array when computing slope of absolute fraction of type vs. rlap
      integer MAXSN    ! maximum number of different supernovae in file list (logwave)
      integer MAXUSE   ! maximum number of templates to use/avoid
      integer MAXTEMP  ! maximum number of templates (also in logwave)
      integer MAXTOK   ! maximum number of words in a given line of file list (logwave)
      integer MAXWAVE  ! maximum number of wavelength bins
      integer NT       ! total number of template types
      integer NST      ! maximum number of template subtypes + 1
      
      parameter (EPSFRAC = 5e-4)
      parameter (EPSRLAP = 5e-2)
      parameter (EPSSLOPE = 5e-4)
      parameter (EPSZ = 5e-4)
      parameter (MAXEPOCH = 300)
      parameter (MAXKNOT = 20)
      parameter (MAXLIST = 20)
      parameter (MAXLOG = 1024)
      parameter (MAXPARAM = 200)
      parameter (MAXPEAK = 20)
      parameter (MAXPLOT = 20)
      parameter (MAXPPT = 200000)
      parameter (MAXR = 999.9)
      parameter (MAXRLAP = 999)
      parameter (MAXSN = 300)
      parameter (MAXUSE = 30)
      parameter (MAXTEMP = 50000)
      parameter (MAXTOK = 32)
      parameter (MAXWAVE = 10000)
      parameter (NT = 10)
      parameter (NST = 10)

      character*10 typename(NT,NST) ! character array containing type/subtype names

c
c User options
c
      integer noption         ! number of input user options
      integer iparam          ! set to 1 if options read from parameter file
      character*200 paramfile ! user-input parameter file
      real agemin,agemax      ! user-defined phase range
      real deltamin,deltamax  ! user-defined delta range
      real wmin,wmax          ! user-defined (observed) wavelength range
      integer iwmin,iwmax     ! set these flags when wmin,wmax options are set
      character*200 wmaskfile ! user-input wavelength mask file
      integer iwmask          ! set this flag if user-input wavelength mask
      real zmin,zmax          ! user-defined redshift range
      real forcez             ! force correlations at this redshift
      real zfake              ! fake redshift to apply for testing purposes
      real znsig              ! sigma value for alternate initial redshift determination
      real zuser              ! user-input redshift

      character*12 avoid(MAXUSE)              ! template(s) to avoid
      character*200 avoids                    ! store avoid= option argument
      integer avoidtype(NT,NST)               ! template (sub)type(s) to avoid
      character*200 avoidts                   ! store avoidtype= option argument
      character*12 use(MAXUSE)                ! template(s) to use
      character*200 uses                      ! store use= option argument
      integer usetype(NT,NST)                 ! template (sub)type(s) to use
      character*200 usets                     ! store usetype= option argument
      integer navoid,navoidtype,nuse,nusetype ! number of elements in the above vectors
      integer nminspec                        ! minimum number of epochs per template in range [agemin,agemax]

      real lapmin  ! minimum overlap to consider
      real rlapmin ! minimum rlap-value to consider
      real zfilter ! maximum tolerated difference between median and template redshift
      real zk      ! constant to use for formal redshift error zerr=zk*wid/(1+rlap)

      real medlen     ! median filtering width (pix)
      real fwmed      ! median filter FWHM (A) [medfw=val option]
      real emclipz    ! clip galaxy emission lines at this redshift [emclip=z option]
      integer skyclip ! clip sky emission lines [skyclip=0/1 option]
      real emx        ! emission clip width (A) [emclip=w option]

      integer k1,k2,k3,k4 ! wave-numbers for bandpass filter
      integer iaband      ! exclude A-band if aband=0
      integer inter       ! toggle interactive mode on/off
      integer iplot       ! disable plotting with plot=0
      integer iquery      ! skip initial query if iquery=0
      integer verbose     ! verbose level

c
c Further declarations
c 
      real percent                     ! percent to apodize
      real w0,w1                       ! wavelength range for binning
      integer nw                       ! total number of wavelength bins (cf. MAXLOG parameter)
      real dwlog                       ! step in log wavelength,  dwlog=alog(w1/w0) / nw
      integer log2n                    ! n=2**log2n is the length of complex vector used as input for fft2c [no longer used]
      integer lz1,lz2                  ! logarithmic bin range corresponding to [zmin,zmax]    
      real wave(MAXWAVE),flux(MAXWAVE) ! (w,f) of input spectrum

      integer nknod                      ! number of knot points for each input spectrum
      real xknod(MAXKNOT),yknod(MAXKNOT) ! knot point (w,f) coordinates for each input spectrum
      character*200 tok(MAXTOK)          ! character array containing separate words in line
      integer ltok(MAXTOK)               ! length of each word in line

      integer it                  ! loop index for types
      integer ist                 ! loop index for subtypes
      integer ntemp               ! number of template spectra
      character*12 sname(MAXTEMP) ! name of SN template
      character*10 stype(MAXTEMP) ! name of SN (sub)type
      integer itype(2,MAXTEMP)    ! type/subtype indeces
      real epoch(MAXTEMP)         ! template age
      integer tflag(MAXTEMP)      ! age flag (0=OK; 1=NoPhaseInfo; 2=NotSNPhase)

      real peaks(3,MAXPEAK) ! correlation peak(s) parameters

      character*20 version ! SNID version number

c
c File output
c
      character*200 fdata ! input spectral file
      character*200 froot ! root name of input spectral file
      integer fout        ! generic file output level
      integer fluxout     ! output fluxed spectra
      integer flatout     ! output flattened spectra
      integer xcorout     ! output correlation functions

c
c Plot parameters
c
      integer istat                        ! check pgopen returns correct value for PS output
      integer iflat,iflux,ixcor,ipeaks,izt ! >1 if corresponding buttons are pressed, 0 otherwise
      integer iia,iib,iic,iii,inotsn,iall  ! >1 if corresponding buttons are pressed, 0 otherwise
      integer ips,iascii                   ! >1 if corresponding buttons are pressed, 0 otherwise
      integer ips2                         ! +1 for each PS output generated
      integer jflux,jcompflux(2,MAXTEMP)   ! =1 if flux PS/ASCII file already created
      integer jflat,jcompflat(2,MAXTEMP)   ! =1 if flat PS/ASCII file already created
      integer jcompxcor(2,MAXTEMP)         ! =1 if xcor PS/ASCII file already created
      integer jpeaks(2)                    ! =1 if peaks PS/ASCII file already created
      integer jzt(2)                       ! =1 if z/t PS/ASCII file already created
      integer jfrac(2,NT)                  ! =1 if frac PS/ASCII file already created
      integer jfracall(2)                  ! =1 if frac PS/ASCII file already created
      character*20 labels(10)              ! various labels
      character*20 dlabels(10)             ! various labels
	

c
c Common blocks
c
      common /snidpar/ iparam,iwmin,wmin,iwmax,wmax,iwmask,
     $      fwmed,medlen,emclipz,skyclip,emx,iaband,agemin,
     $      agemax,deltamin,deltamax,rlapmin,lapmin,zmin,zmax,forcez,
     $      zfake,znsig,zuser,zk,zfilter,percent,nw,w0,w1,k1,k2,k3,k4,
     $      dwlog,log2n,lz1,lz2,fout,fluxout,flatout,xcorout,iplot,
     $      iquery,verbose,inter,noption

      common /snidchar/ paramfile,wmaskfile,tempdir,fdata,froot,
     $      typename,use,uses,usets,avoid,avoids,
     $      avoidts,labels,dlabels,version

      common /snidtype/ nminspec,nuse,usetype,nusetype,
     $      navoid,avoidtype,navoidtype

      common /snidgraph/ istat,iflat,iflux,ixcor,ipeaks,izt,iia,iib,iic,
     $      iii,inotsn,iall,ips,iascii,ips2,jflux,jcompflux,jflat,
     $      jcompflat,jcompxcor,jpeaks,jzt,jfrac,jfracall
