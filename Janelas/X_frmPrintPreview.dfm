object frmPrintPreview: TfrmPrintPreview
  Left = 252
  Top = 167
  Width = 397
  Height = 417
  Caption = 'ModelAGE - Print Preview'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    0000000000000000000000000000000000000000000000077788888888800000
    0000000000000007787888888880000000000000000000077788888888800000
    0000000000000007787888888880000000000000000000000000000000000000
    0000000000000007778888888880000000000000000000077878888888800000
    0000000000000007778888888880000000000000000000000000000000000000
    0000000000000007778888888880000000000000000000077878888888800000
    0000000000000007778888888880000000000000000000077878888888800000
    0000000000000007778888888880000000000000000000000000000000000000
    0000000000000000000000000000077788888888800000000000000000000778
    7888888880000000000000000000077788888888800000000000000000000778
    7888888880000000000000000000000000000000000000000000000000000777
    8888888880000000000000000000077878888888800000000000000000000777
    8888888880000000000000000000000000000000000000000000000000000777
    8888888880000000000000000000077878888888800000000000000000000777
    8888888880000000000000000000077878888888800000000000000000000777
    888888888000000000000000000000000000000000000000000000000000FFFF
    C000FFFFC000FFFFC000FFFFC000FFFFC000FFFFC000FFFFC000FC000000FDFF
    C000FDFFC000FDFFC000FDFFC000E03FC000F77FC000FAFFC000FDFFC0000003
    FFBF0003FF5F0003FEEF0003FF5F0003FFBF0003FFBF0003FFBF0003FFBF0000
    003F0003FFFF0003FFFF0003FFFF0003FFFF0003FFFF0003FFFF0003FFFF}
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Prn: TPagePrinter
    Left = 0
    Top = 0
    Width = 389
    Height = 349
    HorzScrollBar.Increment = 16
    HorzScrollBar.Range = 210
    HorzScrollBar.Tracking = True
    VertScrollBar.Increment = 16
    VertScrollBar.Range = 293
    VertScrollBar.Tracking = True
    Align = alClient
    AutoScroll = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    TabOrder = 0
    MeasureUnit = muMillimeters
    DefaultColWidth = 25.4
    FriendlyFooter = '&l&d&r&t'
    FriendlyHeader = '&l&i&rPage &p'
    Lines.Strings = (
      'type'
      '  TMainForm = class(TForm)'
      '    Prn: TPagePrinter;'
      '    Panel1: TPanel;'
      '    btnPreview: TButton;'
      '    Label1: TLabel;'
      '    btnNextPage: TSpeedButton;'
      '    btnPrevPage: TSpeedButton;'
      '    Label4: TLabel;'
      '    ZoomList: TComboBox;'
      '    ZoomTimer: TTimer;'
      '    btnPrint: TButton;'
      '    procedure btnPreviewClick(Sender: TObject);'
      '    procedure FormShow(Sender: TObject);'
      '    procedure btnNextPageClick(Sender: TObject);'
      '    procedure btnPrevPageClick(Sender: TObject);'
      '    procedure ZoomListKeyPress(Sender: TObject; var Key: Char);'
      '    procedure ZoomListClick(Sender: TObject);'
      '    procedure ZoomTimerTimer(Sender: TObject);'
      '    procedure btnPrintClick(Sender: TObject);'
      '  private'
      '    { Private declarations }'
      '  public'
      '    { Public declarations }'
      '  end;'
      ''
      ''
      'NETDI: NdiCreate(TCP/IP) OK'
      ''
      'NETDI: NETDI: lpRegLogConf = 0x0'
      ''
      
        'NETDI: ClassInstall (0x9 on 0x19fe:0xfa0) on  at Enum\Root\Net\0' +
        '000'
      ''
      'NETDI: Validating TCP/IP at Enum\Network\MSTCP\0000, rc = 0x0'
      ''
      
        'NETDI: Validating Client for NetWare Networks at Enum\Network\NW' +
        'REDIR\0000, rc = 0x0'
      ''
      
        'NETDI: Validating Client for Microsoft Networks at Enum\Network\' +
        'VREDIR\0000, rc = 0x0'
      ''
      'NETDI: Validating NetBEUI at Enum\Network\NETBEUI\0000, rc = 0x0'
      ''
      
        'NETDI: Validating IPX/SPX-compatible Protocol at Enum\Network\NW' +
        'LINK\0000, rc = 0x0'
      ''
      
        'NETDI: Validating Dial-Up Adapter at Enum\Root\Net\0000, rc = 0x' +
        '0 NETDI: ClassInstall(0x9) end NETDI: ClassInstall (0xa on 0x19f' +
        'e:0xfa0) on  at Enum\Root\Net\0000 NETDI: ChangeLine: No matches' +
        ' found. NETDI: ClassInstall(0xa) end'
      ''
      
        'NETDI: ClassInstall (0xc on 0x19fe:0xfa0) on  at Enum\Root\Net\0' +
        '000'
      ''
      'NETDI: ClassInstall(0xc) end')
    MarginBottom = 25.4
    MarginLeft = 25.4
    MarginRight = 25.4
    MarginTop = 25.4
    PageBorderOffset = 1.5875
    PageBorders = [pbTop, pbBottom]
    TableFormat = '<25,4|^-25,4|>25,4'
    TableGrid = True
    Title = 'X-Model'
  end
  object Panel1: TPanel
    Left = 0
    Top = 349
    Width = 389
    Height = 41
    Align = alBottom
    TabOrder = 1
    object Label1: TLabel
      Left = 122
      Top = 14
      Width = 28
      Height = 13
      Caption = 'Page:'
    end
    object lblPage: TLabel
      Left = 207
      Top = 20
      Width = 27
      Height = 13
      Caption = '0 of 0'
    end
    object btnNextPage: TSpeedButton
      Left = 154
      Top = 8
      Width = 25
      Height = 25
      Glyph.Data = {
        4E010000424D4E01000000000000760000002800000012000000120000000100
        040000000000D800000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00BBBBBBFFFFFF
        BBBBBB000000BBBBBB78888FBBBBBB000000BBBBBB78888FBBBBBB000000BBBB
        BB78888FBBBBBB000000BBBBBB78888FBBBBBB000000BBBBBB78888FBBBBBB00
        00007FFFFFF8888FFFFFFF00000078888888888888888F000000788888888888
        88888F00000078888888888888888F00000078888888888888888F0000007777
        7778888F77777F000000BBBBBB78888FBBBBBB000000BBBBBB78888FBBBBBB00
        0000BBBBBB78888FBBBBBB000000BBBBBB78888FBBBBBB000000BBBBBB78888F
        BBBBBB000000BBBBBB777777BBBBBB000000}
      OnClick = btnNextPageClick
    end
    object btnPrevPage: TSpeedButton
      Left = 180
      Top = 8
      Width = 25
      Height = 25
      Glyph.Data = {
        4E010000424D4E01000000000000760000002800000012000000120000000100
        040000000000D800000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00BBBBBBBBBBBB
        BBBBBB000000BBBBBBBBBBBBBBBBBB000000BBBBBBBBBBBBBBBBBB000000BBBB
        BBBBBBBBBBBBBB000000BBBBBBBBBBBBBBBBBB000000BBBBBBBBBBBBBBBBBB00
        00007FFFFFFFFFFFFFFFFF00000078888888888888888F000000788888888888
        88888F00000078888888888888888F00000078888888888888888F0000007777
        7777777777777F000000BBBBBBBBBBBBBBBBBB000000BBBBBBBBBBBBBBBBBB00
        0000BBBBBBBBBBBBBBBBBB000000BBBBBBBBBBBBBBBBBB000000BBBBBBBBBBBB
        BBBBBB000000BBBBBBBBBBBBBBBBBB000000}
      OnClick = btnPrevPageClick
    end
    object btnPrint: TBitBtn
      Left = 8
      Top = 8
      Width = 65
      Height = 25
      Caption = 'Print'
      TabOrder = 0
      OnClick = btnPrintClick
      Glyph.Data = {
        66010000424D6601000000000000760000002800000014000000140000000100
        040000000000F000000000000000000000001000000010000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
        DDDDDDDD0000DDDDDDDDDDDDDDDDDDDD0000DDDDD7777777777DDDDD0000DDDD
        000000000007DDDD0000DDD07878787870707DDD0000DD0000000000000707DD
        0000DD0F8F8F8AAA8F0007DD0000DD08F8F8F999F80707DD0000DD0000000000
        0008707D0000DD08F8F8F8F8F080807D0000DDD0000000000F08007D0000DDDD
        0BFFFBFFF0F080DD0000DDDDD0F00000F0000DDD0000DDDDD0FBFFFBFF0DDDDD
        0000DDDDDD0F00000F0DDDDD0000DDDDDD0FFBFFFBF0DDDD0000DDDDDDD00000
        0000DDDD0000DDDDDDDDDDDDDDDDDDDD0000DDDDDDDDDDDDDDDDDDDD0000DDDD
        DDDDDDDDDDDDDDDD0000}
    end
    object ZoomList: TComboBox
      Left = 279
      Top = 12
      Width = 90
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      Text = '25%'
      OnClick = ZoomListClick
      OnKeyPress = ZoomListKeyPress
      Items.Strings = (
        '200%'
        '175%'
        '150%'
        '125%'
        '100%'
        '50%'
        'Fit To Width'
        'Fit To Height'
        'Whole Page')
    end
  end
  object ZoomTimer: TTimer
    Enabled = False
    Interval = 50
    OnTimer = ZoomTimerTimer
    Left = 4
    Top = 4
  end
end
