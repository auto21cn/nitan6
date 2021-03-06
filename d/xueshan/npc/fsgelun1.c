// /d/xueshan/npc/fsgelun.c
// Summer 9/26/1996.
// Rama modified for hx

inherit NPC;

#define BUSY_TIME 240
int do_fashi();
void create()
{
        set_name("祭祀喇嘛", ({ "jisi lama", "jisi", "lama" }));
        set_weight(3000000);
        set("long", 
"他是密宗的戒律僧，长得膀大腰，手中提着法器，身着黄袍，头戴黄帽，\n"
"满面肃杀之气。\n");
        set("gender", "男性");
        set("age", 20);
        set("attitude", "heroism");
        set("class","bonze");
        set("shen_type", -1);
        set("str", 50);
        
        set("max_qi", 500);
        set("max_jing", 450);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 40);
        set("combat_exp", 50000);
        set("score", 5000);

        set_skill("force", 50);
        set_skill("dodge", 55);
        set_skill("parry", 60);
        set_skill("staff", 60);
        set_skill("cuff", 60);
        set_skill("hammer", 60);

        
        set("inquiry", ([
                "准备法事" : (: do_fashi :),
                "preparation" : (: do_fashi :),
        ]) );

        setup();
        switch( random(3) )
        {
                case 0:
                         carry_object("/clone/weapon/falun")->wield();
                         break;
                case 1:
                         carry_object("/d/xueshan/obj/fachu")->wield();
                         break;
                case 2:
                         carry_object("/d/xueshan/obj/faling")->wield();
        }
        carry_object("/d/xueshan/obj/lamajiasha")->wear();
}


int do_fashi()
{
        int i;
        object ob, me, mengzhu, room, *obj, room1, gang;
        ob=(present("fa tan", (environment(this_object()))));
        me=this_player();
        
        
        if (! present("fa tan", (environment(this_object())))){
        command("say 我正忙着呢，你去问值日的葛伦布吧。");
        return 1;
        }

        if( query("class", me) != "bonze"){
        command("say 你是想让我们大喇嘛把你超度了，是吧？");
        return 1;
        }

        if( query("family/family_name", me) != "雪山寺"
         && query("family/family_name", me) != "血刀门"){
        command("say 你是想让我们大喇嘛把你超度了，是吧？");
        return 1;
        }

        if (me->query_skill("lamaism", 1) < 60){
        command("say 很好！你去弄些做法事用的酥油来吧。");
        return 1;
        }

    // add to involve the butter stuff
        if(!( room1 = find_object("/d/xueshan/dumudian")) )
                room1 = load_object("/d/xueshan/dumudian");
        if ( !objectp(gang = present("tong gang", room1)) ) {
        command("say 做法事用的酥油不见了，上人赶快去查一下吧！");
                return 1;
        }

        if (gang->query_current_liquid() < 40) {
            command("say 做法事用的酥油不够用了，请上人弄些酥油来吧。");
                return 1;
        }
        
        if( time()<query("burn/jobtime", me)+BUSY_TIME )
        {       command("say 超度亡魂可是一件很耗费精元的活，上人还是先去歇息一下吧。");
                return 1;
        }
             // add by Yujie
        
        if( query("burning", ob)){
        obj = all_inventory(environment());
        for(i=0; i<sizeof(obj); i++){
        if( query("name", obj[i]) == query("pending", ob) )
        {
        command("say"+query("pending", ob)+"上人正在做法事，这位"
        + RANK_D->query_respect(me) + "请一旁稍候。\n");
        return 1;
        }
        }
        command("say"+query("pending", ob)+"上人法事做到一半後不知跑哪里去了？真不象话！"
        +query("name", me)+"上人替"+query("pending", ob)+"上人把余下的法事做完吧。\n");
        set("pending",query("name",  me), ob);
        return 1;
        }
/*
        if( query("name", me) == query("last_burner", ob)){
        command("say  上人不是刚做完法事吗？你还是先歇一会儿吧。");
        return 1;
        } 
*/
        if( query("pending", ob)){
        command("say"+query("pending", ob)+"上人刚做完法事，祭坛还未熄，待我等清理完後"
         + RANK_D->query_respect(me) + "再来做法事吧。\n");
        return 1;
        }
        
        else{
        command("say"+query("name", me)+RANK_D->query_respect(me)+
        "是要给哪位施主做法事呀？\n");
        set_temp("marks/葛", 1, me);
        return 1;
        }
}
int accept_object(object me, object ob)
{
        if (ob->is_character() || userp(ob))
                return 0;

        if( query("beheaded", ob)){
        command("say 怎麽没有头？");
        return 0;
        }

        if( query("id", ob) == "corpse" && present("fatan",(environment(this_object())) )
         && query_temp("marks/葛", me) == 1){
        write("祭祀喇嘛急急忙忙吩咐左右往祭坛里填柴，倒酥油。\n");
        delete_temp("marks/葛", me);
        if( query("combat_exp", ob)>query("combat_exp", me )
         && query("my_killer", ob) == query("id", me)){
        set_temp("award_pending",query("combat_exp",  ob), me);
        set_temp("award_pot",query("combat_exp",  ob), me);
        if( query("was_userp", ob) )
        set_temp("award_doubling", 1, me);
        }
        if( query("combat_exp", ob)>1000000
         && query("my_killer", ob) == query("id", me)){
        set_temp("award_pot",query("combat_exp",  ob), me);
        }
        remove_call_out("preparing");
        call_out("preparing",5, me);
        return 1;
        }

        if (ob->name()=="酥油罐"
         && query("class", me) == "bonze"){
        if (me->query_skill("lamaism", 1) < 30){
        set("lama_butter",query("mud_age",  me), me);
        command ("bow");
        command ("say 佛主保佑施主！");
//        remove_call_out("destroy_it");
        call_out("destroy_it", 1, ob);
        return 1;
        }
        if (me->query_skill("lamaism", 1) >= 30
        && me->query_skill("lamaism", 1) < 60){
        set("lama_butter",query("mud_age",  me)+7600, me);
        command ("bow");
        command ("say 佛主保佑施主！");
        remove_call_out("destroy_it");
        call_out("destroy_it", 1, ob);
        return 1;
        }
   }
//      else if (ob->name()!="酥油" && ob->query("id") != "corpse") {
        else {
        write("葛伦布脸上露出迷惑的表情。\n");
        command ("shake");
//      remove_call_out("destroy_it");  // if player #10 give him some stuff,
                                        // 1 got dest but others 9 still on him   
        call_out("destroy_it", 1, ob);
        return 1;
        }
        return 1;
}       
void destroy_it (object ob)
{
        destruct(ob);
        return;

}
void preparing(object me)
{
        object ob, obj, room, tonggang, guan;
        ob=(present("fa tan", (environment(this_object()))));
        if (! objectp(ob)) 
        {
                write("准备未成功，请重新来。\n");
                return;
        }
        obj=(present("corpse", this_object()));
        if (! objectp(obj)) 
        {
                write("奇怪，怎么尸体不见了？\n");
                return;
        }
        set("pending",query("name",  me), ob);
        set("burn/jobtime", time(), me);
        set("in_use", 1, ob);

        say("祭祀喇嘛将"+query("name", obj)+"塞进了"+query("name", ob)+"里。\n");
        write("不一会儿，一切准备停当。\n");
        command("say"+query("name", me)+"上人请为亡灵超度吧！\n");
/*
        command("chat"+query("title", me)+query("name", me)+
                "上人，于今日" + NATURE_D->game_time() + "超度" 
                +query("victim_name", obj)+"！\n");

*/
        destroy_it(obj);
        ob->set_weight(ob->query_weight()*10);
        return;
}
