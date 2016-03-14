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


static char *version = "[grambipan~] v. 1 (2015) for Pd written by Ricky Graham <ricky@rickygraham.net>";



static t_class *grambipan_tilde_class;

typedef struct _grambipan_tilde {
    t_object  x_obj;
    t_sample APf;
    
    double el;
    double az_in;
    double el_in;
    
    int order;
    
    
    t_sample sample1_old, sample2_old, sample3_old;
    
} t_grambipan_tilde;


/* utility function to clip value of input to within -1 -> 1 inclusive */
t_floatarg clip(t_floatarg n)
{
    return (n < -1) ? -1.0 : (n > 1) ? 1.0 : n; //  (integer == 5) ? (TRUE) : (FALSE);
}


/* these functions allow control from the message-rate parameters in the Pd patch */
void grambipan_tilde_az(t_grambipan_tilde *x, t_floatarg APazl)
{
    x->az_in = APazl * radians;
}


/* these functions allow control from the message-rate parameters in the Pd patch */
void grambipan_tilde_el(t_grambipan_tilde *x, t_floatarg APell )

{

    x->el = APell;
    x->el_in = (APell - 0.5) * (kPI);

    //post("%f: ", x->l);
    
}


/* modified perform routine to include two signal rate inputs for azimuth and elevation controls */
t_int *grambipan_tilde_order1(t_int *w)
{
    t_grambipan_tilde *x = (t_grambipan_tilde *)(w[1]);
    t_sample  *APin1 =    (t_sample *)(w[2]);
    t_sample  *APin2 =    (t_sample *)(w[3]);
    t_sample  *APin3 =    (t_sample *)(w[4]);
    t_sample  *APout1 =    (t_sample *)(w[5]);
    t_sample  *APout2 =    (t_sample *)(w[6]);
    t_sample  *APout3 =    (t_sample *)(w[7]);
    t_sample  *APout4 =    (t_sample *)(w[8]);
    int          APn =           (int)(w[9]);
  
    t_sample sample1, sample2, sample3;
    double l = x->el;
    
    while (APn--)
    {
        
        sample1 = (*APin1++); //audio input 1
        sample2 = (*APin2++) * radians; //audio input 2 for azimuth
        sample3 = (*APin3++ - 0.5) * kPI; //audio input 3 for elevation
        
        if(sample2 != x->sample2_old || sample3 != x->sample3_old) { //use message audio input controls
            
            
            (*APout1++) =   sample1 * 0.707; //W
            (*APout4++) =   sample1 * sinf(sample3); //Z
            
            
            if(sample3 == x->sample3_old){
            (*APout2++) =   sample1 * cosf(sample2); //X
            (*APout3++) =   sample1 * sinf(sample2); //Y
            
            } else {
            (*APout2++) = sample1 * cosf(sample2) * cosf(sample3); //X
            (*APout3++) = sample1 * sinf(sample2) * cosf(sample3); //Y
                
            }
            
            
            
            
            
            } else {  //if not, use message rate inputs
              
                (*APout1++) =   sample1 * 0.707;
              
                if(l == 0) { //solve multiply by zero issue
                (*APout2++) =   sample1 * cosf(x->az_in);
                } else {
                (*APout2++) =   sample1 * cosf(x->az_in) * cosf(x->el_in);
                }
                    
                if(l == 0) { //solve multiply by zero issue
                (*APout3++) =   sample1 * sinf(x->az_in);
                } else {
                (*APout3++) =   sample1 * sinf(x->az_in) * cosf(x->el_in);
                }
                
                if(l == 0) { //solve multiply by zero issue
                (*APout4++) =   sample1;
                } else {
                (*APout4++) =   sample1 * sinf(x->el_in);;
                }
                
            
        }
        
      
        x->sample1_old = sample1; //Input
        x->sample2_old = sample2; //Azi
        x->sample3_old = sample3; //Ele
        
        
    }
    
    
    return (w+10);
    
}


t_int *grambipan_tilde_order2(t_int *w)
{
    t_grambipan_tilde *x = (t_grambipan_tilde *)(w[1]);
    t_sample  *APin1 =    (t_sample *)(w[2]);
    t_sample  *APin2 =    (t_sample *)(w[3]);
    t_sample  *APin3 =    (t_sample *)(w[4]);
    t_sample  *APout1 =    (t_sample *)(w[5]);
    t_sample  *APout2 =    (t_sample *)(w[6]);
    t_sample  *APout3 =    (t_sample *)(w[7]);
    t_sample  *APout4 =    (t_sample *)(w[8]);
    t_sample  *APout5 =    (t_sample *)(w[9]);
    int          APn =           (int)(w[10]);
    
    t_sample sample1, sample2, sample3;
    double l = x->el;
    
    while (APn--)
    {

        sample1 = (*APin1++); //audio input 1
        sample2 = (*APin2++) * radians; //audio input 2 for azimuth
        sample3 = (*APin3++ - 0.5) * kPI; //audio input 3 for elevation
       
        
        
        if(sample2 != x->sample2_old || sample3 != x->sample3_old) { //use message audio input controls
            
     
                (*APout1++) =   sample1 * 0.707; //W
            
            
                if(sample3 == x->sample3_old) {
                (*APout2++) =   sample1 * cosf(sample2); //X
                (*APout3++) =   sample1 * sinf(sample2); //Y
                (*APout4++) =   sample1 * cosf(2 * sample2); //U
                (*APout5++) =   sample1 * sinf(2 * sample2); //V
                } else {
                (*APout2++) =   sample1 * cosf(sample2) * cosf(sample3); //X
                (*APout3++) =   sample1 * sinf(sample2) * cosf(sample3); //Y
                (*APout4++) =   sample1 * cosf(2 * sample2) * cosf(sample3) * cosf(sample3); //U
                (*APout5++) =   sample1 * sinf(2 * sample2) * cosf(sample3) * cosf(sample3); //V
                }
            
            
            
            
        } else {  //if not, use message rate inputs
            
                (*APout1++) =   sample1 * 0.707;
                
                
                if(l == 0) { //solve multiply by zero issue
                    (*APout2++) =   sample1 * cosf(x->az_in);
                } else {
                    (*APout2++) =   sample1 * cosf(x->az_in) * cosf(x->el_in);
                }
                
                if(l == 0) { //solve multiply by zero issue
                    (*APout3++) =   sample1 * sinf(x->az_in);
                } else {
                    (*APout3++) =   sample1 * sinf(x->az_in) * cosf(x->el_in);
                }
                
                if(l == 0) { //solve multiply by zero issue
                    (*APout4++) =   sample1 * cosf(2 * x->az_in);
                } else {
                    (*APout4++) =   sample1 * cosf(2 * x->az_in) * cosf(x->el_in) * cosf(x->el_in);;
                }
                
                if(l == 0) { //solve multiply by zero issue
                    (*APout5++) =   sample1 * sinf(2 * x->az_in);
                } else {
                    (*APout5++) =   sample1 * sinf(2 * x->az_in) * cosf(x->el_in) * cosf(x->el_in);;
                }
                
        
            
            
        }
        
        
        x->sample1_old = sample1; //Input
        x->sample2_old = sample2; //Azi
        x->sample3_old = sample3; //Ele
        
        
        
    }
    
    
    return (w+11);
    
}



t_int *grambipan_tilde_order3(t_int *w)
{
    t_grambipan_tilde *x = (t_grambipan_tilde *)(w[1]);
    t_sample  *APin1 =    (t_sample *)(w[2]);
    t_sample  *APin2 =    (t_sample *)(w[3]);
    t_sample  *APin3 =    (t_sample *)(w[4]);
    t_sample  *APout1 =    (t_sample *)(w[5]);
    t_sample  *APout2 =    (t_sample *)(w[6]);
    t_sample  *APout3 =    (t_sample *)(w[7]);
    t_sample  *APout4 =    (t_sample *)(w[8]);
    t_sample  *APout5 =    (t_sample *)(w[9]);
    t_sample  *APout6 =    (t_sample *)(w[10]);
    t_sample  *APout7 =    (t_sample *)(w[11]);
    int          APn =           (int)(w[12]);
    
    t_sample sample1, sample2, sample3;
    double l = x->el;
    
    while (APn--)
    {
        
        
        sample1 = (*APin1++); //audio input 1
        sample2 = (*APin2++) * radians; //audio input 2 for azimuth
        sample3 = (*APin3++ - 0.5) * kPI; //audio input 3 for elevation
        
        
        if(sample2 != x->sample2_old || sample3 != x->sample3_old) { //use message audio input controls
            
            
                (*APout1++) =   sample1 * 0.707; //W
            
            
                if(sample3 == x->sample3_old) {
                (*APout2++) =   sample1 * cosf(sample2); //X
                (*APout3++) =   sample1 * sinf(sample2); //Y
                (*APout4++) =   sample1 * cosf(2 * sample2); //U
                (*APout5++) =   sample1 * sinf(2 * sample2); //V
                (*APout6++) =   sample1 * cosf(3 * sample2); //P
                (*APout7++) =   sample1 * sinf(3 * sample2); //Q
                } else {
                (*APout2++) =   sample1 * cosf(sample2) * cosf(sample3); //X
                (*APout3++) =   sample1 * sinf(sample2) * cosf(sample3); //Y
                (*APout4++) =   sample1 * cosf(2 * sample2) * cosf(sample3) * cosf(sample3); //U
                (*APout5++) =   sample1 * sinf(2 * sample2) * cosf(sample3) * cosf(sample3); //V
                (*APout6++) =   sample1 * cosf(3 * sample2) * cosf(sample3) * cosf(sample3) * cosf(sample3); //P
                (*APout7++) =   sample1 * sinf(3 * sample2) * cosf(sample3) * cosf(sample3) * cosf(sample3); //Q
                }
                    
            
            
            
            
        } else {  //if not, use message rate inputs
    
                (*APout1++) =   sample1 * 0.707;
                
                
                if(l == 0) { //solve multiply by zero issue
                    (*APout2++) =   sample1 * cosf(x->az_in);
                } else {
                    (*APout2++) =   sample1 * cosf(x->az_in) * cosf(x->el_in);
                }
                
                if(l == 0) { //solve multiply by zero issue
                    (*APout3++) =   sample1 * sinf(x->az_in);
                } else {
                    (*APout3++) =   sample1 * sinf(x->az_in) * cosf(x->el_in);
                }
                
                if(l == 0) { //solve multiply by zero issue
                    (*APout4++) =   sample1 * cosf(2 * x->az_in);
                } else {
                    (*APout4++) =   sample1 * cosf(2 * x->az_in) * cosf(x->el_in) * cosf(x->el_in);;
                }
                
                if(l == 0) { //solve multiply by zero issue
                    (*APout5++) =   sample1 * sinf(2 * x->az_in);
                } else {
                    (*APout5++) =   sample1 * sinf(2 * x->az_in) * cosf(x->el_in) * cosf(x->el_in);
                }
                
                if(l == 0) { //solve multiply by zero issue
                    (*APout6++) =   sample1 * cosf(3 * x->az_in);
                } else {
                    (*APout6++) =   sample1 * cosf(3 * x->az_in) * cosf(x->el_in) * cosf(x->el_in) * cosf(x->el_in);
                }
                
                if(l == 0) { //solve multiply by zero issue
                    (*APout7++) =   sample1 * sinf(3 * x->az_in);
                } else {
                    (*APout7++) =   sample1 * sinf(3 * x->az_in) * cosf(x->el_in) * cosf(x->el_in) * cosf(x->el_in);
                }
            
        }
        
        
        x->sample1_old = sample1; //Input
        x->sample2_old = sample2; //Azi
        x->sample3_old = sample3; //Ele
        
        
        
    }
    
    
    return (w+13);
    
}


void grambipan_tilde_dsp(t_grambipan_tilde *x, t_signal **sp)
{
    if(x->order==0)dsp_add(grambipan_tilde_order1, 9, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[0]->s_n);
    if(x->order==1)dsp_add(grambipan_tilde_order1, 9, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[0]->s_n);
     if(x->order==2)dsp_add(grambipan_tilde_order2, 10, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[0]->s_n);
     if(x->order==3)dsp_add(grambipan_tilde_order3, 12, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[8]->s_vec, sp[9]->s_vec, sp[0]->s_n);
}

void *grambipan_tilde_new(t_floatarg order)
{
    t_grambipan_tilde *x = (t_grambipan_tilde *)pd_new(grambipan_tilde_class);
    
    x->order = 0;
    x->order = order;
    
    
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 2
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); //audio input 3
    
    switch(x->order){
    default:
    
    case 0:
    outlet_new(&x->x_obj, gensym ("signal")); //write for loop
    outlet_new(&x->x_obj, gensym ("signal"));
    outlet_new(&x->x_obj, gensym ("signal"));
    outlet_new(&x->x_obj, gensym ("signal"));
    break;
            
    
    case 1:
    outlet_new(&x->x_obj, gensym ("signal"));
    outlet_new(&x->x_obj, gensym ("signal"));
    outlet_new(&x->x_obj, gensym ("signal"));
    outlet_new(&x->x_obj, gensym ("signal"));
    break;
    
    case 2:
    outlet_new(&x->x_obj, gensym ("signal"));
    outlet_new(&x->x_obj, gensym ("signal"));
    outlet_new(&x->x_obj, gensym ("signal"));
    outlet_new(&x->x_obj, gensym ("signal"));
    outlet_new(&x->x_obj, gensym ("signal"));
    break;
    
    case 3:
    outlet_new(&x->x_obj, gensym ("signal"));
    outlet_new(&x->x_obj, gensym ("signal"));
    outlet_new(&x->x_obj, gensym ("signal"));
    outlet_new(&x->x_obj, gensym ("signal"));
    outlet_new(&x->x_obj, gensym ("signal"));
    outlet_new(&x->x_obj, gensym ("signal"));
    outlet_new(&x->x_obj, gensym ("signal"));
    break;
            
    }
    return (void *)x;
}

void grambipan_tilde_setup(void)
{
    grambipan_tilde_class = class_new(gensym("grambipan~"),(t_newmethod)grambipan_tilde_new,0, sizeof(t_grambipan_tilde),CLASS_DEFAULT,A_DEFFLOAT,0);
    class_addmethod(grambipan_tilde_class,
                    (t_method)grambipan_tilde_dsp, gensym("dsp"), 0);
    class_addmethod(grambipan_tilde_class, (t_method)grambipan_tilde_az,gensym("az"), A_DEFFLOAT, 0);
    class_addmethod(grambipan_tilde_class, (t_method)grambipan_tilde_el,gensym("el"), A_DEFFLOAT, 0);
    CLASS_MAINSIGNALIN(grambipan_tilde_class, t_grambipan_tilde, APf);
    class_sethelpsymbol(grambipan_tilde_class, gensym("grambilib-help.pd"));
    post(version);
}
