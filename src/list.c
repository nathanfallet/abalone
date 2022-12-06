#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/****************************************************************************
 * Opérations
 ****************************************************************************/

List *list_init() {
	/* Crée et initialise une nouvelle liste */
	List *l = malloc(sizeof(List));
	l->n = 0;
	l->erreur = LIST_OK;
	l->tete = malloc(sizeof(ListCel));
	l->tete->pdt = NULL;
	l->queue = malloc(sizeof(ListCel));
	l->queue->pdt = l->tete;
	l->queue->svt = l->queue;
	l->tete->svt = l->queue;
	return (l);
}

List *list_insere(void *e, int p, List *l) {
	/* Insère l'élément e à la position p */
	ListCel *crt, *cel;
	int i;
	if (p < 1 || p > l->n + 1)
	{
		l->erreur = LIST_LIMITE;
	}
	else
	{
		cel = malloc(sizeof(ListCel));
		if (cel == NULL)
		{
			l->erreur = LIST_DEBORDE;
		}
		else
		{
			l->erreur = LIST_OK;
			for (crt = l->tete, i = 0; i < p; crt = crt->svt, i++)
				;
			cel->val = e;
			cel->svt = crt;
			cel->pdt = crt->pdt;
			crt->pdt->svt = cel;
			crt->pdt = cel;
			l->n++;
		}
	}
	return (l);
}

void *list_accede(int p, List *l) {
	/* Renvoie l'élément e à la position p */
	int i;
	ListCel *cel;
	if (l->n == 0)
	{
		l->erreur = LIST_VIDE;
		return (LIST_ELT_INVALIDE);
	}
	else
	{
		if (p < 1 || p > l->n)
		{
			l->erreur = LIST_LIMITE;
			return (LIST_ELT_INVALIDE);
		}
		else
		{
			l->erreur = LIST_OK;
			for (i = 0, cel = l->tete; i < p; i++, cel = cel->svt)
				;
			return (cel->val);
		}
	}
}

ListCel *list_adresse(int p, List *l) {
	/* Renvoie l'adresse de l'élément à la position p */
	int i;
	ListCel *cel;
	if (l->n == 0)
	{
		l->erreur = LIST_VIDE;
		return (LIST_ADR_INVALIDE);
	}
	else
	{
		if (p < 1 || p > l->n)
		{
			l->erreur = LIST_LIMITE;
			return (LIST_ADR_INVALIDE);
		}
		else
		{
			l->erreur = LIST_OK;
			for (i = 0, cel = l->tete; i < p; i++, cel = cel->svt)
				;
			return (cel);
		}
	}
}

void *list_contenu(ListCel *cel, List *l) {
	/* Renvoie le contenu val à l'adresse e */
	return (cel->val);
}

ListCel *list_pdt(ListCel *a, List *l) {
	/* Renvoie l'adresse de l'élément précédent */
	if (a->pdt == l->tete)
	{
		l->erreur = LIST_LIMITE;
		return (LIST_ADR_INVALIDE);
	}
	else
	{
		l->erreur = LIST_OK;
		return (a->pdt);
	}
}

List *list_supprime(int p, List *l) {
	/* Supprime l'élément de la position p */

	ListCel *cel;
	int i;
	if (p < 1 || p > l->n + 1)
	{
		l->erreur = LIST_LIMITE;
	}
	else
	{
		l->erreur = LIST_OK;
		for (cel = l->tete, i = 0; i < p; cel = cel->svt, i++)
			;
		cel->pdt->svt = cel->svt;
		cel->svt->pdt = cel->pdt;
		free(cel);
		l->n--;
	}
	return (l);
}

ListCel *list_svt(ListCel *a, List *l) {
	/* Renvoie l'adresse de l'élément suivant */
	if (a->svt == l->queue)
	{
		l->erreur = LIST_LIMITE;
		return (LIST_ADR_INVALIDE);
	}
	else
	{
		l->erreur = LIST_OK;
		return (a->svt);
	}
}

int list_taille(List *l) {
	/* Renvoie la taille de la liste */
	return (l->n);
}

/****************************************************************************
 * Extensions
 ****************************************************************************/

List *list_dup(List *l) {
	List *ld = list_init();
	ListCel *cel;
	int i;
	for (cel = l->queue->pdt, i = 0; i < l->n; i++, cel = cel->pdt)
		list_insere(cel->val, 1, ld);
	return (ld);
}

static void swap(ListCel *c1, ListCel *c2) {
	/*
	 * Échange les contenus (void *val) des deux cellules
	 */
	void *v = c1->val;
	c1->val = c2->val;
	c2->val = v;
}

/* Tri rapide */

static void *partition(ListCel *deb, ListCel *fin, void *piv, int (*cmp)()) {
	do
	{
		swap(deb, fin);
		while (cmp(deb->val, piv) < 0)
			deb = deb->svt;
		while (cmp(fin->val, piv) >= 0)
			fin = fin->pdt;
	} while (deb->pdt != fin);
	return deb;
}

static void *pivot(ListCel *deb, ListCel *fin, int (*cmp)()) {
	ListCel *crt;
	for (crt = deb->svt; crt != fin->svt; crt = crt->svt)
	{
		if (cmp(deb->val, crt->val) > 0)
			return deb->val;
		if (cmp(deb->val, crt->val) < 0)
			return crt->val;
	}
	return NULL;
}

static void quicksort(ListCel *deb, ListCel *fin, int (*cmp)()) {
	ListCel *part;
	void *piv = pivot(deb, fin, cmp);
	if (piv != NULL)
	{
		part = partition(deb, fin, piv, cmp);
		quicksort(deb, part->pdt, cmp);
		quicksort(part, fin, cmp);
	}
}

List *list_trirapide(List *l, int (*cmp)()) {
	if (l->n < 2)
		return l;
	quicksort(l->tete->svt, l->queue->pdt, cmp);
	return l;
}
