#include "stdafx.h"
#include <cv.h>
#include <highgui.h> 
IplImage* image; 
IplImage* copyimage; 
static CvHaarClassifierCascade* cascade = 0; 
static CvMemStorage* storage = 0; 
const char* cascade_name ="haarcascade_frontalface_alt2.xml";
//��Ҫ�����ļ���OpenCV\data\haarcascades�ļ����п�������Ŀ�ļ�����
void detect_and_draw( IplImage* img ); 
//��������  
int _tmain(int argc, _TCHAR* argv[]) 
{ 
	cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
//��������������õķ�����  
if( !cascade ) 
{  
	fprintf( stderr,"ERROR: Could not load classifier cascade\n" );
return -1; 
}  
storage = cvCreateMemStorage(0);     
//��̬�洢�ṹ�������洢������ͼ���е�λ��   
image = cvLoadImage( "D��\\����ʶ��ͼƬ\\2.jpg" ); 
if( !image ) return -1; 
cvNamedWindow( "Original Image", 1 ); 
cvShowImage( "Original Image", image);  
detect_and_draw( image );  
//�Լ��ص�ͼ����м��
cvWaitKey(); 
image = NULL; 
//��image����cvCreateImage()�����ģ���ô��cvReleaseImage()�ͷ�;������"����"��,�Ͳ��ܡ��ͷš� 
cvDestroyWindow("Original"); 
cvDestroyWindow("result"); 
 return 0; 
} 
void detect_and_draw( IplImage* img)
{  static CvScalar colors[] =   
{   
	{{0,0,255}}, 
	{{0,128,255}}, 
	{{0,255,255}}, 
	{{0,255,0}},  
	{{255,128,0}},
	{{255,255,0}},  
	{{255,0,0}},   
	{{255,0,255}} 
};  
double scale = 1.3;  
copyimage=img; 
IplImage* gray = cvCreateImage( cvSize(copyimage->width,copyimage->height), 8, 1 );
cvCvtColor( copyimage, gray, CV_BGR2GRAY ); 
cvClearMemStorage( storage );   
if( cascade )  
{   
	/*����cvHaarDetectObjects���ͼ���е�Ŀ�꣬��OpenCV�ṩ��*/
	CvSeq* faces = cvHaarDetectObjects( gray, cascade, storage, 1.1, 2, CV_HAAR_DO_CANNY_PRUNING ,     cvSize(20, 20) );  
	for( int i = 0; i < (faces ? faces->total : 0); i++ ) 
	{ 
		CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
		cvRectangle( copyimage, cvPoint(r->x,r->y),  
			cvPoint(r->x+r->width,r->y+r->height), CV_RGB(255,0,0), 3 );   
	} 
}  
cvNamedWindow( "result", 1 );  
cvShowImage( "result", copyimage );   
copyimage = NULL;  cvReleaseImage( &gray ); 
��