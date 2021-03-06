// special

#include <ansi.h>

#define TAOZHUANG_D   "/adm/daemons/taozhuangd"

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string tzx, result, *keys_tzlist;
	object ob;
	int i;
	mapping tz;
	string *keys_tz, str_color;

	mapping tzlist = ([
		"head"       :  "头饰",
		"waist"      :  "腰带",
		"boots"      :  "靴子",
		"surcoat"    :  "披风",//
		"armor"      :  "战甲",
		"cloth"      :  "战衣",
		"wrists"     :  "护腕",
		"neck"       :  "项链",
		"rings"      :  "戒指",
		"myheart"    :  "左符",
		"myheart2"   :  "右符",
	]);

	if (! objectp(me))return 0;

	if (! arg)arg = "show";

	keys_tzlist = keys(tzlist);

	// 一次性穿上一套
	if (arg == "wear")
	{
		tz = me->query("tzlist");

		if (! sizeof(tz))
			return notify_fail("你还没有自定义套装列表，详情见 help taozhuang 说明。\n");
		/*
		if (sizeof(tz) < 12 && ! wizardp(me)) // 巫师测试的时候可不用穿12件
			return notify_fail("你还未完成12件套装部件的定义，请使用 suit show 查看！\n");
*/
		keys_tz = keys(tz);
		for (i = 0; i < sizeof(keys_tz); i ++)
		{
			if (! objectp(ob = present(tz[keys_tz[i]], me)))
			{
				// 未在身上，尝试召唤
				__DIR__"summon"->main(me, tz[keys_tz[i]]);
				// 召唤后如果还没有则终止
				if (! objectp(ob = present(tz[keys_tz[i]], me)))
					return notify_fail("未找到装备 " + tz[keys_tz[i]] + "，操作终止！\n");
			}

			if (ob->query("equipped"))continue;


			// 装备特殊处理
			if (ob->query("skill_type"))
			{
				"/cmds/std/wield"->do_wield(me, ob);
			}
			else
			{
				"/cmds/std/wear"->do_wear(me, ob);
			}
		}

		return notify_fail("OK.\n");
	}


	// 显示已加入的套装列表
	if (arg == "show")
	{
		result = HIG "-----------自定义套装列表-------------\n" NOR;

		if (! sizeof(me->query("tzlist")))
			return notify_fail("你还没有自定义套装列表，详情见 help taozhuang 说明。\n");

		if (sizeof(me->query("tzlist/weapon")))
		{
			ob = present(me->query("tzlist/weapon"), me);
			if (objectp(ob))
			{
				str_color = ob->query("equipped") ? HIM : HIC;
				result += str_color + "武器： " + HIC + ob->name() + HIC + "（" +
		                 	  TAOZHUANG_D->taozhuang_name(ob->query("taozhuang")) + HIC "）\n" NOR;
		        }
		        else
		        	result += HIC "武器： " NOR + WHT + me->query("tzlist/weapon") + "\n" NOR;
		}
		else
		{
			result += HIC "武器： " + NOR + WHT "----\n" NOR;
		}

		for (i = 0; i < sizeof(keys_tzlist); i ++)
		{
			if (sizeof(me->query("tzlist/" + keys_tzlist[i])))
			{
				ob = present(me->query("tzlist/" + keys_tzlist[i]), me);
				if (objectp(ob))
				{
					str_color = ob->query("equipped") ? HIM : HIC;
					result += str_color + tzlist[keys_tzlist[i]] + "： " + HIC + ob->name() + HIC + "（" +
		                          	  TAOZHUANG_D->taozhuang_name(ob->query("taozhuang")) + HIC "）\n" NOR;
		                }
		                else
		                	result += HIC + tzlist[keys_tzlist[i]] + "： " NOR + WHT +
		                	          me->query("tzlist/" + keys_tzlist[i]) + "\n" NOR;
			}
			else
			{
				result += HIC + tzlist[keys_tzlist[i]] + "： " NOR + WHT + "----\n" NOR;
			}
		}
		result += HIG "-------------------------------------\n" NOR;
		result += HIW "装备类型名为" HIM "紫红色" HIW "的表示已装备，" HIC "天青色" HIW "为未装备。\n" NOR;
		result += HIY "使用指令 suit add 装备id 添加自定义套装列表。\n" NOR;
		result += HIR "使用指令 suit wear 可将自定义套装列表内的套件批量装备。\n" NOR;
		//result += HIY "使用指令 suit remove 装备id 从自定义套装列表中移出该装备。\n" NOR;
		write(result);
		return 1;
	}


	// 将指定装备加入套装列表
	if (sscanf(arg, "add %s", tzx))
	{
		if (! objectp(ob = present(tzx, me)))
			return notify_fail("你身上没有这件装备！\n");

		// 判断装备是否属于自己
		if (ob->item_owner() != me->query("id"))
			return notify_fail("这个，这个……，好象不属于你吧！\n");

		// 判断是否为12件装备中的类型
		if (ob->query("skill_type") || ob->query("armor_type") == "hands") // 武器
		{
			me->set("tzlist/weapon", tzx);
			return notify_fail("添加自定义套装成功，可使用 suit show 查看。\n");
		}
		if (! ob->query("armor_type"))
			return notify_fail("这件物品不属于装备类型！\n");

		if (member_array(ob->query("armor_type"), keys_tzlist) == -1)
			return notify_fail("这件物品不属于套装部件！\n");

		me->set("tzlist/" + ob->query("armor_type"), tzx);
		return notify_fail("添加自定义套装成功，可使用 suit show 查看。\n");
	}

	return TAOZHUANG_D->suit_special(me, arg);

}