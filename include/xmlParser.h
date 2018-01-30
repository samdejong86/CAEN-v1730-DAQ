#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

#ifndef XmlParser_h
#define XmlParser_h 1

//a class which reads an XML file and holds the information
class XmlParser{

public:
  static std::string startTag;
  static std::string endTag;
  static std::string xmlStartTag;
  static std::string xmlEndTag;


  XmlParser(){}

  //constructor which reads a file
  XmlParser(std::string filename, bool verbose){

    if(verbose) cout<<"Parsing "<<filename<<endl;

    std::ifstream in(filename.c_str());
    
    char str[600];
    
    std::string activeTag = "";
    std::string text;
    
    
    while(in) {
      in.getline(str, 256);    
      std::string st = str;    
      st = this->removeSpaces(st); 
 		
      if((st.compare(xmlStartTag))==0){
      }
      else if((st.compare(xmlEndTag))==0){
      }else if ((st.compare(this->endTag))==0) {
	
      }
      else if (this->isXMLStartTag(st)) {
	activeTag = st;
      }
      else if (this->isXMLEndTag(st)) {
	text = this->removeSpaces(text);
	this->setXMLField(activeTag, text);
	text = "";
      }
      else
	text = text+ "\n" + st;
    }
    in.close();
  }

  //produces a vector of XmlParser objects
  static std::vector<XmlParser> getVector(std::string filename, bool verbose){

    if(verbose) cout<<"Parsing "<<filename<<endl;

    std::vector<XmlParser> Params;

    ifstream in(filename.c_str());
    if(!in) return Params;
    
    char str[600];
    
    XmlParser aParams;
    
    XmlParser * currentParams = 0;
    
    string activeTag = "";
    string text;
        
    while(in) {

      in.getline(str, 256);    
      string st = str;    
      st = aParams.removeSpaces(st);  		
      if((st.compare(xmlStartTag))==0){
      }
      else if((st.compare(xmlEndTag))==0){
      }
      else if ((st.compare(aParams.startTag))==0) {
	currentParams = new XmlParser();
      }
      else if ((st.compare(aParams.endTag))==0) {
	if(currentParams!=0){
	  Params.push_back(*currentParams);
	}
      }
      else if (currentParams->isXMLStartTag(st)) {
	activeTag = st;
      }
      else if (currentParams->isXMLEndTag(st)) {
	if(currentParams!=0){
	  text = aParams.removeSpaces(text);
	  currentParams->setXMLField(activeTag, text);
	  text = "";
	}
      }else if ((st.find("</"))!= std::string::npos){
      text="";
      }else
	text = text+ "\n" + st;
    }
    in.close();
    
    return Params;


  }

  //utility method
  std::string removeSpaces(std::string input)
  {
    int length = input.length();
    for (int i = length-1; i >= 0; --i) { //for (int i = 0; i < length; i++) {
      if(input[i] == ' '||input[i] == '\t'||input[i] == '\n')
	input.erase(i, 1);
    }
    return input;
  }
  
  //return the value of a tag as a double
  double getValue(std::string tag){ 
    for(int i=0; i<(int)tags.size(); i++){
      if(tags[i].compare(tag)==0) return atof(vals[i].c_str());       
    }
    return 0;
  }
  
  //return the value of a tag as a string
  std::string getStringValue(std::string tag){
    for(int i=0; i<(int)tags.size(); i++){
      if(tags[i].compare(tag)==0) return vals[i];       
    }
    return "";
  }

  std::vector<std::string> getTags(){return tags;};
  std::vector<std::string> getValues(){return vals;}
  

  //is aTagstring an xml start tag?
  static bool isXMLStartTag(std::string aTagstring){
    std::string input = aTagstring;
    if(input.length()==0) return false;
    
    char last = input.at(input.length()-1);
    char first = input.at(0);
    
    if(first=='<'&&last=='>'&&input.find("</") == std::string::npos){
      return true;
    }
    return false;

  }

  //is aTagstring an xml end tag?
  static bool isXMLEndTag(std::string aTagstring){
    std::string input = aTagstring;
    if(input.length()==0) return false;
    
    char last = input.at(input.length()-1);
    char first = input.at(0);
    
    if(first=='<'&&last=='>'&&input.find("</") != std::string::npos){
      return true;
    }
    return false;
    
  }
  
  //add text to the xmlField
  void setXMLField(std::string xmlField, std::string text) {
    if(xmlField.compare(startTag)==0||xmlField.compare(xmlStartTag)==0) return;
    if(xmlField.find("</") != std::string::npos) return;
    
    std::string input = xmlField;
    std::string datastring = text;
    input.erase(0,1);
    input.erase(input.length()-1,1);
    
    bool found=false;
    for(int i=0; i<(int)tags.size(); i++){
      if(tags[i].compare(input)==0){
	found=true;
	vals[i] = text;
      }
    }

    if(!found){
      tags.push_back(input);
      vals.push_back(text);
    }
    
  }
  
  void addValue(std::string tag, std::string val){
    tags.push_back(tag);
    vals.push_back(val);
  }
  


  bool fieldExists(std::string xmlField){
    bool exist=false;
    for(int i=0; i<(int)tags.size(); i++){
      if(tags[i]==xmlField) exist=true;
    }
    return exist;
  }

  //print the tags and their values
  void print(){
    for(int i=0; i<(int)tags.size(); i++) std::cout<<tags[i]<<"\t"<<vals[i]<<std::endl;
  }

  void writeXml(std::string filename){

    std::ofstream outfile;
    outfile.open(filename.c_str(), std::ofstream::out);
    

    outfile<<xmlStartTag<<endl;
    outfile<<"  "<<startTag<<endl;
    for(int i=0; i<(int)tags.size(); i++){
      outfile<<"    <"<<tags[i]<<">"<<endl;
      outfile<<"      "<<vals[i]<<endl;    
      outfile<<"    </"<<tags[i]<<">"<<endl;
    }
    outfile<<"  "<<endTag<<endl;
    outfile<<xmlEndTag<<endl;
  }


 
 
 private:
  std::vector<std::string> tags;
  std::vector<std::string> vals;

 



};







#endif
