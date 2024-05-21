#include <iostream>
#include <filesystem>
#include <string>
#include <Eigen/Eigen>
#include "opencv2/opencv.hpp"
#include<fstream>

using namespace std;
using namespace cv;

std::vector<string> getxmlfiles(char *path)
{
	std::vector<string> xmlfiles;
	for (const auto& entry :std::filesystem::directory_iterator(path))
	{
		if (entry.path().extension() ==".xml") //,筛选出扩展名为.xml的文件
		{
			//std::cout,<<,entry.path().filename().string(),<<,std::endl;,,//,输出文件名
			xmlfiles.push_back(entry.path().filename().string());
		}
	}

	return xmlfiles;
}

static cv::Scalar
hsv2rgb(float fH, float fS, float fV)
{
	const float fC = fV * fS; // Chroma
	const float fHPrime = fmod(fH / 60.0, 6);
	const float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
	const float fM = fV - fC;

	float fR, fG, fB;

	if (0 <= fHPrime && fHPrime < 1) {
		fR = fC;
		fG = fX;
		fB = 0;
	} else if (1 <= fHPrime && fHPrime < 2) {
		fR = fX;
		fG = fC;
		fB = 0;
	} else if (2 <= fHPrime && fHPrime < 3) {
		fR = 0;
		fG = fC;
		fB = fX;
	} else if (3 <= fHPrime && fHPrime < 4) {
		fR = 0;
		fG = fX;
		fB = fC;
	} else if (4 <= fHPrime && fHPrime < 5) {
		fR = fX;
		fG = 0;
		fB = fC;
	} else if (5 <= fHPrime && fHPrime < 6) {
		fR = fC;
		fG = 0;
		fB = fX;
	} else {
		fR = 0;
		fG = 0;
		fB = 0;
	}

	fR += fM;
	fG += fM;
	fB += fM;
	return {fR * 255.0f, fG * 255.0f, fB * 255.0f};
}



int main1()
{
#define SAVE

	string path="/home/lae/projects/Hand_pros/keypoint-estimator/datasets/gestures";
	string persons[]={"cwh","fzy","gw","qzj","wwl","zcq","zh","zwb","zyh"};
    //string persons[]={"gw","qzj","wwl","zcq","zh","zwb","zyh"};
	for(auto per : persons)
	{
#ifdef SAVE
		//save,to,csv
		string csvPath=path+"/"+per+".csv";
		std::ofstream ofcsv(csvPath);
#endif
		for (int i=0;i<23;++i)
		{
			std::ofstream ofidxcsv;
			char inputpath[200];
			sprintf(inputpath,"%s/%s/%02d", path.c_str(),per.c_str(),i);
			if (std::filesystem::exists(inputpath) && std::filesystem::is_directory(inputpath))
			{
				char idxcsvPath[100];
				sprintf(idxcsvPath,"%s/%02d.csv",path.c_str(),i);

				if(std::filesystem::exists(idxcsvPath))
					ofidxcsv.open(idxcsvPath,ios::app);
				else
					ofidxcsv.open(idxcsvPath);
			}
			else
			{
				continue;
			}


			std::vector<string> xmlfiles=getxmlfiles(inputpath);
			printf("find,xmlfile,%d\n",xmlfiles.size());
			for(auto xmlf: xmlfiles)
			{
				//read,joint
				sprintf(inputpath,"%s/%s/%02d/%s", path.c_str(),per.c_str(),i,xmlf.c_str());
				FileStorage fs(inputpath, FileStorage::READ);
				std::vector<cv::Point2f> joint2d;
				std::vector<cv::Point3f> joint3d;
				fs["Joint2D"]>>joint2d;
				fs["Joint3D"]>>joint3d;

				//read,image
				std::string file_name = std::filesystem::path(xmlf).stem().string();
				sprintf(inputpath,"%s/%s/%02d/%s.0.png", path.c_str(),per.c_str(),i,file_name.c_str());
				std::cout<<inputpath<<std::endl;
				string image_name(inputpath);

				cv::Mat im=imread(image_name);
				if(im.empty())
					continue;
#ifdef SAVE
				{
					sprintf(inputpath,"|%s/%02d/%s.0.png| ",per.c_str(),i,file_name.c_str());
					ofcsv<<inputpath;
					ofidxcsv<<inputpath;
				}
#endif

				std::vector<cv::Point2f> joint2d_correct;
				std::vector<cv::Point3f> joint2d_valid;
				{
					joint2d_correct.push_back(joint2d[3]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(2*joint2d[2]-joint2d[1]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(joint2d[2]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(joint2d[1]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(joint2d[0]);joint2d_valid.push_back(cv::Point3f(1,1,1));

					joint2d_correct.push_back(joint2d[7]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(joint2d[6]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(joint2d[5]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(joint2d[4]);joint2d_valid.push_back(cv::Point3f(1,1,1));

					joint2d_correct.push_back(joint2d[11]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(joint2d[10]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(joint2d[9]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(joint2d[8]);joint2d_valid.push_back(cv::Point3f(1,1,1));

					joint2d_correct.push_back(joint2d[15]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(joint2d[14]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(joint2d[13]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(joint2d[12]);joint2d_valid.push_back(cv::Point3f(1,1,1));

					joint2d_correct.push_back(joint2d[19]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(joint2d[18]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(joint2d[17]);joint2d_valid.push_back(cv::Point3f(1,1,1));
					joint2d_correct.push_back(joint2d[16]);joint2d_valid.push_back(cv::Point3f(1,1,1));
				}

				std::vector<cv::Point3f> joint3d_correct;
				{
					//joint3D
					joint3d_correct.push_back(joint3d[3]*0.001);
					joint3d_correct.push_back(2*joint3d[2]*0.001-joint3d[1]*0.001);
					joint3d_correct.push_back(joint3d[2]*0.001);
					joint3d_correct.push_back(joint3d[1]*0.001);
					joint3d_correct.push_back(joint3d[0]*0.001);

					joint3d_correct.push_back(joint3d[7]*0.001);
					joint3d_correct.push_back(joint3d[6]*0.001);
					joint3d_correct.push_back(joint3d[5]*0.001);
					joint3d_correct.push_back(joint3d[4]*0.001);

					joint3d_correct.push_back(joint3d[11]*0.001);
					joint3d_correct.push_back(joint3d[10]*0.001);
					joint3d_correct.push_back(joint3d[9]*0.001);
					joint3d_correct.push_back(joint3d[8]*0.001);

					joint3d_correct.push_back(joint3d[15]*0.001);
					joint3d_correct.push_back(joint3d[14]*0.001);
					joint3d_correct.push_back(joint3d[13]*0.001);
					joint3d_correct.push_back(joint3d[12]*0.001);

					joint3d_correct.push_back(joint3d[19]*0.001);
					joint3d_correct.push_back(joint3d[18]*0.001);
					joint3d_correct.push_back(joint3d[17]*0.001);
					joint3d_correct.push_back(joint3d[16]*0.001);

				}

				for(int idx=0;idx<joint2d_correct.size();++idx)
				{
					auto &joint=joint2d_correct[idx];
					cv::Point center((joint.x+1.)*640,joint.y*480);
					cv::circle(im,center,1,Scalar(0,0,255),2);
					cv::putText(im,std::to_string(idx),center,FONT_HERSHEY_SIMPLEX,
								0.5,Scalar(255,0,0));
#ifdef SAVE
					float hand_size=norm(joint3d_correct[0]-joint3d_correct[9]);
					float midpxm_depth=norm(joint3d_correct[9]);
					float idx_depth=norm(joint3d_correct[idx]);
					ofcsv<<center.x<<" "<<center.y<<" "<<(idx_depth-midpxm_depth)/(hand_size)<<" ";
					//相对于9号关节点的深度比例
					ofidxcsv<<center.x<<" "<<center.y<<" "<<(idx_depth-midpxm_depth)/(hand_size)<<" ";
#endif
				}
#ifdef SAVE
				ofcsv<<"0.0 0.0 0.0 ";
				ofidxcsv<<"0.0 0.0 0.0 ";
#endif

				for (int j = 0; j < joint2d_valid.size(); ++j)
				{
					auto &joint_valid=joint2d_valid[j];
#ifdef SAVE
					ofcsv<<joint_valid.x<<" "<<joint_valid.y<<" "<<joint_valid.z<<" ";
					ofidxcsv<<joint_valid.x<<" "<<joint_valid.y<<" "<<joint_valid.z<<" ";
#endif
				}
#ifdef SAVE
				ofcsv<<"0.0 0.0 0.0 True\n";
				ofidxcsv<<"0.0 0.0 0.0 True\n";
#endif

				//imshow("test",im);
				char c=waitKey(1);

				if(c==32)
					waitKey(0);
			}

#ifdef SAVE
			ofidxcsv.close();
#endif
		}
#ifdef SAVE
		ofcsv.close();
#endif

	}



	return 0;
}

int main2()
{

	//return main1();

	string path="/media/lae/data/dataset/handdata_collection2/";

	string namelist[]={"zl_L","zl_R","zq_L","zq_R","mhk_L","mhk_R","cz_L","cz_R","hg_R"};
	for(auto name:namelist)
	{
		string lr=name.substr(name.length()-1,1);
		bool isright=false;
		if(lr=="R")
			isright=true;
		else if(lr=="L")
			isright=false;

		char valPath[100];
		sprintf(valPath,"%s%s/val.csv",path.c_str(),name.c_str());
		std::ofstream ofvalcsv(valPath);

		char allPath[100];
		sprintf(allPath,"%s%s/all.csv",path.c_str(),name.c_str());
		std::ofstream ofallcsv(allPath);

		int id=0;
		while(1)
		{
			char imgs_path[100];
			sprintf(imgs_path,"%s%s/%02d",path.c_str(),name.c_str(),id);
			if (std::filesystem::exists(imgs_path) &&
			    std::filesystem::is_directory(imgs_path))
			{
				char csvPath[100];
				sprintf(csvPath,"%s%s/%02d.csv",path.c_str(),name.c_str(),id);
				std::ofstream ofcsv(csvPath);

				int idx=0;
				while(1)
				{
					string path_img=string(imgs_path)+"/"+std::to_string(idx)+".png";
					string path_pts=string(imgs_path)+"/"+std::to_string(idx)+".txt";
					cv::Mat im=imread(path_img,0);
					if(im.empty())
						break;

					std::ofstream *ofs=NULL;
					if(idx%5==0)
						ofs=&ofvalcsv;
					else
						ofs=&ofcsv;

					char inputdata[100];
					sprintf(inputdata,"|%02d/%d.png| ",id,idx);
					*(ofs)<<inputdata;

					if(idx%5!=0)
						ofallcsv<<inputdata;

					cv::Mat show;
					cvtColor(im,show,cv::COLOR_GRAY2BGR);
					FILE *fp=fopen(path_pts.c_str(),"r");
					float x,y;float X,Y,Z;
					std::vector<Point> pts;
					std::vector<Point3f> pts_3d;
					int pt_size=0;
					while(-1!=fscanf(fp,"%f %f, %f %f %f\n",&x,&y,&X,&Y,&Z))
					{
						pts.push_back(Point2f(x,y));
						pts_3d.push_back(Point3f(X,Y,Z));
						//circle(show,Point2f(x,y),1,Scalar(0,0,255),2);
						//*(ofs)<<int(x)<<" "<<int(y)<<" 0.0 ";
						pt_size++;
					}
					fclose(fp);
					//*(ofs)<<"0.0 0.0 0.0 ";
					for (int k = 0; k < pt_size; ++k)
					{
						cv::circle(show, pts[k], 2, hsv2rgb(k/26.0 * 360.0f, 1, 2), 2);
						float hand_size=norm(pts_3d[0]-pts_3d[9]);
						float midpxm_depth=norm(pts_3d[9]);
						float idx_depth=norm(pts_3d[k]);

						*(ofs)<<pts[k].x<<" "<<pts[k].y<<" "<<(idx_depth-midpxm_depth)/hand_size<<" ";

						if(idx%5!=0)
							ofallcsv<<pts[k].x<<" "<<pts[k].y<<" "<<(idx_depth-midpxm_depth)/hand_size<<" ";
					}
					*(ofs)<<"0.0 0.0 0.0 ";
					if(idx%5!=0)
						ofallcsv<<"0.0 0.0 0.0 ";

					for (int k = 0; k < pt_size; ++k)
					{
						*(ofs) << "1 1 1 ";
						if(idx%5!=0)
							ofallcsv<< "1 1 1 ";
					}

					if(!isright)
					{
						*(ofs) << "0.0 0.0 0.0 False\n";
						if(idx%5!=0)
							ofallcsv<<"0.0 0.0 0.0 False\n";
					}
					else
					{
						*(ofs) << "0.0 0.0 0.0 True\n";
						if(idx%5!=0)
							ofallcsv<<"0.0 0.0 0.0 True\n";
					}

					imshow("show",show);
					char c=waitKey(1);
					if(c==32)
						waitKey();

					idx++;
				}

				ofcsv.close();
			}
			else
				break;

			id++;
		}
		ofvalcsv.close();
		ofallcsv.close();
	}



}

int main3()
{
//	char message[42*7*4];
//	FILE*fp=fopen("/media/lae/data/projects/mercury_steamvr_driver/cmake-build-release/src/1000000.txt","rb");
//	fread(message,1,42*7*4,fp);
//	fclose(fp);
//	float *handdata=(float*)message;
//	for (int k = 0; k < 42; ++k)
//	{
//		printf("%f %f %f %f,%f %f %f\n",handdata[k*7],handdata[k*7+1],handdata[k*7+2],handdata[k*7+3]
//				,handdata[k*7+4],handdata[k*7+5],handdata[k*7+6]);
//	}
//
//	return 0;


	float w=0.99999966;
	float x=0.00053106;
	float y=0.00062314;
	float z=-0.00001957;


	Eigen::Quaternionf q1(w,x,y,z);
	Eigen::Quaternionf q2(w,x,-y,-z);
	std::cout<<"Q1=\n"<<q1.toRotationMatrix()<<std::endl;
	std::cout<<"Q2=\n"<<q2.toRotationMatrix()<<std::endl;
	Eigen::Matrix3f rot;
	rot<<1,0,0,
		 0,1,0,
		 0,0,-1;
	Eigen::Quaternionf q_rot(rot);
	std::cout<<"q_rot="<<q_rot.w()<<", "<<q_rot.x()<<", "<<q_rot.y()<<", "<<q_rot.z()<<std::endl;
	std::cout<<"T2=\n"<<rot*q1.toRotationMatrix()*rot.transpose()<<std::endl;
	Eigen::Quaternionf q3(rot*q1.toRotationMatrix()*rot.transpose());
	std::cout<<"q3="<<q3.w()<<", "<<q3.x()<<", "<<q3.y()<<", "<<q3.z()<<std::endl;
	Eigen::Quaternionf q4=q_rot.inverse()*q1*q_rot;
	std::cout<<"q4="<<q4.w()<<", "<<q4.x()<<", "<<q4.y()<<", "<<q4.z()<<std::endl;
	std::cout<<"q4.rot=\n"<<q4.toRotationMatrix()<<std::endl;
}


float fc[4] = { 243.7930338275045, 243.5629397821401, 315.4532059622837, 239.0306795828101 };
const Mat cameraInstric = (cv::Mat_<float>(3, 3) <<
                                                 fc[0], 0, fc[2],
		0, fc[1], fc[3],
		0, 0, 1);
const Mat distort = (cv::Mat_<float>(4, 1) << 0.03367092942210882, -0.01092536373706107, -0.001379234835882732, -0.000709925283960796);

