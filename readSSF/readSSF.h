
#ifndef READSSF_H
#define READSSF_H



#include <iostream>
#include <fstream>
#include <strstream>
#include <sstream>
#include <list>


#include <vector>
#include <map>
#include "vector3.h"

using namespace std;
struct RCurvePoints
{
	vector<myVector3> cvs;
};

class RCurve
{

private:
	map<int,RCurvePoints>	_frameCurves;

	int		_id;
	bool	_closed;
	bool	_visible;
	int		_age;	//exit till key frame

	myVector3 _center;



public:
	

	bool isClosed(){return _closed;}
	bool isVisible(){return _visible;}
	int  getAge(){return _age;}
	

	void setClosed(bool flag){this->_closed = flag;}
	void setVisible(bool flag){this->_visible = flag;}
	void setAge(int age){this->_age = age ;}
	void setCenterX(float x){this->_center.x = x;}
	void setCenterY(float y){this->_center.y = y;}
	void setCenterZ(float z =0){this->_center.z = z;}
	void insert(int fkey,RCurvePoints points ){
		_frameCurves.insert(std::pair<int,RCurvePoints>(fkey,points));
	}
	
	map<int,RCurvePoints> getframeCache(){return _frameCurves;}
	myVector3 getCenter(){return this->_center;}

};


class RImportCurves
{

public:
	RImportCurves(){};

	///////////inline METHODS////////////////////////////
	inline std::string	getFileName(){return _filename;}
	inline RCurve getCurve(){return rotoCurve;}
	
	//create mesh using 
	//triangulations
	//vector<Vector3> create_tri_Mesh();

	////////METHODS////////////////////
	void readStream(std::string fileName)
	{
		std::ifstream inputStream(fileName.data(),std::ios::in);

		//open file for reading ios::in
		std::string line;
		if(inputStream.fail()){
			std::cout<<"unable to open file "<<fileName<<std::endl;
			return ;
		}

		while(!inputStream.eof())
		{
			getline(inputStream,line);
			//read the line
			processLine(line);
		}
		inputStream.close();
	}


	void writeStream(std::string outfile);
	//void createDeluany();

	~RImportCurves(){};

private:
	std::string		   _filename;
	enum {ssf = 0};
	
protected:

	
	RCurve			rotoCurve;
	RCurvePoints	controlpoints;
	int				key;


protected:
	void processLine(std::string line)
	{
		int num_key_times	= 0; 
		int closed			= 0;
		int visible			= 0;
		
		
		
		//initialize to zero
		myVector3 center(myVector3(0.0f,0.0f,0.0f));

		//store the values in a array 
		vector<string> parts = split(line,' ');

		

		if(parts.size() > 0)
		{
			if(parts[0].compare("closed") == 0){
				closed =  atoi(parts[1].data());
				(closed == 0 )?rotoCurve.setClosed(false):rotoCurve.setClosed(true);

			}
			else if(parts[0].compare("visible")==0){
				visible = atoi(parts[1].data());
				(visible == 0)?rotoCurve.setVisible(false):rotoCurve.setVisible(true);
			}
			else if(parts[0].compare("num_key_times")== 0){
				num_key_times  = atoi(parts[1].data());
				rotoCurve.setAge(num_key_times);

			}
			else if(parts[0].compare("center_x")==0){
				center.x = atof(parts[1].data()); 
				rotoCurve.setCenterX(center.x);
				
			}
			else if(parts[0].compare("center_y")== 0)
			{
				center.y = atof(parts[1].data());
				rotoCurve.setCenterY(center.y);
			}
			else if(parts[0].compare("key_time")==0)
				key = atoi(parts[1].data());
			else if(parts[0].compare("vertex_data")==0)
			{
				int len = parts.size();
				std::cout<<"inside process line parts len"<<parts.size()<<std::endl;
				for(int i=1;i<(len-12);i+=12){
					myVector3 cv(atof(parts[i].data()),atof(parts[i+1].data()),0.0f);
					myVector3 cvLH(atof(parts[i+2].data()),atof(parts[i+3].data()),0.0f);
					myVector3 cvRH(atof(parts[i+4].data()),atof(parts[i+5].data()),0.0f);

					controlpoints.cvs.push_back(cv);
					controlpoints.cvs.push_back(cvLH);
					controlpoints.cvs.push_back(cvRH);

				}
				rotoCurve.insert(key,controlpoints);
				key = -1;
				controlpoints.cvs.clear();
			}
		}
	}

	vector<string> split(const string& strValue, char separator)
	{
		vector<string> vecstrResult;
		int startpos=0;
		int endpos=0;

		endpos = strValue.find_first_of(separator, startpos);
		while (endpos != -1)
		{       
			vecstrResult.push_back(strValue.substr(startpos, endpos-startpos)); // add to vector
			startpos = endpos+1; //jump past sep
			endpos = strValue.find_first_of(separator, startpos); // find next
			if(endpos == -1)
			{
				//lastone, so no 2nd param required to go to end of string
				vecstrResult.push_back(strValue.substr(startpos));
			}
		}

		return vecstrResult;
	}




};

#endif