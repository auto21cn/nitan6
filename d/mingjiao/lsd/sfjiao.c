// /u/qingyun/lsd/sfjiao.c
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", GRN"ɽ�����"NOR);
        set("long", @LONG
�������ܳ������೤�ݣ��˵���Ϊ�����ߵ��������϶�Ȼ������
�࣬��ʱ���ж���ܳ�����������ֻ�ܾ�����ͺ��ɽʯ����š�����
������ɽ�嶥������ϡ�ɼ�һ��é���������С�
LONG );
	set("exits", ([ 
  		"south" : __DIR__"lsgu",
  		"northup" : __DIR__"shanfeng",
	]));
	set("objects",([
            "/clone/beast/snake"  :       1,
	]));
	set("outdoors","���ߵ�");
	setup();
}