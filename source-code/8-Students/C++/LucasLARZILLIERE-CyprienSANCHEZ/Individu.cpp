#include "Individu.h"

char Individu::getStatut()
{
    return statut;
}

void Individu::setStatut(char s)
{
    statut = s;
} 

int Individu::getX()
{
    return x;
} 
void Individu::setX(int v)
{
    x = v;
}
    
int Individu::getY()
{
    return y;
} 
void Individu::setY(int v)
{
    y = v;
} 

char Individu::MajStatut()
{
    tempsStatut++;
    if (statut == 'E')
    {
        if (tempsStatut > dE)
        {
            statut = 'I';
            tempsStatut = 0;
        } 
    }
    if (statut == 'I')
    {
        if (tempsStatut > dI)
        {
            statut = 'R';
            tempsStatut = 0;
        } 
    } 
    if (statut == 'R')
    {
        if (tempsStatut > dR)
        {
            statut = 'S';
            tempsStatut = 0;
        } 
    }
    return statut;
} 

Individu::Individu(mt19937& mt)
{
    AleaPerso a = AleaPerso();
    statut = 'S';
    tempsStatut = 0;
    dE = a.NegExp(3, mt);
    dI = a.NegExp(7, mt);
    dR = a.NegExp(365, mt);
}