#include"stdlib.h"
#include"string.h"

#include "Typedef.h"
#include "basop.h"
#include "cst_lbc.h"
#include "tab_lbc.h"
#include "coder.h"
#include "decod.h"
#include "vad.h"
#include "cod_cng.h"
#include "dec_cng.h"
#include "Util_lbc.h"
#include "Util_cng.h"
#include "Lpc.h"
#include "Lsp.h"
#include "Exc_lbc.h"
#include "Tame.h"
#include"g723.h"
#include "inline.h"


void  Rem_Dc( Word16 *Dpnt,ENC_HANDLE *handle )
{
    int   i  ;


    Word32   Acc0,Acc1 ;

    if ( handle->UseHp )
	{
        for ( i = 0 ; i < Frame ; i ++ ) 
		{

            /* Do the Fir and scale by 2 */
            Acc0 = L_mult( Dpnt[i], (Word16) 0x4000 ) ;
            Acc0 = L_mac ( Acc0, handle->CodStat.HpfZdl, (Word16) 0xc000 ) ;
            handle->CodStat.HpfZdl = Dpnt[i] ;

            /* Do the Iir part */
            Acc1 = L_mls( handle->CodStat.HpfPdl, (Word16) 0x7f00 ) ;
            Acc0 = L_add( Acc0, Acc1 ) ;
            handle->CodStat.HpfPdl = Acc0 ;
            Dpnt[i] = round(Acc0) ;
        }
    }
    else
	{
        for ( i = 0 ; i < Frame ; i ++ )
            Dpnt[i] = shr( Dpnt[i], (Word16) 1 ) ;
    }

    return;
}

Word16  Vec_Norm( Word16 *Vect, Word16 Len )
{
    int   i  ;

    Word16  Acc0,Acc1   ;
    Word16  Exp   ;
    Word16  Rez ;
    Word32  Temp  ;

    static   short ShiftTable[16] = {
      0x0001 ,
      0x0002 ,
      0x0004 ,
      0x0008 ,
      0x0010 ,
      0x0020 ,
      0x0040 ,
      0x0080 ,
      0x0100 ,
      0x0200 ,
      0x0400 ,
      0x0800 ,
      0x1000 ,
      0x2000 ,
      0x4000 ,
      0x7fff
   } ;

    /* Find absolute maximum */
    Acc1 = (Word16) 0 ;
    for ( i = 0 ; i < Len ; i ++ ) {
        Acc0 = abs_s( Vect[i] ) ;
        if ( Acc0 > Acc1 )
            Acc1 = Acc0 ;
    }

    /* Get the shift count */
    Rez = norm_s( Acc1 ) ;
    Exp = ShiftTable[Rez] ;

    /* Normalize all the vector */
    for ( i = 0 ; i < Len ; i ++ ) {
        Temp = L_mult( Exp, Vect[i] ) ;
        Temp = L_shr( Temp, 4 ) ;
        Vect[i] = extract_l( Temp ) ;
    }

    Rez = sub( Rez, (Word16) 3) ;
    return Rez ;
}


void  Mem_Shift( Word16 *PrevDat, Word16 *DataBuff )
{
    int   i  ;

    Word16   Dpnt[Frame+LpcFrame-SubFrLen] ;

    /*  Form Buffer  */
    for ( i = 0 ; i < LpcFrame-SubFrLen ; i ++ )
        Dpnt[i] = PrevDat[i] ;
    for ( i = 0 ; i < Frame ; i ++ )
        Dpnt[i+LpcFrame-SubFrLen] = DataBuff[i] ;

    /* Update PrevDat */
    for ( i = 0 ; i < LpcFrame-SubFrLen ; i ++ )
        PrevDat[i] = Dpnt[Frame+i] ;

    /* Update DataBuff */
    for ( i = 0 ; i < Frame ; i ++ )
        DataBuff[i] = Dpnt[(LpcFrame-SubFrLen)/2+i] ;

    return;
}

Word16   Rand_lbc( Word16 *p )
{
    Word32   Temp ;

    Temp = L_deposit_l( *p ) ;
    Temp &= (Word32) 0x0000ffff ;
    Temp = Temp*(Word32)521 + (Word32) 259 ;
    *p = extract_l( Temp ) ;
    return extract_l( Temp ) ;
}

Word16   Sqrt_lbc( Word32 Num )
{
    int   i  ;

    Word16   Rez = (Word16) 0 ;
    Word16   Exp = (Word16) 0x4000 ;

    Word32   Acc ;

    for ( i = 0 ; i < 14 ; i ++ ) {

        Acc = L_mult( add(Rez, Exp), add(Rez, Exp) ) ;
        if ( Num >= Acc )
            Rez = add( Rez, Exp ) ;

        Exp = shr( Exp, (Word16) 1 ) ;
    }
    return Rez ;
}

Word16* Par2Ser( Word32 Inp, Word16 *Pnt, int BitNum )
{
    int i   ;
    Word16  Temp ;

    for ( i = 0 ; i < BitNum ; i ++ ) {
        Temp = (Word16) Inp & (Word16)0x0001 ;
        Inp >>= 1 ;
        *Pnt ++ = Temp ;
    }

    return Pnt ;
}


void    Line_Pack( LINEDEF *Line, char *Vout, Word16 Ftyp,ENC_HANDLE *handle ,char stride)
{
    int     i ;
    int     BitCount ;

    Word16  BitStream[192] ;
    Word16 *Bsp = BitStream ;
    Word32  Temp ;

    /* Clear the output vector */
    for ( i = 0 ; i < stride ; i ++ )
        Vout[i] = 0 ;

 /*
  * Add the coder rate info and frame type info to the 2 msb
  * of the first word of the frame.
  * The signaling is as follows:
  *     Ftyp  WrkRate => X1X0
  *       1     Rate63     00  :   High Rate
  *       1     Rate53     01  :   Low  Rate
  *       2       x        10  :   Silence Insertion Descriptor frame
  *       0       x        11  :   Used only for simulation of
  *                                 untransmitted silence frames
  */
    switch (Ftyp) {

        case 0 : {
            Temp = 0x00000003L;
            break;
        }

        case 2 : {
            Temp = 0x00000002L;
            break;
        }

        default : {
            if ( handle->mode == G723_63 )
                Temp = 0x00000000L ;
            else
                Temp = 0x00000001L ;
            break;
        }
    }

    /* Serialize Control info */
    Bsp = Par2Ser( Temp, Bsp, 2 ) ;


    /* Check for Speech/NonSpeech case */
    if ( Ftyp == 1 ) {

    /* 24 bit LspId */
    Temp = (*Line).LspId ;
    Bsp = Par2Ser( Temp, Bsp, 24 ) ;

 /*
  * Do the part common to both rates
  */

        /* Adaptive code book lags */
        Temp = (Word32) (*Line).Olp[0] - (Word32) PitchMin ;
        Bsp = Par2Ser( Temp, Bsp, 7 ) ;

        Temp = (Word32) (*Line).Sfs[1].AcLg ;
        Bsp = Par2Ser( Temp, Bsp, 2 ) ;

        Temp = (Word32) (*Line).Olp[1] - (Word32) PitchMin ;
        Bsp = Par2Ser( Temp, Bsp, 7 ) ;

        Temp = (Word32) (*Line).Sfs[3].AcLg ;
        Bsp = Par2Ser( Temp, Bsp, 2 ) ;

        /* Write combined 12 bit index of all the gains */
        for ( i = 0 ; i < SubFrames ; i ++ )
		{
            Temp = (*Line).Sfs[i].AcGn*NumOfGainLev + (*Line).Sfs[i].Mamp ;
            if ( handle->mode == G723_63 )
                Temp += (Word32) (*Line).Sfs[i].Tran << 11 ;
            Bsp = Par2Ser( Temp, Bsp, 12 ) ;
        }

        /* Write all the Grid indices */
        for ( i = 0 ; i < SubFrames ; i ++ )
            *Bsp ++ = (*Line).Sfs[i].Grid ;

        /* High rate only part */
        if ( handle->mode == G723_63 ) 
		{

            /* Write the reserved bit as 0 */
            *Bsp ++ = (Word16) 0 ;

            /* Write 13 bit combined position index */
            Temp = (*Line).Sfs[0].Ppos >> 16 ;
            Temp = Temp * 9 + ( (*Line).Sfs[1].Ppos >> 14) ;
            Temp *= 90 ;
            Temp += ((*Line).Sfs[2].Ppos >> 16) * 9 + ( (*Line).Sfs[3].Ppos >> 14 ) ;
            Bsp = Par2Ser( Temp, Bsp, 13 ) ;

            /* Write all the pulse positions */
            Temp = (*Line).Sfs[0].Ppos & 0x0000ffffL ;
            Bsp = Par2Ser( Temp, Bsp, 16 ) ;

            Temp = (*Line).Sfs[1].Ppos & 0x00003fffL ;
            Bsp = Par2Ser( Temp, Bsp, 14 ) ;

            Temp = (*Line).Sfs[2].Ppos & 0x0000ffffL ;
            Bsp = Par2Ser( Temp, Bsp, 16 ) ;

            Temp = (*Line).Sfs[3].Ppos & 0x00003fffL ;
            Bsp = Par2Ser( Temp, Bsp, 14 ) ;

            /* Write pulse amplitudes */
            Temp = (Word32) (*Line).Sfs[0].Pamp ;
            Bsp = Par2Ser( Temp, Bsp, 6 ) ;

            Temp = (Word32) (*Line).Sfs[1].Pamp ;
            Bsp = Par2Ser( Temp, Bsp, 5 ) ;

            Temp = (Word32) (*Line).Sfs[2].Pamp ;
            Bsp = Par2Ser( Temp, Bsp, 6 ) ;

            Temp = (Word32) (*Line).Sfs[3].Pamp ;
            Bsp = Par2Ser( Temp, Bsp, 5 ) ;
        }

        /* Low rate only part */
        else {

            /* Write 12 bits of positions */
            for ( i = 0 ; i < SubFrames ; i ++ ) 
			{
                Temp = (*Line).Sfs[i].Ppos ;
                Bsp = Par2Ser( Temp, Bsp, 12 ) ;
            }

            /* Write 4 bit Pamps */
            for ( i = 0 ; i < SubFrames ; i ++ ) 
			{
                Temp = (*Line).Sfs[i].Pamp ;
                Bsp = Par2Ser( Temp, Bsp, 4 ) ;
            }
        }

    }

    else if(Ftyp == 2) 
	{  
        /* 24 bit LspId */
        Temp = (*Line).LspId ;
        Bsp = Par2Ser( Temp, Bsp, 24 ) ;

        /* Do Sid frame gain */
        Temp = (Word32)(*Line).Sfs[0].Mamp ;
        Bsp = Par2Ser( Temp, Bsp, 6 ) ;
    }

    /* Write out active frames */
    if ( Ftyp == 1 )
	{
        if ( handle->mode == G723_63 )
            BitCount = 192 ;
        else
            BitCount = 160 ;
    }
    /* Non active frames */
    else if ( Ftyp == 2 )
        BitCount = 32 ;
    else
        BitCount = 2;

    for ( i = 0 ; i < BitCount ; i ++ )
        Vout[i>>3] ^= BitStream[i] << (i & 0x0007) ;

    return;
}
Word32  Ser2Par( Word16 **Pnt, int Count )
{
    int     i ;
    Word32  Rez = 0L ;

    for ( i = 0 ; i < Count ; i ++ ) {
        Rez += (Word32) **Pnt << i ;
        (*Pnt) ++ ;
    }
    return Rez ;
}

LINEDEF  Line_Unpk( char *Vinp, Word16 *Ftyp, Word16 Crc ,DEC_HANDLE *handle)
{
    int   i  ;
    Word16  BitStream[192] ;
    Word16 *Bsp = BitStream ;
    LINEDEF Line ;
    Word32  Temp ;
    Word16  Info;
    Word16 Bound_AcGn;

    Line.Crc = Crc;
    if(Crc != 0) return Line;

    /* Unpack the byte info to BitStream vector */
    for ( i = 0 ; i < 192 ; i ++ )
        BitStream[i] = ( Vinp[i>>3] >> (i & (Word16)0x0007) ) & (Word16)1 ;

    /* Decode the frame type and rate info */
    Info = (Word16)Ser2Par( &Bsp, 2 ) ;

    if ( Info == 3 ) {
        *Ftyp = 0;
        Line.LspId = 0L;    /* Dummy : to avoid Borland C3.1 warning */
        return Line;
    }

    /* Decode the LspId */
    Line.LspId = Ser2Par( &Bsp, 24 ) ;

    if ( Info == 2 ) {
        /* Decode the Noise Gain */
        Line.Sfs[0].Mamp = (Word16)Ser2Par( &Bsp, 6);
        *Ftyp = 2;
        return Line ;
    }

 /*
  * Decode the common information to both rates
  */
    *Ftyp = 1;

    /* Decode the bit-rate */
    handle->mode = (Info == 0) ? G723_63 :G723_53;

    /* Decode the adaptive codebook lags */
    Temp = Ser2Par( &Bsp, 7 ) ;
    /* Test if forbidden code */
    if( Temp <= 123) {
        Line.Olp[0] = (Word16) Temp + (Word16)PitchMin ;
    }
    else {
        /* transmission error */
        Line.Crc = 1;
        return Line ;
    }

    Line.Sfs[1].AcLg = (Word16) Ser2Par( &Bsp, 2 ) ;

    Temp = Ser2Par( &Bsp, 7 ) ;
    /* Test if forbidden code */
    if( Temp <= 123) {
        Line.Olp[1] = (Word16) Temp + (Word16)PitchMin ;
    }
    else {
        /* transmission error */
        Line.Crc = 1;
        return Line ;
    }

    Line.Sfs[3].AcLg = (Word16) Ser2Par( &Bsp, 2 ) ;

    Line.Sfs[0].AcLg = 1 ;
    Line.Sfs[2].AcLg = 1 ;

    /* Decode the combined gains accordingly to the rate */
    for ( i = 0 ; i < SubFrames ; i ++ ) {

        Temp = Ser2Par( &Bsp, 12 ) ;

        Line.Sfs[i].Tran = 0 ;
        Bound_AcGn = NbFilt170 ;
        if ( (handle->mode == G723_63) && (Line.Olp[i>>1] < (SubFrLen-2) ) ) {
            Line.Sfs[i].Tran = (Word16)(Temp >> 11) ;
            Temp &= 0x000007ffL ;
            Bound_AcGn = NbFilt085 ;
        }
        Line.Sfs[i].AcGn = (Word16)(Temp / (Word16)NumOfGainLev) ;
        if(Line.Sfs[i].AcGn < Bound_AcGn ) {
            Line.Sfs[i].Mamp = (Word16)(Temp % (Word16)NumOfGainLev) ;
        }
        else {
            /* error detected */
            Line.Crc = 1;
            return Line ;
        }
    }

    /* Decode the grids */
    for ( i = 0 ; i < SubFrames ; i ++ )
        Line.Sfs[i].Grid = *Bsp ++ ;

    if (Info == 0) {

        /* Skip the reserved bit */
        Bsp ++ ;

        /* Decode 13 bit combined position index */
        Temp = Ser2Par( &Bsp, 13 ) ;
        Line.Sfs[0].Ppos = ( Temp/90 ) / 9 ;
        Line.Sfs[1].Ppos = ( Temp/90 ) % 9 ;
        Line.Sfs[2].Ppos = ( Temp%90 ) / 9 ;
        Line.Sfs[3].Ppos = ( Temp%90 ) % 9 ;

        /* Decode all the pulse positions */
        Line.Sfs[0].Ppos = ( Line.Sfs[0].Ppos << 16 ) + Ser2Par( &Bsp, 16 ) ;
        Line.Sfs[1].Ppos = ( Line.Sfs[1].Ppos << 14 ) + Ser2Par( &Bsp, 14 ) ;
        Line.Sfs[2].Ppos = ( Line.Sfs[2].Ppos << 16 ) + Ser2Par( &Bsp, 16 ) ;
        Line.Sfs[3].Ppos = ( Line.Sfs[3].Ppos << 14 ) + Ser2Par( &Bsp, 14 ) ;

        /* Decode pulse amplitudes */
        Line.Sfs[0].Pamp = (Word16)Ser2Par( &Bsp, 6 ) ;
        Line.Sfs[1].Pamp = (Word16)Ser2Par( &Bsp, 5 ) ;
        Line.Sfs[2].Pamp = (Word16)Ser2Par( &Bsp, 6 ) ;
        Line.Sfs[3].Pamp = (Word16)Ser2Par( &Bsp, 5 ) ;
    }

    else {

        /* Decode the positions */
        for ( i = 0 ; i < SubFrames ; i ++ )
            Line.Sfs[i].Ppos = Ser2Par( &Bsp, 12 ) ;

        /* Decode the amplitudes */
        for ( i = 0 ; i < SubFrames ; i ++ )
            Line.Sfs[i].Pamp = (Word16)Ser2Par( &Bsp, 4 ) ;
    }
   return Line ;
}

void  Scale( Word16 *Tv, Word32 Sen ,DEC_HANDLE *handle)
{
    int   i ;

    Word32   Acc0,Acc1   ;
    Word16   Exp,SfGain  ;


    Acc0 = Sen ;
    Acc1 = Comp_En( Tv ) ;

    /* Normalize both */
    if ( (Acc1 != (Word32) 0) && (Acc0 != (Word32) 0 ) ) {

        Exp = norm_l( Acc1 ) ;
        Acc1 = L_shl( Acc1, Exp ) ;

        SfGain = norm_l( Acc0 ) ;
        Acc0 = L_shl( Acc0, SfGain ) ;
        Acc0 = L_shr( Acc0, (Word16) 1 ) ;
        Exp = sub( Exp, SfGain ) ;
        Exp = add( Exp, (Word16) 1 ) ;
        Exp = sub( (Word16) 6, Exp ) ;
        if ( Exp < (Word16) 0 )
            Exp = (Word16) 0 ;

        SfGain = extract_h( Acc1 ) ;

        SfGain = div_l( Acc0, SfGain ) ;

        Acc0 = L_deposit_h( SfGain ) ;

        Acc0 = L_shr( Acc0, Exp ) ;

        SfGain = Sqrt_lbc( Acc0 ) ;
    }
    else
        SfGain = 0x1000 ;

    /* Filter the data */
    for ( i = 0 ; i < SubFrLen ; i ++ ) {

        /* Update gain */
        Acc0 = L_deposit_h( handle->DecStat.Gain ) ;
        Acc0 = L_msu( Acc0, handle->DecStat.Gain, (Word16) 0x0800 ) ;
        Acc0 = L_mac( Acc0, SfGain, (Word16) 0x0800 ) ;
        handle->DecStat.Gain = round( Acc0 ) ;

        Exp = add( handle->DecStat.Gain, shr( handle->DecStat.Gain, (Word16) 4) ) ;

        Acc0 = L_mult( Tv[i], Exp ) ;
        Acc0 = L_shl( Acc0, (Word16) 4 ) ;
        Tv[i] = round( Acc0 ) ;
    }

    return;
}

Word32   Comp_En( Word16 *Dpnt )
{
    int   i ;
    Word32   Rez ;
    Word16   Temp[SubFrLen] ;

    for ( i = 0 ; i < SubFrLen ; i ++ )
        Temp[i] = shr( Dpnt[i], (Word16) 2 ) ;

    Rez = (Word32) 0 ;
    for ( i = 0 ; i < SubFrLen ; i ++ )
        Rez = L_mac( Rez, Temp[i], Temp[i] ) ;

    return Rez ;
}



