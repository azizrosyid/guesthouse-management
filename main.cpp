#include <iostream>
#include <string>
#define MAX_ROOM 4
#define MAX_TRANSACTION 100
using namespace std;

// struct untuk menampung data pesanan
struct dataTransaction
{
    string name;
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

// struct untuk menampung data kamar
struct dataGuestRoom
{
    int guestId;
    int priceRoom;
    string typeRoom;
    bool statusRoom = 1;

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

string inputString(string);
int inputNumber(string, int, int);
int menu();
void addDataGuestRoom(dataGuestRoom (&)[MAX_ROOM]);
void showDetailTrx(int, dataTransaction (&)[MAX_TRANSACTION]);
void inputTransaction(dataTransaction &, dataGuestRoom &, int, int);

int main()
{
    // initiate data room
    dataGuestRoom arrDataRoom[MAX_ROOM];
    addDataGuestRoom(arrDataRoom);

    // initiate data transaction
    dataTransaction arrDataTrx[MAX_TRANSACTION];
    int lengthDataTrx = 0;
    int choice;

    do
    {
        choice = menu();
        if (choice == 1)
        {
            // mengecek apakah masih ada kamar kosong
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
                // input room id hingga memilih room yang kosong
                int tempRoomId;
                do
                {
                    tempRoomId = inputNumber("Masukkan ID Kamar : ", 1, 4);
                } while (arrDataRoom[tempRoomId - 1].statusRoom == 0 && cout << "Kamar Telah Dibooking!" << endl);

                dataGuestRoom &roomReservation = arrDataRoom[tempRoomId - 1];
                dataTransaction &dataTrx = arrDataTrx[lengthDataTrx];
                inputTransaction(dataTrx, roomReservation, lengthDataTrx, tempRoomId);

                dataTrx.getInfo();
                lengthDataTrx++;
            }
            else
            {
                cout << "Kamar sudah terbooking semua!" << endl;
            }
            cout << endl;
            cin.ignore();
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
                        showDetailTrx(arrDataRoom[i].guestId, arrDataTrx);
                    }
                    cout << endl;
                }
            }

            if (!isRoom)
            {
                cout << "Tidak Ada kamar yang " << (filterStatus ? "Available" : "Booked") << endl;
            }
            cout << endl;
            cin.ignore();
        }
        else if (choice == 3)
        {
            int choiceRoom;
            bool isBookingRoom = 0;
            for (int i = 0; i < MAX_ROOM; i++)
            {
                if (arrDataRoom[i].statusRoom == 0)
                {
                    isBookingRoom = 1;
                    cout << "Kamar " << i + 1 << endl;
                    cout << "Status Kamar : " << (arrDataRoom[i].statusRoom ? "Available" : "Booked") << endl;
                    showDetailTrx(arrDataRoom[i].guestId, arrDataTrx);
                    cout << endl;
                }
            }

            if (isBookingRoom)
            {
                choiceRoom = inputNumber("Pilih kamar yang ingin diselesaikan [1-4] : ", 1, 4);
                if (!arrDataRoom[choiceRoom - 1].statusRoom)
                {
                    int idTransaction = arrDataRoom[choiceRoom - 1].guestId;
                    arrDataTrx[idTransaction].isExit = true;
                    arrDataTrx[idTransaction].getInfo();
                    arrDataRoom[choiceRoom - 1].resetRoom();
                    cout << endl
                         << "Status Kamar " << choiceRoom << " sudah terubah!" << endl;
                    cout << "Kamar " << choiceRoom << endl;
                    cout << "Status Kamar : " << (arrDataRoom[choiceRoom - 1].statusRoom ? "Available" : "Booked") << endl;
                }
                else
                {
                    cout << "Kamar masih tersedia !" << endl;
                }
            }
            else
            {
                cout << "Tidak Ada Kamar yang sedang di Booking!" << endl;
            }
            cout << endl;
            cin.ignore();
        }
        else if (choice == 4)
        {
            cout << "Detail Kamar" << endl;
            int choiceRoom = inputNumber("Pilih kamar untuk melihat detail Kamar [1-4] : ", 1, 4);
            cout << "Kamar " << choiceRoom << endl;
            arrDataRoom[choiceRoom - 1].getInfo();
            cout << endl;

            cout << "History Pemesanan : " << endl;
            bool isHistory = 0;
            for (int i = 0; i < MAX_TRANSACTION; i++)
            {
                dataTransaction &dataTrx = arrDataTrx[i];
                if (dataTrx.roomId == choiceRoom)
                {
                    if (!dataTrx.name.empty())
                    {
                        isHistory = 1;
                        dataTrx.getInfo();
                        cout << endl;
                    }
                }
                else if (dataTrx.name.empty())
                {
                    break;
                }
            }
            if (!isHistory)
            {
                cout << "Tidak ada Histori Pemesanan" << endl;
            }
            cout << endl;
            cin.ignore();
        }

    } while (choice != 0);

    return 0;
}

// fungsi untuk menginput string, dengan tambahan pattern regex
string inputString(string message)
{
    string result;
    cout << message;
    getline(cin, result);
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

// fungsi untuk menginput data ke data kamar
void addDataGuestRoom(dataGuestRoom (&arrDataRoom)[MAX_ROOM])
{
    string arrRoomName[4] = {"Single room", "Double room", "Twin room", "Triple room"};
    int arrPriceRoom[MAX_ROOM] = {10000, 20000, 30000, 40000};
    for (int i = 0; i < MAX_ROOM; i++)
    {
        arrDataRoom[i].priceRoom = arrPriceRoom[i];
        arrDataRoom[i].typeRoom = arrRoomName[i];
    }
}

// fungsi untuk melihat detail transaksi
void showDetailTrx(int guestId, dataTransaction (&arrDataTrx)[MAX_TRANSACTION])
{
    cout << "Kode Pesanan : " << guestId << endl;
    arrDataTrx[guestId].getInfo();
}

// fungsi untuk menginput pesanan
void inputTransaction(dataTransaction &dataTrx, dataGuestRoom &dataGuestRoom, int idTransaction, int roomId)
{
    dataTrx.name = inputString("Masukkan Nama Pemesan : ");
    dataTrx.roomId = roomId;
    dataTrx.lengthStay = inputNumber("Masukkan Jumlah Hari Menginap : ", 0, 31);
    dataTrx.totalPrice = dataGuestRoom.priceRoom * dataTrx.lengthStay;
    dataGuestRoom.statusRoom = 0;
    dataGuestRoom.guestId = idTransaction;
}
