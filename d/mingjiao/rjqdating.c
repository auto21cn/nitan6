//RJQTING.C

inherit ROOM;

void create()
{
        set("short", "��������");
        set("long", @LONG
���������Ĵ�������Ȼ��������֮�ˣ�����ȴ���õù�ɫ���㣬
�Գ����������ڲ�ͬ�������������һ�����ң������ĸ��̽����
��������硻��һ�ٶ�ʮ��ǰ���������������ɹž���һ����ս����
�������������£����߰ˡ��ţ�������������������ڣ�������Դ�
Ϊ����֮�ס���������в輸�����������ʹׯ�������������ڶ�
һ�������
LONG );
        set("exits", ([
                "south" : __DIR__"rjqyuan",
        ]));

        set("objects",([
                __DIR__"npc/zhuangzheng":1,
        ]));
        setup();
        replace_program(ROOM);
}