//Necessary header files are included
#include <stdio.h>
#include <stdlib.h>
//Function prototypes
void Compute_Sq_Root(const char* fname);
double Sq_Rt( double num );
//Program logic:
//Newton Raphson method for Root computation of polynomials
//Theory:The intercept of the the tangent line at any point(say at x0) sufficiently close enough to a suspected root gives a better approximation to the root than x0
//Method: Solve recurrence definition: xk+1=xk-f(xk)/(f'(xk)).The initial value x0 must be close guess to the root.f'(xk) cannot be 0.
//Here, we demonstrate square computation by taking f(x)=x^2-Y where the root gives the square root of Y.
int main()
{
	Compute_Sq_Root("roots.txt");//Compute
	return 0;
}
//Function to compute square root through NRM and store it in the prescribed format in fname
void Compute_Sq_Root(const char* fname)
{
	FILE* rfp=fopen(fname,"r");//fname is opened in read mode
	FILE* wfp=fopen("temp.txt","w");//A temp file named temp.txt is created as it is assumed that a file with this name doesn't exist in the directory of this C file
	double x,sq;//x is used for storing the number scanned from fname, sq is used for storing x's square root
	long fsize;//fsize is used for storing the size of fname
	fseek(rfp,0,SEEK_END);//rfp is made to point to the end of its buffer
	fsize=ftell(rfp);//rfp's position is stored in fsize
	fseek(rfp,0,SEEK_SET);//rfp is brought back to the beginning of the buffer
	while(ftell(rfp)<fsize)//while rfp is not pointing to the end of its buffer
	{
		fscanf(rfp,"%lf",&x);//The value of x is obtained
		fgetc(rfp);//delimiter \n is removed
		sq=Sq_Rt(x);//sqrt of x is stored in sq
		fprintf(wfp,"%8.3lf\t%8.3lf\n",x,sq);//x and sq are printed into wfp's buffer
	}
	fclose(rfp);//The file fname is closed
	fclose(wfp);//the file temp.txt is closed
	remove(fname);//fname is removed
	rename("temp.txt",fname);//temp.txt is renamed as fname
	return;
}
double Sq_Rt(double num)
{
	if(num==0.0)//if num is 0, it square root is trivial and is returned.It is done to avoid division by 0 error.
	{
		return 0.0;
	}
	double x=num/2,y;//x is now x0=num/2 num/2 is taken as a guess to the root of the function x^2-num.We dont face any problem as the function has only one root.
	int i=0;//i will be the loop control variable.
	while(i<1000)//To perform 1000 recursive computation for square root
	{
		y=x-(x*x-num)/(2*x);//y=x(i+1) and x=xi
		x=y;//x is now xi+1 for the next iteration
		i++;
	}
	return x;//Value of square root of num.
}
