/*
 
grambilib~ 2016
 
01.28.16
 
*/



#include <string.h>
#include <math.h>
#include <m_pd.h>
#include <stdio.h>

#define kPI    3.14159265358979323846
#define radians   2 * 3.14159265358979323846


static char *version = "[grambidec~] v. 1 (2015) for Pd written by Ricky Graham <ricky@rickygraham.net>";


static t_class *grambidec_tilde_class;

typedef struct _grambidec_tilde {
    t_object  x_obj;
    t_sample APf;
    t_symbol *x_dec;
    
    float dectype;
    t_symbol decmode;
    
    t_sample sample1_old, sample2_old, sample3_old, sample4_old;
    
} t_grambidec_tilde;


/* modified perform routine to include two signal rate inputs for azimuth and elevation controls */
t_int *grambidec_tilde_mono(t_int *w)
{
    t_grambidec_tilde *x = (t_grambidec_tilde *)(w[1]);
    t_sample  *APin1 =    (t_sample *)(w[2]);
    t_sample  *APin2 =    (t_sample *)(w[3]);
    t_sample  *APin3 =    (t_sample *)(w[4]);
    t_sample  *APin4 =    (t_sample *)(w[5]);
    t_sample  *APout1 =    (t_sample *)(w[6]);
    int          APn =           (int)(w[7]);
    
    t_sample sample1;
    
    while (APn--)
    {
        
        //B-Format Input
        sample1 = (*APin1++); //W
        
        //Basic Stereo Decoder
        (*APout1++) =   sample1 * 0.707;
    
    }
    
    return (w+8);
    
}


t_int *grambidec_tilde_stereo(t_int *w)
{
    t_grambidec_tilde *x = (t_grambidec_tilde *)(w[1]);
    t_sample  *APin1 =    (t_sample *)(w[2]);
    t_sample  *APin2 =    (t_sample *)(w[3]);
    t_sample  *APin3 =    (t_sample *)(w[4]);
    t_sample  *APin4 =    (t_sample *)(w[5]);
    t_sample  *APout1 =    (t_sample *)(w[6]);
    t_sample  *APout2 =    (t_sample *)(w[7]);
    int          APn =           (int)(w[8]);
  
    t_sample sample1, sample2, sample3, sample4;
    
    while (APn--)
    {
        //B-Format Input
        sample1 = (*APin1++); //W
        sample2 = (*APin2++); //X
        sample3 = (*APin3++); //Y
        sample4 = (*APin4++); //Z
        
        //Basic Stereo Decoder
        (*APout1++) =   sample1 * 0.707 + sample3 * 0.5;
        (*APout2++) =   sample1 * 0.707 + sample3 * -0.5;
        
    }
    
    
    return (w+9);
    
}


t_int *grambidec_tilde_quad(t_int *w)
{
    t_grambidec_tilde *x = (t_grambidec_tilde *)(w[1]);
    t_sample  *APin1 =    (t_sample *)(w[2]);
    t_sample  *APin2 =    (t_sample *)(w[3]);
    t_sample  *APin3 =    (t_sample *)(w[4]);
    t_sample  *APin4 =    (t_sample *)(w[5]);
    t_sample  *APout1 =    (t_sample *)(w[6]);
    t_sample  *APout2 =    (t_sample *)(w[7]);
    t_sample  *APout3 =    (t_sample *)(w[8]);
    t_sample  *APout4 =    (t_sample *)(w[9]);
    int          APn =           (int)(w[10]);
    
    t_sample sample1, sample2, sample3, sample4;
    
    while (APn--)
    {
        
        //B-Format Input
        sample1 = (*APin1++); //W
        sample2 = (*APin2++); //X
        sample3 = (*APin3++); //Y
        sample4 = (*APin4++); //Z
        
        
        //Basic Quad Decoder
        (*APout1++) =   sample1 * 0.3536 + sample2 * 0.1768 + sample3 * 0.1768; //FL
        (*APout2++) =   sample1 * 0.3536 + sample2 * -0.1768 + sample3 * 0.1768; //BL
        (*APout3++) =   sample1 * 0.3536 + sample2 * -0.1768 + sample3 * -0.1768; //BR
        (*APout4++) =   sample1 * 0.3536 + sample2 * 0.1768 + sample3 * -0.1768; //FR
        
    }
    
    
    return (w+11);
    
}




t_int *grambidec_tilde_pent(t_int *w)
{
    t_grambidec_tilde *x = (t_grambidec_tilde *)(w[1]);
    t_sample  *APin1 =    (t_sample *)(w[2]);
    t_sample  *APin2 =    (t_sample *)(w[3]);
    t_sample  *APin3 =    (t_sample *)(w[4]);
    t_sample  *APin4 =    (t_sample *)(w[5]);
    t_sample  *APin5 =    (t_sample *)(w[6]);
    t_sample  *APout1 =    (t_sample *)(w[7]);
    t_sample  *APout2 =    (t_sample *)(w[8]);
    t_sample  *APout3 =    (t_sample *)(w[9]);
    t_sample  *APout4 =    (t_sample *)(w[10]);
    t_sample  *APout5 =    (t_sample *)(w[11]);
    int          APn =           (int)(w[12]);
    
    t_sample sample1, sample2, sample3, sample4, sample5;
    
    while (APn--)
    {
        
        //B-Format Input
        sample1 = (*APin1++); //W
        sample2 = (*APin2++); //X
        sample3 = (*APin3++); //Y
        sample4 = (*APin4++); //U
        sample5 = (*APin5++); //V
        
        
        //5.0
        (*APout1++) =   sample1 * 0.405 + sample2 * 0.320 + sample3 * 0.310 + sample4 * 0.085 * sample5 * 0.125;
        (*APout2++) =   sample1 * 0.405 + sample2 * 0.320 + sample3 * -0.310 + sample4 * 0.085 * sample5 * -0.125;
        (*APout3++) =   sample1 * 0.085 + sample2 * 0.040 + sample3 * 0.000 + sample4 * 0.045 * sample5 * 0.000;
        (*APout4++) =   sample1 * 0.635 + sample2 * -0.335 + sample3 * 0.380 + sample4 * -0.080 * sample5 * 0.080;
        (*APout5++) =   sample1 * 0.635 + sample2 * -0.335 + sample3 * -0.280 + sample4 * -0.080 * sample5 * -0.080;
    }
    
    
    return (w+13);
    
}


t_int *grambidec_tilde_hex(t_int *w)
{
    t_grambidec_tilde *x = (t_grambidec_tilde *)(w[1]);
    t_sample  *APin1 =    (t_sample *)(w[2]);
    t_sample  *APin2 =    (t_sample *)(w[3]);
    t_sample  *APin3 =    (t_sample *)(w[4]);
    t_sample  *APin4 =    (t_sample *)(w[5]);
    t_sample  *APin5 =    (t_sample *)(w[6]);
    t_sample  *APout1 =    (t_sample *)(w[7]);
    t_sample  *APout2 =    (t_sample *)(w[8]);
    t_sample  *APout3 =    (t_sample *)(w[9]);
    t_sample  *APout4 =    (t_sample *)(w[10]);
    t_sample  *APout5 =    (t_sample *)(w[11]);
    t_sample  *APout6 =    (t_sample *)(w[12]);
    int          APn =           (int)(w[13]);
    
    t_sample sample1, sample2, sample3, sample4, sample5;
    
    while (APn--)
    {
        
    
        sample1 = (*APin1++);
        sample2 = (*APin2++);
        sample3 = (*APin3++);
        sample4 = (*APin4++);
        sample5 = (*APin5++);
        
        //hex
        (*APout1++) =   sample1 * 0.2357 + sample2 *  0.1987 + sample3 *  0.1147 + sample4 *  0.0321 * sample5 * 0.0556;
        (*APout2++) =   sample1 * 0.2357 + sample2 *  0.0000 + sample3 *  0.2294 + sample4 *  -0.0643 * sample5 * 0.0000;
        (*APout3++) =   sample1 * 0.2357 + sample2 *  -0.1987 + sample3 *  0.1147 + sample4 *  0.0321 * sample5 * -0.0556;
        (*APout4++) =   sample1 * 0.2357 + sample2 *  -0.1987 + sample3 *  -0.1147 + sample4 *  0.0321 * sample5 * 0.0556;
        (*APout5++) =   sample1 * 0.2357 + sample2 *  0.0000 + sample3 *  -0.2294 + sample4 * -0.0643 * sample5 * 0.0000;
        (*APout6++) =   sample1 * 0.2357 + sample2 *  0.1987 + sample3 *  -0.1147 + sample4 * 0.0321 * sample5 * -0.0556;
    }
    
    
    return (w+14);
    
}


t_int *grambidec_tilde_oct(t_int *w)
{
    t_grambidec_tilde *x = (t_grambidec_tilde *)(w[1]);
    t_sample  *APin1 =    (t_sample *)(w[2]);
    t_sample  *APin2 =    (t_sample *)(w[3]);
    t_sample  *APin3 =    (t_sample *)(w[4]);
    t_sample  *APin4 =    (t_sample *)(w[5]);
    t_sample  *APin5 =    (t_sample *)(w[6]);
    t_sample  *APin6 =    (t_sample *)(w[7]);
    t_sample  *APin7 =    (t_sample *)(w[8]);
    t_sample  *APout1 =    (t_sample *)(w[9]);
    t_sample  *APout2 =    (t_sample *)(w[10]);
    t_sample  *APout3 =    (t_sample *)(w[11]);
    t_sample  *APout4 =    (t_sample *)(w[12]);
    t_sample  *APout5 =    (t_sample *)(w[13]);
    t_sample  *APout6 =    (t_sample *)(w[14]);
    t_sample  *APout7 =    (t_sample *)(w[15]);
    t_sample  *APout8 =    (t_sample *)(w[16]);
    int          APn =           (int)(w[17]);
    
    t_sample sample1, sample2, sample3, sample4, sample5, sample6, sample7;
    
    while (APn--)
    {
        

        sample1 = (*APin1++);
        sample2 = (*APin2++);
        sample3 = (*APin3++);
        sample4 = (*APin4++);
        sample5 = (*APin5++);
        sample6 = (*APin6++);
        sample7 = (*APin7++);
        
        
        //Oct
        (*APout1++) =   sample1 * 0.1768 + sample2 * 0.1732 + sample3 * 0.0718 + sample4 * 0.0530 *  sample5 * 0.0530 + sample6 * 0.0048 + sample7 * 0.0115; //NNW
        (*APout2++) =   sample1 * 0.1768 + sample2 * 0.0718 + sample3 * 0.1732 + sample4 * -0.0530 *  sample5 * 0.0530 + sample6 * -0.0115 + sample7 * -0.0048; //WNW
        (*APout3++) =   sample1 * 0.1768 + sample2 * -0.0718 + sample3 * 0.1732 + sample4 * -0.0530 *  sample5 * -0.0530 + sample6 * 0.0048 + sample7 * -0.0115; //WSW
        (*APout4++) =   sample1 * 0.1768 + sample2 * -0.1732 + sample3 * 0.0718 + sample4 * 0.0530 *  sample5 * -0.0530 + sample6 * -0.0115 + sample7 * 0.0048; //SSW
        (*APout5++) =   sample1 * 0.1768 + sample2 * -0.1732 + sample3 * -0.0718 + sample4 * 0.0530 *  sample5 * 0.0530 + sample6 * -0.0048 + sample7 * -0.0115; //SSE
        (*APout6++) =   sample1 * 0.1768 + sample2 * -0.0718 + sample3 * -0.1732 + sample4 * -0.0530 *  sample5 * 0.0530 + sample6 * 0.0115 + sample7 * 0.0048; //ESE
        (*APout7++) =   sample1 * 0.1768 + sample2 * 0.0718 + sample3 * -0.1732 + sample4 * -0.0530 *  sample5 * -0.0530 + sample6 * -0.0048 + sample7 * 0.0115; //ENE
        (*APout8++) =   sample1 * 0.1768 + sample2 * 0.1732 + sample3 * -0.0718 + sample4 * 0.0530 *  sample5 * -0.0530 + sample6 * 0.0115 + sample7 * -0.0048; //NNE
        
      
    }
    
    
    return (w+18);
    
}


t_int *grambidec_tilde_cube(t_int *w)
{
    t_grambidec_tilde *x = (t_grambidec_tilde *)(w[1]);
    t_sample  *APin1 =    (t_sample *)(w[2]);
    t_sample  *APin2 =    (t_sample *)(w[3]);
    t_sample  *APin3 =    (t_sample *)(w[4]);
    t_sample  *APin4 =    (t_sample *)(w[5]);
    t_sample  *APout1 =    (t_sample *)(w[6]);
    t_sample  *APout2 =    (t_sample *)(w[7]);
    t_sample  *APout3 =    (t_sample *)(w[8]);
    t_sample  *APout4 =    (t_sample *)(w[9]);
    t_sample  *APout5 =    (t_sample *)(w[10]);
    t_sample  *APout6 =    (t_sample *)(w[11]);
    t_sample  *APout7 =    (t_sample *)(w[12]);
    t_sample  *APout8 =    (t_sample *)(w[13]);
    int          APn =           (int)(w[14]);
    
    t_sample sample1, sample2, sample3, sample4;
    
    while (APn--)
    {
        
        //B-Format Input
        sample1 = (*APin1++); //W
        sample2 = (*APin2++); //X
        sample3 = (*APin3++); //Y
        sample4 = (*APin4++); //Z
        
        
        //B-Format Cube
        (*APout1++) =   sample1 * 0.1768 + sample2 * 0.0722 + sample3 * 0.0722 + sample4 * -0.0722; //FLL
        (*APout2++) =   sample1 * 0.1768 + sample2 * 0.0722 + sample3 * 0.0722 + sample4 * 0.0722; //FUL
        (*APout3++) =   sample1 * 0.1768 + sample2 * -0.0722 + sample3 * 0.0722 + sample4 * -0.0722; //BLL
        (*APout4++) =   sample1 * 0.1768 + sample2 * -0.0722 + sample3 * 0.0722 + sample4 * 0.0722; //BUL
        (*APout5++) =   sample1 * 0.1768 + sample2 * -0.0722 + sample3 * -0.0722 + sample4 * -0.0722; //BLR
        (*APout6++) =   sample1 * 0.1768 + sample2 * -0.0722 + sample3 * -0.0722 + sample4 * 0.0722; //BUR
        (*APout7++) =   sample1 * 0.1768 + sample2 * 0.0722 + sample3 * -0.0722 + sample4 * -0.0722; //FLR
        (*APout8++) =   sample1 * 0.1768 + sample2 * 0.0722 + sample3 * -0.0722 + sample4 * 0.0722; //FUR
    }
    
    
    return (w+15);
    
}



void grambidec_tilde_dsp(t_grambidec_tilde *x, t_signal **sp)
{
    if(x->dectype==1)
        dsp_add(grambidec_tilde_mono, 7, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[0]->s_n);
    
    if(x->dectype==2)
    dsp_add(grambidec_tilde_stereo, 8, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[0]->s_n);
    
    if(x->dectype==4)dsp_add(grambidec_tilde_quad, 10, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[0]->s_n);
    
    if(x->dectype==5)dsp_add(grambidec_tilde_pent, 12, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[8]->s_vec, sp[9]->s_vec, sp[0]->s_n);
    
    if(x->dectype==6)dsp_add(grambidec_tilde_hex, 13, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[8]->s_vec, sp[9]->s_vec, sp[10]->s_vec, sp[0]->s_n);
    
    if(x->dectype==7)dsp_add(grambidec_tilde_oct, 17, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec,  sp[8]->s_vec,  sp[9]->s_vec, sp[10]->s_vec, sp[11]->s_vec, sp[12]->s_vec, sp[13]->s_vec, sp[14]->s_vec, sp[0]->s_n);
    
    if(x->dectype==8)dsp_add(grambidec_tilde_cube, 14, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec,  sp[8]->s_vec,  sp[9]->s_vec, sp[10]->s_vec, sp[11]->s_vec, sp[0]->s_n);
}






void *grambidec_tilde_new(t_symbol *s, int argc, t_atom *argv) //, t_floatarg test
{
    
    t_grambidec_tilde *x = (t_grambidec_tilde *)pd_new(grambidec_tilde_class);
   
    char teststring[1000];
    if(argc>0)atom_string(argv, teststring, 1000);
    //post("set: %s",teststring);
    //char buf[7];
    //sprintf(buf, "%s", teststring);
    char* type[7] = {"mono", "stereo", "quad", "pent", "hex", "oct", "cube"};
    //compare creation string against type[7] array
    
    int j = 0;
    int ret[7];
    
    for(int i = 0; i < 7; i++) {
    
    ret[i] = strcmp(teststring, type[i]);
   

    if(ret[i] != 0) j = 1; if(ret[0] == 0) j = 1;
    if(ret[1] == 0) j = 2; if(ret[2] == 0) j = 4;
    if(ret[3] == 0) j = 5; if(ret[4] == 0) j = 6;
    if(ret[5] == 0) j = 7; if(ret[6] == 0) j = 8;
    
    //post("%d", j);
        
    }
    
    x->dectype = j;
    
    
    switch(j){ //write a for loop - good task for students
    default:
        case 1:
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 2
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 3
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 4
            outlet_new(&x->x_obj, gensym ("signal")); //mono - write perform routine
            break;
        case 2:
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 2
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 3
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 4
            outlet_new(&x->x_obj, gensym ("signal")); //FL
            outlet_new(&x->x_obj, gensym ("signal")); //FR
            break;
        case 4:
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 2
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 3
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 4
            outlet_new(&x->x_obj, gensym ("signal")); //FL
            outlet_new(&x->x_obj, gensym ("signal")); //BL
            outlet_new(&x->x_obj, gensym ("signal")); //BR
            outlet_new(&x->x_obj, gensym ("signal")); //FR
            break;
        case 5:
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 2
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 3
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 4
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 5
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            break;
        case 6:
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 2
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 3
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 4
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 5
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            break;
        case 7:
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 2
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 3
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 4
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 5
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 6
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 7
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            break;
        case 8:
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 2
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 3
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 4
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            break;
        case 0:
            break;
    }
    
        
    return (void *)x;
}

void grambidec_tilde_setup(void)
{
    grambidec_tilde_class = class_new(gensym("grambidec~"),(t_newmethod)grambidec_tilde_new,0, sizeof(t_grambidec_tilde),CLASS_DEFAULT,A_GIMME,0);
    class_addmethod(grambidec_tilde_class,
                    (t_method)grambidec_tilde_dsp, gensym("dsp"), 0);
    CLASS_MAINSIGNALIN(grambidec_tilde_class, t_grambidec_tilde, APf);
    class_sethelpsymbol(grambidec_tilde_class, gensym("grambilib-help.pd"));
    post(version);
}
