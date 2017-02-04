#ifndef client_http_handler_declare
#define client_http_handler_declare


#include <nds.h>
#include <netinet/in.h>
#include <netdb.h>

//struct that spinlocks a current request
typedef struct {
    //dswifi socket @ PORT 8888
    struct sockaddr_in sain_UDP_PORT;			//local nds, any IP takes 127.0.0.1 or current IP @ port 8888 // really used for sending udp packets
	struct sockaddr_in server_addr;		//server: APP UDP companion address	/ unused
    int socket_id__multi_notconnected;	//initial stage required PORT (server -- DS)	/used for ds - server
    
	//listener IP-port
	struct sockaddr_in sain_listener;			//local nds, any IP takes 127.0.0.1 or current IP @ port 8889 (this IP, which is special for each ds console connected)
	int socket_multi_listener;		//multi NDS UDP PORT reserved / used for ds - ds comms
    
	//sender IP-port
	struct sockaddr_in sain_sender;	//ndsmulti IP (second DS ip): UDP multiplayer stores other NDS IP / used from guest mode -> socket_id__multi_connected 
	int socket_multi_sender;		//multi NDS UDP PORT reserved / used for ds - ds comms
    
	
	
	
	
	//host socket entry
    struct hostent myhost;
    
    bool wifi_enabled;
    unsigned char http_buffer[4 * 1024];
    bool sent_wait_for_recv;	//false: ready to send / true: already sent message: recv only then toggles back    

} client_http_handler;


#endif

#ifdef __cplusplus
extern "C"{
#endif

extern char* server_ip;

//HTTP calls:
extern void request_connection(char* str_url,int str_url_size);

//generate a GET request to a desired DNS/IP address
extern bool issue_get_response(char* str_url,int str_url_size);

//generate a POST request where str_params conforms the FORM HTTP 1.0 spec to send to url
extern bool send_response(char * str_params);

//coworker that deals with command execution from NDS side
extern client_http_handler client_http_handler_context;

//libnds
extern void getHttp(char* url);

#ifdef __cplusplus
}
#endif
