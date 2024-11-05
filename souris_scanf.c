#include <termios.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

struct termios orig_term_settings;
int termsize_col,termsize_row;

#define OUT_BUF_SIZE 100
char stdout_buffer[OUT_BUF_SIZE];

void    graphical_cleanup(void)
{
    //appellé a la sortie, responsable de clean les graphisme et de restaurer le terminal

    //restore les attributs du terminal
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_term_settings);
    //réaffiche le curseur, et reset la couleur d'affichage au valeur par défault
    printf("%s", "\33[H \33[?25h \33[0m \33[2J \e[?1003l");
}

void    init_graphical(void)
{
    //*mets en place les graphismes*
	
    //mets en place le buffering
    setvbuf(stdout, stdout_buffer, _IOFBF, OUT_BUF_SIZE);
    //cache le curseur
    printf("%s", "\33[?25l");
    //obtention de la taille de l'écran
    struct winsize raw_termsize;
    ioctl(0, TIOCGWINSZ, &raw_termsize);
    termsize_col    = raw_termsize.ws_col;
    termsize_row    = raw_termsize.ws_row;

    //setup du terminal sur linux
    #if __unix__
    //sauvegarde les attributs terminal (pour restauration future) et mets le term en raw mode
    //Voir http://manpagesfr.free.fr/man/man3/termios.3.html pour plus de détails
    tcgetattr(STDIN_FILENO, &orig_term_settings);
    struct termios raw = orig_term_settings;
    raw.c_lflag   &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
    raw.c_iflag   &= ~( IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    raw.c_oflag   &= ~(OPOST);
    raw.c_cflag   &= ~(CSIZE | PARENB);
    raw.c_cflag   |= CS8;

	//VTIME et VMIN permettent a scanf (read) de retourner instantanément 0 si l'utilisateur n'a rien rentré
	//et de fonctionner normalement sinon
    raw.c_cc[VMIN] = 1; raw.c_cc[VTIME] = 1;
    //applique tout les changements
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    #else
        #error  "non POSIX system unsupported"
    #endif //SYSTEM_POSIX

    //set la langue a rien, pour que certaint settings de langue bizarre
	//(ex langue de droite a gauche) n'influent pas sur le programme
    setlocale(LC_ALL, "");
    printf("\e[?1003h\e[?1015h\e[?1006h");
    fflush(stdout);
}

void clear_input(){
    scanf("%*[^\e]");
}

int main(){
    int x,y,btn;
    bool up;
    init_graphical();
    
    char c=0;
    while(c!='m'){
        x=0;
        y=0;
        btn=0;
        int num_read=0;
        num_read = scanf("\e[<%i;%i;%i%c",&btn,&x,&y,&c);
        if (num_read!=4){
            fflush(stdout);
            clear_input();
            continue;
        }
        up=(c=='m');
        printf("\n\rbtn:%i x:%i y:%i up:%i",btn,x,y,up);
        fflush(stdout);
        c=0;
    }
    
    graphical_cleanup();
    return 0;
}
