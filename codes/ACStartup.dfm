object Startup: TStartup
  Left = 1495
  Top = 466
  BorderStyle = bsToolWindow
  BorderWidth = 20
  Caption = 'HEK Analog Clock'
  ClientHeight = 352
  ClientWidth = 352
  Color = clWindow
  Ctl3D = False
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu_
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnDblClick = FormDblClick
  OnPaint = FormPaint
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Display_: TImage
    Left = 0
    Top = 0
    Width = 352
    Height = 352
    Align = alClient
    Visible = False
  end
  object Timer_: TTimer
    Interval = 10
    OnTimer = Timer_Timer
    Left = 136
    Top = 64
  end
  object FontDialog_: TFontDialog
    OnClose = FontDialog_Close
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -19
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    MinFontSize = 0
    MaxFontSize = 0
    Left = 40
    Top = 56
  end
  object MainMenu_: TMainMenu
    Left = 216
    Top = 88
    object About_: TMenuItem
      Caption = 'About'
      OnClick = About_Click
    end
  end
end
