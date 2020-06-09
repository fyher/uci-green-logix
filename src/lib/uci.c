// *****************************************************************************
// ************************** System Include Files *****************************
// *****************************************************************************
#include <uci.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// *****************************************************************************
// ************************** User Include Files *******************************
// *****************************************************************************
#include "uciu.h"

// *****************************************************************************
// ************************** Defines ******************************************
// *****************************************************************************

#ifndef MAXSIZE
#define MAXSIZE 255 
#endif

//ici mettre le nom du fichier /etc/config
#ifndef CONFIG 
#define CONFIG "b4a" 
#endif

//ici mettre le nom du du type 'module'
#ifndef  MODULE
#define MODULE "module" 
#endif

// *****************************************************************************
// ************************** Variable *****************************************
// *****************************************************************************
static 	ListFieldUCI ModuleListe = NULL;

// *****************************************************************************
// ************************* Variable Externes *********************************
// *****************************************************************************

// *****************************************************************************
// ************************** Function Prototypes ******************************
// *****************************************************************************



/****************************************************************************
 * FONCTION: AjouteFieldUCI												    *
 *                                                                          *
 * But : 																	*
 *  														                *
 *  Entr�e : Rien 			    	                                        *
 *  Sortie : Rien			                             				 	*
 *  														                *
 *  Derni�me modification :  16/04/2020 par PD                              *
 *  														                *
 ****************************************************************************/
ListFieldUCI AjouteFieldUCI(ListFieldUCI Liste, char *Value)
{
FieldUCI *NewField , *Tmp;
int toto;	
	NewField = malloc(sizeof(FieldUCI));	// On alloue une structure Field 
	memset(NewField, 0, sizeof(FieldUCI));  // On inialise la structure
	NewField->Next = NULL; 					// On ajoute en fin de liste
	
	toto = strlen(Value) + 1;
	NewField->Value = malloc(strlen(Value) + 1);
	strcpy(NewField->Value, Value);
	if(!Liste)
		return NewField;		// Si la liste est vide on renvoi le 1er pointeur cad l'element
    else
	{
					// Sinon on insere en fin de liste
	    Tmp = Liste;
		while (Tmp->Next)
			Tmp = Tmp->Next;
		
		Tmp->Next = NewField;
		return Liste;
	}
}
/****************************************************************************
 * FONCTION: EffaceListUCI												    *
 *                                                                          *
 * But : 		        *
 *  														                *
 *  Entr�e : Rien 			    	                                        *
 *  Sortie : Rien			                             				 	*
 *  														                *
 *  Derni�me modification :  16/04/2020 par PD                              *
 *  														                *
 ****************************************************************************/
ListFieldUCI EffaceListUCI(ListFieldUCI liste)
{
ListFieldUCI Tmp, TmpNxt;
Tmp = liste;
	// Tant que l'on n'est pas au bout de la liste
	while(Tmp)
	{
		free(Tmp->Value);
		TmpNxt = Tmp->Next;
		free(Tmp);
		Tmp = TmpNxt;
	}
	return NULL;
}
/****************************************************************************
 * FONCTION: AfficheListUCI 											    *
 *                                                                          *
 * But : 		        *
 *  														                *
 *  Entr�e : Rien 			    	                                        *
 *  Sortie : Rien			                             				 	*
 *  														                *
 *  Derni�me modification :  16/04/2020 par PD                              *
 *  														                *
 ****************************************************************************/
void AfficheListUCI(ListFieldUCI liste)
{
ListFieldUCI Tmp;
Tmp = liste;
	
	printf("debut de lecture ----\n");
	while (Tmp) 
	{
		printf("value : %s\n", Tmp->Value);
		Tmp = Tmp->Next;
	}
	printf("fin de lecture ----\n");
}
/****************************************************************************
 * FONCTION: NbFieldUCI 												    *
 *                                                                          *
 * But : 		        *
 *  														                *
 *  Entr�e : Rien 			    	                                        *
 *  Sortie : Rien			                             				 	*
 *  														                *
 *  Derni�me modification :  16/04/2020 par PD                              *
 *  														                *
 ****************************************************************************/
int NbFieldUCI(ListFieldUCI liste)
{
int cpt = 0;
ListFieldUCI pt = liste;

	while (pt)
	{
		cpt++;
		pt = pt->Next;
	}
	return cpt;  
}
/****************************************************************************
 * FONCTION: uciget_list 												    *
 *                                                                          *
 * But : 		        *
 *  														                *
 *  Entr�e : Rien 			    	                                        *
 *  Sortie : Rien			                             				 	*
 *  														                *
 *  Derni�me modification :  16/04/2020 par PD                              *
 *  														                *
 ****************************************************************************/
ListFieldUCI uciget_list(char *path)
{
struct uci_context *c;                             
struct uci_ptr ptr;                                
struct uci_option *o;
int retour;
struct uci_element *e;                           
ListFieldUCI Liste = NULL;
int i = 0;
                                                     
	c = uci_alloc_context();                          
	if ((uci_lookup_ptr(c, &ptr, path, true) != UCI_OK) || (ptr.o == NULL))
	{
		uci_free_context(c);
		return NULL;
	} 
	if (ptr.o->type == UCI_TYPE_LIST)
	{                                       
		uci_foreach_element(&ptr.o->v.list, e)
		{
			Liste = AjouteFieldUCI(Liste, e->name);
		}                                            
	} 
	uci_free_context(c);                
	return (Liste);
}
/****************************************************************************
 * FONCTION: uciget_int 												    *
 *                                                                          *
 * But : 		        *
 *  														                *
 *  Entr�e : Rien 			    	                                        *
 *  Sortie : Rien			                             				 	*
 *  														                *
 *  Derni�me modification :  16/04/2020 par PD                              *
 *  														                *
 ****************************************************************************/
int uciget_int(char *path)
{

char buffer[80], chemin[255];
struct uci_ptr ptr;

	strcpy(chemin,path);
	struct uci_context *c = uci_alloc_context();
	if(!c) return 0;
	if ((uci_lookup_ptr(c, &ptr, chemin, true) != UCI_OK) || (ptr.o==NULL || ptr.o->v.string==NULL))
	{
		uci_free_context(c);
		return 0;
	}
	if(ptr.flags & UCI_LOOKUP_COMPLETE)
		strcpy(buffer, ptr.o->v.string);
   
	uci_free_context(c);
	return (atoi(buffer));

}
/****************************************************************************
 * FONCTION: uciget_string 												    *
 *                                                                          *
 * But : 		        *
 *  														                *
 *  Entr�e : Rien 			    	                                        *
 *  Sortie : Rien			                             				 	*
 *  														                *
 *  Derni�me modification :  16/04/2020 par PD                              *
 *  														                *
 ****************************************************************************/
int uciget_string(char *path, char*value)
{
 
char chemin[255];
struct uci_ptr ptr;

   strcpy(chemin,path);
   struct uci_context *c = uci_alloc_context();
   if(!c) return 0;
   if ((uci_lookup_ptr(c, &ptr, chemin, true) != UCI_OK) || (ptr.o==NULL || ptr.o->v.string==NULL))
   {
     uci_free_context(c);
     return 0;
   }
   if(ptr.flags & UCI_LOOKUP_COMPLETE)
      strcpy(value, ptr.o->v.string);
   
	uci_free_context(c);
   return 1;
 
}
//vire tous les ':' contenu dans un uuid
//pour standardiser le nom du module

/****************************************************************************
 * FONCTION: RemoveAllChars												    *
 *                                                                          *
 * But : Supprimer les  ':' contenu dans un uuid,pour standardiser le nom   *
 *  	 du module											                *
 *  Entr�e : Rien 			    	                                        *
 *  Sortie : Rien			                             				 	*
 *  														                *
 *  Derni�me modification :  12/05/2020 par PD                              *
 *  														                *
 ****************************************************************************/
void RemoveAllChars(char* str, char c)
{
char *pr = str, *pw = str;
	while (*pr) 
	{
		*pw = *pr++;
		pw += (*pw != c);
	}
	*pw = '\0';
}

/****************************************************************************
 * FONCTION: uciGetModule_Int											    *
 *                                                                          *
 * But : retourne un entier correspondant a l'option 'variable' du module ' *
 * uuid																		*
 *  	 du module											                *
 *  Entr�e : Rien 			    	                                        *
 *  Sortie : Rien			                             				 	*
 *  														                *
 *  Derni�me modification :  12/05/2020 par PD                              *
 *  														                *
 ****************************************************************************/
int uciGetModule_Int(char *uuid, char *variable)
{
	char buffer[80], chemin[MAXSIZE], id[80];
	struct uci_ptr ptr;
	strcpy(id, uuid);
	RemoveAllChars(id, ':');
	
	sprintf(chemin, "%s.%s.%s", CONFIG, id, variable);
	struct uci_context *c = uci_alloc_context();
	if (!c) return 0;
	if ((uci_lookup_ptr(c, &ptr, chemin, true) != UCI_OK) || (ptr.o == NULL || ptr.o->v.string == NULL)) 
	{ 
		uci_free_context(c);
		return 0;
	}
	if (ptr.flags & UCI_LOOKUP_COMPLETE)
		strcpy(buffer, ptr.o->v.string);
	uci_free_context(c);
	return (atoi(buffer));
}
/****************************************************************************
 * FONCTION: uciGetModule_String										    *
 *                                                                          *
 * But : Lire une variable du module Uuid								    *
 *  														                *
 *  Entr�e : Rien 			    	                                        *
 *  Sortie : 0 -> echec de la lecture                      				 	*
 *  		 1 -> lecture reussi							                *
 *  														                *
 *  Derni�me modification :  12/05/2020 par PD                              *
 *  														                *
 ****************************************************************************/
int uciGetModule_String(char *uuid, char *variable, char *value)
{
	char chemin[MAXSIZE], id[80];
	struct uci_ptr ptr;
	strcpy(id, uuid);
	
	RemoveAllChars(id, ':');
	sprintf(chemin, "%s.%s.%s", CONFIG, id, variable);
	struct uci_context *c = uci_alloc_context();
	if (!c) return 0;
	if ((uci_lookup_ptr(c, &ptr, chemin, true) != UCI_OK) || (ptr.o == NULL || ptr.o->v.string == NULL)) 
	{ 
		uci_free_context(c);
		return 0;
	}
	if (ptr.flags & UCI_LOOKUP_COMPLETE)
		strcpy(value, ptr.o->v.string);
	uci_free_context(c);
	return 1;
}


/****************************************************************************
 * FONCTION: uciGetModule_List											    *
 *                                                                          *
 * But : Retourner une liste  pour la list 'variable' du module 'uuid'	    *
 *  														                *
 *  Entr�e : Rien 			    	                                        *
 *  Sortie :						                      				 	*
 *  		 												                *
 *  														                *
 *  Derni�me modification :  12/05/2020 par PD                              *
 *  														                *
 ****************************************************************************/
ListFieldUCI uciGetModule_List(char *uuid, char *variable)
{
	char chemin[MAXSIZE], id[80];
	struct uci_context *c;                             
	struct uci_ptr ptr;                                
	struct uci_option *o;
	int retour;
	struct uci_element *e;                           
	ListFieldUCI liste = NULL;
	int i = 0;
	
	strcpy(id, uuid);
	RemoveAllChars(id, ':');
	sprintf(chemin, "%s.%s.%s", CONFIG, id, variable);
                                                     
	c = uci_alloc_context();                          
	if ((uci_lookup_ptr(c, &ptr, chemin, true) != UCI_OK) || (ptr.o == NULL))
	{
		uci_free_context(c);
		return 0;
	} 
	if (ptr.o->type == UCI_TYPE_LIST)
	{                                       
		uci_foreach_element(&ptr.o->v.list, e) 
		{
			liste = AjouteFieldUCI(liste, e->name);
		}                                            
	} 
	uci_free_context(c);                
	return (liste);
}

/****************************************************************************
 * FONCTION: uciAddOption												    *
 *                                                                          *
 * But : Ajouter une option (mot cle) � un module							*
 *  	 exemple : option variable 'value'					                *
 *  		 												                *
 *  Entr�e : *uuid -> Adresse du module                                     *
 *           *variable -> Nom de la variable				                *
 *  		 *value -> Valeur de la variable				                *
 *  		 												                *
 *  Sortie : 0 -> Option non cr�e		 									*
 *  		 1 -> Option cr�e								                *
 *  		 												                *
 *  Derni�me modification :  12/05/2020 par PD                              *
 *  														                *
 ****************************************************************************/
int uciAddOption(char *uuid, char *variable, char *value)
{
	char chemin[MAXSIZE], id[80];
	int ret;
	struct uci_ptr ptr;
	strcpy(id, uuid);
	RemoveAllChars(id, ':');
	
	sprintf(chemin, "%s.%s.%s", CONFIG, id, variable);
	struct uci_context *c = uci_alloc_context();
	if (!c) return 0;
	if (uci_lookup_ptr(c, &ptr, chemin, true) != UCI_OK)  
	{ 
		uci_free_context(c);
		return 0;
	}
	ptr.value = value;
	ret = uci_set(c, &ptr);
	if (ret == UCI_OK)       
		ret = uci_save(c, ptr.p); 
	uci_free_context(c); 
	if (ret == UCI_OK)
		return 1;
	else
		return 0;
}

/****************************************************************************
 * FONCTION: uciAddOption												    *
 *                                                                          *
 * But : Modifier la valeur d'une option d'un module                        * 
 *  														                *
 *  Entr�e : *uuid -> Adresse du module                                     *
 *           *variable -> Nom de la variable				                *
 *  		 *value -> Valeur de la variable				                *
 *  		 												                *
 *  Sortie : 0 -> Option non modif�e	 									*
 *  		 1 -> Option modif�e							                *
 *  		 												                *
 *  Derni�me modification :  12/05/2020 par PD                              *
 *  														                *
 ****************************************************************************/
int uciSetOption(char *uuid, char *variable, char *value)
{
	char chemin[MAXSIZE], id[80];
	int ret;
	struct uci_ptr ptr;
	strcpy(id, uuid);
	RemoveAllChars(id, ':');
	
	sprintf(chemin, "%s.%s.%s", CONFIG, id, variable);
	struct uci_context *c = uci_alloc_context();
	if (!c) return 0;
	if ((uci_lookup_ptr(c, &ptr, chemin, true) != UCI_OK)  || (ptr.o == NULL || ptr.o->v.string == NULL))
	{ 
		uci_free_context(c);
		return 0;
	}
	ptr.value = value;
	ret = uci_set(c, &ptr);
	if (ret == UCI_OK)       
		ret = uci_save(c, ptr.p); 
	uci_free_context(c); 
	if (ret == UCI_OK)
		return 1;
	else
		return 0;
}

/****************************************************************************
 * FONCTION: uciAddModule												    *
 *                                                                          *
 * But : Creer un module													*
 *       exemple : config module '*uuid'                                    *
 *                     option type '*type'					                *
 *  		 												                *
 *  Entr�e : *uuid -> Adresse du module � creer                             *
 *           *type -> Nom du type							                *
 *  		 												                *
 *  Sortie : 0 -> Module non cr�e		 									*
 *  		 1 -> Module cr�e												*
 *  		 												                *
 *  Derni�me modification :  12/05/2020 par PD                              *
 *  														                *
 ****************************************************************************/
int uciAddModule(char *uuid, char *type)
{
	char chemin[MAXSIZE], id[80];
	int ret;
	struct uci_ptr ptr;
	strcpy(id, uuid);
	
	RemoveAllChars(id, ':');
	sprintf(chemin, "%s.%s", CONFIG, id);
	struct uci_context *c = uci_alloc_context();
	if (!c) return 0;
	if (uci_lookup_ptr(c, &ptr, chemin, true) != UCI_OK)  
	{
		uci_free_context(c);
		return 0;
	}
	ptr.value = "module";
	ret = uci_set(c, &ptr);
	if (ret == UCI_OK)
		ret = uci_save(c, ptr.p);
	uci_free_context(c);
	if (ret == UCI_OK)
		return uciAddOption(uuid, "type", type);
	else
		return 0;
}

/****************************************************************************
 * FONCTION: uciDeleteModule											    *
 *                                                                          *
 * But : Supprimer un module. Attention ! le commit est fait ensortie de    *
 *       fonction														    *
 *  														                *
 *  Entr�e : *uuid -> Adresse du module a supprimer							*
 *  Sortie : 0 -> Module non supprim�	 									*
 *  		 1 -> Module supprim�											*
 *  		 												                *
 *  Derni�me modification :  12/05/2020 par PD                              *
 *  														                *
 ****************************************************************************/
int uciDeleteModule(char *uuid)
{
	char chemin[MAXSIZE], id[80];                                                                         
	int ret;                                                                                              
	struct uci_ptr ptr;                                                                                   
	strcpy(id, uuid);
	
	RemoveAllChars(id, ':');                                                                             
	sprintf(chemin, "%s.%s", CONFIG, id);                                                      
	struct uci_context *c = uci_alloc_context();                                                          
	if (!c) return 0;                                                                                     
	if (uci_lookup_ptr(c, &ptr, chemin, true) != UCI_OK) 
	{                                                                                                     
		printf("pb lookup\n");
		uci_free_context(c);                                                                                
		return 0;                                                                                           
	}                                                                                                     
	if ((uci_delete(c, &ptr) == UCI_OK) && (uci_save(c, ptr.p) == UCI_OK) && (uci_commit(c, &ptr.p, false) == UCI_OK))
	{                                                                            
		uci_free_context(c);   
		return 1;
	}
	else 
	{                                                                               
		uci_free_context(c);   
		return 0;
	}
}
/****************************************************************************
 * FONCTION: uciDeleteOption											    *
 *                                                                          *
 * But : Supprimer une option d'un module									* 
 *  														                *
 *  Entr�e : *uuid -> Adresse du module			                            *
 *           *variable -> Nom de la variable � supprimer	                *
 *  		 												                *
 *  Sortie : 0 -> Option non supprim�e	 									*
 *  		 1 -> Option supprim�e											*
 *  		 												                *
 *  Derni�me modification :  12/05/2020 par PD                              *
 *  														                *
 ****************************************************************************/
int uciDeleteOption(char *uuid, char *variable)                        
{                                                          
	char chemin[MAXSIZE], id[80];                                       
	int ret;                                                
	struct uci_ptr ptr;                                     
	strcpy(id, uuid);
	
	RemoveAllChars(id, ':');
	sprintf(chemin, "%s.%s.%s", CONFIG, id, variable);
	struct uci_context *c = uci_alloc_context();            
	if (!c) return 0;                                       
	if ((uci_lookup_ptr(c, &ptr, chemin, true) != UCI_OK) || (ptr.o == NULL || ptr.o->v.string == NULL))             
	{ 
		uci_free_context(c);                                   
		return 0;                                              
	}                                                        
	ret = uci_delete(c, &ptr);                                  
	if (ret == UCI_OK)                                       
		ret = uci_save(c, ptr.p);                              
	uci_free_context(c);                                     
	if (ret == UCI_OK)                                       
		return 1;                                              
	else                                                     
		return 0;                                              
} 


/****************************************************************************
 * FONCTION: uciAddList													    *
 *                                                                          *
 * But : Ajoute une entree sur la liste 'variable' dans le module 'uuid'    * 
 * avec la valeur 'value'													* 
 *  														                *
 *  Entr�e :  			    												*
 *  Sortie :						                      				 	*
 *  		 												                *
 *  Derni�me modification :  12/05/2020 par PD                              *
 *  														                *
 ****************************************************************************/
int uciAddList(char *uuid, char *variable, char *value)  
{                                                          
	char chemin[MAXSIZE], id[80];                           
	int ret;                                                
	struct uci_ptr ptr;
	
	strcpy(id, uuid);                                        
	RemoveAllChars(id, ':');                               
	sprintf(chemin, "%s.%s.%s", CONFIG, id, variable);          
	struct uci_context *c = uci_alloc_context();            
	if (!c) return 0;                                       
	if (uci_lookup_ptr(c, &ptr, chemin, true) != UCI_OK)    
	{                                                       
		uci_free_context(c);                                  
		return 0;                                             
	}                                                       
	ptr.value = value;                                        
	ret = uci_add_list(c, &ptr);                                 
	if (ret == UCI_OK)                                      
		ret = uci_save(c, ptr.p);                             
	uci_free_context(c);                                    
	if (ret == UCI_OK)                                      
		return 1;                                             
	else                                                    
		return 0;                                             
}          

/****************************************************************************
 * FONCTION: uciDeleteList												    *
 *                                                                          *
 * But : Efface l'element de la liste 'variable' dans le module 'uuid' pour *
 * la valeur 'value'														*
 *  														                *
 *  Entr�e :  			    												*
 *  Sortie :						                      				 	*
 *  		 												                *
 *  Derni�me modification :  12/05/2020 par PD                              *
 *  														                *
 ****************************************************************************/
int uciDeleteList(char *uuid, char *variable, char *value)     
{                                                           
	char chemin[MAXSIZE], id[80];
	int ret;                                    
	struct uci_ptr ptr;                                 
	strcpy(id, uuid);                                    
	RemoveAllChars(id, ':');                           
	sprintf(chemin, "%s.%s.%s", CONFIG, id, variable);      
	struct uci_context *c = uci_alloc_context();        
	if (!c) return 0;                                   
	if (uci_lookup_ptr(c, &ptr, chemin, true) != UCI_OK)
	{  
		uci_free_context(c);                              
		return 0;                                         
	}                                                   
	ptr.value = value;                                        
	ret = uci_del_list(c, &ptr);                        
	if (ret == UCI_OK)                                  
		ret = uci_save(c, ptr.p);                         
	uci_free_context(c);                                
	if (ret == UCI_OK)                                  
		return 1;                                         
	else                                                
		return 0;                                         
}                    


/****************************************************************************
 * FONCTION: uciDropList												    *
 *                                                                          *
 * But : Efface toute la liste dans le module 'uuid' pour le nom 'variable' *
 *  														                *
 *  Entr�e :  			    												*
 *  Sortie :						                      				 	*
 *  		 												                *
 *  Derni�me modification :  12/05/2020 par PD                              *
 *  														                *
 ****************************************************************************/
int uciDropList(char *uuid, char *variable)
{
	char chemin[MAXSIZE], id[80];
	int ret;      
	struct uci_ptr ptr;          
	strcpy(id, uuid);
	RemoveAllChars(id, ':');
	sprintf(chemin, "%s.%s.%s", CONFIG, id, variable);
	struct uci_context *c = uci_alloc_context();
	if (!c) return 0;
	if (uci_lookup_ptr(c, &ptr, chemin, true) != UCI_OK)  
	{    
		uci_free_context(c);      
		return 0;                
	}          
	ret = uci_delete(c, &ptr);
	if (ret == UCI_OK)        
		ret = uci_save(c, ptr.p);
	uci_free_context(c);                   
	if (ret == UCI_OK)         
		return 1;       
	else             
		return 0;           
}             

/****************************************************************************
 * FONCTION: uciGetModule												    *
 *                                                                          *
 * But : retourne la liste d'objet present dans un fichier UCI				*
 *  														                *
 *  Entr�e : Request -> objet recherch�										*
 *  Sortie : ListFieldUCI -> Liste chain� des module existant			 	*
 *  		 												                *
 *  Derni�me modification :  13/05/2020 par PD                              *
 *  						 13/05/2020 par OL				                *
 ****************************************************************************/
ListFieldUCI uciGetListe(char *Request)
{
struct uci_ptr ptr;
ListFieldUCI liste = NULL;
struct uci_element *e;
struct uci_context *c = uci_alloc_context();

	if (!c) return 0;   
	if ((uci_lookup_ptr(c, &ptr, CONFIG, true) != UCI_OK) || (ptr.p == NULL)) 
	{
		uci_free_context(c);                                                
		return 0;                                                           
	}                  
	uci_foreach_element(&(ptr.p)->sections, e) 
	{     
		if (!strcmp(uci_to_section(e)->type, Request))
			liste = AjouteFieldUCI(liste, e->name);
	}                                                        
	uci_free_context(c);                                                
	return liste; 
}
/****************************************************************************
 * FONCTION: uciObjExiste													*
 *                                                                          *
 * But : Derterminer si un element exite dans une liste						*
 *  														                *
 *  Entr�e : SearchObj -> Objet � recherch�					                *
 *  														                *
 *  Sortie : 0 -> objet existe			 									*
 *  		 1 -> l'objet n'existe pas						                *
 *  														                *
 *  Derni�me modification :  13/05/2020 par OL				                *
 ****************************************************************************/
int uciModuleExiste(char *SearchObj)
{
ListFieldUCI Tmp;

	Tmp = ModuleListe;
	while (Tmp) 
	{
		if (!strcmp(Tmp->Value, SearchObj))
			return (1);
		Tmp = Tmp->Next;
	}
	return(0);
}

/****************************************************************************
 * FONCTION: uciCommitModule											    *
 *                                                                          *
 * But : Commit les modifications sur le module 'uuid'. Cette fonction est  * 
 * � appeller quand on a fini de modifier un module. Ceci permet de ne pas  *
 * se retrouver avec un module incomplet qui pourrait etre lu par un autre  *
 * processus															    *
 *  														                *
 *  Entr�e : uuid ->  Adresse du module � sauvegarder						*
 *  Sortie : 0 -> Echec de sauvegarde                     				 	*
 *  		 1 -> Sauvegarde reussi							                *
  *  														                *
 *  Derni�me modification :  12/05/2020 par PD                              *
 *  														                *
 ****************************************************************************/
int uciCommitModule(char *uuid)
{                                                           
	char chemin[MAXSIZE], id[80];                                        
	int ret;                                                 
	struct uci_ptr ptr;                                      
	strcpy(id, uuid);
	RemoveAllChars(id, ':');
	sprintf(chemin, "%s.%s", CONFIG, id);
	struct uci_context *c = uci_alloc_context();             
	if (!c) return 0;                                        
	if (uci_lookup_ptr(c, &ptr, chemin, true) != UCI_OK) 
	{   
		uci_free_context(c);                                   
		return 0;                                              
	}                                                        
	ret = uci_commit(c, &ptr.p, false);                              
	uci_free_context(c);                                     
	if (ret == UCI_OK)                                       
		return 1;                                              
	else                                                     
		return 0;                                              
}
/****************************************************************************
 * FONCTION:  UciReadModule													*
 *                                                                          *
 * But : Creer la liste des modules exitant									*
 *  														                *
 *  Entr�e : Rien															*
 *  Sortie : Rien															*
 *  														                *
 *  Derni�me modification :  13/05/2020 par OL                              *
 *  														                *
 ****************************************************************************/
void UciReadModule(void)
{
	ModuleListe =  uciGetListe("module");
}

void TestUci(void)
{
	int i = 0;
	char Test[50];
	ListFieldUCI Liste = NULL;
	//uciAddList("300102", "DragonFly", "11:22:33:44:55:66,0,on");
//	i = uciCommitModule("300102");
//	strcpy(Test,"b4a.11:22:33:44:55:66.DragonFly");
	//strcpy(Path, "b4a");
	
//	i=uciDeleteList("300102", "DragonFly", "11:22:33:44:55:66,0,on");  
//	i = uciCommitModule("300102");
//	strcpy(Test, "b4a.300102.DragonFly");
//	Liste = uciget_list(&Test[0]);
	
	//	Liste =  uciGetListe("module");
	//	i =  uciGetModule_String("AirSensor2", "bme280", Test);
	//	i = uciAddOption("AirSensor2", "bme280", "on");
	//	i =  uciGetModule_String("AirSensor2", "bme280", Test);
	//	Liste =  uciGetModule_List("AirSensor2", "ds18b20");
		//	if (!uciModuleExiste("300102"))
		//		uciAddModule("300102", "Toto");
			//i = uciCommitModule("300102");
	//		i = uciGetModule_String("AirSensor2", "mq2", Test);
	//AfficheListUCI(Liste);
	//Liste = EffaceListUCI(Liste);    

}