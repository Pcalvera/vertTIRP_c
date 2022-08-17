
#include "Chrono.h"
Chrono::Chrono(){
    t = map<string,double>();
    taux = map<string,chrono::time_point<chrono::high_resolution_clock>>();
}
void Chrono::start(string name){
    taux[name] = chrono::high_resolution_clock::now();
}
void Chrono::stop(string name){
    auto timeNow = chrono::high_resolution_clock::now();
    auto it = t.find(name);
    if ( it == t.end() )
        it = t.insert(make_pair(name,0)).first;
    it->second += chrono::duration_cast<chrono::nanoseconds>(timeNow - taux.at(name) ).count()*1e-9;
}
void Chrono::print()const{
    for ( auto &it : t)
        cout<<"TEMPS "<<it.first<<": "<<std::setprecision(9)<<it.second<<endl;
}