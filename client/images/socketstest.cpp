#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_net/SDL_net.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cstring>


typedef char charbuf [256];
 
class CNet{
  public:
    //static bool Init(); //Initialize SDL_net
    //static void Quit(); //Exit SDL_net
    bool Init() {
        if (SDLNet_Init() < 0) {
            std::cout << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
              return false;
            }
            else
                return true;
    }
    void Quit() {
        SDLNet_Quit();
    }
};


class CNetMessage {
  protected:
    charbuf buffer; //message stored in buffer, limited to 256 bytes
    enum bufstates { //message states
    EMPTY,
    READING,
    WRITING,
    FULL };
    bufstates state; //the message state
    //void reset(); // reset message: fulfill it with zeroes and change its state to EMPTY
    void reset() {
        for (int i =0; i < 256; i++)
            buffer [i] = 0;
        state = EMPTY;
    }
  public:
    CNetMessage(){
        reset() ;
    } //constructor



//Virtual member function that indicates how many bytes may have to be loaded into the instance. By default, it works with strings that have a maximum
//of 255 characters.
//    virtual int NumToLoad();
    int NumToLoad() {
        if (state == EMPTY)
            return 255;
        else
            return 0;
    }

 
//Virtual member function that indicates how many bytes may have to be downloaded from the instance.
    //virtual int NumToUnLoad();

    int NumToUnLoad() {
        if (state == FULL)
            return strlen(buffer) + 1;
        else
            return 0;
    }
 
    //void LoadBytes(charbuf& inputbuffer, int n); //Load a char set into the message buffer
    void LoadBytes(charbuf& inputbuffer, int n) {
        for (int i = 0; i < n; i++)
            buffer[i] = inputbuffer[i];
        state = READING;
    }
    

    //void UnLoadBytes(charbuf& destbuffer); //Unload a char set from the buffer

      void UnLoadBytes(charbuf& destbuffer) {
        for (int i=0; i < this->NumToUnLoad(); i++)
            destbuffer[i] = buffer[i];
        reset();
    }

    //void finish(); //set the state object to full. No more data to be loaded
    void finish() {
        if (state == READING)
            state = FULL;
    }
};







class CIpAddress {
  private:
    IPaddress m_Ip; //the IPaddress structure
  public:
    //CIpAddress(); //constructor

CIpAddress() {
        m_Ip.host = 0;
        m_Ip.port = 0;
    }



    //CIpAddress (Uint16 port); //create and associate a port to the instance
    CIpAddress (Uint16 port) {
        if (SDLNet_ResolveHost(&m_Ip, NULL, port) < 0){
            std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
            m_Ip.host = 0;
            m_Ip.port = 0;
        }
    }

    
    //CIpAddress (std::string host, Uint16 port); //create and associate a port and a host to the instance

      CIpAddress (std::string host, Uint16 port) {
        if (SDLNet_ResolveHost(&m_Ip, host.c_str(), port) < 0) {
            std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
            m_Ip.host = 0;
            m_Ip.port = 0;
        }
    }
     


    
    
    //bool Ok() const; //True if the object have a port and a host associated to it
    bool Ok() const {
        return !(m_Ip.port == 0);
    }
     


//void SetIp (IPaddress sdl_ip); //set a CIpAddress object from an existing SDL IPaddress
    
    void SetIp (IPaddress sdl_ip) { //sets a CTcpSocket object from a existing SDL socket
    m_Ip = sdl_ip;
}

     


    //IPaddress GetIpAddress() const; //return a SDL_net IPaddress structure
IPaddress GetIpAddress() const {
        return m_Ip;
    }
     


    //Uint32 GetHost() const; //return the host
 Uint32 GetHost() const {
        return m_Ip.host;
    }
     


    //Uint16 GetPort() const; //return the port
Uint16 GetPort() const {
        return m_Ip.port;
    }


};






class CTcpSocket {
  protected:
    TCPsocket m_Socket; //the TCP socket structure
    SDLNet_SocketSet set; //a set of sockets. Used here only to check existing packets
  public:
//    CTcpSocket();

CTcpSocket() {
        m_Socket = NULL;
        set = SDLNet_AllocSocketSet(1);
    }
//    virtual ~CTcpSocket();
~CTcpSocket() {
        if (!(m_Socket == NULL)) {
              SDLNet_TCP_DelSocket(set,m_Socket);
            SDLNet_FreeSocketSet(set);
            SDLNet_TCP_Close (m_Socket);
        }
    }


//    virtual void SetSocket (TCPsocket  the_sdl_socket); //set a CTcpSocket object from a existing SDL socket

        void SetSocket (TCPsocket the_sdl_socket) {
        if (!(m_Socket == NULL)) {
              SDLNet_TCP_DelSocket(set,m_Socket);
              SDLNet_TCP_Close (m_Socket);
          }
        m_Socket = the_sdl_socket;
        if(SDLNet_TCP_AddSocket(set,m_Socket)==-1) {
            std::cerr << "SDLNet_TCP_AddSocket: " << SDLNet_GetError() << std::endl;
            m_Socket = NULL;
        }
    }


//    bool Ok() const; //indicate if theres is a TCPsocket associated to the instance

        bool Ok() const {
        return !(m_Socket == NULL);
    }
     

//    bool Ready() const; //True if there are bytes ready to be read

            bool Ready() const {
        bool rd = false;
        int numready = SDLNet_CheckSockets(set, 0);
        if (numready == -1)
                std::cerr << "SDLNet_CheckSockets: " << SDLNet_GetError() << std:: endl;
          else
                if (numready)
                    rd = SDLNet_SocketReady (m_Socket);
          return rd;
    }


//    virtual void OnReady(); //pure virtual

        void OnReady() {
     
    }

};






class CClientSocket;
 
 
class CHostSocket : public CTcpSocket {
  public:
//    CHostSocket (CIpAddress& the_ip_address); //create and open a new socket, with an existing CIpAddress object
        CHostSocket (CIpAddress& the_ip_address) {
        CTcpSocket();
        IPaddress iph = the_ip_address.GetIpAddress();
        if (!(m_Socket = SDLNet_TCP_Open(&iph))) {
                SDLNet_FreeSocketSet(set);
                std::cerr << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
        }
    }

 
//    CHostSocket (Uint16 port); //create and open a new socket with the desired port

        CHostSocket (Uint16 port) {
        CIpAddress iplistener (port);
        if (!iplistener.Ok()) {
            m_Socket = NULL;
        }
        else {
            CTcpSocket();
            IPaddress iph = iplistener.GetIpAddress();
            if (!(m_Socket = SDLNet_TCP_Open(&iph))) {
                SDLNet_FreeSocketSet(set);
                std::cerr << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
            }
        }
    }

//    bool Accept (CClientSocket&); //set a client CTcpSocket object after listening to the port
            bool Accept (CClientSocket& the_client_socket) {
        TCPsocket cs;
        if ((cs = SDLNet_TCP_Accept(m_Socket))) {
            SetSocket(cs);
            return true;
        }
        else
            return false;
    }



//    virtual void OnReady(); //pure virtual
        void OnReady() {
     
    }

};



class CClientSocket : public CTcpSocket {
  private:
    CIpAddress m_RemoteIp; //the CIpAddress object corresponding to the remote host
  public:
    //CClientSocket(); //constructor
        CClientSocket() {
    CTcpSocket();
    }

    //CClientSocket (std::string host, Uint16 port); //Create the object and connect to a host, in a given port
        CClientSocket (std::string host, Uint16 port) {
        CIpAddress remoteip (host.c_str(), port);
        if (!remoteip.Ok()) {
            m_Socket = NULL;
        }
        else {
    CTcpSocket();
            Connect(remoteip);
        }
    }

    //bool Connect (CIpAddress& remoteip); //make a connection to communicate with a remote host
        

bool Connect (CIpAddress& remoteip) {
        TCPsocket cs;
        IPaddress ip = remoteip.GetIpAddress();
        if ((cs = SDLNet_TCP_Open(&ip)))
        {
            SetSocket(cs);
            return true;
        }
        else {
            std::cerr << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
            return false;
        }
    }

    //bool Connect (CHostSocket& the_listener_socket); //make a connection to communicate with a client
        
        bool Connect (CHostSocket& the_listener_socket) {
        return false;
    }

    //void SetSocket (TCPsocket  the_sdl_socket); //set a CTcpSocket object from an existing SDL_net socket

        void SetSocket (TCPsocket the_sdl_socket) {
        CTcpSocket::SetSocket (the_sdl_socket);
        IPaddress* ips;
        if ((ips = SDLNet_TCP_GetPeerAddress(m_Socket))) {
        /* Print the address, converting it onto the host format */
            m_RemoteIp.SetIp(*ips);
            Uint32 hbo = m_RemoteIp.GetHost();
            Uint16 pbo = m_RemoteIp.GetPort();
            std::cout << "Client connected: " << SDLNet_Read32(&hbo) << ' '
                << SDLNet_Read16 (&pbo) << std::endl;
        }
        else
            std::cerr << "SDLNet_TCP_GetPeerAddress: " << SDLNet_GetError() << std::endl;
    }

    //CIpAddress getIpAddress () const; //return a CIpAddress object associated to the remote host

        CIpAddress getIpAddress () const {
        return m_RemoteIp;
    }

//    virtual void OnReady(); //pure virtual

        void OnReady() {
     
    }


    //bool Receive(CNetMessage& rData); //receive data and load it into a CNetMessage object

        bool Receive(CNetMessage& rData) {
    //Firstly, check if there is a socket
        if (m_Socket == NULL)
            return false;
        charbuf buf;
     
    //Check if the instance can receive bytes, if it can, load the number of bytes specified by NumToLoad() virtual function
        while (rData.NumToLoad() > 0) {
            if (SDLNet_TCP_Recv(m_Socket, buf, rData.NumToLoad()) > 0) {
                rData.LoadBytes (buf, rData.NumToLoad());
            }
            else {
                return false;
            }
        }
        rData.finish();
        return true;
    }

    //bool Send (CNetMessage& sData); //send data from a CNetMessage object

        bool Send (CNetMessage& sData) {
    //check if there is a socket
        if (m_Socket == NULL)
            return false;
        charbuf buf;
        int len;
     
    //Check if the instance can send bytes, if it can, unload the number of bytes specified by NumToLoad() virtual function
        while ((len = sData.NumToUnLoad()) > 0) {
            sData.UnLoadBytes (buf);
            if (SDLNet_TCP_Send(m_Socket, (void *)buf, len) < len) {
                std::cerr << "SDLNet_TCP_Send: " << SDLNet_GetError() << std::endl;
                return false;
            }
        }
        return true;
    }

};



//CLIENT CODE STARTS
















class CApp {
    public:
        bool            Running;

    public:

        int             CurrentPlayer;

    public:
//network status indicator
        bool Connected;
//network objects
        CIpAddress* remoteip;
        CClientSocket* tcpclient;
        CNetMessage msg;

    public:
        //CApp();

    CApp() {
    CurrentPlayer = 0;

    Running = true;

    Connected = false;
    tcpclient = NULL;
    remoteip = NULL;
}

        //void OnExit();

void OnExit() {
Running = false;
}

         //void OnCleanup();
        void OnCleanup() {

   delete remoteip;
    delete tcpclient;

    SDL_Quit();
}

    //int OnExecute();

int OnExecute() {
if(OnInit() == false) {
return -1;
}

SDL_Event Event;

while(Running) {
while(SDL_PollEvent(&Event)) {
    OnEvent(&Event);
}

OnLoop();
}

OnCleanup();

return 0;
}
//bool OnInit();

void Reset() {

//void SetCell(int ID, int Type);
}



bool OnInit() {

//Creating host socket
    tcplistener = new CHostSocket (1234);
    if (!tcplistener->Ok())
        exit(EXIT_FAILURE);
//Creating client socket
    tcpclient = new CClientSocket();


    //CSurface::Transparent(Surf_X, 255, 0, 255);
    //CSurface::Transparent(Surf_O, 255, 0, 255);

    Reset();

    return true ;
}


        void OnEvent(SDL_Event* Event) {
	switch(Event->type) {

        /*
		case SDL_KEYDOWN: {
			OnKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
			break;
		}

        */
            
            
		case SDL_QUIT: {
			OnExit();
			break;
		}
        case SDLK_e: {
            if (Connected) {
//Player == 0 will always be Server. Always starts to play and always will be "X"
        if(CurrentPlayer == 0) {

            //SetCell(ID, GRID_TYPE_X);
            CurrentPlayer = 1;
//Send a message to the client, telling the ID of the clicked cell
            charbuf c ;
            c[0] = 't' ;
            c[1] = 'e' ;

            msg.LoadBytes(c, 2);
            tcpclient->Send(msg);
        }
    }
            break ;
        }

        /*
		default: {
			OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
			break;
		}
        */
	}
}





     void OnLoop() {
//if not connected, try to connect to the server
    if (!Connected) {
        if (tcpclient->Connect(*remoteip)) {
            if (tcpclient->Ok()) {
                Connected = true;
            }
        }
	}
    else {

//if connected, checks the socket for messages ready to be read
        if (tcpclient->Ready()){
// if there is a message, try to receive it. In case of disconnection, the TCP protocol sends
// a message with no bytes
            if (tcpclient->Receive (msg)) {
                //if there is a valid message, we can set the grid and player status
                //SetCell((int) msg.UnLoadByte(), GRID_TYPE_X);
                cout << "Received message" << endl ;
                CurrentPlayer = 1;
            }
            else {
                Connected = false;
            }
        }
    }
}
    
            
    
        
};






//CLIENT CODE ENDS





int main(int argc, char* argv[]) {
    CApp theApp;

    return theApp.OnExecute();
}