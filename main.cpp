#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
class Baza{
public:
    virtual float Calcul() = 0;
    virtual ~Baza() = default;
};
class GenerareID{
private:
    static int Nr;
public:
    static int Generare(){
        return Nr++;
    }
    ~GenerareID() = default;
};
class Ingredient{
private:
    std::string Denumire;
    float Pret;
public:
    Ingredient(){
        Pret = 0;
    }
    Ingredient(std::string Nume_, float Pret_){
        Denumire = Nume_;
        Pret = Pret_;
    }
    void SetPret(float x){
        this->Pret = x;
    }
    float GetPret(){
        return Pret;
    }
    Ingredient operator+(Ingredient &rhs){
        Ingredient x;
        x.Pret = rhs.Pret +Pret;
        return x;
    }
    void Citire(std::istream &is){
        std::cout<<"Ingredientul este: ";
        is>>this->Denumire;
        std::cout<<"\nPretul dorit: ";
        is>>this->Pret;
    }
    friend std::ostream &operator<<(std::ostream &os, const Ingredient &ingr) {
        os <<"Ingredient: "<<ingr.Denumire<<" Pret: "<<ingr.Pret<<'\n';
        return os;
    }
    friend std::istream &operator>>(std::istream &is,Ingredient &ingr){
       ingr.Citire(is);
       return is;
    }
};
int GenerareID::Nr = 0;

class Pizza: public Baza{
private:
    std::string nume;
    std::vector<Ingredient> Ingr;
    bool Vegetariana;
public:
    void SetNume(std::string s){
        nume = s;
    }
    Pizza(){
        nume = "Blat";
        Vegetariana = false;
        Ingredient a1("Faina",3),a2("Apa",0.5),a3("Drojdie",1),a4("Sare",0.1);
        Ingr.push_back(a1);
        Ingr.push_back(a2);
        Ingr.push_back(a3);
        Ingr.push_back(a4);
    }
    Pizza(std::string nume_, std::vector<Ingredient> v){
        nume = nume_;
        Ingr = v;
        Vegetariana = false;
        Ingredient a1("Faina",3),a2("Apa",0.5),a3("Drojdie",1),a4("Sare",0.1);
        Ingr.push_back(a1);
        Ingr.push_back(a2);
        Ingr.push_back(a3);
        Ingr.push_back(a4);
    }
    float Calcul() override{
        Ingredient x;
        for(int i = 0; i < Ingr.size(); i++){
            x = x + Ingr[i];
        }
        return x.GetPret();
    }
    void Print(std::ostream &os){
        os<<"Pizza "<<nume<<" costa "<<this->Calcul()<<" lei\n";
    }
    friend std::ostream &operator<<(std::ostream &os, Pizza &Piz){
        Piz.Print(os);
        return os;
    }
    void ListareIngrediente(){
        for(int i = 0; i < Ingr.size(); i++){
            std::cout<<Ingr[i];
        }
    }
    void InserareIngredient(Ingredient x){
        Ingr.push_back(x);
    }
};
template<typename T>
class Meniu{
private:
    std::vector<Pizza> Lista;
public:
    Meniu(){}
    void Inserare(Pizza &x){
        Lista.push_back(x);
    }
    void Print(){
        for(int i = 0; i < Lista.size(); i++){
            std::cout<<i+1<<'.'<<Lista[i];
        }
        std::cout<<"\n\n";
    }
    void PrintCuIngr(){
        for(int i = 0; i < Lista.size(); i++){
            std::cout<<i+1<<'.'<<Lista[i];
            Lista[i].ListareIngrediente();
            std::cout<<"\n\n";
        }
    }
};
int main() {

    Pizza y;
    Ingredient a1("Masline", 0.3), a2("Salam", 7), a3("Ciuperci", 5);
    Pizza p("Gustoasa",{a1,a2,a3});
    Meniu<Pizza> Menu;
    Menu.Inserare(y);
    Menu.Inserare(p);
    Menu.Print();
    Menu.PrintCuIngr();
    return 0;
}
