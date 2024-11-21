#include <stdio.h>
#include <math.h>

//TIME DOMAIN
int audio_sample_measured[1500],finite_impulse_response[1500],total_system_response[1500];
//FREQUENCY DOMAIN --> AUDIO SAMPLES TRANSFORMATION
float Xr[1500];
float Xi[1500];
//FREQUENCY DOMAIN --> FIR AUDIO SAMPLES TRANSFORMATION
float XrFIR[1500];
float XiFIR[1500];
//FREQUENCY DOMAIN --> TOTAL RESPONSE SAMPLES TRANSFORMATION
float XrY[1500];
float XiY[1500];
void AUDIO_zero_padding(int* INPUT,int INPUT_DIM, int FIR_DIM);
void FIR_zero_padding(int* FIR,int FIR_DIM, int INPUT_DIM);
void insertValueAudio(int* INPUT,int INPUT_DIM);
void insertValueFIR(int* FIR,int FIR_DIM);
void calc_conv(int* INPUT,int INPUT_DIM,int* FIR,int FIR_DIM, int* RESPONSE);
void linear_calc_conv(int len1, int len2);
void calculateDFT(int dim_AUDIO,int dim_FIR);
void calculate_IDFT(int len, int *x);

int main() {
    int m,n;

    printf("\n-------------------------zero_padded_CONVOLUTION without USING MODULAR APPROACH--------------------------------\n");

    printf("\n enter value dimension for audio_sample_measured");
    scanf("%d",&m);
    printf("Enter values for i/p x(n):\n");
    for(int i=0;i<m;i++)
        scanf("%d",&audio_sample_measured[i]);

    printf("\n enter value dimension for finite_impulse_response");
    scanf("%d",&n);
    printf("Enter Values for i/p h(n) \n");
    for(int i=0;i<n; i++)
        scanf("%d",&finite_impulse_response[i]);

    // padding of zeros for INPUT
    for(int i=m;i<=m+n-1;i++)
        audio_sample_measured[i]=0;


    for(int i=n;i<=m+n-1;i++)
        finite_impulse_response[i]=0;


    /* convolution operation */
    for(int i=0;i<m+n-1;i++){
        total_system_response[i]=0;
        for(int j=0;j<=i;j++){
            total_system_response[i]=total_system_response[i]+(audio_sample_measured[j]*finite_impulse_response[i-j]);
        }
    }
    //displaying the o/p
    for(int i=0;i<m+n-1;i++)
        printf("\n The Value of output y[%d]=%d",i,total_system_response[i]);


    printf("\n-------------------------zero_padded_CONVOLUTION USING MODULAR APPROACH--------------------------------\n");
     insertValueAudio(audio_sample_measured,m);
     insertValueFIR(finite_impulse_response,n);
     AUDIO_zero_padding(audio_sample_measured,m,n);
     FIR_zero_padding(finite_impulse_response,n,m);
     calc_conv(audio_sample_measured,m,finite_impulse_response,n, total_system_response);
    for(int i=0;i<m+n-1;i++)
        printf("\n The Value of output y[%d]=%d",i,total_system_response[i]);

    printf("\n-------------------------NOT-zero_padded_CONVOLUTION USING MODULAR APPROACH--------------------------------\n");
    linear_calc_conv(m,n);


    printf("\n-------------------------zero_padded_CONVOLUTION USING MODULAR APPROACH and DFT/PRODUCT_TERMS_BY_TERMS/IDFT--------------------------------\n");
    //insertValueAudio(audio_sample_measured,m);
    //insertValueFIR(finite_impulse_response,n);
    //AUDIO_zero_padding(audio_sample_measured,m,n);
    //FIR_zero_padding(finite_impulse_response,n,m);
    //calculateDFT(m,audio_sample_measured);//X(f)

    return 0;
}


void insertValueAudio(int* INPUT,int INPUT_DIM){
    printf("\n Enter value dimension for audio_sample_measured");
    scanf("%d",&INPUT_DIM);
    printf("Enter values for i/p x(n):\n");
    for(int i=0;i<INPUT_DIM;i++)
        scanf("%d",&INPUT[i]);
}

void insertValueFIR(int* FIR,int FIR_DIM){
    printf("\n Enter value dimension for audio_sample_measured");
    scanf("%d",&FIR_DIM);
    printf("Enter values for i/p x(n):\n");
    for(int i=0;i<FIR_DIM;i++)
        scanf("%d",&FIR[i]);
}


void AUDIO_zero_padding(int* INPUT,int INPUT_DIM, int FIR_DIM){
    for(int i=INPUT_DIM;i<=INPUT_DIM+FIR_DIM-1;i++)
        INPUT[i]=0;
}

void FIR_zero_padding(int* FIR,int FIR_DIM, int INPUT_DIM){
    for(int i=FIR_DIM;i<=INPUT_DIM+FIR_DIM-1;i++)
        FIR[i]=0;
}

void calc_conv(int* INPUT,int INPUT_DIM,int* FIR,int FIR_DIM, int* RESPONSE){
    for(int i=0;i<INPUT_DIM+FIR_DIM-1;i++){
        RESPONSE[i]=0;//sum=0
        for(int j=0;j<=i;j++){
            RESPONSE[i]=RESPONSE[i]+(INPUT[j]*FIR[i-j]);
        }
    }


}


void linear_calc_conv(int len1, int len2)
{
    int l = (len1) + (len2) - 1;//Ly
    int  n, k = 0;
    // Getting values of 1st sequence
    printf("\n enter value dimension for audio_sample_measured");
    for (int i = 0; i < len1; i++) { //n=#audio_samples
        scanf("%d", &audio_sample_measured[i]);
    }
    // Getting values of 2nd sequence
    printf("\n enter value dimension for fir_sample_measured");
    for (int i = 0; i < len2; i++) {//m=#fir_samples
        scanf("%d", &finite_impulse_response[i]);
    }
    for (n = 0; n < l; n++) {
        total_system_response[n] = 0;
        for (k = 0; k < len1; k++) {
            // To right shift the impulse
            if ((n - k) >= 0 && (n - k) < len2) {
                // Main calculation
                total_system_response[n] = total_system_response[n] + audio_sample_measured[k] * finite_impulse_response[n - k];
            }
            printf("%d\t", total_system_response[n]);
        }
    }
}

/*

 //FREQUENCY DOMAIN --> AUDIO SAMPLES TRANSFORMATION
float Xr[1500];
float Xi[1500];
//FREQUENCY DOMAIN --> FIR AUDIO SAMPLES TRANSFORMATION
float XrFIR[1500];
float XiFIR[1500];
//FREQUENCY DOMAIN --> TOTAL RESPONSE SAMPLES TRANSFORMATION
float XrY[1500];
float XiY[1500];
 */



void calculateDFT(int dim_AUDIO,int dim_FIR){
    //NECESSARY CONDITION FOR DFT+PRODUCT_TERM_BY_TERM+IDFT = LINEAR CONVOLUTION IS THE ZERO PADDING
    int i, k, n, N = 0;


    //AUDIO SAMPLE 1-DIMENSIONAL DFT
    printf("Enter the number of ""points in the DFT: ");//put the same #samples pls
    scanf("%d", &N);
    for (k = 0; k < N; k++) {
        Xr[k] = 0;
        Xi[k] = 0;
        for (n = 0; n < dim_AUDIO; n++) {
            Xr[k]
                    = (Xr[k]
                       + audio_sample_measured[n] * cos(2 * 3.141592 * k * n / N));
            Xi[k]
                    = (Xi[k]
                       + audio_sample_measured[n] * sin(2 * 3.141592 * k * n / N));
        }

        printf("(%f) + j(%f)\n",Xr[k], Xi[k]);
    }


    //FIR SAMPLE 1-DIMENSIONAL DFT
    printf("Enter the number of ""points in the DFT: ");
    scanf("%d", &N);
    for (k = 0; k < N; k++) {
        XrFIR[k] = 0;
        XiFIR[k] = 0;
        for (n = 0; n < dim_FIR; n++) {
            Xr[k]
                    = (Xr[k]
                       + finite_impulse_response[n] * cos(2 * 3.141592 * k * n / N));
            Xi[k]
                    = (Xi[k]
                       + finite_impulse_response[n] * sin(2 * 3.141592 * k * n / N));
        }

        printf("(%f) + j(%f)\n",Xr[k], Xi[k]);
    }

    //PRODUCT TERM BY TERM SECTION (real)
        for(int i=0;i<dim_FIR;i++){ XrY[i] = Xr[i] * XrFIR[i] ;}
    //PRODUCT TERM BY TERM SECTION (immaginary)
        for(int i=0;i<dim_FIR;i++){XiY[i] = Xi[i] * XiFIR[i] ;}

        int Ly = 2*dim_FIR - 1;
        calculate_IDFT(Ly,total_system_response);
}


void calculate_IDFT(int len, int *x){

    float XrY[len];
    float XiY[len];
    int i, k, n, N = 0;
    for (i = 0; i < len; i++) {
        printf(
                "Enter the real and "
                "imaginary bits of X(%d): ",
                i);
        scanf("%f %f", &Xr[i], &Xi[i]);
    }

    printf("Enter the number of "
           "points in the IDFT: ");
    scanf("%d", &N);

    for (n = 0; n < N; n++) {
        x[n] = 0;
        for (k = 0; k < N; k++) {
            int theta = (2 * 3.141592 * k * n) / N;
            x[n] = x[n] + Xr[k] * cos(theta)+ Xi[k] * sin(theta);
        }
        x[n] = x[n] / N;
        printf("\n x[%d] = %d\n", n,x[n]);
    }

    printf("\n-----------x[n]------------\n\n");
}




/*
 C:\Users\39348\CLionProjects\digital_filtering\cmake-build-debug\digital_filtering.exe

-------------------------without USING MODULAR APPROACH--------------------------------

 enter value dimension for audio_sample_measured4
Enter values for i/p x(n):
1
2
3
4

 enter value dimension for finite_impulse_response4
Enter Values for i/p h(n)
1
2
2
1

 The Value of output y[0]=1
 The Value of output y[1]=4
 The Value of output y[2]=9
 The Value of output y[3]=15
 The Value of output y[4]=16
 The Value of output y[5]=11
 The Value of output y[6]=4
-------------------------USING MODULAR APPROACH--------------------------------

 Enter value dimension for audio_sample_measured4
Enter values for i/p x(n):
1
2
3
4

 Enter value dimension for audio_sample_measured4
Enter values for i/p x(n):
1
2
2
1

 The Value of output y[0]=1
 The Value of output y[1]=4
 The Value of output y[2]=9
 The Value of output y[3]=15
 The Value of output y[4]=16
 The Value of output y[5]=11
 The Value of output y[6]=4
Process finished with exit code 0


 */