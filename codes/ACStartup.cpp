//
//	HEK Analog Clock - 28/04/2024
//
// ACStartup.cpp
//
// Author:
//       Kartal, Hakan Emre <hek@nula.com.tr>
//
// Copyright (c) 2024 Kartal, Hakan Emre
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "ACStartup.h"
#include "ACAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TStartup *Startup;
//---------------------------------------------------------------------------
#define F_RAD           ((float)(M_PI / 180.0))
#define RAD_F           (1.0f / F_RAD)
//---------------------------------------------------------------------------
#define HOUR_F          (30.0f * F_RAD)
#define MINUTE_F        (06.0f * F_RAD)
#define SECOND_F        (06.0f * F_RAD)
#define SPLITSECOND_F   (00.36f * F_RAD)
//---------------------------------------------------------------------------
#ifndef min
#  define min(a,b)(((a)>(b))?(b):(a))
#endif
//---------------------------------------------------------------------------
void __fastcall TStartup::SinCos( const float inValue, float& outSin, float &outCos )
{
   outSin = sin( inValue );
   outCos = cos( inValue );
}
//---------------------------------------------------------------------------
void __fastcall TStartup::XY( const float inLength, const float inSin, const float inCos, int &outX, int &outY )
{
   outX = (int)(inLength * inCos);
   outY = (int)(inLength * inSin);
}
//---------------------------------------------------------------------------
int TStartup::GetR()
{
   return (int)(min(Display_->Height, Display_->Width) * 0.425f);
}
//---------------------------------------------------------------------------
void TStartup::DrawBackground()
{
#define _Canvas ((TCanvas *)Display_->Picture->Bitmap->Canvas)
   _Canvas->Brush->Style = bsSolid;
   _Canvas->Brush->Color = this->Color;

   _Canvas->FillRect( Display_->ClientRect );
#undef _Canvas
}
//---------------------------------------------------------------------------
void TStartup::DrawMark()
{
#define _Canvas ((TCanvas *)Display_->Picture->Bitmap->Canvas)
   AnsiString \
      l_strMark = "HEK";
   TRect \
      l_varRect = Display_->ClientRect, \
      l_varTextRect = l_varRect;

   _Canvas->Font = FontDialog_->Font;
   _Canvas->Font->Size = 30;

   DrawTextA( _Canvas->Handle, l_strMark.c_str(), l_strMark.Length(), &l_varTextRect,
              DT_CALCRECT );

   OffsetRect( &l_varTextRect,
               ((l_varRect.Right - l_varRect.Left) - (l_varTextRect.Right - l_varTextRect.Left)) / 2.0,
               (int)((l_varTextRect.Bottom - l_varTextRect.Top) * 2.00f) );

   DrawTextA( _Canvas->Handle, l_strMark.c_str(), l_strMark.Length(), &l_varTextRect,
              DT_TOP | DT_CENTER | DT_SINGLELINE );
#undef _Canvas
}

//---------------------------------------------------------------------------
void TStartup::DrawMinuteDial()
{
#define _Canvas ((TCanvas *)Display_->Picture->Bitmap->Canvas)

   TRect \
      l_varRect;
   TPoint \
      l_varCenter;
   float \
      l_fSin, \
      l_fCos;
   int \
      y, x, i, \
      R = GetR();

   l_varRect = Display_->ClientRect;

   l_varCenter.x = (l_varRect.Left + ((l_varRect.Right - l_varRect.Left) * 0.5));
   l_varCenter.y = (l_varRect.Top + ((l_varRect.Bottom - l_varRect.Top) * 0.5));

   _Canvas->Brush->Style = bsSolid;

   _Canvas->Pen->Style = psSolid;
   
   _Canvas->Pen->Width = 1;
   _Canvas->Pen->Color = clSilver;

   for (i = 0; i < 60; i++)
   {
      SinCos( i * MINUTE_F, l_fSin, l_fCos );

      XY( (int)(R * 0.85f), l_fSin, l_fCos, y, x );
      _Canvas->MoveTo( l_varCenter.x + x, l_varCenter.y - y );

      XY( (int)(R * 0.95f), l_fSin, l_fCos, y, x );
      _Canvas->LineTo( l_varCenter.x + x, l_varCenter.y - y );
   }

#undef _Canvas
}
//---------------------------------------------------------------------------
void TStartup::DrawHourDial()
{
#define _Canvas ((TCanvas *)Display_->Picture->Bitmap->Canvas)

   TRect \
      l_varRect;
   TPoint \
      l_varCenter;
   float \
      l_fSin, \
      l_fCos;
   int \
      y, x, i, \
      R = GetR();
   TSize \
      l_varSize;
   AnsiString \
      l_strText;

   l_varRect = Display_->ClientRect;

   l_varCenter.x = (l_varRect.Left + ((l_varRect.Right - l_varRect.Left) * 0.5));
   l_varCenter.y = (l_varRect.Top + ((l_varRect.Bottom - l_varRect.Top) * 0.5));

   _Canvas->Pen->Style = psSolid;
   _Canvas->Pen->Width = 5;

   _Canvas->Font = FontDialog_->Font;

   for (i = 0; i < 12; i++)
   {
      _Canvas->Brush->Style = bsSolid;
      _Canvas->Pen->Style = psSolid;

      _Canvas->Pen->Color = ((i % 0x0003) == 0) ? clGray : clSilver;

      SinCos( i * HOUR_F, l_fSin, l_fCos );

      XY( (int)(R * 0.85f), l_fSin, l_fCos, y, x );
      _Canvas->MoveTo( l_varCenter.x + x, l_varCenter.y - y );

      XY( R, l_fSin, l_fCos, y, x );
      _Canvas->LineTo( l_varCenter.x + x, l_varCenter.y - y );

      _Canvas->Brush->Style = bsClear;
      _Canvas->Pen->Style = psClear;

      x = (int)((R * 1.125f) * l_fSin);
      y = (int)((R * 1.125f) * -l_fCos);

      l_varSize = _Canvas->TextExtent( l_strText = IntToStr( (i == 0) ? (12) : (i) ) );

      _Canvas->TextOut( l_varCenter.x + (x - (int)(l_varSize.cx * 0.5)),
                        l_varCenter.y + (y - (int)(l_varSize.cy * 0.5)),
                        l_strText );

   }
#undef _Canvas
}
//---------------------------------------------------------------------------
void __fastcall TStartup::DrawHour( const unsigned short inHour, const unsigned short inMinute )
{
#define _Canvas ((TCanvas *)Display_->Picture->Bitmap->Canvas)

   TRect \
      l_varRect;
   TPoint \
      l_varCenter;
   float \
      l_fSin, \
      l_fCos;
   int \
      y, x, \
      R = GetR();

   l_varRect = Display_->ClientRect;

   l_varCenter.x = (l_varRect.Left + ((l_varRect.Right - l_varRect.Left) * 0.5));
   l_varCenter.y = (l_varRect.Top + ((l_varRect.Bottom - l_varRect.Top) * 0.5));

   _Canvas->Pen->Style = psSolid;
   _Canvas->Pen->Color = clBlue;
   _Canvas->Pen->Width = 12;

   _Canvas->MoveTo( l_varCenter.x, l_varCenter.y ),

   SinCos( (((inHour % 12) + (inMinute / 60.0f)) * HOUR_F), l_fSin, l_fCos );

   XY( (int)(R * 0.65f), l_fSin, l_fCos, y, x );
   _Canvas->LineTo( l_varCenter.x + x, l_varCenter.y - y );

   _Canvas->Brush->Style = bsSolid;
   _Canvas->Brush->Color = clRed;

   _Canvas->Pen->Color = clBlue;
   _Canvas->Pen->Width = 5;

   _Canvas->Ellipse( l_varCenter.x - 13, l_varCenter.y - 13, l_varCenter.x + 13, l_varCenter.y + 13 );
#undef _Canvas
}
//---------------------------------------------------------------------------
void __fastcall TStartup::DrawMinute( const unsigned short inMinute, const unsigned short inSecond )
{
#define _Canvas ((TCanvas *)Display_->Picture->Bitmap->Canvas)

   TRect \
      l_varRect;
   TPoint \
      l_varCenter;
   float \
      l_fSin, \
      l_fCos;
   int \
      y, x, \
      R = GetR();

   l_varRect = Display_->ClientRect;

   l_varCenter.x = (l_varRect.Left + ((l_varRect.Right - l_varRect.Left) * 0.5));
   l_varCenter.y = (l_varRect.Top + ((l_varRect.Bottom - l_varRect.Top) * 0.5));

   /*
    * MINUTE
    */
   _Canvas->Pen->Color = clLime;

   _Canvas->MoveTo( l_varCenter.x, l_varCenter.y ),

   SinCos( ((inMinute + (inSecond / 60.0f)) * MINUTE_F), l_fSin, l_fCos );

   XY( (int)(R * 0.80f), l_fSin, l_fCos, y, x );
   _Canvas->LineTo( l_varCenter.x + x, l_varCenter.y - y );

   _Canvas->Brush->Style = bsSolid;
   _Canvas->Brush->Color = clRed;

   _Canvas->Pen->Color = clLime;
   _Canvas->Pen->Width = 5;

   _Canvas->Ellipse( l_varCenter.x - 13, l_varCenter.y - 13, l_varCenter.x + 13, l_varCenter.y + 13 );
#undef _Canvas
}
//---------------------------------------------------------------------------
void __fastcall TStartup::DrawSecond( const unsigned short inSecond, const unsigned short inMillisecond )
{
#define _Canvas ((TCanvas *)Display_->Picture->Bitmap->Canvas)

   TRect \
      l_varRect;
   TPoint \
      l_varCenter;
   float \
      l_fSin, \
      l_fCos;
   int \
      y, x, \
      R = GetR();

   l_varRect = Display_->ClientRect;

   l_varCenter.x = (l_varRect.Left + ((l_varRect.Right - l_varRect.Left) * 0.5));
   l_varCenter.y = (l_varRect.Top + ((l_varRect.Bottom - l_varRect.Top) * 0.5));

   _Canvas->Pen->Style = psSolid;
   _Canvas->Pen->Color = clRed;
   _Canvas->Pen->Width = 3;

   _Canvas->MoveTo( l_varCenter.x, l_varCenter.y ),

   SinCos( ((inSecond + (inMillisecond / 1000.f)) * SECOND_F), l_fSin, l_fCos );

   XY( (int)(R * 0.75f), l_fSin, l_fCos, y, x );
   _Canvas->LineTo( l_varCenter.x + x, l_varCenter.y - y );

   _Canvas->MoveTo( l_varCenter.x, l_varCenter.y );

   XY( (int)(R * 0.25f), -l_fSin, -l_fCos, y, x );
   _Canvas->LineTo( l_varCenter.x + x, l_varCenter.y - y );

#undef _Canvas
}
//---------------------------------------------------------------------------
void TStartup::DrawDigitalClock()
{
#define _Canvas ((TCanvas *)Display_->Picture->Bitmap->Canvas)

   TRect \
      l_varRect = Display_->ClientRect, \
      l_varTextRect = l_varRect;
   AnsiString \
      l_strDateTime = FormatDateTime( "dd/MMM/yyyy dddd\r\H:nn:ss.zzz", Now() );


   _Canvas->Font = FontDialog_->Font;
   _Canvas->Font->Size = 10;

   DrawTextA( _Canvas->Handle, l_strDateTime.c_str(), l_strDateTime.Length(), &l_varTextRect,
              DT_WORDBREAK | DT_CALCRECT );

   OffsetRect( &l_varTextRect,
               (((l_varRect.Right - l_varRect.Left) - (l_varTextRect.Right - l_varTextRect.Left)) / 2),
               (l_varRect.Bottom - (int)((l_varTextRect.Bottom - l_varTextRect.Top) * 4.25f)) );

   l_varRect = l_varTextRect;
   InflateRect( &l_varRect, +8, +5 );

   _Canvas->Brush->Style = bsClear;

   _Canvas->Pen->Style = psSolid;
   _Canvas->Pen->Color = _Canvas->Font->Color;
   _Canvas->Pen->Width = 1;

   _Canvas->RoundRect( l_varRect.Left, l_varRect.Top,
                       l_varRect.Right, l_varRect.Bottom,
                       5, 5 );

   DrawTextA( _Canvas->Handle, l_strDateTime.c_str(), l_strDateTime.Length(), &l_varTextRect,
              DT_WORDBREAK | DT_CENTER );

#undef _Canvas
}
//---------------------------------------------------------------------------
__fastcall TStartup::TStartup(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TStartup::FormCreate(TObject *Sender)
{
   Display_->Picture->Bitmap = new Graphics::TBitmap();

   Display_->Picture->Bitmap->PixelFormat = pf24bit;

   Display_->Picture->Bitmap->Width = Display_->Width;
   Display_->Picture->Bitmap->Height = Display_->Height;

}
//---------------------------------------------------------------------------
void __fastcall TStartup::Timer_Timer(TObject *Sender)
{
   Timer_->Enabled = false;

   unsigned short \
      l_ushHour,
      l_ushMinute,
      l_ushSecond,
      l_ushMillisecond;

   DecodeTime( Time(), l_ushHour, l_ushMinute, l_ushSecond, l_ushMillisecond );

   DrawBackground();

   DrawMark();

   DrawMinuteDial();
   DrawHourDial();

   DrawDigitalClock();

   DrawHour( l_ushHour, l_ushMinute );
   DrawMinute( l_ushMinute, l_ushSecond );
   DrawSecond( l_ushSecond, l_ushMillisecond );

   TRect \
      l_varRect = ClientRect;
      
   InvalidateRect( Handle, &l_varRect, FALSE );

   Timer_->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TStartup::FormPaint(TObject *Sender)
{
   Canvas->Draw( 0, 0, Display_->Picture->Bitmap );
}
//---------------------------------------------------------------------------
void __fastcall TStartup::FormDblClick(TObject *Sender)
{
   FontDialog_->Execute();   
}
//---------------------------------------------------------------------------
void __fastcall TStartup::FontDialog_Close(TObject *Sender)
{
   Timer_Timer( NULL );   
}
//---------------------------------------------------------------------------
void __fastcall TStartup::FormShow(TObject *Sender)
{
   Timer_Timer( NULL );
}
//---------------------------------------------------------------------------


void __fastcall TStartup::About_Click(TObject *Sender)
{
   (new TAbout( Application ))->ShowModal();
}
//---------------------------------------------------------------------------

