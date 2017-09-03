#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

void banner(){
    puts(" _____         _____   ");
    puts("|  __ \\      / ____|  ");
    puts("| |  | | ___| (___     ");
    puts("| |  | |/ _ \\___ \\   ");
    puts("| |__| | (_) |___) |   ");
    puts("|_____/ \\___/_____/   ");
	                     
    printf("\n");                 
    puts("[+]Author: Lexroot");
    puts("[+]github: github/Lexroot");
}

void help(){
    fprintf(stderr,
            "Use: %s [OPCAO]\n\n"
            "OPCOES:\n"
            "-h, --host     Informe o host(alvo)\n"
            "-p, --port     Informe a porta\n"
            "-n, --npacket  Informe o numero de pacotes\n");
    exit(1);

}

//funcao para retornar possiveis erros
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

const char *opts = "h:p:n";

const struct option opts1[] = {

    { "host",    1, 0, 'h' },
    { "port",    1, 0, 'p' },
    { "npacket", 1, 0, 'n' },
    { 0, 0, 0,0 },
    
};

int main(int argc, char *argv[]){
    if(argc < 3){
        help();
        exit(1);
    }
    
    int c;
    struct sockaddr_in vit;
    struct pool p;

    memset(&p, 0, sizeof(p));
    while((c = getopt_long(argc, argv, opts, opts1, &optind)) != -1){
    
        switch(c){
            case 'h':
                p.host = optarg;
                break;
            
            case 'p':
                p.port = atoi(optarg);
                break;

            case 'n':
                p.fim = atoi(optarg);
                break;

            default:
                help(); 
        }
    }

    /* 
    p.host   = argv[1];
    p.port   = atoi(argv[2]);
    p.fim  	 = atoi(argv[3]);
    */

    for(p.inicio = 0; p.inicio < p.fim; p.inicio++){ 

        p.mysockd = socket(AF_INET, SOCK_STREAM, 0);

        vit.sin_family      = AF_INET;
        vit.sin_port        = htons(p.port);
        vit.sin_addr.s_addr = inet_addr(p.host);
    
        if(p.conecta = connect(p.mysockd, (struct sockaddr *)&vit, sizeof(vit)) < 0){
            fatal("Nao foi possivel criar conexao com o host");
        }
    
        if(p.conecta == 0){
            printf("Packet -> %d - Bytes - %zu\n", p.inicio, sizeof(p.inicio));
        }
    }

    return 0;
}
