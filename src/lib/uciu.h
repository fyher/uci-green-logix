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
typedef  char value_t[100];

int uciget_int(char *);
int uciget_string(char*, char*);
ListFieldUCI AjouteFieldUCI(ListFieldUCI, char *);
ListFieldUCI EffaceListUCI(ListFieldUCI);
void AfficheListUCI(ListFieldUCI);
int NbFieldUCI(ListFieldUCI);
int NbSensor(ListFieldSensor);
int NbCapteur(ListFieldCapteur,char *);
ListFieldUCI uciget_list(char *);
int uciCommitModule(char *);
int uciDropList(char , char );
int uciDeleteList(char , char , char *);
int uciAddList(char , char , char *);
int uciDeleteOption(char , char );
int uciDeleteModule(char *);
int uciDeleteSensor(char *uuid);
int uciAddModule(char , char );
int uciAddSensor(char ,char );

int uciSetOption(char , char , char *);
int uciAddOption(char , char , char *);
ListFieldUCI uciGetModule_List(char , char );
int uciGetModule_String(char , char , char *);
int uciGetModule_Int(char , char );
void RemoveAllChars(char* , char);
ListFieldUCI uciGetListe(char *);
void UciReadModule(void);
int uciModuleExiste(char *);
int uciSensorExiste(char *);
int isArchived(char *);
int setArchived(char *);
int unsetArchived(char *);
int isUp(char *);
long getValues(char ,char , int, char *);
int setOffset(char , char , int, char *);
char getOffset(char , char *, int);
ListFieldCapteur getCapteurs(char *);

#endif
