#include"key.h"
#include"adcx.h"
#include"oled.h"
float uhis[16],ihis[16];
uint8_t h,t,buf[128];
void Disp_init(){
    uhis[0]=Get_U_Value();
    ihis[0]=Get_I_Value();
    h=t=0;
}
void his_refresh(){
    t++;
    if(t==16)
        t=0;
    if(t==h)
        h++;
    if(h==16)
        h=0;
    uhis[t]=Get_U_Value();
    ihis[t]=Get_I_Value();
}
void Disp_Welcome(){
    OLED_Clear();
    OLED_ShowString(0,0,"PowerMetre@ZJU");
    OLED_ShowString(0,2,"Standby");
}//字体大小为16*8
// void Disp_Debug(char* Debug_str){
//     OLED_Clear();
//     OLED_ShowString(0,0,Debug_str);
// }
void OLED_Showdecimal(u8 x,u8 y,float num){
    if(x<0||x>100)
        x=0;
    if(y<0||y>100)
        y=0;
    OLED_ShowChar(x,y,'0'+(u8)num/10%10);
    OLED_ShowChar(x+SIZE/2,y,'0'+(u8)num%10);
    OLED_ShowChar(x+SIZE/2*2,y,'.');
    num-=(u8)num;
    for(u8 i=1;i<=4;i++){
        num*=10;
        OLED_ShowChar(x+SIZE/2*(i+2),y,(u8)num+'0');
        num-=(u8)num;
    }
}
void Disp_Digit_Mode(){
    his_refresh();
    float ucur=uhis[t],icur=ihis[t];
    OLED_Clear();
    OLED_Showdecimal(32+0,0,ucur);
    OLED_ShowChar(32+7*8,0,'V');
    // OLED_ShowChar(24,0,'|');
    // OLED_ShowChar(96,0,'|');
    OLED_Showdecimal(32+0,2,icur);
    OLED_ShowChar(32+7*8,2,'A');
    // OLED_ShowChar(24,2,'|');
    // OLED_ShowChar(96,2,'|');
    OLED_Showdecimal(32+0,4,ucur*icur);
    OLED_ShowChar(32+7*8,4,'W');
    // OLED_ShowChar(24,2,'|');
    // OLED_ShowChar(96,2,'|');
    // OLED_ShowString(0,6,"Num");
}
void Disp_Power_Mode(){
    his_refresh();
    OLED_Clear();
    uint8_t cur,nxt,cnt,i,j;
    for(i=0;i<=5;i++){
        cur=h;
        cnt=0;
        nxt=cur+1;
        if(nxt==16)
            nxt=0;
        for(j=0;j<128;j++)
            buf[j]=0;
        while(1){
            if(uhis[cur]*ihis[cur]>7-i&&uhis[cur]*ihis[cur]<=8-i)
                buf[cnt*8]=1<<(7-(uint8_t)(8*(uhis[cur]*ihis[cur]-(7-i))));
            if(cur!=t){
                for(j=1;j<=7;j++){
                    float tmp=(uhis[nxt]*ihis[nxt]-uhis[cur]*ihis[cur])/8*j+uhis[cur]*ihis[cur];
                    if(tmp>7-i&&tmp<=8-i)
                        buf[cnt*8+j]=1<<(7-(uint8_t)(8*(tmp-(7-i))));
                }
            }
            // if((uhis[cur]*ihis[cur]+uhis[nxt]*ihis[nxt])/2>7-i&&(uhis[cur]*ihis[cur]+uhis[nxt]*ihis[nxt])/2<=8-i)
            //     buf[cnt*2+1]=1<<(7-(uint8_t)(8*((uhis[cur]*ihis[cur]+uhis[nxt]*ihis[nxt])/2-(7-i))));
            if(cur==t)
                break;
            cnt++;
            cur=nxt;
            nxt++;
            if(nxt==16)
                nxt=0;
        }
        OLED_Set_Pos(0,i);
        for(j=0;j<128;j++)
            OLED_WR_Byte(buf[j],OLED_DATA);
    }
    OLED_ShowString(0,6,"P Chart");
    OLED_ShowChar(120,0,'8');
    OLED_ShowChar(120,6,'0');
}//以8W为上限
void Disp_U_Mode(){
    his_refresh();
    OLED_Clear();
    uint8_t cur,nxt,cnt,i,j;
    for(i=0;i<=5;i++){
        cur=h;
        cnt=0;
        nxt=cur+1;
        if(nxt==16)
            nxt=0;
        for(j=0;j<128;j++)
            buf[j]=0;
        while(1){
            if(uhis[cur]>7-i&&uhis[cur]<=8-i)
                buf[cnt*8]=1<<(7-(uint8_t)(8*(uhis[cur]-(7-i))));
            // if(cur!=t){
            //     for(j=1;j<=7;j++){
            //         float tmp=(uhis[nxt]-uhis[cur])/8*j+uhis[cur];
            //         if(tmp>7-i&&tmp<=8-i)
            //             buf[cnt*8+j]=1<<(7-(uint8_t)(8*(tmp-(7-i))));
            //     }
            // }
            // if((uhis[cur]+uhis[nxt])/2>7-i&&(uhis[cur]+uhis[nxt])/2<=8-i)
            //     buf[cnt*2+1]=1<<(7-(uint8_t)(8*((uhis[cur]+uhis[nxt])/2-(7-i))));
            if(cur==t)
                break;
            cnt++;
            cur=nxt;
            nxt++;
            if(nxt==16)
                nxt=0;
        }
        OLED_Set_Pos(0,i);
        for(j=0;j<128;j++)
            OLED_WR_Byte(buf[j],OLED_DATA);
    }
    OLED_ShowString(0,6,"U Chart");
    OLED_ShowChar(120,0,'8');
    OLED_ShowChar(120,6,'0');
}//以8V为上限
void Disp_I_Mode(){
    // his_refresh();
    // OLED_Clear();
    // uint8_t cur,nxt,cnt,i,j;
    // for(i=0;i<=5;i++){
    //     cur=h;
    //     cnt=0;
    //     nxt=cur+1;
    //     if(nxt==16)
    //         nxt=0;
    //     for(j=0;j<128;j++)
    //         buf[j]=0;
    //     while(1){
    //         if(ihis[cur]>0.25*(7-i)&&ihis[cur]<=0.25*(8-i))
    //             buf[cnt*8]=1<<(7-(uint8_t)(32*(ihis[cur]-0.25*(7-i))));
    //         // if(cur!=t){
    //         //     for(j=1;j<=7;j++){
    //         //         float tmp=(ihis[nxt]-ihis[cur])/8*j+ihis[cur];
    //         //         if(tmp>0.25*(7-i)&&tmp<=0.25*(8-i))
    //         //             buf[cnt*8+j]=1<<(7-(uint8_t)(32*(tmp-0.25*(7-i))));
    //         //     }
    //         // }
    //         if(cur==t)
    //             break;
    //         cnt++;
    //         cur=nxt;
    //         nxt++;
    //         if(nxt==16)
    //             nxt=0;
    //     }
    //     OLED_Set_Pos(0,i);
    //     for(j=0;j<128;j++)
    //         OLED_WR_Byte(buf[j],OLED_DATA);
    // }
    // OLED_ShowString(0,6,"I Chart");
    // OLED_ShowChar(120,0,'2');
    // OLED_ShowChar(120,6,'0');
}
//以2A为上限 2/8*(7-i)~2/8*(8-i)
//完全放不下啊
//大刀阔斧，删掉两个模式？