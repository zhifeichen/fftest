#ifndef GET_REST_H
#define GET_REST_H

#include <string>
#include "NetCommon.h"
class sky_rest
{
private:
	static bool parse_url(const std::string url, std::string& host, short& port, std::string& path);
	static int connect_to_server(const std::string host, const short port, long connect_time_out);
	static int send_request(int s, const std::string path, const std::string token, const std::string host, const short port);
	static int send_post_request(int s, const std::string path, const std::string data, const std::string token, const std::string host, const short port);
	static int get_response(int s, std::string& result);
	static int get_response_body(const std::string response, std::string& body);
	static int check_receiv_complete(const char* buf);
public:
// get_rest: use GET method; post_rest: use POST method
// url: in
// data: in,  post data
// body: out, response body
// connect_time_out: in, connect time out, second
// token: in, user token
// return: 0 success, else failure
	static int get_rest(const std::string url, std::string& body, long connect_time_out = 1, const std::string token = "");
	static int post_rest(const std::string url, const std::string data, std::string& body, long connect_time_out = 1, const std::string token = "");
};
#endif //#ifndef GET_REST_H