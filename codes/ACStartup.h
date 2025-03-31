//
//	HEK Analog Clock - 28/04/2024
//
// ACStartup.h
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

#ifndef ACStartupH
#define ACStartupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <AppEvnts.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TStartup : public TForm
{
__published:	// IDE-managed Components
   TImage *Display_;
   TTimer *Timer_;
   TFontDialog *FontDialog_;
   TMainMenu *MainMenu_;
   TMenuItem *About_;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall Timer_Timer(TObject *Sender);
   void __fastcall FormPaint(TObject *Sender);
   void __fastcall FormDblClick(TObject *Sender);
   void __fastcall FontDialog_Close(TObject *Sender);
   void __fastcall FormShow(TObject *Sender);
   void __fastcall About_Click(TObject *Sender);
private:	// User declarations
   int GetR();
   void __fastcall SinCos( const float inValue, float &outSin, float &outCos );
   void __fastcall XY( const float inLength, const float inSin, const float inCos, int &outX, int &outY );
   void DrawBackground();
   void DrawMark();
   void DrawMinuteDial();
   void DrawHourDial();
   void __fastcall DrawHour( const unsigned short inHour, const unsigned short inMinute );
   void __fastcall DrawMinute( const unsigned short inMinute, const unsigned short inSecond );
   void __fastcall DrawSecond( const unsigned short inSecond, const unsigned short inMillisecond );
   void DrawDigitalClock();
public:		// User declarations
   __fastcall TStartup(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TStartup *Startup;
//---------------------------------------------------------------------------
#endif
