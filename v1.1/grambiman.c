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


static char *version = "[grambiman~] v. 1 (2016) for Pd written by Ricky Graham <ricky@rickygraham.net>";

static t_class *grambiman_tilde_class;

typedef struct _grambiman_tilde {
    t_object  x_obj;
    
    //TODO: message rate inputs for A & B
    t_sample APf;
    double el;
    double az_in;
    double el_in;

    //to set perform routine
    float type;
    
    //for loop for inlet and outlet creation
    int ADincount;
    int ADoutcount;
    
    
    
} t_grambiman_tilde;



/* these functions allow control from the message-rate parameters in the Pd patch
void grambiman_tilde_az(t_grambiman_tilde *x, t_floatarg APazl)
{
    x->az_in = APazl * radians;
}

void grambiman_tilde_el(t_grambiman_tilde *x, t_floatarg APell )
{
    x->el = APell;
    x->el_in = (APell - 0.5) * (kPI);
}*/



/* modified perform routine to include two signal rate inputs for azimuth and elevation controls */
t_int *grambiman_tilde_rotate(t_int *w)
{
    t_grambiman_tilde *x = (t_grambiman_tilde *)(w[1]);
    t_sample  *APin1 =    (t_sample *)(w[2]);
    t_sample  *APin2 =    (t_sample *)(w[3]);
    t_sample  *APin3 =    (t_sample *)(w[4]);
    t_sample  *APin4 =    (t_sample *)(w[5]);
    /*
    t_sample  *APin5 =    (t_sample *)(w[6]);
    t_sample  *APin6 =    (t_sample *)(w[7]);
    t_sample  *APin7 =    (t_sample *)(w[8]);
    t_sample  *APin8 =    (t_sample *)(w[9]);
    t_sample  *APin9 =    (t_sample *)(w[10]);
    */
    t_sample  *APin10 =    (t_sample *)(w[6]);
    t_sample  *APout1 =    (t_sample *)(w[7]);
    t_sample  *APout2 =    (t_sample *)(w[8]);
    t_sample  *APout3 =    (t_sample *)(w[9]);
    t_sample  *APout4 =    (t_sample *)(w[10]);
    /*
    t_sample  *APout5 =    (t_sample *)(w[16]);
    t_sample  *APout6 =    (t_sample *)(w[17]);
    t_sample  *APout7 =    (t_sample *)(w[18]);
    t_sample  *APout8 =    (t_sample *)(w[19]);
    t_sample  *APout9 =    (t_sample *)(w[20]);
    */
    int          APn =           (int)(w[11]);
    
    t_sample sample1, sample2, sample3, sample4, sample10;
    
    while (APn--)
    {
        
        //Manipulation Input - WXYZRSTUV
        sample1 = (*APin1++); //W
        sample2 = (*APin2++); //X
        sample3 = (*APin3++); //Y
        sample4 = (*APin4++); //Z
        /*
        sample5 = (*APin5++); //R
        sample6 = (*APin6++); //S
        sample7 = (*APin7++); //T
        sample8 = (*APin8++); //U
        sample9 = (*APin9++); //V
        */
        sample10 = (*APin10++) * radians; //Positive Angle of Rotation - A
        
        
        /*
         x' = x * cos A - y * sin A;
         y' = x * sin A + y * cos A
         W & Z remain unchanged
         */
        
        //Manipulation Output - WXYZRSTUV - Checked - Should be good to go!
        (*APout1++) =   sample1 * 1; //W
        (*APout2++) =   sample2 * cosf(sample10) + (sample3 * -(sinf(sample10))); //X
        (*APout3++) =   sample2 * sinf(sample10) + (sample3 * cosf(sample10)); //Y
        (*APout4++) =   sample4 * 1; //Z
        /*(*APout5++) =   sample5 * 1; //R
        (*APout6++) =   sample6 * cosf(sample10) + (sample7 * -(sinf(sample10))); //S
        (*APout7++) =   sample6 * sinf(sample10) + (sample7 * cosf(sample10)); //T
        (*APout8++) =   sample8 * cosf(2 * (sample10)) + (sample9 * -(sinf(2 * (sample10)))); //U
        (*APout9++) =   sample8 * sinf(2 * (sample10)) + (sample9 * cosf(2 * (sample10))); //V
         */
    }
    
    
    return (w+12);
    

}


t_int *grambiman_tilde_tilt(t_int *w)
{
    
    t_grambiman_tilde *x = (t_grambiman_tilde *)(w[1]);
    t_sample  *APin1 =    (t_sample *)(w[2]);
    t_sample  *APin2 =    (t_sample *)(w[3]);
    t_sample  *APin3 =    (t_sample *)(w[4]);
    t_sample  *APin4 =    (t_sample *)(w[5]);
    /*
    t_sample  *APin5 =    (t_sample *)(w[6]);
    t_sample  *APin6 =    (t_sample *)(w[7]);
    t_sample  *APin7 =    (t_sample *)(w[8]);
    t_sample  *APin8 =    (t_sample *)(w[9]);
    t_sample  *APin9 =    (t_sample *)(w[10]);
    */
    t_sample  *APin10 =    (t_sample *)(w[6]);
    t_sample  *APout1 =    (t_sample *)(w[7]);
    t_sample  *APout2 =    (t_sample *)(w[8]);
    t_sample  *APout3 =    (t_sample *)(w[9]);
    t_sample  *APout4 =    (t_sample *)(w[10]);
    /*
    t_sample  *APout5 =    (t_sample *)(w[16]);
    t_sample  *APout6 =    (t_sample *)(w[17]);
    t_sample  *APout7 =    (t_sample *)(w[18]);
    t_sample  *APout8 =    (t_sample *)(w[19]);
    t_sample  *APout9 =    (t_sample *)(w[20]);
    */
    int          APn =           (int)(w[11]);
    
    t_sample sample1, sample2, sample3, sample4, sample10;
    
    while (APn--)
    {
        
        /*
        x' = x;
        w' = w;
        y' = y * cos B - z * sin B;
        z' = y * sin B + z * cos B
        */
        
        //Manipulation Input - WXYZRSTUV
        sample1 = (*APin1++); //W
        sample2 = (*APin2++); //X
        sample3 = (*APin3++); //Y
        sample4 = (*APin4++); //Z
       /*
        sample5 = (*APin5++); //R
        sample6 = (*APin6++); //S
        sample7 = (*APin7++); //T
        sample8 = (*APin8++); //U
        sample9 = (*APin9++); //V
        */
        sample10 = (*APin10++) * radians;
        
        
        
        //Manipulation Output - WXYZRSTUV - Checked - Should be good to go!
        (*APout1++) =   sample1 * 1; //W
        
        (*APout2++) =   sample2 * 1; //X
    
        (*APout3++) =   sample3 * cosf(sample10) - (sample4 * (sinf(sample10))); //Y
        
        (*APout4++) =   sample3 * sinf(sample10) + (sample4 * cosf(sample10)); //Z
        
       /* (*APout5++) =   (sample5 * ((3/4) * cosf(2 * sample10)+(1/4))) + (sample7 * (3/4) * sinf(2 * sample10)) - (sample8 * (3/8) * cosf(2 * sample10)-(3/8)); //R
        
        (*APout6++) =   sample6 * cosf(sample10) + (sample9 * sinf(sample10)); //S
        
        (*APout7++) = (sample7 * (2 * cosf(sample10))) - (sample5 * sinf(sample10)) - (sample8 * (1/2) * sinf(2 * sample10));
        //T
        
        (*APout8++) =  (sample5 * (1/2) * cosf(2 * sample10) - ((1/2))) + (sample7 * ((1/2) * sinf(2 * sample10))) + (sample8 * ((1/4)*cosf(2*sample10)+(3/4))); //U
        
        (*APout9++) =   (sample9 * cosf(sample10)) - (sample6 * sinf(sample10)); //V
        */
    }
    
    
    return (w+12);


}



t_int *grambiman_tilde_tumble(t_int *w)
{
    
    t_grambiman_tilde *x = (t_grambiman_tilde *)(w[1]);
    t_sample  *APin1 =    (t_sample *)(w[2]);
    t_sample  *APin2 =    (t_sample *)(w[3]);
    t_sample  *APin3 =    (t_sample *)(w[4]);
    t_sample  *APin4 =    (t_sample *)(w[5]);
    /*
    t_sample  *APin5 =    (t_sample *)(w[6]);
    t_sample  *APin6 =    (t_sample *)(w[7]);
    t_sample  *APin7 =    (t_sample *)(w[8]);
    t_sample  *APin8 =    (t_sample *)(w[9]);
    t_sample  *APin9 =    (t_sample *)(w[10]);
    */
    t_sample  *APin10 =    (t_sample *)(w[6]);
    t_sample  *APout1 =    (t_sample *)(w[7]);
    t_sample  *APout2 =    (t_sample *)(w[8]);
    t_sample  *APout3 =    (t_sample *)(w[9]);
    t_sample  *APout4 =    (t_sample *)(w[10]);
    /*
    t_sample  *APout5 =    (t_sample *)(w[16]);
    t_sample  *APout6 =    (t_sample *)(w[17]);
    t_sample  *APout7 =    (t_sample *)(w[18]);
    t_sample  *APout8 =    (t_sample *)(w[19]);
    t_sample  *APout9 =    (t_sample *)(w[20]);
     */
    int          APn =           (int)(w[11]);
    
    t_sample sample1, sample2, sample3, sample4, sample10;
    
    while (APn--)
    {
        
        /*
         
         x' = x * cos B - z * sin B
         w' = w
         y' = y
         z' = x * sin B + z * cos B
         
        */
        
        //Manipulation Input - WXYZRSTUV
        sample1 = (*APin1++); //W
        sample2 = (*APin2++); //X
        sample3 = (*APin3++); //Y
        sample4 = (*APin4++); //Z
        /*sample5 = (*APin5++); //R
        sample6 = (*APin6++); //S
        sample7 = (*APin7++); //T
        sample8 = (*APin8++); //U
        sample9 = (*APin9++); //V
         */
        sample10 = (*APin10++) * radians; //Angle - B
        //sample10 = (*APin10++ - 0.5) * kPI; //Angle - B
        
        //Manipulation Output - WXYZRSTUV
        (*APout1++) =   sample1 * 1; //W
        (*APout2++) =   sample2 * cosf(sample10) - (sample4 * sinf(sample10)); //X
        (*APout3++) =   sample2 * 1; //Y
        (*APout4++) =   sample2 * sinf(sample10) + (sample4 * cosf(sample10)); //Z
        /*(*APout5++) =   (sample5 * ((3/4) * cosf(2 * sample10)+(1/4))) + (sample6 * ((3/4) * sinf(2 * sample10))) + (sample8 *((3/8) - (3/8 * cosf(2 * sample10)))); //R
        (*APout6++) = sample6 * cosf(2 * sample10) - (sample5 * sinf(2 * sample10)) + (sample8 * ((1/2) * sinf(2 * sample10))); //S
        (*APout7++) = sample7 * cosf(sample10) + (sample9 * sinf(sample10)); //T
        (*APout8++) =  (sample5 * ((1/2)-(1/2) * cosf(2 * sample10))) + (sample6 * ((-1/2) * sinf(2 * sample10))) + (sample8 * ((1/4) * cosf(2 * sample10) + (3/4)));
        (*APout9++) =   (sample9 * cosf(sample10)) - (sample7 * sinf(sample10)); //Y
         */
    }
    
    
    return (w+12);
    


}




t_int *grambiman_tilde_rotilt(t_int *w) //leave out for now
{
    
    t_grambiman_tilde *x = (t_grambiman_tilde *)(w[1]);
    t_sample  *APin1 =    (t_sample *)(w[2]);  //W
    t_sample  *APin2 =    (t_sample *)(w[3]);  //X
    t_sample  *APin3 =    (t_sample *)(w[4]);  //Y
    t_sample  *APin4 =    (t_sample *)(w[5]);  //Z
    t_sample  *APin10 =    (t_sample *)(w[6]); //A
    t_sample  *APin11 =    (t_sample *)(w[7]); //B
    t_sample  *APout1 =    (t_sample *)(w[8]);
    t_sample  *APout2 =    (t_sample *)(w[9]);
    t_sample  *APout3 =    (t_sample *)(w[10]);
    t_sample  *APout4 =    (t_sample *)(w[11]);
    int          APn =           (int)(w[12]);
    
    t_sample sample1, sample2, sample3, sample4, sample10, sample11;
    
    while (APn--)
    {
        /* - two inputs A (rotate) and B (tilt)
         x' = x * cos A - y * sin A
         w' = w
         y' = x * sin A * cos B + y * cos A * cos B - z * sin B
         z' = x * sin A * sin B + y * cos A * sin B + z * cos B
        */
        
        //Manipulation Input
        sample1 = (*APin1++); //W
        sample2 = (*APin2++); //X
        sample3 = (*APin3++); //Y
        sample4 = (*APin4++); //Z
        sample10 = (*APin10++) * radians; //Angle A
        sample11 = (*APin11++) * radians; //Angle B
        //sample11 = (*APin11++ - 0.5) * kPI; //Angle B
        
        //Manipulation Output
        (*APout1++) =   sample1 * 1; //W
        (*APout2++) =   sample2 * cosf(sample10) - (sample3 * sinf(sample10)); //X
        (*APout3++) =   (sample2 * sinf(sample10) * cosf(sample11)) + (sample3 * cosf(sample10) * cosf(sample11)) - (sample4 *sinf(sample11)); //Y
        (*APout4++) = (sample2 * sinf(sample10) * sinf(sample11)) + (sample3 * cosf(sample10) * sinf(sample11)) + (sample4 * cosf(sample11)); //Z
        
        //RSTUV? - Higher Orders - Require HOA Encoders
        
    }

    
    return (w+13);
    
}




void grambiman_tilde_dsp(t_grambiman_tilde *x, t_signal **sp)
{
    
    if(x->type==1)dsp_add(grambiman_tilde_rotate, 11, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[8]->s_vec, sp[0]->s_n);
    
    if(x->type==2)dsp_add(grambiman_tilde_tilt, 11, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[8]->s_vec, sp[0]->s_n);
    
    if(x->type==3)dsp_add(grambiman_tilde_tumble, 11, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[8]->s_vec, sp[0]->s_n);
    
    if(x->type==4)dsp_add(grambiman_tilde_rotilt, 12, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[8]->s_vec, sp[9]->s_vec, sp[0]->s_n);
}


void *grambiman_tilde_new(t_symbol *s, int argc, t_atom *argv)
{
    
    t_grambiman_tilde *x = (t_grambiman_tilde *)pd_new(grambiman_tilde_class);
    
    char teststring[1000];
    if(argc>0)atom_string(argv, teststring, 1000);
    char* type[4] = {"rotate", "tilt", "tumble", "rotilt"};
    
    int j = 0;
    int ret[4];
    
    for(int i = 0; i < 4; i++) {
            ret[i] = strcmp(teststring, type[i]);
            if(ret[0] == 0) j = 1;
            if(ret[1] == 0) j = 2;
            if(ret[2] == 0) j = 3;
            if(ret[3] == 0) j = 4;
    }
    
    
      post("type updated: %i", j);
      x->type=j; //assign value to type
    
    if(x->type == 1){
            post("Rotate - B-Format Only\n");
            for(x->ADincount = 0; x->ADincount < 4;x->ADincount++)inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal);
            for(x->ADoutcount = 0; x->ADoutcount < 4;x->ADoutcount++)outlet_new(&x->x_obj, gensym ("signal"));
    }
            
            
    if(x->type == 2){
            post("Tilt - B-Format Only\n");
            for(x->ADincount = 0; x->ADincount < 4;x->ADincount++)inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal);
            for(x->ADoutcount = 0; x->ADoutcount < 4;x->ADoutcount++)outlet_new(&x->x_obj, gensym ("signal"));
    }
            
            
    if(x->type == 3){
            post("Tumble - B-Format Only\n");
            for(x->ADincount = 0; x->ADincount < 4;x->ADincount++)inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal);
            for(x->ADoutcount = 0; x->ADoutcount < 4;x->ADoutcount++)outlet_new(&x->x_obj, gensym ("signal"));
    }

    if(x->type == 4){
            post("Rotilt - B-Format Only\n");
            for(x->ADincount = 0; x->ADincount < 5;x->ADincount++)inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal);
            for(x->ADoutcount = 0; x->ADoutcount < 4;x->ADoutcount++)outlet_new(&x->x_obj, gensym ("signal"));
    }
    
    
    
  
    return (void *)x;
}


void grambiman_tilde_setup(void)
{
    grambiman_tilde_class = class_new(gensym("grambiman~"),(t_newmethod)grambiman_tilde_new,0, sizeof(t_grambiman_tilde),CLASS_DEFAULT,A_GIMME,0);
    class_addmethod(grambiman_tilde_class,
                    (t_method)grambiman_tilde_dsp, gensym("dsp"), 0);
    
    /*class_addmethod(grambiman_tilde_class, (t_method)grambiman_tilde_az,gensym("a"), A_DEFFLOAT, 0);
    class_addmethod(grambiman_tilde_class, (t_method)grambiman_tilde_el,gensym("b"), A_DEFFLOAT, 0);*/
    
    CLASS_MAINSIGNALIN(grambiman_tilde_class, t_grambiman_tilde, APf);
    class_sethelpsymbol(grambiman_tilde_class, gensym("grambilib-help.pd"));
    post(version);
}
