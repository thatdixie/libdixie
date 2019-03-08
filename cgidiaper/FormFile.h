#ifndef _FORMFILE_H_
#define _FORMFILE_H_

#include <iostream>
#include <string>

using namespace std;

// ============================================================
// Class FormFile
// ============================================================

/* @class FormFile FormFile.h (refactored from cgicc/FormFile.h)
 * @brief Class representing a file submitted via an HTML form.
 *
 * FormFile is an immutable class reprenting a file uploaded via
 * the HTTP file upload mechanism.  If you are going to use file upload
 * in your CGI application, remember to set the ENCTYPE of the form to
 * multipart/form-data.
 * 
 * <form method="post" action="http://change_this_path/cgi-bin/upload.cgi" 
 * enctype="multipart/form-data">
 *
 */
class FormFile
{
    private:
    string 	fName;
    string 	fFilename;
    string 	fDataType;
    string 	fData;
    
    public:
  
    inline string getName() const
    {
	return fName;
    }
  
    inline string getFilename() const
    {
	return fFilename;
    }

    inline string getDataType() const
    {
	return fDataType;
    }
    
    inline string getData() const
    {
	return fData;
    }
  
    inline string::size_type getDataLength() const
    {
	return fData.length();
    }

    FormFile(string, string, string, string);
    FormFile();
};


// ============================================================
// Class MultipartHeader
// ============================================================ 
/* @class MultipartHeader (refactored from cgicc.cpp)
 * @brief Class representing the multipart header of a file 
 * submitted via an HTML form.
 *
 * MultipartHeader is an immutable class reprenting a file uploaded via
 * the HTTP file upload mechanism.  If you are going to use file upload
 * in your CGI application, remember to set the ENCTYPE of the form to
 * multipart/form-data.
 * 
 * <form method="post" action="http://change_this_path/cgi-bin/upload.cgi" 
 * enctype="multipart/form-data">
 *
 */
class MultipartHeader
{
    private:
    string fContentDisposition;
    string fName;
    string fFilename;
    string fContentType;
    
    public:

    inline string getContentDisposition() const
    {
	return fContentDisposition;
    }

    inline string getName() const
    {
	return fName;
    }

    inline string getFilename() const
    {
	return fFilename;
    }

    inline string getContentType() const
    {
	return fContentType;
    }

    MultipartHeader(string, string, string, string);
};


#endif
