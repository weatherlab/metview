SUBROUTINE rlnkdb2(koffset, &
 & parr_in, klda, krows, kcol1, kcol2, &
 & ktarget, karr_out) 
USE PARKIND1  ,ONLY : JPIM     ,JPRB
USE YOMHOOK   ,ONLY : LHOOK,   DR_HOOK
implicit none
INTEGER(KIND=JPIM), intent(in)  :: koffset
INTEGER(KIND=JPIM), intent(in)  :: klda, krows, kcol1, kcol2, ktarget
REAL(KIND=JPRB)   , intent(in)  :: parr_in(klda, kcol1:kcol2)
INTEGER(KIND=JPIM), intent(out) :: karr_out(krows + 1)
INTEGER(KIND=JPIM) :: j, imin, imax
REAL(KIND=JPRB) :: ZHOOK_HANDLE
IF (LHOOK) CALL DR_HOOK('RLNKDB2',0,ZHOOK_HANDLE)
if (krows > 0) then
  imin =  huge(krows)
  imax = -huge(krows)
  do j=1,krows
    imin = min(imin,int(parr_in(j,ktarget)))
    imax = max(imax,int(parr_in(j,ktarget)))
  enddo
  if (imax == imin) then
    do j=1,krows + 1
      karr_out(j) = koffset + (j-1) * imax
    enddo
  else
    karr_out(1) = koffset
    do j=2,krows + 1
      karr_out(j) = karr_out(j-1) + int(parr_in(j-1,ktarget))
    enddo
  endif
endif
IF (LHOOK) CALL DR_HOOK('RLNKDB2',1,ZHOOK_HANDLE)
END SUBROUTINE rlnkdb2
