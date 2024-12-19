#ifndef TRAIN_H_INCLUDED
#define TRAIN_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

#define firstGerbong(L) L.firstGerbong
#define lastGerbong(L) L.lastGerbong

#define idGerbong(pG) pG->idGerbong
#define namaGerbong(pG) pG->namaGerbong
#define kelasGerbong(pG) pG->kelasGerbong
#define hargaTiket(pG) pG->hargaTiket
#define nextGerbong(pG) pG->nextGerbong
#define prevGerbong(pG) pG->prevGerbong
#define firstPenumpang(pG) pG->firstPenumpang

#define idPenumpang(pP) pP->idPenumpang
#define namaPenumpang(pP) pP->namaPenumpang
#define nomorKursi(pP) pP->nomorKursi
#define nextPenumpang(pP) pP->nextPenumpang

typedef struct gerbong* adrGerbong;
typedef struct penumpang* adrPenumpang;

struct listGerbong {
    adrGerbong firstGerbong;
    adrGerbong lastGerbong;
};

struct gerbong {
    int idGerbong;
    string namaGerbong;
    string kelasGerbong;
    int hargaTiket;
    adrGerbong nextGerbong;
    adrGerbong prevGerbong;
    adrPenumpang firstPenumpang;
};

struct penumpang {
    int idPenumpang;
    string namaPenumpang;
    int nomorKursi;
    adrPenumpang nextPenumpang;
};

// Gerbong dan Penumpang
void initListGerbong(listGerbong &G);

adrGerbong newGerbong(adrGerbong pG, int id, string nama, string kelas, int harga);
adrPenumpang newPenumpang(adrPenumpang pP, int id, string nama, int kursi);

void insertGerbongDepan(listGerbong &G, adrGerbong &pG);
void insertGerbongBelakang(listGerbong &G, adrGerbong &pG);
void insertPenumpang(adrGerbong &pG, adrPenumpang &pP);

void deleteGerbong(listGerbong &G, int id);
void deleteLastPenumpang(adrGerbong &pG);
void deletePenumpang(adrGerbong &pG, int id);

adrGerbong searchGerbong(listGerbong G, int id);
adrPenumpang searchPrevPenumpang(listGerbong G, int id);
adrGerbong searchGerbong(listGerbong G, int id);
adrGerbong searchGerbongPenumpang(listGerbong G, int id);
adrPenumpang searchPenumpangSpesifik(adrGerbong pG, int id);

void alterGerbong(listGerbong &G, int id, string nama, string kelas, int harga);
void alterPenumpang(listGerbong &G, int id, string nama, int kursi);

void showAllGerbong(listGerbong G);
void showAllGerbongDetails(listGerbong G);
void showGerbong(adrGerbong pG);
void showPenumpang(adrPenumpang pP);

void hitungTotalPenumpang(listGerbong G);
void hitungTotalPendapatan(listGerbong G);

bool checkEmptySeat(adrGerbong pG, adrPenumpang pP);
bool checkEmptyGerbong(listGerbong G, adrGerbong pG);

void importTemplateTrain();

void handle_menuStart();
void handle_menuMain();
void handle_showDetails();
void handle_menuInsert();
void handle_addGerbong();
void handle_addPenumpang();
void handle_menuDelete();
void handle_deleteGerbong();
void handle_deletePenumpang();
void handle_menuEdit();
void handle_editGerbong();
void handle_editPenumpang();
void handle_menuSearch();
void handle_searchGerbong();
void handle_searchPenumpang();
void handle_menuExit();
void handle_menuData();

void menuStart();
void menuMain();
void menuInsert();
void menuDelete();
void menuEdit();
void menuSearch();
void menuData();
void menuExit();

#endif // TRAIN_H_INCLUDED
