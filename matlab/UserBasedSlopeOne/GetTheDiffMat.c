#include "mex.h"
#include "math.h" 

void mexFunction(int nlhs, mxArray *plhs[], 
    int nrhs, const mxArray *prhs[]){
	int Rm,Rn,Dm,Dy;
	double *R,*D;
    int index1;
    int a;
    int row3;
    int i,j,k;
	int count_u;
	R = mxGetPr(prhs[0]); 
	Rm = mxGetM(prhs[0]);
	Rn = mxGetN(prhs[0]);
	// D matrix
	plhs[0]=mxCreateDoubleMatrix(Rn,Rn,mxREAL);
	D = mxGetPr(plhs[0]);
    a = 0;
    for (i = 0; i < Rn; ++i)
    {
    	for(j = i + 1 ; j < Rn ; j++)
    	{
            index1 = i*Rn + j;

    		for( k = 0 ; k < Rm ; k++)
    		{
                row3 = k*Rn;
				if (R[row3 + i] > 0 && R[row3 + j] > 0){
					D[index1] += (R[row3 + i] - R[row3 + j]);
				}
    		}
            D[j*Rn + i] = -D[index1];
    	}
    }
}