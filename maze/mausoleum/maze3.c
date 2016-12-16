// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit VRM_SERVER;

void create()
{
        //�Թ��������̳е�����ĵ������ơ�
        set_inherit_room( ROOM );

        //Ψһ����
        set_unique_room( ({
                "/maze/mausoleum/unique_room/goldman_room",
                "/maze/mausoleum/unique_room/goldman_room2",
                "/maze/mausoleum/unique_room/goldman_room3",
                "/maze/mausoleum/unique_room/goldman_room4",
        }) );

        //���ķ���
        set_center_room("/maze/mausoleum/unique_room/king_room");

        set_lonely_create(1);

        set_maze_boxs(1);

        set_maze_traps(2);

        //�Թ��ĵ��߳�
        set_maze_long(10);

        //��ڷ���(�����ڶ���)
        set_entry_dir("west");

        //�������������ӷ���
        set_link_entry_dir("west");

        //�������������ӵ�����
        set_link_entry_room(__DIR__"westgate");

        //��������������ӷ���
        set_link_exit_dir("east");

        //��������������ӵ�����
        set_link_exit_room("/d/luoyang/wenmiao");


        //��ͨ��������
        set_maze_room_short(HIY "�����ڹ�" NOR);

        set_maze_room_desc(@LONG
�Լ�վ�ڳ����İ���ʯ��֮�ף�ʯ��ֱͨ���Ϸ����������ߡ�ʮ��
�����ľ޴�ƽ̨����ͷ��ȥ�������ĺ�ɫ���׺����ǧ��ű�ʯ�����飬
��ʶ�Ŀ�������Ǻӣ������ҹ�գ��������յ�һƬ������������
�����Ķ���·�����Ȼ����һ���εض�������������ΰ���ǡ���Ρ
��׳���ĳ�¥������Ķ��ǵ����ܷ��ߣ������۴��ڰ���ʯ̨�ϣ���
̩ɽѹ�������ȳ�����¥��Ҫ���ư��硢���������ʯ�����ߵĹ㳡�ϣ�
�������龹ȫ���гɷ���ı�ٸ��ͭ�ˡ���ٸ��ʯ�񡭡�������ӣ���
˵Ҳ�м���֮�ڣ�������׳���������ݡ��㳡�ϣ�һ�����������ѽ�����
��ҫ����Ŀ�Ĺ��󣬾����ǽ��ӻ㼯��һ�볯����һ���׹�������ˮ��
��ȥ��
LONG);

        //��ڷ��������
        set_entry_short(HIR "�����ڹ����" NOR);

        //��ڷ�������
        set_entry_desc(@LONG
�Լ�վ�ڳ����İ���ʯ��֮�ף�ʯ��ֱͨ���Ϸ����������ߡ�ʮ��
�����ľ޴�ƽ̨����ͷ��ȥ�������ĺ�ɫ���׺����ǧ��ű�ʯ�����飬
��ʶ�Ŀ�������Ǻӣ������ҹ�գ��������յ�һƬ������������
�����Ķ���·�����Ȼ����һ���εض�������������ΰ���ǡ���Ρ
��׳���ĳ�¥������Ķ��ǵ����ܷ��ߣ������۴��ڰ���ʯ̨�ϣ���
̩ɽѹ�������ȳ�����¥��Ҫ���ư��硢���������ʯ�����ߵĹ㳡�ϣ�
�������龹ȫ���гɷ���ı�ٸ��ͭ�ˡ���ٸ��ʯ�񡭡�������ӣ���
˵Ҳ�м���֮�ڣ�������׳���������ݡ��㳡�ϣ�һ�����������ѽ�����
��ҫ����Ŀ�Ĺ��󣬾����ǽ��ӻ㼯��һ�볯����һ���׹�������ˮ��
��ȥ��
LONG);

        //���ڷ��������
        set_exit_short(HIW "�����ڹ�����" NOR);

        //���ڷ�������
        set_exit_desc(@LONG
�Լ�վ�ڳ����İ���ʯ��֮�ף�ʯ��ֱͨ���Ϸ����������ߡ�ʮ��
�����ľ޴�ƽ̨����ͷ��ȥ�������ĺ�ɫ���׺����ǧ��ű�ʯ�����飬
��ʶ�Ŀ�������Ǻӣ������ҹ�գ��������յ�һƬ������������
�����Ķ���·�����Ȼ����һ���εض�������������ΰ���ǡ���Ρ
��׳���ĳ�¥������Ķ��ǵ����ܷ��ߣ������۴��ڰ���ʯ̨�ϣ���
̩ɽѹ�������ȳ�����¥��Ҫ���ư��硢���������ʯ�����ߵĹ㳡�ϣ�
�������龹ȫ���гɷ���ı�ٸ��ͭ�ˡ���ٸ��ʯ�񡭡�������ӣ���
˵Ҳ�м���֮�ڣ�������׳���������ݡ��㳡�ϣ�һ�����������ѽ�����
��ҫ����Ŀ�Ĺ��󣬾����ǽ��ӻ㼯��һ�볯����һ���׹�������ˮ��
��ȥ��
LONG);
}