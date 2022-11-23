#include "http_server.hh"
#include <bits/stdc++.h>

#include <vector>

#include <sys/stat.h>

#include <fstream>
#include <sstream>
using namespace std;

vector<string> split(const string &s, char delim)
{
  vector<string> elems;

  stringstream ss(s);
  string item;

  while (getline(ss, item, delim))
  {
    if (!item.empty())
      elems.push_back(item);
  }

  return elems;
}

// GET /index.html HTTP/1.1
HTTP_Request::HTTP_Request(string request)
{
  vector<string> lines = split(request, '\n');
  vector<string> first_line = split(lines[0], ' ');

  this->HTTP_version = "1.0"; // We'll be using 1.0 irrespective of the request

  /*
   TODO : extract the request method and URL from first_line here
  */
  this->method = first_line[0];
  this->url = first_line[1];

  if (this->method != "GET")
  {
    cerr << "Method '" << this->method << "' not supported" << endl;
    exit(1);
  }
}

HTTP_Response *handle_request(string req)
{
  HTTP_Request *request = new HTTP_Request(req);

  HTTP_Response *response = new HTTP_Response();

  string url = string("html_files") + request->url;

  response->HTTP_version = "1.0";

  struct stat sb;
  if (stat(url.c_str(), &sb) == 0) // requested path exists
  {
    response->status_code = "200";
    response->status_text = "OK";
    response->content_type = "text/html";
    string body;

    if (S_ISDIR(sb.st_mode))
    {
      /*
      In this case, requested path is a directory.
      TODO : find the index.html file in that directory (modify the url
      accordingly)
      */
      if (url[url.size() - 1] != '/')
        url += '/';
      url += "index.html";
    }
    const char *tmpurl = url.c_str();

    /*
    TODO : open the file and read its contents
    */

    FILE *fileptr = fopen(tmpurl, "r");
    // while (!feof(fileptr)) {
    //     char ch = fgetc(fileptr);
    //     body+=ch;
    // }

    struct stat si;
    stat(url.c_str(), &si);
    char buffer[si.st_size + 1];
    int x = fread(buffer, si.st_size, 1, fileptr);
    fclose(fileptr);
    /*
    TODO : set the remaining fields of response appropriately
    */
    response->content_length = to_string(si.st_size);
    response->body = buffer;
  }
  else
  {
    response->status_code = "404";

    /*
    TODO : set the remaining fields of response appropriately
    */
    response->content_type = "text/html";
    response->status_text = "Not Found";
    response->body = "";
    response->content_length = "0";
  }

  delete request;

  return response;
}

string HTTP_Response::get_string()
{
  /*
  TODO : implement this function
  */
  return "HTTP/" +
         this->HTTP_version + " " +
         this->status_code + " " +
         this->status_text + "\nContent-Length: " +
         this->content_length + "\nContent-type: " +
         this->content_type + "\n\n" +
         this->body + "\n";
}