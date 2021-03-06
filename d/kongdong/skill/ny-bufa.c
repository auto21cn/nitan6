// ny-bufa.c

inherit SKILL;

mapping *action = ({
    ([ "action":"$n纵身一跃，一个「鹞子翻身」，闪身躲了开去。",
       "lian"  :"$N提气在胸，收腹提肩，一个「鹞子翻身」，高高跃起。",
       "jibie" :5,
       "sen"   :2, ]),
    ([ "action":"$n猛的一个「神龙摆尾」，向后跳开数尺。",
       "lian"  :"$N足下一蹬，一个「神龙摆尾」向后退去，险些扭伤了足踝。",
       "jibie" :10,
       "sen"   :2, ]),
    ([ "action":"$n双脚轻点，一个「白鹤冲天」，身形向上蹿起数尺。",
       "lian"  :"$N双足一点，一个「白鹤冲天」，蹿起三尺来高。",
       "jibie" :20,
       "sen"   :2, ]),
    ([ "action":"$n轻飘飘地向旁边一闪，$N的凌厉攻势尽数落在了空里。",
       "lian"  :"$N把握住身体的平衡，借着踢腿的力量，向旁边一跃。",
       "jibie" :30,
       "sen"   :3, ]),
    ([ "action":"$n向高空里一纵身，跃起五尺来高。",
       "lian"  :"$N向高空里一纵身，跃起五尺来高。",
       "jibie" :40,
        "sen"  :3, ]),
    ([ "action":"$n跃向空中，一招「蜻蜓点水」，从$N头上跃了过去。",
       "lian"  :"$N跃起五尺，一招「蜻蜓点水」，轻轻落下地来。",
       "jibie" :50,
       "sen"   :3, ]),
//    ([ "action":"$n低头侧身，蜷腿一纵，向旁边跃开七尺。",
//       "lian"  :"$N低头侧身，蜷腿一纵，向旁边跃开七尺。",
//       "jibie" :60,
//       "sen"   :4, ]),
});

int valid_learn(object me)
{
	return 1;
}

int valid_lian(object me)
{
//    int encu;
//    encu = me->query_encumbrance() * 100 / me->query_max_encumbrance();
//    if ( encu < 10 )
//        return notify_fail("轻功必须负重练习。\n");
    return 1;
}

mapping query_action(int jibie)
{
    int i, size;

    size = sizeof( action );
    for ( i = 0; i < sizeof( action ); i++ )
        if ( action[ i ][ "jibie" ] > jibie )
        {
            size = i;
            break;
        }
    return action[ random( size ) ];
}

string query_xiuwei_type()
{
    return "dodge";
}

// 返回这路武功的等级, 第一等返回 1, 第十等返回 10.
int query_dengji()
{
	return 2;
}

