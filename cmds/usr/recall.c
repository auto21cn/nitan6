// recall.c
// created by lonely@nitan2

#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        string file;
        string str;
        object ob;
 
        if (! environment(me)) 
                return 0; 

        if (! arg || (arg != "back" && 
            arg != "home" && sscanf(arg, "%s %s", arg, str) != 2))
                return help(me);
                               
        if (me->is_busy())
                return notify_fail("你正忙著呢。\n");

        if (me->is_fighting())
                return notify_fail("你现在正在战斗！\n"); 

        if (me->is_ghost()) 
                return notify_fail("等你还了阳再说吧。\n"); 
                
        if (me->is_in_prison())   
                return notify_fail("你正在做牢呢。\n");

        if( query("doing", me) )
                return notify_fail("你还想干什么？！\n");
                
        if( query("no_magic", environment(me)) )
                return notify_fail("你发现这里有点古怪！\n");                
        
        if (arg == "back")
        {
                if( query_temp("warquest/party", me) )
                        return notify_fail("你还想在战争中使用？！\n");

                if (present("biao huo", me))
                        return notify_fail("你身上带著镖银，不能施展！\n");

                if( sscanf(base_name(environment(me)), "/d/register/%*s") )
                        return notify_fail("你还没有出生呢，不能施展！\n");

                if( sscanf(base_name(environment(me)), "/d/newbie/%*s") )
                        return notify_fail("你在古村中，不能施展！\n");
                
                file = "/d/city/kedian";
                
                if (base_name(environment(me)) == file)
                        return notify_fail("你已经在扬州客店了。\n");
                        
                if (! get_object(file))
                        return notify_fail("你感觉到似乎有什么不对劲！\n");

                message("vision", me->name() + "举起右手在面前极速画了一个圆，竟划破了面前的"
                        "空间，\n只见圆内的空间真空将" + me->name() + "给吸了进去。\n",
                        environment(me), ({me}));
                
                tell_object(me, "你从客店的某个角落空间裂缝中钻出。\n");

                me->move(file);
                message("vision", me->name() + "从客店的某个角落空间裂缝中钻出。\n",
                        environment(me), ({me}));

                MYGIFT_D->check_mygift(me, "newbie_mygift/recall");
                return 1;
        }
 
        if (arg == "back" || arg == "home")
        {
                if( query_temp("warquest/party", me) )
                        return notify_fail("你还想在战争中使用？！\n");

                if (present("biao huo", me))
                        return notify_fail("你身上带著镖银，不能施展！\n");

                if( sscanf(base_name(environment(me)), "/d/newbie/%*s") )
                        return notify_fail("你在古村中，不能施展！\n");
                
                if( arg == "back" )
                        file = "/d/city/kedian";
                else
                        file = query("private_room/position", me);
                
                if( !file ) return notify_fail("你还没有住房呢！\n");
                
                if (base_name(environment(me)) == file)
                        return notify_fail("你已经在这里了。\n");
                        
                if (! get_object(file))
                        return notify_fail("你感觉到似乎有什么不对劲！\n");

                message("vision", me->name() + "举起右手在面前极速画了一个圆，竟划破了面前的"
                        "空间，\n只见圆内的空间真空将" + me->name() + "给吸了进去。\n",
                        environment(me), ({me}));
                
                tell_object(me, "你从某个角落空间裂缝中钻出。\n");

                me->move(file);
                message("vision", me->name() + "从某个角落空间裂缝中钻出。\n",
                        environment(me), ({me}));

                MYGIFT_D->check_mygift(me, "newbie_mygift/recall");
                return 1;
        }
                                       
        if( !stringp(file=query("can_whistle/"+str, me)) )
                return notify_fail("你并没有这个魔幻兽。\n");

        if (file_size(file + ".c") < 0)
                return notify_fail("你并没有这个魔幻兽。\n");
                                
        if( arg == "reborn" && query("warcraft/status", me) == "died" )
        {
                if (me->query_skill("huisheng-jue", 1) < 100)
                        return notify_fail("你的回生决功力不够，无法让魔幻兽重生。\n"); 

                if( query("neili", me)<query("max_neili", me)*9/10 )
                        return notify_fail("你现在内力并不充沛，怎敢贸然运用？\n");

                if( query("jingli", me)<query("max_jingli", me)*9/10 )
                        return notify_fail("你现在精力不济，怎敢贸然运用？\n");

                if (me->query_skill("force") < 200)
                        return notify_fail("你的内功根基不够扎实，不能贸然运用。\n");

                if( query("max_neili", me)<3000 )
                        return notify_fail("你尝试运了一下内力，无法顺"
                                   "利运足一个周天，难以施展你的能力。\n");

                if( query("max_jingli", me)<1000 )
                        return notify_fail("你试图凝神运用精力，但是感觉尚有欠缺。\n");                                
                
                if( query("experience", me)<query("learned_experience", me)+1000 )
                        return notify_fail("你现在积累的实战体会还太少，无法贸然运用。\n");

                message_sort(HIR "$N集中精神，手指大地，同时运转丹田内力，经"
                        "由奇经八脉源源由体内流出，注入大地。\n" NOR, me); 

                me->start_busy(1);
        
                addn("max_neili", -500, me);
                set("neili",query("max_neili",  me), me);
                addn("max_jingli", -300, me);
                set("jingli",query("max_jingli",  me), me);
                addn("learned_experience", 1000, me);
                set("warcraft/status", "living", me);
                tell_object(me, HIW "你凝神片刻，觉得魔幻兽"
                        HIW "似乎复活过来，就在不远处，不禁微微一笑。\n" NOR);                                                                             
                
        } 
        else return help(me);
        return 1;
}

int help(object me)
{
 write(@HELP
指令格式 : recall back | home
回到扬州客店的指令为 < recall back >。
回到住房的指令为 < recall home >。
HELP
    );
    return 1;
}

