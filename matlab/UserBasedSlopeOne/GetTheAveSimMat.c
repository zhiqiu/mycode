#include "mex.h"
#include "math.h" 

void mexFunction(int nlhs, mxArray *plhs[], 
    int nrhs, const mxArray *prhs[]){
	int Rm,Rn,Dm,Dy;
	double *R,*S,*Sim;
    int index1;
    int a;
    int row3;
    int i,j,k;
	int count_u;
	double ss;
	R = mxGetPr(prhs[0]); 
	Sim = mxGetPr(prhs[1]);
	Rm = mxGetM(prhs[0]);
	Rn = mxGetN(prhs[0]);

	// D matrix
	plhs[0]=mxCreateDoubleMatrix(Rm,Rn,mxREAL);
	S = mxGetPr(plhs[0]);
    a = 0;
    for (i = 0; i < Rm; ++i)
    {
    	for(j = 0 ; j < Rn ; j++)
    	{
            index1 = i*Rn + j;
			count_u = 0;
			ss = 0;
    		for( k = 0 ; k < Rm ; k++)
    		{
                row3 = k*Rn;
				
				if (R[row3 + j] > 0 && k != i){
					count_u ++;
					ss += Sim[i*Rm + k];
				}
    		}
            if(count_u!=0) S[i*Rn + j] = ss/count_u;
			else S[i*Rn + j] = 0;
    	}
    }
}