************************************************************************
**                                                                    **
**             Type information routines for SNID and Logwave         **
**                                                                    **
**                                                                    **
**                 Copyright (C) 2006 Stephane Blondin                **
**                                                                    **
************************************************************************

c Included in this file:
c
c subroutine typeinfo
c subroutine typeidx



************************************************************************
* subroutine typeinfo -- Initialize the typename array
************************************************************************

      subroutine typeinfo

C     NOTE: 
C     
C     After adding more (sub)types, make sure to change the values of
C     the parameters NT and NST in snid.inc. NT is the total number of
C     template types; NST is the maximum number of template subtypes in
C     any given type, +1.
C
C     E.g. "Ia" type has the maximum number of subtypes (5; norm, 91T,
C     91bg, csm, pec), so NST = 6

      implicit none

      include 'snid.inc'

* initialize typename array
      do it=1, NT
         do ist=1, NST
            typename(it,ist)='typename'
         end do
      end do

* SN Ia
      typename(1,1) = 'Ia'      ! first element is name of type
      typename(1,2) = 'Ia-norm' ! subtypes follow...(normal, peculiar, etc.)
      typename(1,3) = 'Ia-91T'
      typename(1,4) = 'Ia-91bg'
      typename(1,5) = 'Ia-csm'
      typename(1,6) = 'Ia-pec'
      typename(1,7) = 'Ia-02cx'
      typename(1,8) = 'Ia-03fg' ! formerly super-chandra
      typename(1,9) = 'Ia-02es'
      typename(1,10) = 'Ia-Ca-rich'
* SN Ib
      typename(2,1) = 'Ib'
      typename(2,2) = 'Ib-norm'
      typename(2,3) = 'Ib-pec'
      typename(2,4) = 'IIb'     ! IIb is not included in SNII
      typename(2,5) = 'Ibn'
      typename(2,6) = 'Ib-Ca-rich'
      typename(2,7) = 'Ib-csm'
* SN Ic
      typename(3,1) = 'Ic'
      typename(3,2) = 'Ic-norm'
      typename(3,3) = 'Ic-pec'
      typename(3,4) = 'Ic-Broad'
      typename(3,5) = 'Icn'
      typename(3,6) = 'Ic-Ca-rich'
      typename(3,7) = 'Ic-csm'
* SN II
      typename(4,1) = 'II'
      typename(4,2) = 'IIP'     ! IIP is the "normal" SN II
      typename(4,3) = 'II-pec'
      typename(4,4) = 'IIn'
      typename(4,5) = 'IIL'
      typename(4,6) = 'IIn-pec'
* NotSN
      typename(5,1) = 'NotSN'
      typename(5,2) = 'AGN'
      typename(5,3) = 'Gal'
      typename(5,4) = 'QSO'
      typename(5,5) = 'M-star'
      typename(5,6) = 'C-star'
      typename(5,7) = 'Afterglow'
      typename(5,8) = 'Nova'
      typename(5,9) = 'CV'
* SLSN
      typename(6,1) = 'SLSN'
      typename(6,2) = 'SLSN-I'
      typename(6,3) = 'SLSN-Ib'
      typename(6,4) = 'SLSN-Ic'
      typename(6,5) = 'SLSN-II'
      typename(6,6) = 'SLSN-IIn'
* LFBOT
      typename(7,1) = 'LFBOT'
      typename(7,2) = '18cow'
      typename(7,3) = '20xnd'
* TDE
      typename(8,1) = 'TDE'
      typename(8,2) = 'TDE-H'
      typename(8,3) = 'TDE-He'
      typename(8,4) = 'TDE-H-He'
      typename(8,5) = 'TDE-Featless'
* KN
      typename(9,1) = 'KN'
      typename(9,2) = '17gfo'
* Gap
      typename(10,1) = 'GAP'
      typename(10,2) = 'LRN'
      typename(10,3) = 'LBV'
      typename(10,4) = 'ILRT'

      return
      end



************************************************************************
* subroutine typeidx -- get typename index
************************************************************************

      subroutine typeidx(name,type,ierr)

      implicit none

      include 'snid.inc'

      character*10 name
      integer type(NT,NST)
      integer ierr

* Initialize error flag
      ierr = 1
      
      do it=1, NT
* Select all subtypes if a given type is selected
         if(index(typename(it,1),name).gt.0) then
            ierr = 0
            do ist=1, NST
               type(it,ist) = 1
            end do
* Otherwise select subtype and set corresponding type index
         else 
            do ist=2, NST
               if(index(typename(it,ist),name).gt.0) then
                  ierr = 0
                  type(it,1)   = 1
                  type(it,ist) = 1
               end if
            end do
         end if
      end do
      
      return
      end
