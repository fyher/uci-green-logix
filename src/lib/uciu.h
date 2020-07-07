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
ListFieldUCI uciget_list(char *);
int uciCommitModule(char *);
int uciDropList(char *, char *);
int uciDeleteList(char *, char *, char *);
int uciAddList(char *, char *, char *);
int uciDeleteOption(char *, char *);
int uciDeleteModule(char *);
int uciAddModule(char *, char *);
int uciSetOption(char *, char *, char *);
int uciAddOption(char *, char *, char *);
ListFieldUCI uciGetModule_List(char *, char *);
int uciGetModule_String(char *, char *, char *);
int uciGetModule_Int(char *, char *);
void RemoveAllChars(char* , char);
ListFieldUCI uciGetListe(char *);
void UciReadModule(void);
int uciModuleExiste(char *);
int isDiscovered(char *);
int Discovered(char *);

#endif
