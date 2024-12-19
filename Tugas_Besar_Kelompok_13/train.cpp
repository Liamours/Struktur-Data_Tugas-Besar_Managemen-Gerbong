#include "train.h"

const int maxGerbong = 10;
const int maxPenumpang = 10;
listGerbong G;

void initListGerbong(listGerbong &G) {
    // I.S. listGerbong G yang belum diinisiasi
    // F.S. firstGerbong dan lastGerbong dari listGerbong G diassign dengan NULL
    firstGerbong(G) = NULL;
    lastGerbong(G) = NULL;
}

adrGerbong newGerbong(adrGerbong pG, int id, string nama, string kelas, int harga) {
    // I.S. Menerima pointer ke gerbong pG, int id, string nama dan kelas serta harga dari gerbong yang akan dibuat
    // F.S. Mengembalikan pointer pada gerbong yang sudah didefinisikan
    pG = new gerbong;

    idGerbong(pG) = id;
    namaGerbong(pG) = nama;
    kelasGerbong(pG) = kelas;
    hargaTiket(pG) = harga;
    nextGerbong(pG) = NULL;
    prevGerbong(pG) = NULL;
    firstPenumpang(pG) = NULL;

    return pG;
}

adrPenumpang newPenumpang(adrPenumpang pP, int id, string nama, int kursi) {
    // I.S. Menerima pointer ke penumpang pP, int id, string nama, dan nomor kursi
    // F.S. Mengembalikan pointer pada penumpang yang sudah didefinisikan
    pP = new penumpang;

    idPenumpang(pP) = id;
    namaPenumpang(pP) = nama;
    nomorKursi(pP) = kursi;
    nextPenumpang(pP) = NULL;

    return pP;
}

void insertGerbongDepan(listGerbong &G, adrGerbong &pG) {
    // I.S. Menerima list gerbong G dan pointer ke gerbong pG
    // F.S. Elemen yang ditunjuk pG akan ditambahkan di list gerbong G, berada di paling awal (depan) list
    if (!checkEmptyGerbong(G, pG)) {
        delete pG;
        handle_menuInsert();
    }

    if (searchGerbong(G, idGerbong(pG)) != NULL) {
        cout << "Gerbong dengan ID tersebut sudah ada" << endl;
        return;
    }

    if (firstGerbong(G) == NULL) {
        firstGerbong(G) = pG;
        lastGerbong(G) = pG;
    } else {
        nextGerbong(pG) = firstGerbong(G);
        prevGerbong(firstGerbong(G)) = pG;
        firstGerbong(G) = pG;
    }
}

void insertGerbongBelakang(listGerbong &G, adrGerbong &pG) {
    // I.S. Menerima list gerbong G dan pointer ke gerbong pG
    // F.S. Elemen yang ditunjuk pG akan ditambahkan di list gerbong G, berada di paling akhir (belakang) list
    if (!checkEmptyGerbong(G, pG)) {
        delete pG;
        handle_menuInsert();
    }

    if (searchGerbong(G, idGerbong(pG)) != NULL) {
        cout << "Gerbong dengan ID tersebut sudah ada" << endl;
        return;
    }

    if (firstGerbong(G) == NULL) {
        firstGerbong(G) = pG;
        lastGerbong(G) = pG;
    } else {
        prevGerbong(pG) = lastGerbong(G);
        nextGerbong(lastGerbong(G)) = pG;
        lastGerbong(G) = pG;
    }
}

void insertPenumpang(adrGerbong &pG, adrPenumpang &pP) {
    // I.S. Menerima pointer ke gerbong pG dan pointer ke penumpang pP
    // F.S. Pointer penumpang pP akan ditunjuk oleh elemen terakhir dari elemen di gerbong pG
    if (!checkEmptySeat(pG, pP)) {
        delete pP;
        handle_menuInsert();
    }

    if (firstPenumpang(pG) == NULL) {
        firstPenumpang(pG) = pP;
    } else {
        adrPenumpang helperP = firstPenumpang(pG);
        while (nextPenumpang(helperP) != NULL) {
            helperP = nextPenumpang(helperP);
        }
        nextPenumpang(helperP) = pP;
    }
}

void showAllGerbong(listGerbong G) {
    // I.S. Menerima list gerbong G
    // F.S. Menampilkan seluruh gerbong dan datanya pada setiap gerbong di list gerbong
    adrGerbong pG = firstGerbong(G);

    cout << left << setw(12) << "ID Gerbong"
         << setw(30) << "Nama Gerbong"
         << setw(30) << "Kelas Gerbong"
         << setw(30) << "Harga Tiket" << endl;
    cout << string(148, '-') << endl;
    while (pG != NULL) {
        cout << left << setw(12) << idGerbong(pG)
             << setw(30) << namaGerbong(pG)
             << setw(30) << kelasGerbong(pG)
             << setw(30) << hargaTiket(pG) << endl;
        pG = nextGerbong(pG);
    }
}

void showAllGerbongDetails(listGerbong G) {
    // I.S. Menerima list gerbong G
    // F.S. Menampilkan detail seluruh gerbong beserta penumpangnya
    adrGerbong pG = firstGerbong(G);
    adrPenumpang pP;

    if (pG == NULL) {
        cout << "Gerbong kosong." << endl;
        return;
    }

    cout << string(148, '=') << endl;
    cout << left << setw(12) << "ID Gerbong"
         << setw(30) << "Nama Gerbong"
         << setw(30) << "Kelas Gerbong"
         << setw(30) << "Harga Tiket" << endl;
    cout << string(148, '=') << endl;

    while (pG != NULL) {
        cout << endl;
        cout << string(79, '-') << endl;
        showGerbong(pG);
        cout << string(79, '-') << endl;

        pP = firstPenumpang(pG);

        cout << left << setw(16) << "ID Penumpang"
             << setw(32) << "Nama Penumpang"
             << setw(12) << "Nomor Kursi" << endl;
        cout << string(60, '-') << endl;

        if (pP == NULL) {
            cout << "  Tidak ada penumpang pada gerbong ini" << endl;
        } else {
            while (pP != NULL) {
                showPenumpang(pP);
                pP = nextPenumpang(pP);
            }
        }
        pG = nextGerbong(pG);
    }
}

void showGerbong(adrGerbong pG) {
    // I.S. Menerima pointer ke gerbong pG
    // F.S. Menampilkan detail data gerbong yang ditunjuk pG
    cout << left << setw(12) << idGerbong(pG)
         << setw(30) << namaGerbong(pG)
         << setw(30) << kelasGerbong(pG)
         << setw(30) << hargaTiket(pG) << endl;
}

void showPenumpang(adrPenumpang pP) {
    // I.S. Menerima pointer ke penumpang pP
    // F.S. Menampilkan detail data penumpang yang ditunjuk pP
    cout << left << setw(16) << idPenumpang(pP)
         << setw(32) << namaPenumpang(pP)
         << setw(12) << nomorKursi(pP) << endl;
}

void deleteGerbong(listGerbong &G, int id) {
    // I.S. menerima list gerbong G dan id gerbong yang akan di hapus
    // F.S. gerbong dengan id yang cocok akan di dealokasi dan dihapus seluruh penumpangnya
    // lalu gerbong itu sendiri akan di dealokasi dan di putus dari listGerbong G
    adrGerbong pG = searchGerbong(G, id), prevG = NULL;

    if (pG == NULL) {
        cout << "Gerbong tidak ditemukan" << endl;
        return;
    }

    while (firstPenumpang(pG) != NULL) {
        deleteLastPenumpang(pG);
    }

    if (pG == firstGerbong(G)) {
        firstGerbong(G) = nextGerbong(pG);
    } else {
        prevG = firstGerbong(G);
        while (nextGerbong(prevG) != pG) {
            prevG = nextGerbong(prevG);
        }
        nextGerbong(prevG) = nextGerbong(pG);
    }
    delete pG;
}

void deleteLastPenumpang(adrGerbong &pG) {
    // I.S. menerima pointer ke gerbong pG
    // F.S. penumpang dengan urutan di akhir akan di dealokasi dan di putus dari urutan penumpang
    // bila list penumpang kosong, maka akan menampilkan teks "Gerbong sudah kosong"
    adrPenumpang pP = firstPenumpang(pG), pDelete;

    if (pP == NULL) {
        cout << "Gerbong sudah kosong" << endl;
    } else if (nextPenumpang(pP) == NULL) {
        firstPenumpang(pG) = NULL;
        delete pP;
    } else {
        while (nextPenumpang(nextPenumpang(pP)) != NULL) {
            pP = nextPenumpang(pP);
        }
        pDelete = nextPenumpang(pP);
        nextPenumpang(pP) = NULL;
        delete pDelete;
    }
}

void deletePenumpang(adrGerbong &pG, int id) {
    // I.S. menerima pointer ke gerbong pG
    // F.S. penumpang dengan id yang sesuai akan didelete dari gerbong
    // Bila penumpang dengan id tersebut tidak ditemukan, maka akan menampilkan teks
    adrPenumpang pP = firstPenumpang(pG), pPrev = NULL;
    bool found = false;

    while (pP != NULL && !found) {
        if (idPenumpang(pP) == id) {
            found = true;
        } else {
            pPrev = pP;
            pP = nextPenumpang(pP);
        }
    }

    if (found) {
        if (pPrev == NULL) {
            firstPenumpang(pG) = nextPenumpang(pP);
        } else {
            nextPenumpang(pPrev) = nextPenumpang(pP);
        }
        delete pP;
        cout << "Penumpang dengan ID " << id << " berhasil dihapus." << endl;
    } else {
        cout << "Penumpang dengan ID " << id << " tidak ditemukan." << endl;
    }
}

adrGerbong searchGerbong(listGerbong G, int id) {
    // I.S. menerima listGerbong G dan id gerbong yang akan dicari
    // F.S. mengembalikan NULL bila tidak ditemukan gerbong dengan id yang sesuai
    // atau mengembalikan pointer ke gerbong yang memiliki id sesuai
    adrGerbong pG = firstGerbong(G);

    while (pG != NULL && idGerbong(pG) != id) {
        pG = nextGerbong(pG);
    }

    return pG;
}

adrPenumpang searchPrevPenumpang(listGerbong G, int id) {
    // I.S. menerima list gerbong G dan id penumpang
    // F.S. mengembalikan pointer ke elemen penumpang sebelum penumpang dengan id yang sesuai
    // bila penumpang ada di urutan pertama atau tidak ada di dalam list gerbong, maka akan mengembalikan NULL
    adrGerbong pG = firstGerbong(G);
    adrPenumpang pPrev = NULL, pCurr = NULL;

    while (pG != NULL) {
        pPrev = NULL;
        pCurr = firstPenumpang(pG);
        while (pCurr != NULL) {
            if (idPenumpang(pCurr) == id) {
                return pPrev;
            }
            pPrev = pCurr;
            pCurr = nextPenumpang(pCurr);
        }
        pG = nextGerbong(pG);
    }

    return NULL;
}

adrPenumpang searchPenumpang(listGerbong G, int id) {
    // I.S. menerima list gerbong G dan id penumpang
    // F.S. mengembalikan pointer ke elemen penumpang dengan id yang sesuai
    // bila penumpang tidak ada di dalam list gerbong, maka akan mengembalikan NULL
    adrGerbong pG = firstGerbong(G);
    adrPenumpang pP;

    while (pG != NULL) {
        pP = firstPenumpang(pG);
        while (pP != NULL) {
            if (idPenumpang(pP) == id) {
                return pP;
            }
            pP = nextPenumpang(pP);
        }
        pG = nextGerbong(pG);
    }

    return NULL;
}

adrGerbong searchGerbongPenumpang(listGerbong G, int id) {
    // I.S. menerima list gerbong G dan id penumpang
    // F.S. mengembalikan pointer ke elemen gerbong dengan id penumpang yang sesuai
    // bila penumpang tidak ada di dalam list gerbong, maka akan mengembalikan NULL
    adrGerbong pG = firstGerbong(G);

    while (pG != NULL) {
        adrPenumpang pP = firstPenumpang(pG);
        while (pP != NULL) {
            if (idPenumpang(pP) == id) {
                return pG;
            }
            pP = nextPenumpang(pP);
        }
        pG = nextGerbong(pG);
    }

    return NULL;
}

void alterGerbong(listGerbong &G, int id, string nama, string kelas, int harga) {
    // I.S. menerima list gerbong G dan seluruh data gerbong
    // F.S. mengubah data gerbong dengan id yang sesuai
    // nama, kelas, dan harga akan diubah berdasarkan parameter yang diberikan
    // bila gerbong dengan id tidak ditemukan maka tidak akan melakukan perubahan
    adrGerbong pG = searchGerbong(G, id);

    namaGerbong(pG) = nama;
    kelasGerbong(pG) = kelas;
    hargaTiket(pG) = harga;
}

void alterPenumpang(listGerbong &G, int id, string nama, int kursi) {
    // I.S. menerima list gerbong G dan seluruh data penumpang
    // F.S. mengubah data penumpang dengan id yang sesuai
    // nama dan kursi akan diubah berdasarkan parameter yang diberikan
    adrPenumpang pP = searchPenumpang(G, id);
    adrGerbong pG = searchGerbongPenumpang(G, id);
    adrPenumpang p = firstPenumpang(pG);
    char choice;
    bool kursiTersedia = true;

    while (p != NULL) {
        if (nomorKursi(p) == kursi) {
            kursiTersedia = false;
            cout << "Kursi ini sudah ditempati penumpang lain.\n";
            cout << "Tekan '0' untuk kembali ke menu Data.\n";
            cin >> choice;
            while (choice != '0') {
                cin >> choice;
            }
            handle_menuData();
            return;
        }
        p = nextPenumpang(p);
    }

    if (kursiTersedia) {
        namaPenumpang(pP) = nama;
        nomorKursi(pP) = kursi;
    }
}

void hitungTotalPenumpang(listGerbong G) {
    // I.S. -
    // F.S. Menampilkan total penumpang pada tiap gerbong serta total penumpang dari seluruh gerbong
    adrGerbong pG = firstGerbong(G);
    int totalPenumpang = 0;

    cout << left << setw(40) << "Gerbong" << setw(20) << "ID Gerbong" << "Penumpang" << endl;
    cout << string(70, '-') << endl;

    while (pG != NULL) {
        adrPenumpang pP = firstPenumpang(pG);
        int totalPenGer = 0;

        while (pP != NULL) {
            totalPenGer++;
            pP = nextPenumpang(pP);
        }

        cout << left << setw(40) << namaGerbong(pG) << setw(20) << idGerbong(pG)
             << totalPenGer << endl;

        totalPenumpang += totalPenGer;
        pG = nextGerbong(pG);
    }

    cout << string(70, '-') << endl;
    cout << "Total penumpang seluruh gerbong: " << totalPenumpang << endl;
}

void hitungTotalPendapatan(listGerbong G) {
    // I.S. -
    // F.S. Menampilkan total pendapatan dari tiap gerbong dan menampilkan total pendapatan dari seluruh gerbong
    adrGerbong pG = firstGerbong(G);
    int totalPendapatan = 0;

    cout << left << setw(40) << "Gerbong" << setw(20) << "ID Gerbong" << "Pendapatan" << endl;
    cout << string(70, '-') << endl;

    while (pG != NULL) {
        adrPenumpang pP = firstPenumpang(pG);
        int totalPenGer = 0;

        while (pP != NULL) {
            totalPenGer++;
            pP = nextPenumpang(pP);
        }

        int pendapatanGerbong = totalPenGer * hargaTiket(pG);
        totalPendapatan += pendapatanGerbong;

        cout << left << setw(40) << namaGerbong(pG) << setw(20) << idGerbong(pG)
             << "Rp " << pendapatanGerbong << endl;

        pG = nextGerbong(pG);
    }

    cout << string(70, '-') << endl;
    cout << "Total pendapatan seluruh gerbong: Rp " << totalPendapatan << endl;
}

bool checkEmptySeat(adrGerbong pG, adrPenumpang pP) {
    // I.S. Menerima pointer gerbong dan penumpang
    // F.S. Mengembalikan nilai True apa bila kursi penumpang kosong di gerbong dan False apabila nomor kursi sudah ada atau gerbong full
    adrPenumpang p = firstPenumpang(pG);
    int total = 0;
    char choice;

    if (nomorKursi(pP) > maxPenumpang) {
        return false;
    }

    while (p != NULL && total < maxPenumpang) {
        total = total + 1;
        if (nomorKursi(pP) == nomorKursi(p)) {
            cout << "Kursi nomor " << nomorKursi(pP) << " sudah terisi.\n";
            cout << "Tekan '0' untuk kembali ke menu utama.\n";

            cin >> choice;
            if (choice == '0') {
                return false;
            }
        }
        p = nextPenumpang(p);
    }

    if (total >= maxPenumpang) {
        cout << "Gerbong sudah penuh.\n";
        cout << "Tekan '0' untuk kembali ke menu utama.\n";

        cin >> choice;
        if (choice == '0') {
            return false;
        }
    }

    return true;
}

bool checkEmptyGerbong(listGerbong G, adrGerbong pG) {
    // I.S. Menerima list gerbong dan pointer gerbong
    // F.S. Mengembalikan nilai True apabila jumlah gerbong kurang dari maxGerbong dan False apabila gerbong sudah penuh
    adrGerbong g = firstGerbong(G);
    int total = 0;
    char choice;

    while (g != NULL && total < maxGerbong) {
        total = total + 1;
        g = nextGerbong(g);
    }

    if (total >= maxGerbong) {
        cout << "Gerbong sudah penuh.\n";
        cout << "Tekan '0' untuk kembali ke menu utama.\n";

        cin >> choice;
        if (choice == '0') {
            return false;
        }
    }

    return true;
}

void handle_menuStart() {
    // I.S. -
    // F.S. Mengoperasikan fungsionalitas menu start
    char choice;
    bool exitMenu = false;

    while (!exitMenu) {
        menuStart();
        cin >> choice;

        if (choice == '1') {
            importTemplateTrain();
            handle_menuMain();
            exitMenu = true;
        } else if (choice == '2') {
            initListGerbong(G);
            handle_menuMain();
            exitMenu = true;
        } else if (choice == '0') {
            handle_menuExit();
            exitMenu = true;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void importTemplateTrain() {
    // I.S. -
    // F.S. Melakukan input terhadap data gerbong dan penumpang

    adrGerbong pG;
    adrPenumpang pP;
    initListGerbong(G);

    struct GerbongData { int id; string nama, kelas; int harga; } gerbongData[] = {
        {1, "Gerbong_A", "Eksekutif", 500000}, {2, "Gerbong_B", "Bisnis", 350000},
        {3, "Gerbong_C", "Ekonomi", 200000}, {4, "Gerbong_D", "Ekonomi", 150000},
        {5, "Gerbong_E", "Eksekutif", 550000}, {6, "Gerbong_F", "Ekonomi", 120000},
        {7, "Gerbong_G", "Eksekutif", 600000}, {8, "Gerbong_H", "Bisnis", 400000},
        {9, "Gerbong_I", "Ekonomi", 180000}, {10, "Gerbong_J", "Eksekutif", 650000}
    };

    for (auto& g : gerbongData) {
        pG = newGerbong(pG, g.id, g.nama, g.kelas, g.harga);
        if (g.id == 1) insertGerbongDepan(G, pG);
        else insertGerbongBelakang(G, pG);
    }

    struct PenumpangData { int id; string nama; int kursi; } penumpangData[] = {
        {1, "Aprilianza_Muhammad_Yusup", 1}, {2, "Muhammad_Irgiansyah", 2}, {3, "Auliya_Marifah", 3},
        {4, "Arkanzi_Suharjanto", 4}, {5, "Bintang_Saputra", 5}, {6, "Fathan_Arya_Maulana", 6},
        {7, "Veiron_Vaya_Yarief", 7}, {8, "Nasywa_Kamila", 8}, {9, "Athila_Ramdani_Saputra", 9},
        {10, "Farraz_Raya_Abdillah", 10}, {11, "Yolanda_Rahma_Chrysti", 1}, {12, "Muhammad_Arya_Dwi_Kesuma", 2},
        {13, "Dandy_Fadilla", 3}, {14, "Velisia_Nihan_Rahmawati", 4}, {15, "Arsyad_Maulana_Ahsan", 5},
        {16, "Ahmad_Refi_Widi_Katibin", 6}, {17, "Samuel_Yohanes_Michael_Kaunang", 7}, {18, "Arsyad_Fillah", 8},
        {19, "Nevan_Nabil_Firmansyah_Har", 9}, {20, "Muhammad_Ihsan_Naufal", 10}, {21, "Fadhilla_M_Wiryasukma", 1},
        {22, "Nabila_Putri_Azhari", 2}, {23, "Muhammad_Rafif_Taufiq_Ramadhan", 3}, {24, "Arfian_Ghifari_Mahya", 4},
        {25, "Jeany_Ferliza_Nayla", 5}
    };

    adrGerbong tempG = firstGerbong(G);
    int penumpangIndex = 0;

    for (int i = 0; i < 10; ++i) {
        int penumpangPerGerbong = 10;

        for (int j = 0; j < penumpangPerGerbong; ++j) {
            if (penumpangIndex >= 25) break;

            pP = newPenumpang(pP, penumpangData[penumpangIndex].id, penumpangData[penumpangIndex].nama, penumpangData[penumpangIndex].kursi);
            insertPenumpang(tempG, pP);
            penumpangIndex++;
        }

        if (penumpangIndex >= 25) break;
        if (i < 9) tempG = nextGerbong(tempG);
    }
}

void handle_menuMain() {
    // I.S. -
    // F.S. Mengoperasikan fungsionalitas menu main
    char choice;
    bool exitMenu = false;

    while (!exitMenu) {
        menuMain();
        cin >> choice;

        if (choice == '1') {
            handle_showDetails();
        } else if (choice == '2') {
            handle_menuInsert();
        } else if (choice == '3') {
            handle_menuDelete();
        } else if (choice == '4') {
            handle_menuEdit();
        } else if (choice == '5') {
            handle_menuSearch();
        } else if (choice == '6') {
            handle_menuData();
        } else if (choice == '0') {
            handle_menuExit();
            exitMenu = true;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void handle_showDetails() {
    // I.S. -
    // F.S. display Gerbong details sampai user input 0 untuk kembali ke main menu
    char choice;

    system("cls");
    while (choice != '0') {
        showAllGerbongDetails(G);
        cout << "\nTekan 0 untuk kembali ke menu utama..." << endl;
        cin >> choice;
    }
}

void handle_menuInsert() {
    // I.S. -
    // F.S. Mengoperasikan fungsionalitas menu insert
    char choice;
    bool exitMenu = false;

    while (!exitMenu) {
        menuInsert();
        cin >> choice;

        if (choice == '1') {
            handle_addGerbong();
        } else if (choice == '2') {
            handle_addPenumpang();
        } else if (choice == '0') {
            handle_menuMain();
            exitMenu = true;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void handle_addGerbong() {
    // I.S. menerima inputan user berupa id, nama, kelas, dan harga tiket gerbong baru serta dimasukkan kedepan atau kebelakang list
    // F.S. menambahkan gerbong ke list gerbong G ke bagian depan/belakang apabila id gerbong belum ada di list gerbong
    // bila gerbong dengan id yang sama sudah ada, maka gerbong tidak jadi dimasukkan dan memberi peringatan ke user
    char choice;
    int id, harga;
    string nama, kelas;
    adrGerbong pG;

    cout << "ID Gerbong\t: ";
    cin >> id;
    cout << "Nama Gerbong\t: ";
    cin >> nama;
    cout << "Kelas Gerbong\t: ";
    cin >> kelas;
    cout << "Harga Tiket Gerbong\t: ";
    cin >> harga;

    pG = searchGerbong(G, id);
    if (pG == NULL) {
        pG = newGerbong(pG, id, nama, kelas, harga);
        bool validPlacement = false;

        while (!validPlacement) {
            cout << "Penempatan posisi gerbong baru:\n";
            cout << "1. Depan\n2. Belakang\nPilihan: ";
            cin >> choice;

            if (choice == '1') {
                insertGerbongDepan(G, pG);
                cout << "Gerbong dengan ID " << id << " berhasil ditambahkan di depan." << endl;
                validPlacement = true;
            } else if (choice == '2') {
                insertGerbongBelakang(G, pG);
                cout << "Gerbong dengan ID " << id << " berhasil ditambahkan di belakang." << endl;
                validPlacement = true;
            } else {
                cout << "Pilihan tidak valid!" << endl;
            }
        }
    } else {
        cout << "ID gerbong sudah ada." << endl;
    }

    do {
        cout << "\nTekan 0 untuk kembali: ";
        cin >> choice;
        if (choice != '0') {
            cout << "Input invalid. Harap masukkan 0 untuk kembali." << endl;
        }
    } while (choice != '0');
}

void handle_addPenumpang() {
    // I.S. menerima inputan user berupa id gerbong
    // Bila input id gerbong valid maka user dapat input id, nama, dan kursi
    // F.S. data penumpang baru dimasukkan ke gerbong yang dipilih
    int idGerbong, id, kursi;
    char choice;
    string nama;
    adrGerbong pG;
    adrPenumpang pP;

    cout << "ID Gerbong: ";
    cin >> idGerbong;

    pG = searchGerbong(G, idGerbong);
    if (pG != NULL) {
        cout << "Gerbong dengan ID: " << idGerbong << " ditemukan." << endl;
        cout << "ID Penumpang\t: ";
        cin >> id;
        cout << "Nama Penumpang\t: ";
        cin >> nama;
        cout << "Nomor Kursi Penumpang\t: ";
        cin >> kursi;

        if (searchPenumpang(G, id) == NULL) {
            pP = newPenumpang(pP, id, nama, kursi);
            insertPenumpang(pG, pP);
            cout << "Penumpang baru berhasil ditambahkan ke gerbong dengan ID " << idGerbong << "." << endl;
        } else {
            cout << "ID penumpang sudah ada." << endl;
        }
    } else {
        cout << "ID gerbong tidak ditemukan." << endl;
    }

    do {
        cout << "\nTekan 0 untuk kembali: ";
        cin >> choice;
        if (choice != '0') {
            cout << "Input invalid. Harap masukkan 0 untuk kembali." << endl;
        }
    } while (choice != '0');
}

void handle_menuDelete() {
    // I.S. -
    // F.S. Mengoperasikan fungsionalitas menu delete
    char choice;
    bool exitMenu = false;

    while (!exitMenu) {
        menuDelete();
        cin >> choice;

        if (choice == '1') {
            handle_deleteGerbong();
        } else if (choice == '2') {
            handle_deletePenumpang();
        } else if (choice == '0') {
            handle_menuMain();
            exitMenu = true;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void handle_deleteGerbong() {
    // I.S. Meminta id gerbong yang ingin di delete oleh user
    // F.S. Mencari gerbong tersebut dari list gerbong
    // apabila ditemukan maka akan meminta konfirmasi user untuk melakukan delete gerbong
    int id;
    char choice;
    adrGerbong pG;

    cout << "ID Gerbong\t: ";
    cin >> id;

    pG = searchGerbong(G, id);
    if (pG != NULL) {
        cout << "Apakah anda yakin ingin menghapus gerbong:" << endl;
        cout << string(84, '=') << endl;
        cout << left << setw(12) << "ID Gerbong"
             << setw(30) << "Nama Gerbong"
             << setw(30) << "Kelas Gerbong"
             << setw(30) << "Harga Tiket" << endl;
        cout << string(84, '=') << endl;
        showGerbong(pG);
        cout << string(84, '-') << endl;

        cout << "1. Ya" << endl;
        cout << "2. Tidak" << endl;
        cout << "Pilihan: ";
        cin >> choice;

        if (choice == '1') {
            deleteGerbong(G, id);
            cout << "Gerbong dengan ID " << id << " berhasil dihapus." << endl;
        } else {
            cout << "Penghapusan gerbong dibatalkan." << endl;
        }
    } else {
        cout << "Gerbong dengan ID " << id << " tidak ditemukan." << endl;
    }

    do {
        cout << "\nTekan 0 untuk kembali: ";
        cin >> choice;
        if (choice != '0') {
            cout << "Input invalid. Harap masukkan 0 untuk kembali." << endl;
        }
    } while (choice != '0');
}

void handle_deletePenumpang() {
    // I.S. Meminta id penumpang yang ingin di delete oleh user
    // F.S. Mencari penumpang tersebut dari seluruh gerbong
    // apabila ditemukan maka akan meminta konfirmasi user untuk melakukan delete penumpang
    int id;
    char choice;
    adrGerbong pG;
    adrPenumpang pP;

    cout << "ID Penumpang\t: ";
    cin >> id;

    pG = searchGerbongPenumpang(G, id);
    pP = searchPenumpang(G, id);
    if (pG != NULL) {
        cout << "Apakah anda yakin ingin menghapus penumpang:" << endl;
        cout << left << setw(16) << "ID Penumpang"
             << setw(32) << "Nama Penumpang"
             << setw(12) << "Nomor Kursi" << endl;
        cout << string(60, '=') << endl;
        showPenumpang(pP);
        cout << string(60, '-') << endl;

        cout << "1. Ya" << endl;
        cout << "2. Tidak" << endl;
        cout << "Pilihan: ";
        cin >> choice;

        if (choice == '1') {
            deletePenumpang(pG, id);
        } else {
            cout << "Penghapusan penumpang dibatalkan." << endl;
        }
    } else {
        cout << "Penumpang dengan ID " << id << " tidak ditemukan." << endl;
    }

    do {
        cout << "\nTekan 0 untuk kembali: ";
        cin >> choice;
        if (choice != '0') {
            cout << "Input invalid. Harap masukkan 0 untuk kembali." << endl;
        }
    } while (choice != '0');
}

void handle_menuEdit() {
    // I.S. -
    // F.S. Mengoperasikan fungsionalitas menu delete
    char choice;
    bool exitMenu = false;

    while (!exitMenu) {
        menuEdit();
        cin >> choice;

        if (choice == '1') {
            handle_editGerbong();
        } else if (choice == '2') {
            handle_editPenumpang();
        } else if (choice == '0') {
            handle_menuMain();
            exitMenu = true;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }

    do {
        cout << "\nTekan 0 untuk kembali: ";
        cin >> choice;
        if (choice != '0') {
            cout << "Input invalid. Harap masukkan 0 untuk kembali." << endl;
        }
    } while (choice != '0');
}

void handle_editGerbong() {
    // I.S. Meminta user mid gerbong yang ingin di edit oleh user
    // F.S. Bila ditemukan, meminta user seluruh informasi gerbong
    // informasi baru ini akan menggantikan informasi lama gerbong
    int id, harga;
    char choice;
    string nama, kelas;
    adrGerbong pG;

    cout << "ID Gerbong\t: ";
    cin >> id;

    pG = searchGerbong(G, id);
    if (pG != NULL) {
        cout << string(84, '=') << endl;
        cout << left << setw(12) << "ID Gerbong"
             << setw(30) << "Nama Gerbong"
             << setw(30) << "Kelas Gerbong"
             << setw(30) << "Harga Tiket" << endl;
        cout << string(84, '=') << endl;
        showGerbong(pG);
        cout << string(84, '-') << endl;
        cout << "Ubah Nama Gerbong Menjadi\t: ";
        cin >> nama;
        cout << "Ubah Kelas Gerbong Menjadi\t: ";
        cin >> kelas;
        cout << "Harga Tiket Gerbong Menjadi\t: ";
        cin >> harga;

        alterGerbong(G, id, nama, kelas, harga);

        cout << "Gerbong dengan ID: " << id << ", berhasil di ubah." << endl;
    } else {
        cout << "Gerbong dengan ID " << id << " tidak ditemukan." << endl;
    }

    do {
        cout << "\nTekan 0 untuk kembali: ";
        cin >> choice;
        if (choice != '0') {
            cout << "Input invalid. Harap masukkan 0 untuk kembali." << endl;
        }
    } while (choice != '0');
}

void handle_editPenumpang() {
    // I.S. Menerima id penumpang yang ingin di edit oleh user
    // F.S. Bila ditemukan, meminta user informasi baru mengenai user tersebut
    // Informasi baru ini akan menggantikan informasi lama penumpang
    int id, kursi;
    char choice;
    string nama;
    adrPenumpang pP;

    cout << "ID Penumpang\t: ";
    cin >> id;

    pP = searchPenumpang(G, id);
    if (pP != NULL) {
        cout << string(60, '=') << endl;
        cout << left << setw(16) << "ID Penumpang"
             << setw(32) << "Nama Penumpang"
             << setw(12) << "Nomor Kursi" << endl;
        cout << string(60, '=') << endl;
        showPenumpang(pP);
        cout << string(60, '-') << endl;
        cout << "Ubah Nama Penumpang Menjadi\t: ";
        cin >> nama;
        cout << "Ubah Kursi Penumpang Menjadi\t: ";
        cin >> kursi;

        alterPenumpang(G, id, nama, kursi);

        cout << "Penumpang dengan ID: " << id << ", berhasil di ubah." << endl;
    } else {
        cout << "Penumpang dengan ID " << id << " tidak ditemukan." << endl;
    }

    do {
        cout << "\nTekan 0 untuk kembali: ";
        cin >> choice;
        if (choice != '0') {
            cout << "Input invalid. Harap masukkan 0 untuk kembali." << endl;
        }
    } while (choice != '0');
}

void handle_menuSearch() {
    // I.S. -
    // F.S. Mengoperasikan fungsionalitas menu search
    char choice;
    bool exitMenu = false;

    while (!exitMenu) {
        menuSearch();
        cin >> choice;

        if (choice == '1') {
            handle_searchGerbong();
        } else if (choice == '2') {
            handle_searchPenumpang();
        } else if (choice == '0') {
            handle_menuMain();
            exitMenu = true;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void handle_searchGerbong() {
    // I.S. Meminta id gerbong yang ingin dicari
    // F.S. Mengembalikan informasi mengenai gerbong yang dicari
    // Apabila tidak ditemukan maka akan menampilkan pesan
    int id;
    char choice;
    adrGerbong pG;

    cout << "ID Gerbong\t: ";
    cin >> id;
    pG = searchGerbong(G, id);

    if (pG != NULL) {
        cout << string(84, '=') << endl;
        cout << left << setw(12) << "ID Gerbong"
             << setw(30) << "Nama Gerbong"
             << setw(30) << "Kelas Gerbong"
             << setw(30) << "Harga Tiket" << endl;
        cout << string(84, '=') << endl;
        showGerbong(pG);
        cout << string(84, '-') << endl;
    } else {
        cout << "Gerbong tidak ditemukan" << endl;
    }

    do {
        cout << "\nTekan 0 untuk kembali: ";
        cin >> choice;
        if (choice != '0') {
            cout << "Input invalid. Harap masukkan 0 untuk kembali." << endl;
        }
    } while (choice != '0');
}

void handle_searchPenumpang() {
    // I.S. Menerima id penumpang yang ingin di cari
    // F.S. Mengembalikan informasi penumpang dengan id yang di cari
    // Apabila tidak ditemukan maka akan menampilkan pesan
    int id;
    char choice;
    adrPenumpang pP;

    cout << "ID Penumpang\t: ";
    cin >> id;
    pP = searchPenumpang(G, id);

    if (pP != NULL) {
        cout << string(60, '=') << endl;
        cout << left << setw(16) << "ID Penumpang"
             << setw(32) << "Nama Penumpang"
             << setw(12) << "Nomor Kursi" << endl;
        cout << string(60, '=') << endl;
        showPenumpang(pP);
        cout << string(60, '-') << endl;
    } else {
        cout << "Penumpang tidak ditemukan" << endl;
    }

    do {
        cout << "\nTekan 0 untuk kembali: ";
        cin >> choice;
        if (choice != '0') {
            cout << "Input invalid. Harap masukkan 0 untuk kembali." << endl;
        }
    } while (choice != '0');
}

void handle_menuData() {
    // I.S. -
    // F.S. Mengoperasikan fungsionalitas menu search
    char choice;
    bool exitMenu = false;

    while (!exitMenu) {
        menuData();
        cin >> choice;

        if (choice == '1') {
            hitungTotalPenumpang(G);
        } else if (choice == '2') {
            hitungTotalPendapatan(G);
        } else if (choice == '0') {
            handle_menuMain();
            exitMenu = true;
            break;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }

        while (!exitMenu) {
            cout << "\nTekan 0 untuk kembali: ";
            cin >> choice;
            if (choice == '0') {
                exitMenu = true;
            } else {
                cout << "Input invalid. Harap masukkan 0 untuk kembali." << endl;
            }
        }
    }
}

void handle_menuExit() {
    // I.S. -
    // F.S. Mengoperasikan fungsionalitas menu exit
    char choice;

    while (true) {
        menuExit();
        cin >> choice;
        switch (choice) {
            case '1':
                exit(0);
            case '2':
                return;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void menuStart() {
    // I.S. -
    // F.S. menampilkan menu start
    system("cls");
    cout << "\t\t\t                                             ______\n";
    cout << "\t\t\t                                          .-\"\"\"\".._'.       _,##\n";
    cout << "\t\t\t                                   _..__ |.-\"\"\"-.|  |   _,##'`-._\n";
    cout << "\t\t\t                                  (_____)||_____||  |_,##'`-._,##'`\n";
    cout << "\t\t\t                                  _|   |.;-\"\"\"-.  |  |#'`-._,##'`\n";
    cout << "\t\t\t                               _.;_ `--' `\\    \\ |.'`\\._,##'`\n";
    cout << "\t\t\t                              /.-.\\ `\\     |.-\";.`_, |##'`\n";
    cout << "\t\t\t                              |\\__/   | _..;__  |'-' /\n";
    cout << "\t\t\t                              '.____.'_.-`)\\--' /'-'`\n";
    cout << "\t\t\t                               //||\\\\(_.-'_,'-'`\n";
    cout << "\t\t\t                             (`-...-')_,##'`\n";
    cout << "\t\t\t                          _,##`-..,-;##`\n";
    cout << "\t\t\t                       _,##'`-._,##'`\n";
    cout << "\t\t\t                    _,##'`-._,##'`\n";
    cout << "\t\t\t                      `-._,##'\n";
    cout << string(148, '=') << endl;
    cout << "--------------------------------------------------------------- PILIH KERETA -----------------------------------------------------------------------" << endl;
    cout << string(148, '=') << endl;
    cout << "   1. Kereta Template            " << endl;
    cout << "   2. Kereta Kosong              " << endl;
    cout << "   0. Exit                       " << endl;
    cout << string(148, '=') << endl;
}

void menuMain() {
    // I.S. -
    // F.S. menampilkan menu main
    system("cls");
    cout << string(148, '=') << endl;
    cout << "------------------------------------------------------- SISTEM INFORMASI GERBONG -------------------------------------------------------------------" << endl;
    cout << string(148, '=') << endl;
    showAllGerbong(G);
    cout << string(148, '=') << endl;
    cout << "   1. Tampilkan Detail Gerbong   " << endl;
    cout << "   2. Tambah Gerbong / Penumpang " << endl;
    cout << "   3. Hapus Gerbong / Penumpang  " << endl;
    cout << "   4. Ubah Gerbong / Penumpang   " << endl;
    cout << "   5. Cari Gerbong / Penumpang   " << endl;
    cout << "   6. Tampilkan Data Gerbong     " << endl;
    cout << "   0. Exit                       " << endl;
    cout << string(148, '=') << endl;
}

void menuInsert() {
    // I.S. -
    // F.S. menampilkan menu insert
    system("cls");
    cout << string(148, '=') << endl;
    cout << "------------------------------------------------------------- TAMBAHKAN DATA -----------------------------------------------------------------------" << endl;
    cout << string(148, '=') << endl;
    cout << "   1. Tambahkan Gerbong Baru     " << endl;
    cout << "   2. Tambahkan Penumpang Baru   " << endl;
    cout << "   0. Kembali ke Menu Utama      " << endl;
    cout << string(148, '=') << endl;
}

void menuDelete() {
    // I.S. -
    // F.S. menampilkan menu delete
    system("cls");
    cout << string(148, '=') << endl;
    cout << "---------------------------------------------------------------- HAPUS DATA ------------------------------------------------------------------------" << endl;
    cout << string(148, '=') << endl;
    cout << "   1. Hapus Gerbong              " << endl;
    cout << "   2. Hapus Penumpang            " << endl;
    cout << "   0. Kembali ke Menu Utama      " << endl;
    cout << string(148, '=') << endl;
}

void menuEdit() {
    // I.S. -
    // F.S. menampilkan menu edit
    system("cls");
    cout << string(148, '=') << endl;
    cout << "---------------------------------------------------------------- EDIT DATA -------------------------------------------------------------------------" << endl;
    cout << string(148, '=') << endl;
    cout << "   1. Edit Gerbong               " << endl;
    cout << "   2. Edit Penumpang             " << endl;
    cout << "   0. Kembali ke Menu Utama      " << endl;
    cout << string(148, '=') << endl;
}

void menuSearch() {
    // I.S. -
    // F.S. menampilkan menu search
    system("cls");
    cout << string(148, '=') << endl;
    cout << "---------------------------------------------------------------- CARI DATA -------------------------------------------------------------------------" << endl;
    cout << string(148, '=') << endl;
    cout << "   1. Cari Gerbong               " << endl;
    cout << "   2. Cari Penumpang             " << endl;
    cout << "   0. Kembali ke Menu Utama      " << endl;
    cout << string(148, '=') << endl;
}

void menuData() {
    // I.S. -
    // F.S. menampilkan menu data
    system("cls");
    cout << string(148, '=') << endl;
    cout << "------------------------------------------------------------- TAMPILKAN DATA -----------------------------------------------------------------------" << endl;
    cout << string(148, '=') << endl;
    cout << "   1. Data Jumlah Penumpang      " << endl;
    cout << "   2. Data Total Penghasilan     " << endl;
    cout << "   0. Kembali ke Menu Utama      " << endl;
    cout << string(148, '=') << endl;
}

void menuExit() {
    // I.S. -
    // F.S. menampilkan menu exit
    system("cls");
    cout << string(148, '=') << endl;
    cout << "------------------------------------------------------------------- EXIT ---------------------------------------------------------------------------" << endl;
    cout << string(148, '=') << endl;
    cout << "   Apakah Anda ingin keluar?     " << endl;
    cout << string(148, '=') << endl;
    cout << "   1. Ya                         " << endl;
    cout << "   2. Tidak                      " << endl;
    cout << string(148, '=') << endl;
}
