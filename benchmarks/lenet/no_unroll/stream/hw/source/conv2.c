#include "../../lenet5_clstr_hw_defines.h"

typedef uint32_t array3d_in[conv2KSize][conv2KSize][conv2InChan];
typedef uint32_t array4d_t[conv2KSize][conv2KSize][conv2InChan][conv2OutChan];

void compute(array3d_in convWin, array4d_t kernel, uint32_t* strOut) {

    int h,w,c,cc,x,y;
    uint32_t sum;

    #pragma nounroll
    for (h=0; h<conv2OutDim; h++){
        #pragma nounroll
        for (w=0; w<conv2OutDim; w++){
            sum = 0;
            #pragma nounroll
            for(cc=0; cc<conv2OutChan; cc++){
                #pragma nounroll
                for(x=0; x<conv2KSize; x++) {
                    #pragma nounroll
                    for(y=0; y<conv2KSize; y++){
                        #pragma nounroll
                        for(c=0; c<conv2InChan; c++){
                            sum += convWin[x][y][c] * kernel[x][y][c][cc];
                        }
                    }
                }
                
            // if(sum >= 2){
            //     sum = sum*0.964027580076;
            // } else if (sum < 2 && sum >= 1){
            //     sum = sum*0.761594155956;
            // } else if (sum < 1 && sum >= .5){
            //     sum = sum*0.46211715726;
            // } else if (sum < .5 && sum >= .25){
            //     sum = sum*.244918662404;
            // } else if (sum < .25 && sum >= 0){
            //     sum = sum*0;
            // } else if (sum < 0 && sum >= -.25){
            //     sum = sum*-.244918662404;
            // } else if (sum < -.25 && sum >= -.5){
            //     sum = sum*-0.46211715726;
            // } else if (sum < -.5 && sum >= -1){
            //     sum = sum*-0.761594155956;
            // } else if (sum > -1){
            //     sum = sum*-0.964027580076;
            // }
            *strOut = sum;
            }
        }
    }
}

void top() {
    void* convWin = (void*)Conv2Window;
    void* kernel = (void*)Conv2Weights;
    void* strOut = (void*)Conv2Out;

	compute(convWin,kernel,strOut);

	return;
}