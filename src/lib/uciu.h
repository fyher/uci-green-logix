#define FFI_LIB "lib-b4a.so"

#define FFI_LIB "lib-b4a.so"

#ifndef UCIU_H
#define UCIU_H

typedef struct FieldUCI FieldUCI;
struct FieldUCI
{
        char *Value;
        struct FieldUCI *Next;
};
typedef FieldUCI *ListFieldUCI;

typedef struct FieldCapteur FieldCapteur;
struct FieldCapteur
{
        char *Type ;                    //au sens Sensor dans le config.yaml
        int Index ;                             //sa position/index (3eme valeur dans les list des uci)
        char *Value;                    //au sens UUID
        long Lastseen ;                 //nb de seconde depuis sa derniere mise à jour
        struct FieldCapteur *Next;
};
typedef FieldCapteur *ListFieldCapteur;

typedef struct FieldSensor FieldSensor;
struct FieldSensor
{
        char *Type;                     //au sens Sensor dans le config.yaml
        char *Uuid;                     //au sens UUID
        char *Parent ;                  //uuid du parent
        int Archived ;                          //1 on stocke les valeurs en historique
        int Up ;                        //1=yes 0=je le vois pas mais il est connu en uci
        ListFieldCapteur Capteurs ;     //liste chainée des capteurs le composant
        struct FieldSensor *Next;
};
typedef FieldSensor *ListFieldSensor;

typedef char Value_t[255];

int uciGet_Int(char *);
int uciGet_String(char*, char*);
ListFieldUCI uciGet_List(char *);
ListFieldUCI ajouteFieldUCI(ListFieldUCI, char *);
ListFieldUCI effaceListUCI(ListFieldUCI);
void afficheListUCI(ListFieldUCI);
int nbFieldUCI(ListFieldUCI);
void uciReadModule(void);
ListFieldSensor uciReadSensor(ListFieldSensor);
int uciCommitModule(char *);
int uciDropList(char *, char *);
int uciDeleteList(char *, char *, char *);
int uciAddList(char *, char *, char *);
int uciDeleteOption(char *, char *);
int uciDeleteObjet(char *);
int uciAddModule(char *, char *);
int uciAddSensor(char *,char *);
int uciSetOption(char *, char *, char *);
int uciAddOption(char *, char *, char *);
ListFieldUCI uciGetModule_List(char *, char *);
int uciGetModule_String(char *, char *, char *);
int uciGetModule_Int(char *, char *);
ListFieldUCI uciGetListe(char *);
int uciExisteModule(char *);
int uciExisteSensor(ListFieldSensor, char *);
int isArchivedSensor(char *);
int setArchivedSensor(char *);
int unsetArchivedSensor(char *);
int isUpSensor(char *);
long getValuesCapteur(char *,char *, int, char *);
int setOffsetCapteur(char *, char *, int, char *);
char* getOffsetCapteur(char *, char *, int);
int memDelSensorListe(ListFieldSensor);

#endif

