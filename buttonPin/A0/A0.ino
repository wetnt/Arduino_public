//================================================================================
//================================================================================
//	Keyboard

#define KEY_LEFT_CTRL		0x80
#define KEY_LEFT_SHIFT		0x81
#define KEY_LEFT_ALT		0x82
#define KEY_LEFT_GUI		0x83
#define KEY_RIGHT_CTRL		0x84
#define KEY_RIGHT_SHIFT		0x85
#define KEY_RIGHT_ALT		0x86
#define KEY_RIGHT_GUI		0x87

#define KEY_UP_ARROW		0xDA
#define KEY_DOWN_ARROW		0xD9
#define KEY_LEFT_ARROW		0xD8
#define KEY_RIGHT_ARROW		0xD7
#define KEY_BACKSPACE		0xB2
#define KEY_TAB				0xB3
#define KEY_RETURN			0xB0
#define KEY_ESC				0xB1
#define KEY_INSERT			0xD1
#define KEY_DELETE			0xD4
#define KEY_PAGE_UP			0xD3
#define KEY_PAGE_DOWN		0xD6
#define KEY_HOME			0xD2
#define KEY_END				0xD5
#define KEY_CAPS_LOCK		0xC1
#define KEY_F1				0xC2
#define KEY_F2				0xC3
#define KEY_F3				0xC4
#define KEY_F4				0xC5
#define KEY_F5				0xC6
#define KEY_F6				0xC7
#define KEY_F7				0xC8
#define KEY_F8				0xC9
#define KEY_F9				0xCA
#define KEY_F10				0xCB
#define KEY_F11				0xCC
#define KEY_F12				0xCD




ASCII表
ASCII值	控制字符	ASCII值	控制字符	ASCII值	控制字符	ASCII值	控制字符
0	NUT	32	(space)	64	@	96	、
1	SOH	33	！	65	A	97	a
2	STX	34	”	66	B	98	b
3	ETX	35	#	67	C	99	c
4	EOT	36	$	68	D	100	d
5	ENQ	37	%	69	E	101	e
6	ACK	38	&	70	F	102	f
7	BEL	39	,	71	G	103	g
8	BS	40	(	72	H	104	h
9	HT	41	)	73	I	105	i
10	LF	42	*	74	J	106	j
11	VT	43	+	75	K	107	k
12	FF	44	,	76	L	108	l
13	CR	45	-	77	M	109	m
14	SO	46	.	78	N	110	n
15	SI	47	/	79	O	111	o
16	DLE	48	0	80	P	112	p
17	DCI	49	1	81	Q	113	q
18	DC2	50	2	82	R	114	r
19	DC3	51	3	83	S	115	s
20	DC4	52	4	84	T	116	t
21	NAK	53	5	85	U	117	u
22	SYN	54	6	86	V	118	v
23	TB	55	7	87	W	119	w
24	CAN	56	8	88	X	120	x
25	EM	57	9	89	Y	121	y
26	SUB	58	:	90	Z	122	z
27	ESC	59	;	91	[	123	{
28	FS	60	<	92		124	|
29	GS	61	=	93	]	125	}
30	RS	62	>	94	^	126	~
31	US	63	?	95	—	127	DEL

NUL	VT 垂直制表	SYN 空转同步
SOH     标题开始	FF      走纸控制	ETB     信息组传送结束
STX     正文开始	CR      回车	CAN     作废
ETX     正文结束	SO      移位输出	EM      纸尽
EOY     传输结束	SI       移位输入	SUB     换置
ENQ     询问字符	DLE     空格	ESC     换码
ACK     承认	DC1     设备控制1	FS      文字分隔符
BEL     报警	DC2     设备控制2	GS      组分隔符
BS      退一格	DC3     设备控制3	RS      记录分隔符
HT      横向列表	DC4     设备控制4	US      单元分隔符
LF      换行	NAK     否定	DEL     删除

键盘常用ASCII码
ESC键 VK_ESCAPE (27) 
回车键： VK_RETURN (13)
TAB键： VK_TAB (9)
Caps Lock键： VK_CAPITAL (20)
Shift键： VK_SHIFT ($10)
Ctrl键： VK_CONTROL (17)
Alt键： VK_MENU (18)
空格键： VK_SPACE ($20/32)
退格键： VK_BACK (8)
左徽标键： VK_LWIN (91)
右徽标键： VK_LWIN (92)
鼠标右键快捷键：VK_APPS (93)       
Insert键： VK_INSERT (45)
Home键： VK_HOME (36)
Page Up： VK_PRIOR (33)
PageDown： VK_NEXT (34)
End键： VK_END (35)
Delete键： VK_DELETE (46)
方向键(←)： VK_LEFT (37)
方向键(↑)： VK_UP (38)
方向键(→)： VK_RIGHT (39)
方向键(↓)： VK_DOWN (40)
F1键： VK_F1 (112)
F2键： VK_F2 (113)
F3键： VK_F3 (114)
F4键： VK_F4 (115)
F5键： VK_F5 (116)
F6键： VK_F6 (117)
F7键： VK_F7 (118)
F8键： VK_F8 (119)
F9键： VK_F9 (120)
F10键： VK_F10 (121)
F11键： VK_F11 (122)
F12键： VK_F12 (123)
Num Lock键： VK_NUMLOCK (144)
小键盘0： VK_NUMPAD0 (96)
小键盘1： VK_NUMPAD0 (97)
小键盘2： VK_NUMPAD0 (98)
小键盘3： VK_NUMPAD0 (99)
小键盘4： VK_NUMPAD0 (100)
小键盘5： VK_NUMPAD0 (101)
小键盘6： VK_NUMPAD0 (102)
小键盘7： VK_NUMPAD0 (103)
小键盘8： VK_NUMPAD0 (104)
小键盘9： VK_NUMPAD0 (105)
小键盘.： VK_DECIMAL (110)
小键盘*： VK_MULTIPLY (106)
小键盘+： VK_MULTIPLY (107)
小键盘-： VK_SUBTRACT (109)
小键盘/： VK_DIVIDE (111)
Pause Break键： VK_PAUSE (19)
Scroll Lock键： VK_SCROLL (145)
