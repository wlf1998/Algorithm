/***************
 * The Closest Pair Of Points
 * Lifeng Wang
 * 2018.11
 * ************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
 
const double BOUND = 100000000;                 //bound
const int N = 10000;
 
struct Point{
    double x;
    double y;
}point[N];                                      //point coordinate

int tmp[N];                                     //contain mid-area points 
 
int CompareXY(const void *a, const void *b){    //compare x in ascending order, if x is same, then compare y                                        
    Point *c=(Point *)a;
	Point *d=(Point *)b;
    if(c->x!= d->x)
        return c->x-d->x;
    return c->y-d->y;
}
 
int Compare(const void *a, const void * b){     //compare y in ascending order    
	int c=*(int*)a, d=*(int*)b;
    return point[c].y - point[d].y;
}
 
double Minimum(double a, double b){             //minimum
    return a < b ? a : b;
}
 
double Distance(int i, int j){                  //distance
    return sqrt((point[i].x-point[j].x)*(point[i].x-point[j].x)+(point[i].y-point[j].y)*(point[i].y-point[j].y));
}
 
double Closest_Pair(int left, int right){       //get the closest pair of points
    double d = BOUND;
    if(left==right)                             //only one point
        return d;
    if(left + 1 == right)                       //only two points
        return Distance(left, right);
    int mid = (left+right)/2;  
    double d1 = Closest_Pair(left,mid); 
    double d2 = Closest_Pair(mid+1,right); 
    d = Minimum(d1,d2);  
    int i,j,k=0;

    for(i=left;i<=right;i++){                   //find the mid-area
        if(fabs(point[mid].x-point[i].x)<=d)
            tmp[k++]=i;
    }
    qsort(tmp,k,sizeof(int),Compare); 
    
    for(i = 0;i<k;i++){                         //get the closest pair of points in mid-area
        for(j=i+1;j<k;j++){
        	if(point[tmp[j]].y-point[tmp[i]].y<d){
               double d3 = Distance(tmp[i],tmp[j]);
               if(d > d3)
               d = d3;
            }
        }
    }

    return d;
}
 
int main(){ 
    int n;
    scanf("%d",&n);
    for(int i = 0; i < n; i++)
        scanf("%lf%lf",&point[i].x,&point[i].y);
    qsort(point,n,sizeof(Point),CompareXY);
    printf("%.4lf\n",Closest_Pair(0,n-1));
        
    return 0;
}

