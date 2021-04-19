#include <stdio.h>
#include <string>
#include <array>
#define MAX_ROOM 10
#define MAX_TRANSACTION 100
using namespace std;

struct dataTransaction
{
    string name;
    int age;
    string guestId;
    int lengthStay;
    int roomId;
    int totalPrice;
};

struct dataGuestRoom
{
    int roomId;
    int priceRoom;
    bool statusRoom;
};

int menu()
{
    int result;
    bool valid;
    printf("Menu Utama \n"
           "1. Input Transaksi \n"
           "2. Cari Kamar \n"
           "3. Edit Pesanan \n"
           "0. Keluar \n"
           "Pilih Menu [0-3] : ");
    if (scanf("%d", &result) != 1)
    {
        // clean input buffer
        while (getchar() != '\n')
            ;
        return menu();
    }

    return result;
}

int main()
{
    // initiate data room
    dataGuestRoom arrDataRoom[MAX_ROOM];
    int arrPriceRoom[4] = {1000, 2000, 3000, 4000};
    for (int i = 0; i < 4; i++)
    {
        arrDataRoom[i].roomId = i;
        arrDataRoom[i].priceRoom = arrPriceRoom[i];
        arrDataRoom[i].statusRoom = 1;
    }

    dataTransaction arrDataTrx[MAX_TRANSACTION];
    int lengthDataTrx = 0;
    int choice;
    choice = menu();
    if (choice == 1)
    {
        printf("afeafaefa");
    }

    return 0;
}
