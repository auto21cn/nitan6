//1997-3-10 by qyz
#include <room.h>
#include <ansi.h>

inherit ROOM;


void create()
{
	set("short",WHT"玄鹤洞"NOR);
	set("long",@LONG
玄鹤洞又叫仙鹤洞，处在绝壁之上，传说洞里有玄鹤，本是广成子座前的仙
童，只因受命到龙门洞提取玉液琼水，与龙宫玉女相恋，广成子大怒，将仙童化
为玄鹤打入石洞，从此，玄鹤情绵绵，恨悠悠，蛰居不出，偶尔在雨霁和风之际
，出洞翱翔。又传说玄鹤出洞，广成子就要回崆峒山收徒。
LONG);
	set("exits",
	([
          "southdown" : __DIR__"xiangtou_ya",
          	]));
        set("outdoors","kongdong");
	set("objects",([
	__DIR__"npc/meihua_lu" : 2,
		]) );
        setup();
        //place_program(ROOM);
}
void init()
{
    object me;
    me = this_player();
    if (!wizardp(me)&&!avatarp(me)&&userp(me)&&!me->query("marks/kongdong/zhou"))
    {
        message_vision("你怎么进来的.....死去吧.....\n",me);
        me->die();
    }
    add_action("do_perform","perform");
    add_action("do_search","search");    
}

int do_search()
{
	object me=this_player();
//	if (me->query("marks/kongdong/dao"))
	{
	tell_object(me,HIG"听罢你顿起好奇心，不由得四处打探了一番，最后你的眼光落在洞口一块突出的岩石上。\n"NOR);
	tell_object(me,HIG"何不拿这块岩石试试新练成的胡家刀法？\n"NOR);
	me->set("marks/kongdong/dao",2);
        return 1;              
	}
	return 0;

}

int do_perform()
{
	object me=this_player();
	object ob;
  	ob = me->query_temp("weapon");
 	if ( !ob || (string)ob->query("weapon_type") != "blade" )
	{tell_object(me,"可惜你没有带刀。\n");
	return 1;} 	
	if (me->query("marks/kongdong/dao")!=2)
	return 0;
	if (me->query_jibie("hujia-dao")<135)
	{tell_object(me,"你的胡家刀法修为不够，在此处施展不开绝技。\n");
	return 1;}
	if (this_object()->query_temp("performed"))
        {message_vision("巨石已经被劈开了。\n",me);
        return 1;
	}        
	message_vision(HIB"$N看准那块突出的岩石,暴喝一声，使出威震八方的绝技，绕着岩石迅速劈\n出四实四虚八刀，手中的刀如同活物。\n刹那间，漫天刀光从各个方向劈向岩石。\n"NOR,me);
	if (me->query("force_factor")>450)
        message_vision(HIR"一道金石撞击之声过后，巨石表面应声而裂，居然露出一面光滑的石壁来。\n",me);
        this_object()->set_temp("performed",1);
        new(__DIR__"obj/shibi")->move(this_object());       
        return 1;
}


int valid_leave(object me,string dir)
{
    if(dir=="southdown")
      message_vision("$N小心翼翼地攀岩附草，往山下爬去。\n",me);
    return ::valid_leave(me,dir);
}
