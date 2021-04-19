#include <iostream>
#include <regex> // regex_match, regex
#define MAX_ROOM 4
#define MAX_TRANSACTION 100
using namespace std;

struct dataTransaction
{
    string name;
    // string guestId;
    int lengthStay;
    int roomId;
    int totalPrice;
    bool isExit = false;

    void getInfo()
    {
        cout << "Nama Pemesan : " << name << endl
             << "Jumlah Hari : " << lengthStay << endl
             << "ID Kamar : " << roomId << endl
             << "Total Harga : " << totalPrice << endl;
    }
};

struct dataGuestRoom
{
    int guestId;
    int priceRoom;
    string typeRoom;
    bool statusRoom;

    void resetRoom()
    {
        guestId = -1;
        statusRoom = 1;
    }

    void getInfo()
    {
        cout << "Harga Kamar : " << priceRoom << endl
             << "Tipe Kamar : " << typeRoom << endl
             << "Status Kamar : " << (statusRoom ? "Available" : "Booked") << endl;
    }
};

// fungsi untuk menginput string, dengan tambahan pattern regex
string inputString(string message, string messageFailed, string patternRegex)
{
    regex pattern(patternRegex);
    string result;
    while (true)
    {
        cout << message;
        getline(cin, result);
        if (patternRegex.empty())
            return result;
        if (!regex_match(result, pattern))
        {
            cout << messageFailed << endl;
            continue;
        }
        break;
    }
    return result;
}

// fungsi untuk menginput angka
int inputNumber(string message, int min, int max)
{
    int result;
    while (true)
    {
        cout << message;
        cin >> result;
        if (cin.fail() || (result < min || result > max))
        {
            cout << "Masukkan Angka yang benar! (" << min << "-" << max << ")" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        break;
    }
    cin.ignore();
    return result;
}
int menu()
{
    cout << "Menu Utama" << endl
         << "1. Input Order" << endl
         << "2. Cari Kamar" << endl
         << "3. Penyelesaian Transaksi" << endl
         << "4. Detail Kamar" << endl
         << "0. Keluar" << endl;
    return inputNumber("Masukkan Pilihan [0-4] : ", 0, 4);
}
int main()
{
    // initiate data room
    dataGuestRoom arrDataRoom[MAX_ROOM];
    string arrRoomName[4] = {"Single room", "Double room", "Twin room", "Triple room"};
    int arrPriceRoom[MAX_ROOM] = {10000, 20000, 30000, 40000};
    for (int i = 0; i < MAX_ROOM; i++)
    {
        arrDataRoom[i].priceRoom = arrPriceRoom[i];
        arrDataRoom[i].typeRoom = arrRoomName[i];
        arrDataRoom[i].statusRoom = 1;
    }

    dataTransaction arrDataTrx[MAX_TRANSACTION];
    int lengthDataTrx = 0;
    int choice;

    do
    {
        choice = menu();
        if (choice == 1)
        {
            bool isAvailableRoom = 0;
            for (int i = 0; i < MAX_ROOM; i++)
            {
                if (arrDataRoom[i].statusRoom)
                {
                    isAvailableRoom = 1;
                    break;
                }
            }

            if (isAvailableRoom)
            {
                int tempRoomId;
                arrDataTrx[lengthDataTrx].name = inputString("Masukkan Nama Pemesan : ", "Format Nama salah!", "^[A-Za-z ]+[^\\s]$");
                do
                {
                    tempRoomId = inputNumber("Masukkan ID Kamar : ", 1, 4);
                } while (arrDataRoom[tempRoomId - 1].statusRoom == 0 && cout << "Kamar Telah Dibooking!" << endl);

                arrDataTrx[lengthDataTrx].roomId = tempRoomId;
                dataGuestRoom &roomReservation = arrDataRoom[tempRoomId - 1];
                arrDataTrx[lengthDataTrx].lengthStay = inputNumber("Masukkan Jumlah Hari Menginap : ", 0, 31);
                arrDataTrx[lengthDataTrx].totalPrice = roomReservation.priceRoom * arrDataTrx[lengthDataTrx].lengthStay;
                roomReservation.statusRoom = 0;
                roomReservation.guestId = lengthDataTrx;
                arrDataTrx[lengthDataTrx].getInfo();
                lengthDataTrx++;
            }
            else
            {
                cout << "Kamar sudah terbooking semua!" << endl;
            }
        }
        else if (choice == 2)
        {
            // available = 1, booked = 0
            cout << "1. Booked" << endl
                 << "2. Available" << endl;
            bool filterStatus = inputNumber("Masukkan Pilihan : ", 1, 2) == 2 ? 1 : 0;
            bool isRoom = 0;
            for (int i = 0; i < MAX_ROOM; i++)
            {
                if (arrDataRoom[i].statusRoom == filterStatus)
                {
                    isRoom = 1;
                    cout << "Kamar " << i + 1 << endl;
                    cout << "Status Kamar : " << (arrDataRoom[i].statusRoom ? "Available" : "Booked") << endl;
                    if (filterStatus == 0)
                    {
                        int idTransaction = arrDataRoom[i].guestId;
                        cout << "Kode Pesanan : " << idTransaction << endl;
                        arrDataTrx[idTransaction].getInfo();
                    }
                }
            }

            if (!isRoom)
            {
                cout << "Tidak Ada kamar yang " << (filterStatus ? "Available" : "Booked") << endl;
            }
        }
        else if (choice == 3)
        {
            int choiceRoom;
            bool isBookingRoom = 0;
            for (int i = 0; i < MAX_ROOM; i++)
            {
                if (!arrDataRoom[i].statusRoom)
                {
                    isBookingRoom = 1;
                    cout << "Kamar " << i + 1 << endl;
                    cout << "Status Kamar : " << (arrDataRoom[i].statusRoom ? "Available" : "Booked") << endl;
                    int idTransaction = arrDataRoom[i].guestId;
                    cout << "Kode Pesanan : " << idTransaction << endl;
                    arrDataTrx[idTransaction].getInfo();
                }
            }

            if (isBookingRoom)
            {
                choiceRoom = inputNumber("Pilih kamar yang ingin diselesaikan [1-4] : ", 1, 4);
                int idTransaction = arrDataRoom[choiceRoom - 1].guestId;
                arrDataTrx[idTransaction].isExit = true;
                arrDataRoom[choiceRoom - 1].resetRoom();
                cout << "Kamar " << choiceRoom << endl;
                cout << "Status Kamar : " << (arrDataRoom[choiceRoom - 1].statusRoom ? "Available" : "Booked") << endl;
            }
            else
            {
                cout << "Tidak Ada Kamar yang sedang di Booking!" << endl;
            }
        }
        else if (choice == 4)
        {
            cout << "Detail Kamar" << endl;
            int choiceRoom = inputNumber("Pilih kamar untuk melihat detail Kamar [1-4] : ", 1, 4);
            cout << "Kamar " << choiceRoom << endl;
            arrDataRoom[choiceRoom - 1].getInfo();

            cout << "History Pemesanan : " << endl;
            bool isHistory = 0;
            for (int i = 0; i < MAX_TRANSACTION; i++)
            {
                dataTransaction &dataTrx = arrDataTrx[i];
                if (!dataTrx.name.empty())
                {
                    isHistory = 1;
                    dataTrx.getInfo();
                    cout << endl;
                }
                else
                {
                    break;
                }
            }
            if (!isHistory)
            {
                cout << "Tidak ada Histori Pemesanan" << endl;
            }
        }

    } while (choice != 0);

    return 0;
}
