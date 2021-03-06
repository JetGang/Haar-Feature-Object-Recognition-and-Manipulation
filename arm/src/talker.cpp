#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <iostream>

#include <sstream>

#include<math.h>
#include<iomanip>
//#include <conio.h>
using namespace std;
#define PI 3.14159265
#define l1 0.5
#define l2 0.5
#define l3 0.2
void TINVERT(double x[3][3],double y[3][3]);
void TMULT(double a[3][3],double b[3][3],double c[3][3]);
void reverseMatri(double x[1][3],double theata[1][6],int l[1][1],int q);
void Path(double alpha[1][3],double theata[1][6],double beta[1][3],double N[1][3],double F[1][3]);
void solve(double a_1[1][3],double a_2[1][3],double a_3[1][3],double h[1][3],double N[1][3],double B[1][3]);

using namespace std;

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{   
    
        cout<<"l1=0.5,l2=0.5,l3=0.2"<<endl;
	int w[1][1],x[2][1];
	double W[1][3]={{0,0,1}},S[1][3]={{0,0,1}};
	double G[1][3],I[1][3],N[1][3],B[1][3];
	cout<<"input the initial joint angle's value :"<<endl;
        double sp,sl,ef,wf,g;
        ros::init(argc, argv, "arm_shoulder_pan_joint");
        ros::init(argc, argv, "arm_shoulder_lift_joint");
        ros::init(argc, argv, "arm_elbow_flex_joint");
        ros::init(argc, argv, "arm_wrist_flex_joint");
        ros::init(argc, argv, "gripper_joint");

        ros::NodeHandle n;
        ros::Publisher a_pub = n.advertise<std_msgs::Float64>("arm_shoulder_pan_joint/command", 1000);
        ros::Publisher b_pub = n.advertise<std_msgs::Float64>("arm_shoulder_lift_joint/command", 1000);
        ros::Publisher c_pub = n.advertise<std_msgs::Float64>("arm_elbow_flex_joint/command", 1000);
        ros::Publisher d_pub = n.advertise<std_msgs::Float64>("arm_wrist_flex_joint/command", 1000);
        ros::Publisher e_pub = n.advertise<std_msgs::Float64>("gripper_joint/command", 1000);

        ros::Rate loop_rate(1);

        std_msgs::Float64 msg_1;
        std_msgs::Float64 msg_2;
        std_msgs::Float64 msg_3;
        std_msgs::Float64 msg_4;
        std_msgs::Float64 msg_5;

        msg_1.data = 0.0;
        msg_2.data = 1.2;
        msg_3.data = -1.8;
        msg_4.data = 0.65;
        msg_5.data = 1.57;
         int count_0 = 0;
         while (ros::ok())
		 {
        a_pub.publish(msg_1);
        b_pub.publish(msg_2);
        c_pub.publish(msg_3);
        d_pub.publish(msg_4);
        e_pub.publish(msg_5);
        
        loop_rate.sleep();
        if(count_0>5){
        break;
        }
        ++count_0;
        }


    for(int i=0; i<1; i++)
    {
        for(int j=0; j<3; j++)
		{
          cin>>I[i][j];
		}
		cout<<endl;
    }
//	while(true)
//	{
		cout<<"input the three-element goal position :"<<endl;
		for(int i=0; i<1; i++)
    {
        for(int j=0; j<3; j++)
		{
          cin>>G[i][j];
		}
		cout<<endl;
    }

	solve(W,S,G,I,N,B);
	 for(int i=0; i<1; i++)
    {
        for(int j=0; j<3; j++)
		{
          I[i][j]=N[i][j]*180/PI;
		}
    }
	double N_1[3][3]=
	{
		{cos((N[0][0]+N[0][1]+N[0][2])),-sin((N[0][0]+N[0][1]+N[0][2])),l1*cos(N[0][0])+l2*cos((N[0][0]+N[0][1]))+l3*cos((N[0][0]+N[0][1]+N[0][2]))},
		{sin((N[0][0]+N[0][1]+N[0][2])),cos((N[0][0]+N[0][1]+N[0][2])),l1*sin(N[0][0])+l2*sin((N[0][0]+N[0][1]))+l3*sin((N[0][0]+N[0][1]+N[0][2]))},
		{0,0,1}
	};
	double W_1[3][3]=
	{
		{cos(W[0][2]*3.1415926/180),-sin(W[0][2]*3.1415926/180),W[0][0]},
		{sin(W[0][2]*3.1415926/180),cos(W[0][2]*3.1415926/180),W[0][1]},
		{0,0,1}
	};
	double S_1[3][3]=
	{
		{cos(S[0][2]*3.1415926/180),-sin(S[0][2]*3.1415926/180),S[0][0]},
		{sin(S[0][2]*3.1415926/180),cos(S[0][2]*3.1415926/180),S[0][1]},
		{0,0,1}
	};
	double S_2[3][3],e_1[3][3],e_2[3][3],k[1][3];
	TINVERT(S_1,S_2);
	TMULT(S_2,N_1,e_1);
	TMULT(e_1,W_1,e_2);
	k[0][0]=e_2[0][2];
	k[0][1]=e_2[1][2];
	double f_0,f_1;
	f_0=e_2[0][0];
	f_1=e_2[1][0];
	if(abs(f_0)<=0.0001)
	{
		if(f_1>=0)
			k[0][2]=90;
		else
			k[0][2]=-90;
		
	}
	else
	{
		k[0][2]=atan2(e_2[1][0],e_2[0][0])*180/PI; 

	}

    cout<<"pan and gripper: "<<endl;
    cin>>sp>>g;
  
         int count = 0;
         while (ros::ok())
		 {

         msg_1.data = sp;
         msg_2.data = B[0][0];
         msg_3.data = B[0][1];
         msg_4.data = B[0][2];
         msg_5.data = g;

         ROS_INFO("%f", msg_1.data);
         ROS_INFO("%f", msg_2.data);
         ROS_INFO("%f", msg_3.data);
         ROS_INFO("%f", msg_4.data);
         ROS_INFO("%f", msg_5.data);

   
        a_pub.publish(msg_1);
        b_pub.publish(msg_2);
        c_pub.publish(msg_3);
        d_pub.publish(msg_4);
        e_pub.publish(msg_5);

        ros::spinOnce();

        loop_rate.sleep();
        if(count>5){
        break;
        }
        ++count;
        }

 //  }

  return 0;
}


void TINVERT(double x[3][3],double y[3][3])
{
	  for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
          y[i][j]=0;
    }
	  	for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {       		
            y[j][i]=x[i][j];	
		}
        
    }
       int j=2;
         for(int k=0;k<2;k++)
		 {
			 for (int l=0;l<2;l++)
            y[k][j]+=y[k][l]*x[l][j];   
		 }
			 for(int i=0;i<3;i++)
			 {
	          y[2][i]=0;
			 }
	 y[0][2]=-y[0][2];
	 y[1][2]=-y[1][2];
	 y[2][2]=1;
}
void TMULT(double a[3][3],double b[3][3],double c[3][3])
{
   int i,j,k;
   for(i=0;i<3;i++)
     for(j=0;j<3;j++)
	 {
         c[i][j]=0;
         for(k=0;k<3;k++)
            c[i][j]+=a[i][k]*b[k][j];             
     }    
}
void reverseMatri(double x[1][3],double theata[1][6],int l[1][1],int q)
{
	l[0][0]=0;
	double a[1][2];
	int i,j,k;
    for(i=0;i<1;i++)
	{
     for(j=0;j<6;j++)
	 {
         theata[i][j]=0;            
     } 
	}
	 for(i=0;i<1;i++)
	 {
     for(j=0;j<2;j++)
	 {
         a[i][j]=0;            
     } 
	 }
	 double x_1;
	 x_1=x[0][2]/(90*PI/180);
	 if(x_1==1||x_1==-1)
	 {
		 a[0][0]=x[0][0]-l3*cos(x[0][2]);
		 a[0][1]=x[0][1]-l3*sin(x[0][2]);
	 }
	 else
	 {
		 a[0][0]=x[0][0]-l3*cos(x[0][2]);
		 a[0][1]=x[0][1]-l3*sin(x[0][2]);
	 }
	theata[0][2]=atan2(sqrt(1-(((a[0][0]*a[0][0]+a[0][1]*a[0][1]-l1*l1-l2*l2)/(2*l1*l2))*((a[0][0]*a[0][0]+a[0][1]*a[0][1]-l1*l1-l2*l2)/(2*l1*l2)))),(a[0][0]*a[0][0]+a[0][1]*a[0][1]-l1*l1-l2*l2)/(2*l1*l2));
	theata[0][3]=atan2(-sqrt(1-(((a[0][0]*a[0][0]+a[0][1]*a[0][1]-l1*l1-l2*l2)/(2*l1*l2))*((a[0][0]*a[0][0]+a[0][1]*a[0][1]-l1*l1-l2*l2)/(2*l1*l2)))),(a[0][0]*a[0][0]+a[0][1]*a[0][1]-l1*l1-l2*l2)/(2*l1*l2));
	if(abs((l1+l2*cos(theata[0][2]))*a[0][0]+l2*sin(theata[0][2])*a[0][1])<=0.013||abs((l1+l2*cos(theata[0][3]))*a[0][0]+l2*sin(theata[0][3])*a[0][1])<=0.013)
	{
		if(q==0)
		{
		theata[0][0]=90*PI/180;
		theata[0][1]=90*PI/180;
		}
		else
		{
		theata[0][0]=-90*PI/180;
		theata[0][1]=-90*PI/180;
		}
	}
	else
	{
	theata[0][0]=atan2(((l1+l2*cos(theata[0][2]))*a[0][1]-l2*sin(theata[0][2])*a[0][0])/(a[0][0]*a[0][0]+a[0][1]*a[0][1]),((l1+l2*cos(theata[0][2]))*a[0][0]+l2*sin(theata[0][2])*a[0][1])/(a[0][0]*a[0][0]+a[0][1]*a[0][1]));
	theata[0][1]=atan2(((l1+l2*cos(theata[0][3]))*a[0][1]-l2*sin(theata[0][3])*a[0][0])/(a[0][0]*a[0][0]+a[0][1]*a[0][1]),((l1+l2*cos(theata[0][3]))*a[0][0]+l2*sin(theata[0][3])*a[0][1])/(a[0][0]*a[0][0]+a[0][1]*a[0][1]));
	}
	theata[0][4]=(x[0][2])-theata[0][2]-theata[0][0];
	if(theata[0][4]/PI>1)
		theata[0][4]=theata[0][4]-2*PI;
	else if(theata[0][4]/PI<-1)
		theata[0][4]=theata[0][4]+2*PI;
	else
		theata[0][4]=theata[0][4];
	theata[0][5]=(x[0][2])-theata[0][3]-theata[0][1];
	if(theata[0][5]/PI>1)
		theata[0][5]=theata[0][5]-2*PI;
	else if(theata[0][5]/PI<-1)
		theata[0][5]=theata[0][5]+2*PI;
	else
		theata[0][5]=theata[0][5];
	int t_1,t_2;
	if(abs(theata[0][0])<=170*3.1415926/180&&abs(theata[0][2])<=170*3.1415926/180&&abs(theata[0][4])<=170*3.1415926/180)
		t_1=1;
	else
		t_1=0;
	if(abs(theata[0][1])<=170*3.1415926/180&&abs(theata[0][3])<=170*3.1415926/180&&abs(theata[0][5])<=170*3.1415926/180)
		t_2=1;
	else
		t_2=0;
	if(t_1==1&&t_2==0)
	{
		theata[0][1]=theata[0][0];
		theata[0][3]=theata[0][2];
		theata[0][5]=theata[0][4];
		l[0][0]=1;
		cout<<"there is only one available solution"<<endl;
	}
	else if(t_1==0&&t_2==1)
	{
		theata[0][0]=theata[0][1];
		theata[0][2]=theata[0][3];
		theata[0][4]=theata[0][5];
		l[0][0]=1;
		cout<<"there is only one available solution"<<endl;
	}
	else if(t_1==1&&t_2==1)
		l[0][0]=1;
	else
		l[0][0]=0;
}
void Path(double alpha_0[1][3],double theata[1][6],double beta[1][3],double N[1][3],double F[1][3])
{
	int i;
	double alpha[1][3];
	alpha[0][0]=alpha_0[0][0]*PI/180;
	alpha[0][1]=alpha_0[0][1]*PI/180;
	alpha[0][2]=alpha_0[0][2]*PI/180;
	beta[0][0]=0;
	beta[0][1]=0;
	beta[0][2]=0;
	int m_0=0,n_0=0;
	if(alpha[0][0]==theata[0][0]&&alpha[0][1]==theata[0][2]&&alpha[0][2]==theata[0][4])
	{
		beta[0][0]=0;
		beta[0][1]=0;
		beta[0][2]=0;
		m_0=1;
	}
	
	else if(alpha[0][0]==theata[0][1]&&alpha[0][1]==theata[0][3]&&alpha[0][2]==theata[0][5])
	{
		beta[0][0]=0;
		beta[0][1]=0;
		beta[0][2]=0;
		n_0=1;
	}
	else
	{
		double z_1[3][2]=
		{
		{l1*cos(alpha[0][0]),l1*sin(alpha[0][0])},
		{l1*cos(alpha[0][0])+l2*cos((alpha[0][0])+(alpha[0][1])),l1*sin(alpha[0][0])+l2*sin((alpha[0][0])+(alpha[0][1]))},
		{l1*cos(alpha[0][0])+l2*cos((alpha[0][0])+(alpha[0][1]))+l3*cos((alpha[0][0])+(alpha[0][1])+(alpha[0][2])),l1*sin(alpha[0][0])+l2*sin((alpha[0][0])+(alpha[0][1]))+l3*sin((alpha[0][0])+(alpha[0][1])+(alpha[0][2]))}
		};

		double z_2[6][2]=
		{
			{l1*cos(theata[0][0]),l1*sin(theata[0][0])},
			{l1*cos(theata[0][0])+l2*cos((theata[0][0])+(theata[0][2])),l1*sin(theata[0][0])+l2*sin((theata[0][0])+(theata[0][2]))},
			{l1*cos(theata[0][0])+l2*cos((theata[0][0])+(theata[0][2]))+l3*cos((theata[0][0])+(theata[0][2])+(theata[0][4])),l1*sin(theata[0][0])+l2*sin((theata[0][0])+(theata[0][2]))+l3*sin((theata[0][0])+(theata[0][2])+(theata[0][4]))},
			{l1*cos(theata[0][1]),l1*sin(theata[0][1])},
			{l1*cos(theata[0][1])+l2*cos((theata[0][1])+(theata[0][3])),l1*sin(theata[0][1])+l2*sin((theata[0][1])+(theata[0][3]))},
			{l1*cos(theata[0][1])+l2*cos((theata[0][1])+(theata[0][3]))+l3*cos((theata[0][1])+(theata[0][3])+(theata[0][5])),l1*sin(theata[0][1])+l2*sin((theata[0][1])+(theata[0][3]))+l3*sin((theata[0][1])+(theata[0][3])+(theata[0][5]))}
		};
		double a1,a2,b1,b2,c1,c2,d,f;
		a1=sqrt((z_1[0][0]-z_2[0][0])*(z_1[0][0]-z_2[0][0])+(z_1[0][1]-z_2[0][1])*(z_1[0][1]-z_2[0][1]));
		b1=sqrt((z_1[1][0]-z_2[1][0])*(z_1[1][0]-z_2[1][0])+(z_1[1][1]-z_2[1][1])*(z_1[1][1]-z_2[1][1]));
		c1=sqrt((z_1[2][0]-z_2[2][0])*(z_1[2][0]-z_2[2][0])+(z_1[2][1]-z_2[2][1])*(z_1[2][1]-z_2[2][1]));
		a2=sqrt((z_1[0][0]-z_2[3][0])*(z_1[0][0]-z_2[3][0])+(z_1[0][1]-z_2[3][1])*(z_1[0][1]-z_2[3][1]));
		b2=sqrt((z_1[1][0]-z_2[4][0])*(z_1[1][0]-z_2[4][0])+(z_1[1][1]-z_2[4][1])*(z_1[1][1]-z_2[4][1]));
		c2=sqrt((z_1[2][0]-z_2[5][0])*(z_1[2][0]-z_2[5][0])+(z_1[2][1]-z_2[5][1])*(z_1[2][1]-z_2[5][1]));
		d=a1+b1+c1;
		f=a2+b2+c2;
		if(d<=f)
		{
			beta[0][0]=theata[0][0]-alpha[0][0];
			beta[0][1]=theata[0][2]-alpha[0][1];
		    beta[0][2]=theata[0][4]-alpha[0][2];
			m_0=1;

		}
		else
		{
			beta[0][0]=theata[0][1]-alpha[0][0];
			beta[0][1]=theata[0][3]-alpha[0][1];
		    beta[0][2]=theata[0][5]-alpha[0][2];
			n_0=1;
		}
	 }
	for(i=0;i<3;i++)
	{
	if(beta[0][i]/PI>1)
		beta[0][i]=beta[0][i]-2*PI;
	else if(beta[0][i]/PI<-1)
		beta[0][i]=beta[0][i]+2*PI;
	else
		beta[0][i]=beta[0][i];
	}
	if(m_0==1&&n_0==0)
		{
			N[0][0]=theata[0][0];
			N[0][1]=theata[0][2];
			N[0][2]=theata[0][4];
			F[0][0]=theata[0][1];
			F[0][1]=theata[0][3];
			F[0][2]=theata[0][5];
			
		}
	else if(m_0==0&&n_0==1)
		{
			N[0][0]=theata[0][1];
			N[0][1]=theata[0][3];
			N[0][2]=theata[0][5];
			F[0][0]=theata[0][0];
			F[0][1]=theata[0][2];
			F[0][2]=theata[0][4];
		}
	else
		{
			cout<<"the reuslt is wrong";
		}

}
void solve(double a_1[1][3],double a_2[1][3],double a_3[1][3],double h[1][3],double N[1][3],double B[1][3])
{
	double a_4[1][3];
	double b_1[3][3]=
	{
		{cos(a_1[0][2]*3.1415926/180),-sin(a_1[0][2]*3.1415926/180),a_1[0][0]},
		{sin(a_1[0][2]*3.1415926/180),cos(a_1[0][2]*3.1415926/180),a_1[0][1]},
		{0,0,1}
	};
	double b_2[3][3]=
	{
		{cos(a_2[0][2]*3.1415926/180),-sin(a_2[0][2]*3.1415926/180),a_2[0][0]},
		{sin(a_2[0][2]*3.1415926/180),cos(a_2[0][2]*3.1415926/180),a_2[0][1]},
		{0,0,1}
	};
	double b_3[3][3]=
	{
		{cos(a_3[0][2]*3.1415926/180),-sin(a_3[0][2]*3.1415926/180),a_3[0][0]},
		{sin(a_3[0][2]*3.1415926/180),cos(a_3[0][2]*3.1415926/180),a_3[0][1]},
		{0,0,1}
	};
	
	double c_1[3][3],d_1[3][3],d_2[3][3];
	TINVERT(b_1,c_1);
	TMULT(b_2,b_3,d_1);
	TMULT(d_1,c_1,d_2);
	a_4[0][0]=d_2[0][2];
	a_4[0][1]=d_2[1][2];
	int q=0;
	double r_0,r_1;
	r_0=d_2[0][0];
	r_1=d_2[1][0];
	if(abs(r_0)<=0.0001)
	{
		if(r_1>=0)
			a_4[0][2]=90*PI/180;
		else
		{
			a_4[0][2]=-90*PI/180;
			q=1;
		}
		
	}
	else
	{
		a_4[0][2]=atan2(d_2[1][0],d_2[0][0]); 

	}
	double theata[1][6],beta[1][3],F[1][3];
	int Sol,l[1][1];
	reverseMatri(a_4,theata,l,q);
	Sol=l[0][0];
	if(Sol!=0)
	{
		Path(h,theata,beta,N,F);
	/*
		cout<<"rotation angle :"<<endl;
		for (int i_0 = 0; i_0 < 1; i_0++)
			{
				for (int j_0 = 0; j_0 < 3; j_0++)
				{
					cout <<std::left<<setw(10)<<setiosflags(ios::fixed)<<setprecision(3)<< beta[i_0][j_0]*180/PI<<"       ";
				}
				cout<<"              beta"<<endl;
			}
		cout<<"near solution :"<<endl;
		for (int i_0 = 0; i_0 < 1; i_0++)
			{
				for (int j_0 = 0; j_0 < 3; j_0++)
				{
					cout <<"near solution  "<<std::left<<setw(10)<<setiosflags(ios::fixed)<<setprecision(3)<< N[i_0][j_0]*180/PI<<"       ";
				}
				cout<<endl;
			}
		cout<<"far solution :"<<endl;
		for (int i_0 = 0; i_0 < 1; i_0++)
			{
				for (int j_0 = 0; j_0 < 3; j_0++)
				{
					cout <<"far solution  "<<std::left<<setw(10)<<setiosflags(ios::fixed)<<setprecision(3)<< F[i_0][j_0]*180/3.1415926535898<<"       ";
				}
				cout<<endl;
			}
			
	*/
	
		h[0][0]=N[0][0];
		h[0][1]=N[0][1];
		h[0][2]=N[0][1];
                
                B[0][0]=beta[0][0];
		B[0][1]=beta[0][1];
		B[0][2]=beta[0][1];
		
		
	
	}
	else
		cout<<"the solution dosen't exist"<<endl;
}
