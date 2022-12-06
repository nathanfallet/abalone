#ifndef LIST_H_
#define LIST_H_

#define LIST_ELT_INVALIDE NULL
#define LIST_POS_INVALIDE -1
#define LIST_ADR_INVALIDE NULL
#define LIST_MAX_CHAINE 4096

typedef enum { LIST_OK, LIST_DEBORDE, LIST_LIMITE, LIST_VIDE } ListError;

typedef struct list_cel_t {
	void *val;
	struct list_cel_t *svt;
	struct list_cel_t *pdt;
} ListCel;

typedef struct list_t {
	ListCel *tete;
	ListCel *queue;
	int n;
	ListError erreur;
} List;

/* Opérations */

void *list_accede(int p, List *l);
ListCel *list_adresse(int p, List *l);
void *list_contenu(ListCel *e,List *l);
List *list_init();
List *list_insere(void *e, int p, List *l);
ListCel *list_pdt(ListCel *e, List *l);
List *list_supprime(int p, List *l);
ListCel *list_svt(ListCel *e, List *l);
int list_taille(List *l);

/* Extension(s) */

List *list_dup(List *l);
List *list_trirapide(List *l, int (*cmp)(void *v1, void *v2));

#endif