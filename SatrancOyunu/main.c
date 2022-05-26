//
//  main.c
//  SatrancOyunu
//
//  Created by Barış Yeşilkaya on 26.05.2022.
//


#include <stdio.h>

//Tas Puanlari ve takım puanları bütün fonksiyonlarda kullanılacağı için globalde tanımlandı.
double p = 1;
double a = 3;
double f = 3;
double k = 5;
double v = 9;
double s = 100;

double beyazOyuncuPuani = 0;
double siyahOyuncuPuani = 0;


int depo[8][8] = {0};  /*Tehdit edilen bir taşın başka bir taş tarafından tehdir edilip birden fazla kez puan düşümü yaşanmaması için, tehdit edilen taşların bulunduğu kordinatları hafızada tutacak 2d array tanımlandı. */

/* Takımlara göre board arrayinde bulunan taşların puanları toplanması için fonksiyon tanımlandı.*/
void puanHesaplama(char tas, char renk) {
    if (renk == 's') {
        if (tas == 'p')
            siyahOyuncuPuani += p;
        if (tas == 'a')
            siyahOyuncuPuani += a;
        if (tas == 'f')
            siyahOyuncuPuani += f;
        if (tas == 'k')
            siyahOyuncuPuani += k;
        if (tas == 'v')
            siyahOyuncuPuani += v;
        if (tas == 's')
            siyahOyuncuPuani += s;
    }
    else if(renk == 'b') {
        if (tas == 'p')
            beyazOyuncuPuani += p;
        if (tas == 'a')
            beyazOyuncuPuani += a;
        if (tas == 'f')
            beyazOyuncuPuani += f;
        if (tas == 'k')
            beyazOyuncuPuani += k;
        if (tas == 'v')
            beyazOyuncuPuani += v;
        if (tas == 's')
            beyazOyuncuPuani += s;
    }
}



void puanDusme(int x, int y, char tRenk, char board[8][8][2]) { //Puan düşümü için fonksiyon tanımlandı.
    if(depo[x][y] == 0){ //Kordinatlardaki taşın daha önce tehdit edilmemiş olma koşulu kontrol edildi.
        if (board[x][y][1] != tRenk) { /*Kordinatlardaki taş ile tehdit eden taşın takım renkleri karşılaştırılıp kontrol edildi. */
            switch (board[x][y][0]) { //Konumda bulunan taşın ne olduğu kontrol edildi.
                case 'p':
                    /*Tehdit altındaki taşın takımı belirlenip toplam puandan, taş puanının yarısı düşüldü. */
                    if(board[x][y][1] == 's') {
                        siyahOyuncuPuani -= p/2;
                        depo[x][y] = 1; //Taşın tehdit edildiği depo arrayine bildirildi.
                    }
                    else if (board[x][y][1] == 'b'){
                        beyazOyuncuPuani -= p/2;
                        depo[x][y] = 1;
                    }
                    break;
                case 'k':
                    if(board[x][y][1] == 's'){
                        siyahOyuncuPuani -= k/2;
                        depo[x][y] = 1;
                    }
                    else if (board[x][y][1] == 'b'){
                        beyazOyuncuPuani -= k/2;
                        depo[x][y] = 1;
                    }
                    break;
                case 'a':
                    if(board[x][y][1] == 's'){
                        siyahOyuncuPuani -= a/2;
                        depo[x][y] = 1;
                    }
                    else if (board[x][y][1] == 'b'){
                        beyazOyuncuPuani -= a/2;
                        depo[x][y] = 1;
                    }
                    break;
                case 'f':
                    if(board[x][y][1] == 's'){
                        siyahOyuncuPuani -= f/2;
                        depo[x][y] = 1;
                    }
                    else if (board[x][y][1] == 'b'){
                        beyazOyuncuPuani -= f/2;
                        depo[x][y] = 1;
                    }
                    break;
                case 'v':
                    if(board[x][y][1] == 's'){
                        siyahOyuncuPuani -= v/2;
                        depo[x][y] = 1;
                    }
                    else if (board[x][y][1] == 'b'){
                        beyazOyuncuPuani -= v/2;
                        depo[x][y] = 1;
                    }
                    break;
                case 's':
                    if(board[x][y][1] == 's'){
                        siyahOyuncuPuani -= s/2;
                        depo[x][y] = 1;
                    }
                    else if (board[x][y][1] == 'b'){
                        beyazOyuncuPuani -= s/2;
                        depo[x][y] = 1;
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

void at(int x, int y, char board[8][8][2]){ //At taşının hareketleri için fonksiyon tanımlandı.
    
    char tasRengi = board[x][y][1]; /*Tehdit eden taş ile tehdit edilen alanda bulunan taşın rakip olup olamdığı karşılatırılmak için tehdit eden taşın takım rengi karakteri tanımlanan değişkene atandı. */
    
    /*At taşının tehdit ettiği kordinatlar, atın rengi ve taşların bulunduğu konumları tutan array, puan düşümü için tanımlanan fonksiyona girdi olarak gönderildi. */
    puanDusme(x+2, y+1, tasRengi, board);
    puanDusme(x+1, y+2, tasRengi, board);
    puanDusme(x-1, y+2, tasRengi, board);
    puanDusme(x-2, y+1, tasRengi, board);
    puanDusme(x-2, y-1, tasRengi, board);
    puanDusme(x-1, y-2, tasRengi, board);
    puanDusme(x+1, y-2, tasRengi, board);
    puanDusme(x+2, y-1, tasRengi, board);
    
}



void piyon(int x, int y, char board[8][8][2]) { //Piyon taşının hareketleri için fonksiyon tanımlandı.

    
    char tasRengi = board[x][y][1]; /*Tehdit eden taş ile tehdit edilen alanda bulunan taşın rakip olup olamdığı karşılatırılmak için tehdit eden taşın takım rengi karakteri tanımlanan değişkene atandı. */
    
    if(tasRengi == 'b') { //Piyonlar geriye hareket edemediği için kontrol ifadesi oluşuturulup, takım koşulu belirlendi.

        /*Belirlene takıma göre piyon taşının tehdit ettiği kordinatlar, piyonun rengi ve taşların bulunduğu konumları tutan array, puan düşümü için tanımlanan fonksiyona girdi olarak gönderildi. */
        puanDusme(x-1, y+1, tasRengi, board);
        puanDusme(x-1, y-1, tasRengi, board);
        
    }else if (tasRengi == 's') {
        
        puanDusme(x+1, y+1, tasRengi, board);
        puanDusme(x+1, y-1, tasRengi, board);
        
    }
    
}


void vezir(int x, int y, char board[8][8][2]) {
    
    char tasRengi = board[x][y][1]; /*Tehdit eden taş ile tehdit edilen alanda bulunan taşın rakip olup olamdığı karşılatırılmak için tehdit eden taşın takım rengi karakteri tanımlanan değişkene atandı. */
    
    /*Vezir taşının 8 yönlü ve sınırlara kadar hareket etmesi sebebi ile her hareketi için döngüler oluşturuldu. */
    
    //Kuzeye hareket kontrolü
    for (int i = x-1; i>=0 ; --i) { //Hareket alanınna Bulunduğu konumu dahil etmemesi için hareket edeceği yöne doğru 1 sıra ilerlendi.
        
        if (board[i][y][0] != '-') {
            puanDusme(i, y, tasRengi, board);
            break;  /*Vezir taşı rakip taşın yahut kendi taşının üstünden atlayamadığı için herhangi bir taşla karşılaştığında döngü sonlarıldı. */
        }
    }
    
    //Doğuya hareket kontrolü
    for (int i = y+1; i<8 ; ++i) {
        
        if (board[x][i][0] != '-') {
            puanDusme(x, i, tasRengi, board);
            break;
        }
        
    }
    
    //Güneye hareket kontrolü
    for (int i = x+1; i<8 ; ++i) {
        
        if (board[i][y][0] != '-') {
            puanDusme(i, y, tasRengi, board);
            break;
        }
    }
    
    //Batıya hareket kontrolü
    for (int i = y-1; i>=0 ; --i) {
        
        if (board[x][i][0] != '-') {
            puanDusme(x, i, tasRengi, board);
            break;
        }
    }
    
    //Kuzey-Doğuya hareket
    int x1=x-1, y1=y+1; //Kordinatlarda değişiklik yapılacağı için kordinatlar yeni değişkenlere atandı.
    while (x1>=0 && y1<8) {
        
        if (board[x1][y1][0] != '-') {
            puanDusme(x1, y1, tasRengi, board);
            break;
        }
        //Kordinatlar hareket alanına doğru azaltıldı veya artırıldı.
        --x1;
        ++y1;
    }
    
    //Güney-Doğuya hareket
    int x2=x+1, y2=y+1; //Kordinatlarda değişiklik yapılacağı için kordinatlar yeni değişkenlere atandı.
    while (x2<8 && y2<8) {
        
        if (board[x2][y2][0] != '-') {
            puanDusme(x2, y2, tasRengi, board);
            break;
        }
        ++x2;
        ++y2;
    }
    
    //Güney-Batı hareket
    int x3=x+1, y3=y-1; //Kordinatlarda değişiklik yapılacağı için kordinatlar yeni değişkenlere atandı.
    while (x3<8 && y3>=0) {
        
        if (board[x3][y3][0] != '-') {
            puanDusme(x3, y3, tasRengi, board);
            break;
        }
        ++x3;
        --y3;
    }
    
    //Kuzey-Batı hareket
    int x4=x-1, y4=y-1; //Kordinatlarda değişiklik yapılacağı için kordinatlar yeni değişkenlere atandı.
    while (x4>=0 && y4>=0) {
        
        if (board[x4][y4][0] != '-') {
            puanDusme(x4, y4, tasRengi, board);
            break;
        }
        --x4;
        --y4;
    }
    
}


int main () {
    
    char c; //Boşlukların '\b' ve satırların '\n' atanması için karakter tipli değişken tanımlandı.
    char board[8][8][2]; //Satranc taşlarının konumları için 3boyutlu karakter tipli array tanımlandı.


    //Girdinin okunması basladi...
    for (int i = 0; i<8; ++i) {
        
        for (int k = 0; k<8; ++k){
            
            for (int l = 0; l<2; ++l) {
                
                scanf("%c", &board[i][k][l]);
            }
            if((c = getchar()) != '\b')
                continue;
        }
        if((c = getchar()) != '\n')
            continue;
    }
    //Girdi okunması bitti.
    
    //Tarafların puanlarının belirlenmesi için döngü tanımlandı.
    for (int i=0; i<8; ++i) {
        for (int k=0; k<8; ++k) {
            if (board[i][k][0] != '-') { // '-' tire karakteri baz alınmadı.
                puanHesaplama(board[i][k][0], board[i][k][1]);
            }
        }
    }
    
    //Girdinin ardından tarafların puanları kontrol edildi.
    printf("---OYUN BASINDAKI PUANLAR---- \n");
    printf("Siyah oyuncunun puani = %.2f \n", siyahOyuncuPuani);
    printf("Beyaz oyuncunun puani = %.2f \n", beyazOyuncuPuani);
    printf("\n");
    
    
    //Belirtiği üzere At, Vezir ve Piyon taşlarının tehditleri sonucu puan düşümü için, bu taşların konumları belirlenip, puan düşümü için tanımlanan fonksiyonlar çağırıldı.
    for (int i = 0; i<8; ++i) {
        
        for (int k=0; k<8; ++k) {
            
            if(board[i][k][0] != '-'){ //
                
                switch (board[i][k][0]) { //Puan düşümünü sağlayacak harflerin belirlenmesi için koşul oluşturuldu.
                    case 'a':
                        at(i, k, board); //At taşının tehdit alanları için fonksiyon çağırıldı.
                        break;
                    case 'p':
                        piyon(i, k, board); //Piyon taşının tehdit alanları için fonksiyon çağırıldı.
                        break;
                    case 'v':
                        vezir(i, k, board); //Vezir taşının tehdit alanları için fonksiyon çağırıldı.
                        break;
                    default:
                        break;
                        
                }
            }
        }
    }
    
    
    printf("---OYUN SONUNDAKI PUANLAR---- \n");
    printf("Siyah oyuncunun puani = %.2f \n", siyahOyuncuPuani); //Puan sonuçları ekrana yazdırıldı.
    printf("Beyaz oyuncunun puani = %.2f \n", beyazOyuncuPuani); //Puan sonuçları ekrana yazdırıldı.
    
    
/* //Depo tahtasının kontrolü sağlandı.
    printf("------------------ \n");
    for (int i= 0; i<8; ++i) {
        for (int k = 0; k<8; ++k) {
                printf("%d", depo[i][k]);
            printf(" ");
        }
        printf("\n");
    }
*/
    
}


