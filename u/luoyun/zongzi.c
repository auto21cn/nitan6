#include <ansi.h>
#define GIFT_NAME "粽子"
// 本次的礼物发放
#define THIS_GIFT_USER "2013_端午"
// 上次的礼物发放
#define LAST_GIFT_USER "2013_测试礼物5"

inherit ITEM;

void create()
{
	set_name(HIR + GIFT_NAME + NOR, ({"zong zi","zong", "zi"}));
	set_weight(200);
	set("unit", "件");
	set("long",HIG"NT巫师特地为大家制作的端午粽子，看起来很美味的样子，\n品尝(eat)一下是什么味道？\n"NOR);
	set("value", 0);
	set("no_give",1);
	set("no_get",1);
	set("no_put",1);
	set("no_drop",1);
        setup();
}

void init()
{
	add_action("do_eat", "eat");
}

int do_eat(string arg)
{
	object me;
	me = this_player();
	
	if (!id(arg))
		return notify_fail("你要吃什么？\n");
	
	if (query(THIS_GIFT_USER, me) && query("gift_dw", me) == (CHINESE_D->chinese_time(7, ctime(time()))) )  
	{
		tell_object(me,HIY "端午节使者突然在一阵烟雾中出现，一把抓过你手中的粽子：“你今天已经吃过了吧？可别贪心哦！”说完将粽子收走了。\n"NOR);
		destruct(this_object());	
		return 1;
	}
	
	if ( (CHINESE_D->chinese_time(7, ctime(time()))) != "2013/06/12" &&
		(CHINESE_D->chinese_time(7, ctime(time()))) != "2013/06/13" &&
		(CHINESE_D->chinese_time(7, ctime(time()))) != "2013/06/14" ) { //限定在这3天之间使用有效
		tell_object(me,HIY "端午节使者突然在一阵烟雾中出现，一把抓过你手中的粽子：“你这粽子已经过期了吧？”说完将粽子收走了。\n"NOR);
		destruct(this_object());	
		return 1;
	} else {
		tell_object(me, HIC "你看着美味的粽子，想也不想一口吞进了肚里！\n" NOR);     	
		delete(LAST_GIFT_USER, me);//删除上次派礼物生成的参数，增加本次参数，确保每位玩家只能用一次。
		set(THIS_GIFT_USER, 1, me);
		set("gift_dw", (CHINESE_D->chinese_time(7, ctime(time()))), me);
		addn("combat_exp", 10000, me);
		addn("potential", 10000, me);
		addn("max_neili", 100, me);
		addn("max_jingli", 100, me);
		tell_object(me,HIC "你感觉自己身体发生了明显的变化－－长胖了！\n" NOR);     	
		destruct(this_object());
	}
	return 1;
}

void owner_is_killed() { destruct(this_object()); }
